/*
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

#ifndef __PASS2_H
#define __PASS2_H

#include "labels.h"

extern char *_new_macro_line;
extern int macro_params[10];    // integer parametri	
extern char *macro_sparams[10];
extern int param_count;
extern bool in_macro;
extern bool in_rep;
extern unsigned short *emit_buffer;
extern int emit_index;


void init_emit_buffer();
void emit(unsigned short opcode);
void kill_emit_buffer();
void do_define();
void do_if(bool enter_if);
void do_assign(char *label_name);
void do_macro();
void expand_param_line();
void macro_get_line();
void macro_expand(t_label *macro);
void do_expand_macro(char *macro_name);
void do_param_left();
void do_param_right();
void do_rep();
void do_instruction();
void do_asm();
void do_pass2();


#endif
