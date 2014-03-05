/*
     config.h

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

#ifndef __CONFIG_H
#define __CONFIG_H

#include <cstdio>
#include <cstring>
#include "parser.h"
#include "mas.h"

#define OPCODE 1
#define SIZE 2
#define POSITION  3
#define WARNING 4
#define ERROR 5
#define PARAM 6
#define INST 7
#define CORE 8
#define DEVICE 9
#define MEMORY 9


#define IS_INSTRUCTION() (c_sym >= 0 && c_sym < number_of_inst)

extern int number_of_inst, max_mem, device_bits;
extern t_instruction *instructions;
extern char config_dir[128];
extern char device_title[128];

bool open_config(char *str);
void kill_config();
int script_tok(char *str);
void get_scr_token();
void accept(int sym, char *err) ;
void accept_scr(int s, char *err);
int accept_num(char *err);
void do_new_inst(char *inst);
void pars_cfg_line();
void pars_config();

int find_inst(char *str);
void dump_config();

#endif
