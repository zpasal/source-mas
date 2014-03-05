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

#ifndef __OBJECTS_H
#define __OBJECTS_H

#define OBJ_BINT 0
#define OBJ_BIN  1
#define OBJ_IHEX 2

typedef struct {
       unsigned short len;
       unsigned short address;
       unsigned short type;
       unsigned char data[16];
       unsigned short crc;
} t_ihex;

void output_bint();
void output_bin();
int _ihex_cmp(const void *h1, const void *h2);
void output_ihex();
void make_list(char*);
void make_output(int type);


#endif
