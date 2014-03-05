/*
     Copyright (C) 2004 Pasalic Zaharije (zaharije@klika.ba, s4063m@pmf.unsa.ba)

					Last Revision: 30.06.2004
*/

#ifndef __PARSER_H
#define __PARSER_H

#include <cstdlib>

#define MAXLINELEN 256
#define MAXTOKENLEN 32

#define MSG_NONE  0
#define MSG_ERROR 1
#define MSG_WARN  2
#define MSG_FATAL 3

#define KEYWORDS 37
#define DIRECTIVES 24

#define OPER_NONE 0

typedef struct {
        char *name;         // name of instruction
        int op1, op2, op3;       // size of operands in bits, 0 == NONE
	 int place1, place2, place3; // where we place operands - 0 bit-based
        unsigned short opcode;  // opcode
	 int msg_type1, msg_type2, msg_type3;	// MSG_xxxx
	 char *msg1, *msg2, *msg3;
} t_instruction;

extern FILE *indat, *outdat;

extern void (*get_line)(void);

extern char module_file[128];
extern char _line[MAXLINELEN+1];
extern char *lineptr;
extern int current_line, mass_line_count;
extern int error_number;

extern char token_string[MAXTOKENLEN];
extern int  token_number;
extern int  c_sym;

extern bool no_error;

void do_exit();
void _get_line();
void error(int msg, const char *fmt, ...);
void get_token();
int faktor();
int clan2();
int clan1();
int expression();
char* tok2str();

#endif
