/*
     parser.cpp

     Main rutines for parsing expression's:

	expression := clan1 [ {>,>=,<,<=,==,!=} clan1]

	clan1 := clan2 [ {&,|,^,<<,>>,.ror,.rol} clan2]

	clan2 := clan3 [ {*,/,%} clan3]

	clan3 := faktor [ {+,-} faktor]

	faktor := 	ident
			number
			- faktor
			+ faktor
			! faktor
			~ faktor
			( expression )
			{.lo8, .hi8, .lo16, .hi16} faktor
			.argc
			.isdef
			.isndef
			$
			
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

#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <cctype>
#include "mas.h"
#include "labels.h"
#include "parser.h"
#include "config.h"

// list of directives (without . (dot))
char *directives[DIRECTIVES] = {
	"lo8", "hi8", "lo16", "hi16",
	"ror", "rol",
	"isdef", "isndef",
	
	"define", "if", "else", "endif",
	"org", "include", "macro", "endm" ,
	"rep", "endrep", "argc", "left", "right",
	"warn", "error", "device"
};

// number of arguments of macro (pass2.cpp) for .argc evaluation
extern int param_count;
// offset (pass1.cpp) for $ evolution
extern int current_offset;

// files for input and output
FILE *indat, *outdat;

// name of module
char module_file[128];
// current line of parser
char _line[MAXLINELEN+1];
// pointer in '_line' for parsing
char *lineptr;
// current line and number of errors
int current_line, mass_line_count = 0;
int error_number;

// parser fill this if find ident
char token_string[MAXTOKENLEN];
// parser fill this if find number
int  token_number;
// current symbol
int c_sym = si_none;
// does we count instructions or not
bool match_inst;
// do not show error/warn/fatal message
bool no_error = false;

/*
	This pointer is switched for input from
	file or from string buffer (in macros and .rep)
*/
void (*get_line)(void) = _get_line;

// is 'str' directive
int find_directive(char *str) 
{	
	for(int i=0; i<DIRECTIVES; i++)
		if (!strcmp(str, directives[i]))
			return i + si_lo8;
return -1;
}

// exiting
void do_exit()
{
	exit(1);
}

// geting new line from file (get_line pointer points to this
// function if parsing file)
void _get_line()
{
	lineptr = fgets(_line, MAXLINELEN, indat);
	current_line++;
	mass_line_count++;
}

// display errors like in format like 'printf'
// 'msg' can be:
//	MSG_WARN	- warning
//	MSG_ERROR	- error
//	MSG_FATAL	- fatal error (exiting program)
void error(int msg, const char *fmt, ...)
{
char printf_buf[1024];
va_list args;
	if (no_error) return;
       va_start(args, fmt);
       vsprintf(printf_buf,fmt,args);
       va_end(args);
       if (msg == MSG_WARN)
              fprintf(stderr, "warning:");
       else if (msg == MSG_ERROR) {
              fprintf(stderr, "error:");
		error_number++;
	}
       else {
		fprintf(stderr, "fatal:");
		error_number++;
	}
       fprintf(stderr, "%s:%i:%s\n", module_file, current_line, printf_buf);
       if (msg == MSG_FATAL)
              do_exit();
}

// convert 'c_sym' to string representation info
char* tok2str()
{
static char buf[MAXTOKENLEN+1];
	switch(c_sym) {
		case si_warn:	return "<user-warning '.warn'>";
		case si_error: return "<user-error '.error'>";
		case si_lo8: return "<lower-bits '.lo8'>";
		case si_hi8: return "<higher-bits '.hi8'>";
		case si_lo16: return "<lower-bits '.lo16'>";
		case si_hi16: return "<higher-bits '.hi16'>";
		case si_ror: return "<rotate-right '.ror'>";
		case si_rol: return "<rotate-left '.rol'>";
		case si_isdef: return "<definition-check '.isdef'>";
		case si_isndef: return "<definition-check '.isndef'>";
		case si_define: return "<definition '.define'>";
		case si_if: return "<condition-if '.if'>";
		case si_else: return "<condition-else '.else'>";
		case si_endif: return "<condition-if-end '.endif'>";
		case si_org: return "<memory-org '.org'>";
		case si_include: return "<including '.include'>";
		case si_macro: return "<definition-macro '.macro'>";
		case si_endm: return "<end-macro '.endm'>";
		case si_rep: return "<repetition '.rep'>";
		case si_endrep: return "<end-repetition '.endrep'>";
		case si_argc: return "<number-of-args '.argc'>";
		case si_left: return "<rotate-param-left '.left'>";
		case si_right: return "<rotate-param-right '.right'>";
		case si_plus: return "<plus '+'>";
		case si_minus: return "<minus '-'>";
		case si_mul: return "<multiplication '*'>";
		case si_div: return "<division '/'>";
		case si_mod: return "<modulo '%'>";
		case si_assign: return "<assign '='>";
		case si_and: return "<and '&'>";
		case si_or: return "<or '|'>";
		case si_xor: return "<xor '^'>";
		case si_comp: return "<complement '~'>";
		case si_not: return "<not '!'>";
		case si_shl: return "<shift-left '<<'>";
		case si_shr: return "<shitf-right '>>'>";
		case si_less: return "<less '<'>";
		case si_grt: return "<greater '>'>";
		case si_lesse: return "<less-or-equ '<='>";
		case si_grte: return "<greater-or-equ '>='>";
		case si_equ: return "<equ '=='>";
		case si_nequ: return "<not-equ '!='>";
		case si_eof: return "<end-of-file>";
		case si_newline: return "<new-line>";
		case si_dollar: return "<current-offset '$'>";
		case si_hash: return "<param '#'>";
		case si_comma: return "<comma ','>";
		case si_collon: return "<collon ':'>";
		case si_rpar: return "<right-paretnese ')'>";
		case si_lpar: return "<left-parenthese '('>";
		case si_device: return "<device-specification '.device'>";
		case si_quote: return "<quote - '\"'>";
		default: if (c_sym == si_ident)
				sprintf(buf, "<ident '%s'>", token_string);
			  else if (c_sym == si_number) 
				  sprintf(buf, "<number '%i'>", token_number);
			  else if (IS_INSTRUCTION())
				  sprintf(buf, "<instruction '%s'>", instructions[c_sym].name);
			  else strcpy(buf, "< ??? >");
			  return buf;
	}
}

/*
	three functions fro checking is char in set for
	some number representation (BIN, OCT and HEX)
*/
int bincrc(int c)
{
return c == '1' || c == '0';
}

int octcrc(int c) 
{
return c >= '0' && c <= '7';
}

int hexcrc(int c)
{
return isdigit(c) || (c >= 'A' && c <= 'F');
}

// rotating number 'a' for 'b' bits
int ror(unsigned int a, unsigned int b)
{
int cary;
	if (a & 1)
		cary = 0x80000000;
	else cary = 0;
	a <<= b;
	a |= cary;
return a;
}

int rol(unsigned int a, unsigned int b)
{
int cary;
	if (a & 0x80000000)
		cary = 1;
	else cary = 0;
	a <<= b;
	a |= cary;
return a;
}


void read_number()
{
int base = 10, add;
int (*crc)(int) = isdigit;
	if (*lineptr == '0') { // some other base: oct,bin or hex
		lineptr++;
		if (*lineptr == 'x' || *lineptr == 'X')  {
			base = 16;
			lineptr++;
			crc = hexcrc;
		}
		else if (*lineptr == 'b' || *lineptr == 'B') {
			base = 2;
			lineptr++;
			crc = bincrc;
		}
		else {
			base = 8;
			crc = octcrc;
		}
	}
	token_number = 0;
	while(crc(toupper(*lineptr))) {
		if (isdigit(*lineptr))
			add = *lineptr - '0';
		else add = toupper(*lineptr) - 'A' + 10;
		token_number = token_number*base + add;
		lineptr++;
	}
}

// main function for reading tokens from line
void get_token()
{
bool directive = false;
	if (lineptr == 0) {
		c_sym = si_eof;
		return;
	}
	SKIP_SPACE(lineptr);
	switch(*lineptr) {
		case ';' : // drop-down (dead)
		case '\0': c_sym = si_newline; return;
		case '\"': c_sym = si_quote; break;
		case ':' : c_sym = si_collon; break;
		case ',' : c_sym = si_comma; break;
		case '#' : c_sym = si_hash; break;
		case '$' : c_sym = si_dollar; break;
		case '!' :lineptr++;
			   if (*lineptr == '=') 
				   c_sym = si_nequ;
			   else {
				   c_sym = si_not;
				   return;
			   }
			   break;
		case '+': c_sym = si_plus; break;
		case '-': c_sym = si_minus; break;
		case '*': c_sym = si_mul; break;
		case '/': c_sym = si_div; break;
		case '%': c_sym = si_mod; break;
		case '=': lineptr++;
			   if (*lineptr == '=')
				   c_sym = si_equ;
			   else {
				   c_sym = si_assign;
				   return;
			   }
			   break;
		case '(': c_sym = si_lpar; break;
		case ')': c_sym = si_rpar; break;
		case '^': c_sym = si_xor; break;
		case '|': c_sym = si_or; break;
		case '&': c_sym = si_and; break;
		case '~': c_sym = si_comp; break;
		case '<': lineptr++;
			   if (*lineptr == '<') 
				   c_sym = si_shl;
			   else if (*lineptr == '=')
				   c_sym = si_lesse;
			   else {
				   c_sym = si_less;
				   return;
			   }
			   break;
		case '>': lineptr++;
			   if (*lineptr == '>') 
				   c_sym = si_shr;
			   else if (*lineptr == '=')
				   c_sym = si_grte;
			   else {
				   c_sym = si_grt;
				   return;
			   }
			   break;
		default:  if (isalpha(*lineptr) || *lineptr == '.' || *lineptr == '_') {
				char *ptr = token_string;
				int i = 0;
				if (*lineptr == '.') {
					directive = true;
					lineptr++;
				}
				while(isalnum(*lineptr) || *lineptr == '_') {
					*ptr++ = *lineptr++;
					if (++i > MAXTOKENLEN) {
						error(MSG_WARN, "identifer too long - truncating");
						break;
					}
				}
				*ptr = '\0';
				if (!directive)
					if (match_inst)
						c_sym = find_inst(token_string);
					else c_sym = si_ident;
				else {
					c_sym = find_directive(token_string);
					if (c_sym == -1)
						error(MSG_ERROR, "unknown directive .%s", token_string);
				}
				return;
			   }
			   else if (isdigit(*lineptr)) {
				read_number();
				c_sym = si_number;
				return;
			   }
			   else error(MSG_ERROR, "unknown stray \%03o", *lineptr);
	}
	lineptr++;
}

/*
	There goes function for parsing expression. For more details see
	begining of this file!
*/

int expression();

int faktor()
{
int ret = 0;
t_label *lab;
	switch(c_sym) {
		case si_ident:if ((lab=find_label(token_string)) == 0)
					error(MSG_ERROR, "undefined label %s", token_string);
				else ret = lab->val;
				get_token();
				break;
		case si_number:ret = token_number;
				get_token();
				break;
		case si_minus:get_token();
				ret = -faktor();
				break;
		case si_plus: get_token();
				ret = faktor();
				break;
		case si_not:  get_token();
				ret = !expression();
				break;
		case si_comp: get_token();
				ret = ~expression();
				break;
		case si_lo8:  get_token();
				ret = faktor() & 0x000000FF;
				break;
		case si_lo16:  get_token();
				ret = faktor() & 0x0000FFFF;
				break;
		case si_hi8:  get_token();
				ret = (faktor() & 0xFF000000) >> 24;
				break;
		case si_hi16: get_token();
				ret = (faktor() & 0xFFFF0000) >> 16;
				break;
		case si_argc: ret = param_count;
			       get_token();
				break;
		case si_dollar:ret = current_offset;
				get_token();
				break;
		case si_isdef:get_token(); //mora ici ident
				if (c_sym != si_ident) {
					error(MSG_ERROR, "identifer expected, got %s", tok2str());
					break;
				}
				lab = find_label(token_string);
				if (lab == 0) ret = 0;
				else ret = 1;
				get_token();
				break;
		case si_isndef:get_token(); //mora ici ident
				if (c_sym != si_ident) {
					error(MSG_ERROR, "identifier expected, got %s", tok2str());
					break;
				}
				lab = find_label(token_string);
				if (lab == 0) ret = 1;
				else ret = 0;
				get_token();
				break;
		case si_lpar: get_token();
				ret = expression();
				if (c_sym != si_rpar) 
					error(MSG_ERROR, "expected ), got %s", tok2str());
				get_token();
				break;
		default:      error(MSG_ERROR, "unexpeceted %s", tok2str());
				get_token();
				break;
	}
return ret;
}

int clan3()
{
int a, b, s;
	a = faktor();
	while(c_sym == si_mul || c_sym == si_div || c_sym == si_mod) {
		s = c_sym;
		get_token();
		b = faktor();
		if (s == si_mul) a *= b;
		else if (s == si_div) {
			if (b == 0) 
				error(MSG_ERROR, "division by zero");
			else a /= b;
		}
		else a %= b;
	}
return a;
}

int clan2()
{
int a, b, s;
	a = clan3();
	while(c_sym == si_plus || c_sym == si_minus) {
		s = c_sym;
		get_token();
		b = clan3();
		if (s == si_plus) a += b;
		else a -= b;
	}
return a;
}

int clan1()
{
int a, b, s;
	a = clan2();
	while(c_sym == si_and || c_sym == si_or || 
	      c_sym == si_xor || c_sym == si_shl || 
	      c_sym == si_shr || c_sym == si_ror || c_sym == si_rol) {
		s = c_sym;
		get_token();
		b = clan2();
		if (s == si_and) a &= b;
		else if (s == si_or) a |= b;
		else if (s == si_xor) a ^= b;
		else if (s == si_shl) a <<= b;
		else if (s == si_ror) a = ror(a, b);
		else if (s == si_rol) a = rol(a, b);
		else a >>= b;
	}
return a;
}


int expression()
{
int a, b, s;
	a = clan1();
	while(c_sym == si_less || c_sym == si_lesse || c_sym == si_grt
	      || c_sym == si_grte || c_sym == si_equ || c_sym == si_nequ  ) {
		s = c_sym;
		get_token();
		b = clan1();
		if (s == si_less) a = a < b;
		else if (s == si_lesse) a = a <= b;
		else if (s == si_grt) a = a > b;
		else if (s == si_grte) a = a >= b;
		else if (s == si_equ) a = a == b;
		else a = a != b;
	}
return a;
}
