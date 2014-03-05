/*
	config.cpp

	Parser for device files scripts- .dfs

	.dfs files describe particular device. This scripts are
	adopted for PICxxx microcontroller families, however
	it can be used for another devices, too.

	.dfs files have two parts: header and instructions
	descriptors.

	Format of header is:

		device = ident
		core = number
		memory = number
		inst = number

	It must be in this ortder!

	'device' is name of device. Name of device can be used
	in assembler source. Name is prefxed with __:

		device = p16c84	; makro - __P16c84

	'core' is number of bits in opcode field. 

	'memory' is max memory for code

	'inst' is number of instructions

	
	After header goes instructions descriptors:

	name = (
		'opcode' = number
		'param' = ...
		'param' = ...
	)

     where opcode is opcode of instruction ('name'). After opcode can goes one or two
     descriptors for operand. Operand descriptor begins with 'param = ( describe )'

     In opcode-descriptor four names are used:
		size = number 	;  size of opernad in bits
		position =number 	; offset in bits where operand is placed in opcode (0-based)
		error = <any chars>	; issue error if operand is bigger than 'size'
		warning = <any chars>; issue warning if operand is bigger than 'size'



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

#include <cstdio>
#include <cstring>
#include <cctype>
#include "labels.h"
#include "parser.h"
#include "mas.h"
#include "config.h"

// extern variable : false - parser ca not recognize instructions
//		     : true - pareser recognize instructions
extern bool match_inst;

// directory for device files (have name config_dir, cos' first time i
// call it config files :)
char config_dir[128] = "device";

// description of all instructions
t_instruction *instructions = 0;
// number of instructions
int number_of_inst = 0;
// number of bits for opcode
int device_bits = 0;
// maximum memory for code
int max_mem = 0;
// name of device
char device_title[128];

// check if string is any legal instruction
int find_inst(char *str)
{
	for(int i=0; i<number_of_inst; i++)
		if (!strcmp(str, instructions[i].name))
			return i;
return si_ident;
}


void str_upper(char *str) {
	while(*str) {
		*str = toupper(*str);
		str++;
	}
}

void dump_config()
{
t_instruction *s = instructions;
int params;
	printf("\t\tDevice dump %s\n\n", device_title);
	printf("\t\tMax memory  = 0x%04X\n", max_mem);
	printf("\t\tOpcode size = %i\n", device_bits);
	printf("\t\tInstructions= %i\n\n", number_of_inst);
	printf("inst       opcd params   MSG1    MSG2    MSG3\n");
	printf("----------------------------------------------------------\n");
	for(int i=0; i<number_of_inst; i++, s++) {
		params = 0;
		if (instructions[i].op1) params++;
		if (instructions[i].op2) params++;
		if (instructions[i].op3) params++;
		printf("%-10s ", instructions[i].name);
		printf("%04X   ", instructions[i].opcode);
		printf("%i      ", params);
		if (instructions[i].msg_type1 == MSG_WARN)
			printf("WARNING ");
		else if (instructions[i].msg_type1 == MSG_ERROR)
			printf("ERROR   ");
		else   printf("        ");
		if (instructions[i].msg_type2 == MSG_WARN)
			printf("WARNING ");
		else if (instructions[i].msg_type2 == MSG_ERROR)
			printf("ERROR   ");
		if (instructions[i].msg_type3 == MSG_WARN)
			printf("WARNING ");
		else if (instructions[i].msg_type3 == MSG_ERROR)
			printf("ERROR   ");
		printf("\n");
	}
}

// just open device file. 'str' must be name of device, not name of file
// and define macro with name toupper("__%s", str)
bool open_config(char *str)
{
char buf[128];
	sprintf(buf, "__%s", str);
	str_upper(buf);
	Labele.Dodaj(t_label(buf, L_CONST, 1, 0));	
	sprintf(buf, "%s/%s.dev", config_dir, str);
	sprintf(module_file, "dev(%s)", str);
	indat = fopen(buf, "r");
	if (indat == 0) {
		error(MSG_FATAL, "can not open %s", buf);
		return false;
	}
	current_line = 0;
	return true;
}

void kill_config()
{
	for(int i=0; i<number_of_inst; i++) {
		delete instructions[i].name;
		delete instructions[i].msg1;
		delete instructions[i].msg2;
		delete instructions[i].msg3;
	}
	delete instructions;
}

// two instructions that check if token is any
// parser directive
int script_tok(char *str) {
	if (!strcmp(str, "opcode")) return OPCODE;
	else if (!strcmp(str, "size")) return SIZE;
	else if (!strcmp(str, "position")) return POSITION;
	else if (!strcmp(str, "warning")) return WARNING;
	else if (!strcmp(str, "error")) return ERROR;
	else if (!strcmp(str, "param")) return PARAM;
return 0;
}

int script_tok2(char *str) {
	if (!strcmp(str, "inst")) return INST;
	else if (!strcmp(str, "core")) return CORE;
	else if (!strcmp(str, "memory")) return MEMORY;
	else if (!strcmp(str, "device")) return DEVICE;
return 0;
}

// like get_token() except that read token
// if token is end-of-line read new line
// unlike get_token that stops after end-of-line
void get_scr_token()
{
	get_token();
	while(c_sym == si_newline) {
		get_line();
		get_token();
	}
}

// few functions accept_xxx for checking, reading and
// reporting errors
void accept(int sym, char *err) 
{
	if (c_sym == sym) 
		get_scr_token();
	else error(MSG_FATAL, err);
}

void accept_scr(int s, char *err)
{
int t;
	if (c_sym == si_ident) {
		t = script_tok(token_string);
		if (!t)
			error(MSG_FATAL, err);
		get_scr_token();
	}
	else error(MSG_FATAL, err);
}

void accept_scr2(int s, char *err)
{
int t;
	if (c_sym == si_ident) {
		t = script_tok2(token_string);
		if (!t)
			error(MSG_FATAL, err);
		get_scr_token();
	}
	else error(MSG_FATAL, err);
}


int accept_num(char *err)
{
int t=0;
	if (c_sym == si_number) {
		t = token_number;
		get_scr_token();
	}
	else error(MSG_FATAL, err);
	return t;
}

/*
	Pars param declaration:

	'param' '=' '(' 'size' = number  'position' = number
		[{'error', 'warning'} '=' '<' any-chars '>'] ')'
	
*/
void do_scr_param(int &size, int &pos, int &msgt, char *msg)
{
int t;
	accept(si_assign, "expected =");
	accept(si_lpar, "expected (");
	accept_scr(SIZE, "expected 'size' declaration");
	accept(si_assign, "expected =");
	size = accept_num("expected number of 'size'");
	accept_scr(POSITION, "expected position");
	accept(si_assign, "expected =");
	pos = accept_num("expected number for 'position'");
	if (c_sym == si_ident) {
		t = script_tok(token_string);
		if (t) {
			if (t == WARNING) {
				get_scr_token();
				msgt = MSG_WARN;
			}
			else if (t == ERROR) {
				get_scr_token();
				msgt = MSG_ERROR;
			}
			else msgt = 0;
			accept(si_assign, "expected =");
			accept(si_less, "expected <");
			while(*lineptr != '<') lineptr--;
			lineptr++;
			while(*lineptr != '>') {
				*msg++ = *lineptr++;
				if (*lineptr == 0)
					error(MSG_FATAL, "unterminated <");
			}
			c_sym = si_grt; // FLUSH BUFFER
			accept(si_grt, "");
			get_scr_token();
		}
	}
	accept(si_rpar, "expected )");
}

/*
	Pars instruction descriptor:

	ident '=' '(' 'opcode' '=' number [ instruction-descriptor ] ')'

	And puts descriptor in new 'instructions' array
*/
void do_new_inst(char *inst)
{
static int index = 0;
char msg1[128] = "";
char msg2[128] = "";
char msg3[128] = "";
int msg_type1 = MSG_NONE;
int msg_type2 = MSG_NONE;
int msg_type3 = MSG_NONE;
int opcode;
int op1=0, pos1;
int op2=0, pos2;
int op3=0, pos3;
	get_scr_token();
	accept(si_assign, "expected =");
	accept(si_lpar, "expected (");
	accept_scr(OPCODE, "expected 'opcode'");
	accept(si_assign, "expected =");
	opcode = accept_num("expected opcode number");
	if (c_sym == si_ident) {
		accept_scr(PARAM, "expected param declaration");
		do_scr_param(op1, pos1, msg_type1, msg1);
		if (c_sym == si_ident) {
			accept_scr(PARAM, "expected param declaration");
			do_scr_param(op2, pos2, msg_type2, msg2);
			if (c_sym == si_ident) {
				accept_scr(PARAM, "expected param declaration");
				do_scr_param(op3, pos3, msg_type3, msg3);
			}
		}
	}
	accept(si_rpar, "expected )");
	// ubacimo instrukciju
	if (index >= number_of_inst)
		error(MSG_FATAL, "too many instructions at instruction '%s'", inst);
	instructions[index].opcode = opcode;
	instructions[index].op1 = op1;
	instructions[index].op2 = op2;
	instructions[index].op3 = op3;
	instructions[index].place1 = pos1;
	instructions[index].place2 = pos2;
	instructions[index].place3 = pos3;
	instructions[index].name = new char[strlen(inst)+1];
	instructions[index].msg_type1 = msg_type1;
	instructions[index].msg_type2 = msg_type2;
	instructions[index].msg_type3 = msg_type3;
	if (msg1[0] != 0) {
		instructions[index].msg1 = new char[strlen(msg1)+1];
		strcpy(instructions[index].msg1, msg1);
	}
	if (msg2[0] != 0) {
		instructions[index].msg2 = new char[strlen(msg2)+1];
		strcpy(instructions[index].msg2, msg2);
	}
	if (msg3[0] != 0) {
		instructions[index].msg3 = new char[strlen(msg3)+1];
		strcpy(instructions[index].msg3, msg3);
	}
	instructions[index].name = new char[strlen(inst)+1];
	strcpy(instructions[index++].name, inst);
}

/*
	Pars header of device config file:

	'device' = ident 'core' = number 'memory' = number 'inst' = number
	IT MUST BE IN THIS ORDER!!!

	After that, allocate number of instructions and reset all descriptors
	to empty.
	
*/
void do_scr_header()
{
int t;
	accept_scr2(DEVICE, "expected 'device'");
	accept(si_assign, "expected =");
	if (c_sym == si_ident) {
		strcpy(device_title, token_string);
		get_scr_token();
	}
	accept_scr2(CORE, "expected 'core'");
	accept(si_assign, "expected =");
	device_bits = accept_num("expected number for 'core'");
	accept_scr2(MEMORY, "expected 'memory'");
	accept(si_assign, "expected =");
	max_mem = accept_num("expected number for 'memory'");
	accept_scr2(INST, "expected 'inst'");
	accept(si_assign, "expected '='");
	number_of_inst = accept_num("expected number for 'inst'");
	instructions = new t_instruction[number_of_inst];
	for(t = 0; t < number_of_inst; t++) {
		instructions[t].op1 = 0;
		instructions[t].op2 = 0;
		instructions[t].place1 = 0;
		instructions[t].place2 = 0;
		instructions[t].opcode = 0;
		instructions[t].msg1 = 0;
		instructions[t].msg_type1 = MSG_NONE;
		instructions[t].msg2 = 0;
		instructions[t].msg_type2 = MSG_NONE;
	}
}

// pars device config file
void pars_config()
{
char token[MAXTOKENLEN+1];
int t;
	match_inst = false;
	get_line();
	get_scr_token();
	do_scr_header();
	while(c_sym  == si_ident) {
		t = script_tok(token_string);
		if (t)
			error(MSG_FATAL, "syntax error exp");
		else {
			strcpy(token, token_string);
			do_new_inst(token);
		}
	}
	if (c_sym != si_eof)
		error(MSG_FATAL, "unexpected %s", tok2str());
	match_inst = true;
}

