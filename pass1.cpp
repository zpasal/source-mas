/*

	pass1.cpp

	First pass compilation

	Only get's labels, .org and .include directives, anithing else is
	error or copied to temp file for pass2 compilation.

     Copyright (C) 2004 Pasalic Zaharije (zaharije@klika.ba, s4063m@pmf.unsa.ba)

					Last Revision: 30.06.2004
 */
#define __ALATI_SVE
#define __ALATI_ISPIS

#include <cstring>
#include <cstdio>
#include <string>
#include "tools/Alati.hpp"
#include "labels.h"
#include "parser.h"
#include "config.h"
#include "mas.h"


// current offset in compilation
int current_offset;
// directory where to find include files
char include_dir[128] = "include";
bool config_ok = false;


/*
	Catch all labels and check is any instruction after label.
*/
void do_labelinst(char *label_name)
{
t_label *lab;
	get_token(); 
	// provjerimo dali postoji labela
	lab = find_label(label_name);
	if (lab != NULL) {
		error(MSG_ERROR, "label %s already declared", label_name);
		return;
	}
	Labele.Dodaj(t_label(label_name, L_LABEL, current_offset, current_line));
	// dali ide instrukcija poslije labele
	if (IS_INSTRUCTION()) { // ide instrukcija
		lineptr = strchr(_line, ':');
		lineptr++;
		fprintf(outdat, "%s", lineptr);
		current_offset++;
		return; // ne pregledaj kraj linije
	}
	else { // mora biti si_newline
		if (c_sym != si_newline) 
			error(MSG_ERROR, "unexpected %s", tok2str());
		fprintf(outdat, "\n");
	}
}


/*
	Including files. Function just remember were we are in current file,
	save positions and some data, than open new file (include file)
	to 'indat' data.

	Function just remember our current position, switch input to
	include file and call 'pass1'. After that, we restore input
	where we broked earlier.

 PREPRAVITI DA NUDE: INCLUDE "" I INCLUDE <>
*/

void do_pass2();

void do_include()
{
char old_module[128], tmp[128];
int old_offset=0, old_line=0;
char *cptr, endch;
static int inc_count = 0;

	get_token();
	if (c_sym == si_less) 
		endch = '>';
	else if (c_sym == si_quote)
		endch = '\"';
	else {
		error(MSG_ERROR, "bad .include syntax");
		return;
	}
	inc_count++;
	SKIP_SPACE(lineptr);
	// sacuvamo sve podatke gdje smo stali
	//**strcpy(old_module, module_file);
	sprintf(old_module, module_file);
	cptr = strchr(lineptr, endch);
	if (!cptr) {
		error(MSG_ERROR, "bad .include syntax");
		goto __restore;
	}
	else *cptr = 0;
	//strcpy(module_file, lineptr);
	if (endch == '>')
		sprintf(module_file, "%s/%s", include_dir, lineptr);
	else sprintf(module_file, lineptr);
	old_offset = ftell(indat);
	old_line = current_line;
	fclose(indat);
	// input je sada novi fajl
	current_line = 0;
	indat = fopen(module_file, "r");
	if (indat == 0) 
		error(MSG_FATAL, "can not open file %s", module_file); // here we go to exit(1);
	do_pass2();
	fclose(indat);
__restore:;
	// resetujemo input na stari fajl
	strcpy(module_file, old_module);
	inc_count--;
	if (inc_count == 0)
		sprintf(tmp, "%s.$$$", module_file);
	else strcpy(tmp, module_file);
	indat = fopen(tmp, "r");
	fseek(indat, old_offset, SEEK_SET);
	current_line = old_line;
}


// .org - new current_offset and outpfut same line
void do_org(bool out)
{
int val;
	get_token();
	val = expression();
	if (c_sym != si_newline)
		error(MSG_ERROR, "unexpected (%s)", tok2str());
	current_offset = val;
	if (out)
		fprintf(outdat, "%s", _line);
}

void do_device()
{
char device_name[MAXTOKENLEN+1];
char old_module[128];
long off;
int old_line, old_err;
   if (instructions != 0) {
	error(MSG_ERROR, "changing device at middle of code");
	return;
   }
   get_token();
   if (c_sym != si_ident) {
	error(MSG_ERROR, "expected device name");
	return;
   }
   strcpy(device_name, token_string);
   	// snimimo stanje compilacije
   old_line = current_line;
   old_err = error_number;
   off = ftell(indat);
   fclose(indat);
   strcpy(old_module, module_file);
   // pars device config file
   open_config(device_name);
   pars_config();
   fclose(indat);
	//return all
   current_line = old_line;
   error_number = old_err;
   strcpy(module_file, old_module);
   indat = fopen(module_file, "r");
   fseek(indat, off, SEEK_SET);
   config_ok = true;
   fprintf(outdat, "\n");
}


/*
			TWO MAIN FUNCTIONS THAT DO PASS1 COMPILING.

	Pars one line of code. This represents no-natural :) gramar of one line.
	Some parts can not be represented by BNF form becuase I screw !
	PASS1
		1. labeles
		2. .org directives
		3. .include directive
	OUT:
		1. .org directive
		2. anything else that is
			2.1. instruction
			2.2. directive
*/

void skip_to(int start, int end, char *who) {
int count = 1;
	while(1) {
		fprintf(outdat, "%s", _line);
		get_line();
		get_token();
		if (c_sym == start)
			count++;
		if (c_sym == end) {
			if (!--count)
				break;
		}
		if (c_sym == si_eof) {
			error(MSG_ERROR, "unexpected end-of-file caused form %s", who);
			return;
		}
	}
	fprintf(outdat, "%s", _line);
}


void do_assignlabel()
{
char label_name[MAXTOKENLEN+1];
static bool do_something = false;
	if (c_sym == si_newline) {
		fprintf(outdat, "\n");
		return;
	}
	if (do_something && !config_ok) {
		error(MSG_FATAL, "select device first");
	}
	if (c_sym == si_ident) { // label ,assign or macro
		strcpy(label_name, token_string);
		get_token();
		if (c_sym == si_collon)
			do_labelinst(label_name);
		else if (c_sym == si_assign) { // prebacimo za PASS2
				fprintf(outdat, "%s", _line);
		}
		else {	// macro call
			if (c_sym == si_lpar)
				fprintf(outdat, "%s", _line);
			else error(MSG_ERROR, "unexpected %s", tok2str());
		}
	}
	else if (IS_INSTRUCTION()) { // instruction - copy to output
		fprintf(outdat, "%s", _line);
		current_offset++;
	}
	else if (c_sym == si_define)  { 
		fprintf(outdat, "%s", _line);
	}
	else if (c_sym == si_if)      skip_to(si_if, si_endif, ".if");
	else if (c_sym == si_include) fprintf(outdat, "%s", _line);
	else if (c_sym == si_macro)   skip_to(si_macro, si_endm, ".macro");
	else if (c_sym == si_org)	  do_org(true);
	else if (c_sym == si_rep)	  skip_to(si_rep, si_endrep, ".rep");
	else if (c_sym == si_error)   fprintf(outdat, "%s", _line);
	else if (c_sym == si_warn)    fprintf(outdat, "%s", _line);
	else if (c_sym == si_device)  do_device();
	else error(MSG_ERROR, "unexpected %s", tok2str());
	do_something = true;
}

void do_pass1()
{
	get_line();
	get_token();
	while(c_sym != si_eof) {
		do_assignlabel();
		get_line();
		get_token();
	}
}

