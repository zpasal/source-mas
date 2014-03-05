/*

	pass2.cpp

	Second pass compilation

	THIS IS MAIN FILE OF WHOLE PROGRAM. PASS 2 COMPILATION
	DOES ALL DIRECTIVES, ALL ASSIGN-EXPRESSIONS AND GENERATE
	CODE FOR INSTRUCTIONS

     Copyright (C) 2004 Pasalic Zaharije (s4063m@pmf.unsa.ba)
     
     This program is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation; either version 2 of the License, or
     any later version.
     
     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.
     
     You should have received a copy of the GNU General Public License
     along with this program; if not, write to the Free Software
     Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.


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
#include "pass1.h"
#include "mas.h"
#include "config.h"
#include "pass2.h"

// list of numbers: 2^i - 1 for bit AND when
// calculate size of number in bits
int negs[16] = {
	0x2-1,0x4-1,0x8-1,0x10-1,0x20-1,0x40-1,
	0x80-1,0x100-1,0x200-1,0x400-1,0x800-1,
	0x1000-1,0x2000-1,0x4000-1,
	0x8000-1,0x10000-1
};

/*
	MOST CONFUSING PART!!!!! :(

_new_macro_line - have whole macro, used with _get_macro_line
macro_params	- 10 params passed to macro
macro_sparams - 10 params (strings) passed to macro
param_count   - number of passed params to macro
*/
char *_new_macro_line;
int macro_params[10];    
char *macro_sparams[10] = {0,0,0,0,0,0,0,0,0,0}; // string parametri
int param_count=0;

// flags: 'we-are-in-macro' and 'we-are-in-rep'
bool in_macro = false;
bool in_rep = false;

// array of instructions that is generated
unsigned short *emit_buffer;
// index in 'emit_buffer;
int emit_index = 0;

// format of emit buffer:
//	[0] - opcode
//	[1] - offset
void init_emit_buffer()
{
	emit_buffer = new unsigned short[max_mem*4];
	for(int i=0; i<max_mem*4; i++)
		emit_buffer[i] = 0;
}

void emit(unsigned short opcode)
{
	emit_buffer[emit_index*4] = opcode;
	emit_buffer[emit_index*4+1] = current_offset;
	emit_buffer[emit_index*4+2] = current_line;
	emit_buffer[emit_index*4+3] = in_macro;
	emit_index++;
}

void kill_emit_buffer()
{
	delete emit_buffer;
}


/* do .define

	.define ident ['=' expression]

*/
void do_define()
{
char const_name[MAXTOKENLEN+1];
t_label *lab;
int value = 1;
	get_token();
	if (c_sym != si_ident) {
		error(MSG_ERROR, "identifer expected in .define, got %s", tok2str());
		return;
	}
	strcpy(const_name, token_string);
	lab = find_label(const_name);
	if (lab != 0) {
		error(MSG_ERROR, "identifier %s already defined", const_name);
		return;
	}
	get_token();
	if (c_sym == si_assign) { // ako stavimo "= expression"
		get_token();
		value = expression();
	}
	Labele.Dodaj(t_label(const_name, L_CONST, value, current_line));
	if (c_sym != si_newline)
		error(MSG_ERROR, "unexpected %s", tok2str());
}

void do_asm();

/*
	UGLY CODE ....

	.if expression
		; some code
	[.else
		; some code
	]
	.endif
*/
void do_if(bool enter_if)
{
int ret;
	get_token(); // skinemo .if
	if (enter_if)
		ret = expression();
	else ret = 0;
	if (ret == 0) 
		enter_if = false;
	while(1) {
		if (!ret) no_error = true;
		get_line();
		get_token();
		if (c_sym == si_eof) {
			no_error = false;
			error(MSG_ERROR, "unexpected end-of-file in .if");
			return;
		}
		if (c_sym == si_if) {
			do_if(enter_if);
			get_line();
			get_token();
		}
		if (c_sym == si_endif) break;
		if (c_sym == si_else) break;
		if (ret)
			do_asm();
	}
	no_error = false;
	// ako je else
	if (c_sym == si_else) {
		if (ret) no_error = true;
		get_token();
		while(1) {
			get_line();
			get_token();
			if (c_sym == si_eof) {
				no_error = false;
				error(MSG_ERROR, "unexpected end-of-file in .else");
				return;
			}
			if (c_sym == si_if) {
				do_if(!enter_if);
				get_line();
				get_token();
			}
			if (c_sym == si_endif) break;
			if (!ret) 
				do_asm();
		}
	}
	no_error = false;
}

/*
	Pars assing-expression

	ident '=' expression

*/
void do_assign(char *label_name)
{
t_label *lab;
	get_token();
	// provjerimo dali postoji labela-ident
	lab = find_label(label_name);
	if (lab == 0)  // nema, dodaj i uzmi pointer
		lab = &(Labele.Dodaj(t_label(label_name, L_IDENT, 0, current_line)))->Vrijednost;
	else if (lab->type == L_CONST || lab->type == L_MACRO) {
		error(MSG_ERROR, "changing permission of %s", label_name);
		return;
	}
	lab->val = expression();
	if (c_sym != si_newline) 
		error(MSG_ERROR, "unexpected %s", tok2str());
}


/*
	Macro definition
	
		.macro ident [expression]
			; some core
		.endm

*/
void do_macro()
{
char macro_name[MAXTOKENLEN];
int params = 0;
std::string s = "";
t_label *lab;
	get_token();
	if (c_sym != si_ident) {
		error(MSG_ERROR, "macro name expected , got %s", tok2str());
		return;
	}
	strcpy(macro_name, token_string);
	get_token();
	if (c_sym != si_newline) {
		params = expression();
		if (params == 0)
			params = -1;
	}
	if(find_label(macro_name) != 0) 
		error(MSG_WARN, "redeclaration of macro '%s'", macro_name);
	lab = &(Labele.Dodaj(t_label(macro_name, L_MACRO, params, current_line)))->Vrijednost;
	while(1) {
		get_line();
		get_token();
		if (c_sym == si_eof) {
			error(MSG_ERROR, "unexpected end-of-file in .macro");
			return;
		}
		if (c_sym == si_endm) break;
		s += _line;
	}
	lab->macro_line = new char[s.length() + 1];
	strcpy(lab->macro_line, s.c_str());
}

/*
	Function that expand parametars from '_line'
*/

void expand_param_line()
{
char *ptr, *lptr = _line;
std::string s = "";
char val[MAXTOKENLEN+1];
  if (!in_rep) {
	while((ptr = strchr(lptr, '#')) != 0) { // dok god ima parametara
		*ptr++ = 0;
		s += lptr;
		if (!isdigit(*ptr)) {
			error(MSG_ERROR, "parametar must be one digit number");
			return;
		}
		if (*ptr - '0' >= param_count) {
			error(MSG_ERROR, "param #%c out of range", *ptr);
			return;
		}
		if (macro_sparams[*ptr-'0'] == 0) {
			sprintf(val, "%i", macro_params[*ptr - '0']);
			s += val;
		}
		else s += macro_sparams[*ptr - '0'];
		lptr = ptr+1;
	}
	s += lptr;
	strcpy(_line, s.c_str());
  }
}

// another function that simulate reading from macro-line as read from
// file
void macro_get_line()
{
char *ptr;
	ptr = strchr(_new_macro_line, '\n');
	if (ptr != 0) {
		*ptr = 0;
		strcpy(_line, _new_macro_line);
		strcat(_line, "\n");
		lineptr = _line;
		_new_macro_line = ptr+1;
		current_line++;
		mass_line_count++;
		expand_param_line();	
	} else lineptr = 0;
}


/*
	THIS IS THE MOST UGLYEST CODE THAT I WRITE IN WHOLE MY LIFE!
	IT EXPAND MACRO ...
*/
void macro_expand(t_label *macro)
{
int old_current_line;		  // tekuca linija
char old_line[MAXLINELEN+1];	  // linija teksta
char old_module[128];		  // ime modula
char *old_lineptr;	  		  // tekuci karakter za parsiranje
void (*old_get_line)();		  // funkcija za uzimanje novog reda
char *old_macro_line;		  // tekuci pointer ako je makro u makrou
int old_macro_params[10];		  // parametri od makroa
char *old_macro_sparams[10];	  //  ---- " ----	
int old_param_count;
char *_nml_tmp;
void do_pass2();

       strcpy(old_module, module_file);
       strcat(module_file, ">>");
       strcat(module_file, macro->name); // zbog gresaka da se zna u kojem makrou je greska
	strcpy(old_line, _line);
	old_current_line = current_line;
	old_get_line = get_line;
	old_macro_line = _new_macro_line;
	old_lineptr = lineptr;
	// if we use .rep in macro - all params are sam
	memcpy(old_macro_params, macro_params, sizeof(int)*10);
	old_param_count = param_count;
	for(int i=0; i<10; i++) {
		if (macro_sparams[i] != 0) {
			old_macro_sparams[i] = new char[strlen(macro_sparams[i])+1];
			strcpy(old_macro_sparams[i], macro_sparams[i]);
		} else old_macro_sparams[i] = 0;
	}
	
       // prebacimo novi ulaz
       _nml_tmp = _new_macro_line = new char[strlen(macro->macro_line)+1];
	strcpy(_new_macro_line, macro->macro_line);
       get_line = macro_get_line;
	current_line=0;
       do_pass2();
       // vratimo sve na staro da nastavimo sa parsiranjem
       strcpy(module_file, old_module);
	strcpy(_line, old_line);
       current_line = old_current_line;
	get_line = old_get_line;
	delete _nml_tmp;
	_new_macro_line = old_macro_line;
       lineptr = old_lineptr;
	// if we not in .rep no params change
	memcpy(macro_params, old_macro_params, sizeof(int)*10);
	param_count = old_param_count;
	for(int i=0; i<10; i++) {
		delete macro_sparams[i];
		if (old_macro_sparams[i] != 0) {
			macro_sparams[i] = new char[strlen(old_macro_sparams[i])+1];
			strcpy(macro_sparams[i], old_macro_sparams[i]);
		} else macro_sparams[i] = 0;
	}
}

void do_expand_macro(char *macro_name)
{
t_label *macro;
int param_no = 0;
int param_val;
bool old_in_macro;
	macro = find_label(macro_name);
	if (macro == 0) {
		error(MSG_ERROR, "undefined macro %s", macro_name);
		return;
	}
	if (macro->type != L_MACRO) {
		error(MSG_ERROR, "can not expand non macro %s", macro_name);
		return;
	}
	if (c_sym != si_lpar) {
		error(MSG_ERROR, "calling macro %s without (", macro_name);
		return;
	}
	get_token();
	while(c_sym != si_rpar) {
		if (param_no >= 10) {
			error(MSG_ERROR, "maximum of 10 parametars");
			return;
		}
		if (c_sym == si_less) {
			get_token();
			if (c_sym != si_ident) {
				error(MSG_ERROR, "identifer expected, got %s", tok2str());
				return;
			}
			macro_sparams[param_no] = new char[strlen(token_string)+1];
			strcpy(macro_sparams[param_no++], token_string);
			get_token();
			if (c_sym != si_grt) {
				error(MSG_ERROR, "non-terminated param");
				return;
			}
			get_token();
		} 
		else {
			param_val = expression();
			macro_params[param_no++] = param_val;
		}
		if (c_sym == si_comma)
			get_token();
		else if (c_sym == si_rpar) break;
		else {
			error(MSG_ERROR, "expected ',', got %s", tok2str());
			return;
		}
		if (c_sym == si_newline) {
			error(MSG_ERROR, "expected ), got %s", tok2str());
			return;
		}
	}
	if (param_no < macro->val) {
		error(MSG_ERROR, "macro %s expected %i param(s)", macro_name, macro->val);
		return;
	}
	if (param_no != macro->val && macro->val != -1) 
		error(MSG_WARN, "to few parametars in macro %s", macro_name);
	param_count = param_no;
	old_in_macro = in_macro;
	in_macro = true;
	macro_expand(macro);
	in_macro = old_in_macro;
}

/*
	Rotation of params .left and .right
*/
void do_param_left()
{
int first;
char *sfirst;
	get_token();
	first = macro_params[0];
	sfirst = macro_sparams[0];
	for (int i=1; i<param_count; i++)  {
		macro_params[i-1] = macro_params[i];
		macro_sparams[i-1] = macro_sparams[i];
	}
	macro_params[param_count-1] = first;
	macro_sparams[param_count-1] = sfirst;
	if (c_sym != si_newline)
		error(MSG_ERROR, "unexpected %s", tok2str());
}

// rotate params left by one
void do_param_right()
{
int first;
char *sfirst;
       // 1 2 3 p
       // 3 1 2 p
	get_token();
	first = macro_params[param_count-1];
	sfirst = macro_sparams[param_count-1];
	for (int i=param_count-1; i>=1; i--)  {
		macro_params[i] = macro_params[i-1];
		macro_sparams[i-1] = macro_sparams[i-1];
	}
	macro_params[0] = first;
	macro_sparams[0] = sfirst;
	if (c_sym != si_newline)
		error(MSG_ERROR, "unexpected %s", tok2str());
}

/*
	.rep directive

	.rep expression
		; some code
	.endrep
*/
void do_rep()
{
int count = 0;
std::string s = "";
char *old_macro_line;
void (*old_get_line)();
int old_current_line;
char *old_lineptr;
void do_pass2();
bool old_in_rep;
char *nml_tmp;
int in_rep_count = 1;
	get_token();
	count = expression();
	old_in_rep = in_rep;
	in_rep = true;
	get_line();
	get_token();
	// cut all code enclosed with .rep and .endrep
	while(1) {
		if (c_sym == si_rep)
			in_rep_count++;
		if (c_sym == si_endrep) {
			if (!--in_rep_count)
				break;
		}
		s += _line;
		get_line();
		get_token();
	}
	while(count)	{
		in_rep = false;
		old_lineptr = lineptr;
		old_macro_line = _new_macro_line;
		nml_tmp = _new_macro_line = new char[s.length()+1];
		strcpy(_new_macro_line, s.c_str());
		old_get_line = get_line;
		get_line = macro_get_line;
		old_current_line = current_line;
	
		current_line = 0;
		do_pass2();
	
		lineptr = old_lineptr;
		delete nml_tmp;
		_new_macro_line = old_macro_line;
		get_line = old_get_line;
		current_line = old_current_line;
		count--;
	}
}

void do_usermsg(int msg)
{
char *ptr;
	ptr = strchr(lineptr, '\n');
	if (ptr)
		*ptr = 0;
	while(isspace(*lineptr))
		lineptr++;
	error(msg, "%s", lineptr);
}


int size_of_bits(int num)
{
int count = 0;
	while(num) {
		count++;
		num >>= 1;
	}
return count;
}


bool limit(int value, int bits)
{
	if (value < 0)
		value &= negs[bits-1];
	return size_of_bits(value) <= bits;
}

void gen(int op1, int op2, int op3, int vop1, int vop2, int vop3, int inst)
{
unsigned short opcode = instructions[inst].opcode;
int p1, p2, p3;
int m1, m2, m3;
char *msg1, *msg2, *msg3;
	p1 = instructions[inst].place1;
	p2 = instructions[inst].place2;
	p3 = instructions[inst].place3;
	m1 = instructions[inst].msg_type1;
	m2 = instructions[inst].msg_type2;
	m3 = instructions[inst].msg_type3;
	msg1 = instructions[inst].msg1;
	msg2 = instructions[inst].msg2;
	msg3 = instructions[inst].msg2;
	if (op1) { // ima parametara:
		if (!limit(vop1, op1)) {
			if (msg1 == 0)
				error(MSG_WARN, "expected %ibit(s) num, truncating from 0x%X to 0x%X", 
					   op1, vop1, vop1 & negs[op1-1]);
			else error(m1, msg1);
			vop1 &= negs[op1-1];
		}
		opcode = opcode | (vop1 << p1);
	}
	if (op2) { // ima parametara:
		if (!limit(vop2, op2)) {
			if (msg2 == 0)
				error(MSG_WARN, "expected %ibit(s) num, truncating from 0x%X to 0x%X", 
					   op2, vop2, vop2 & negs[op2-1]);
			else error(m2, msg2);
			vop2 &= negs[op2-1];
		}
		// smjestimo na place1
		opcode = opcode | (vop2 << p2);
	}
	if (op3) { // ima parametara:
		if (!limit(vop3, op3)) {
			if (msg3 == 0)
				error(MSG_WARN, "expected %ibit(s) num, truncating from 0x%X to 0x%X", 
					   op3, vop3, vop3 & negs[op3-1]);
			else error(m3, msg3);
			vop3 &= negs[op3-1];
		}
		// smjestimo na place1
		opcode = opcode | (vop3 << p3);
	}
	emit(opcode);
}

void do_instruction()
{
int inst = c_sym;
int op1, op2, op3;
int vop1=0, vop2=0, vop3=0;
int err = error_number;
	if (current_offset >= max_mem) {
		error(MSG_ERROR, "memory size to long for specified device");
		return;
	}
	op1 = instructions[inst].op1;
	op2 = instructions[inst].op2;
	op3 = instructions[inst].op3;
	get_token();
	if (op1 != OPER_NONE) {
		vop1 = expression();
		if (op2 != OPER_NONE) {
			if (c_sym != si_comma) {
				error(MSG_ERROR, "second operand expected");
				return;
			}
			get_token();
			vop2 = expression();
			if (op3 != OPER_NONE) {
				if (c_sym != si_comma) {
					error(MSG_ERROR, "third operand expected");
					return;
				}
				get_token();
				vop3 = expression();
			}
		}
	}
	if (err == error_number)
		gen(op1, op2, op3, vop1, vop2, vop3, inst);
	if (c_sym != si_newline)
		error(MSG_ERROR, "unexpected %s", tok2str());
}

void do_asm()
{
char label_name[MAXTOKENLEN+1];
	switch(c_sym) {
		case si_ident:  strcpy(label_name, token_string);
				  get_token();
				  if (c_sym == si_assign) 
					do_assign(label_name);
				  else do_expand_macro(label_name);
				  break;
		case si_define: do_define(); 
				  break;
		case si_if: 	  do_if(true); 
				  break;
		case si_include: do_include(); 
				   break;
		case si_macro:  do_macro(); 
				  break;
		case si_org: 	  do_org(false);
				  break;
		case si_rep: 	  do_rep(); 
				  break;
		case si_left:   do_param_left(); 
				  break;
		case si_right:  do_param_right(); 
				  break;
		case si_error:  do_usermsg(MSG_ERROR); 
				  break;
		case si_warn:   do_usermsg(MSG_WARN); 
				  break;
		case si_newline: break;
		default:  	if (IS_INSTRUCTION()) {
					do_instruction();
					current_offset++;
				}
				else error(MSG_ERROR, "unexpected %s", tok2str());
				break;
	}
	
}

void do_pass2()
{
	get_line();
	get_token();
	while(c_sym != si_eof) {
		do_asm();
		get_line();
		get_token();
	}
}
