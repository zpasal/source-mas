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

#ifndef __LABELS_H
#define __LABELS_H

#define L_LABEL 0
#define L_IDENT 1
#define L_CONST 2
#define L_MACRO 3
#define L_LOCAL 4
#define L_NONE  5

#include <cstring>
#include "tools/Lista.hpp"

struct t_label
{
	char *name;
	int type;
	int line;
	int val;
	char *macro_line;	
	
	t_label() 
	{
		type = L_NONE;
		macro_line = name = 0;
	}
	
	~t_label()
	{
		delete name;
		delete macro_line;
	}
	
	t_label(char *n, int t, int val, int l);
	
	t_label(t_label &);
	
	t_label& operator=(t_label &lab) 
	{
		if (this == &lab) return *this;
		delete name;
		delete macro_line;
		name = new char[strlen(lab.name)+1];
		strcpy(name, lab.name);
		if (lab.macro_line != 0) {
			macro_line = new char[strlen(lab.macro_line)+1];
			strcpy(macro_line, lab.macro_line);
		}
		else macro_line = 0;
		type = lab.type;
		line = lab.line;
		val = lab.val;
	return *this;
	}
	
	bool operator==(t_label& l) 
	{
		return !strcmp(name, l.name);
	}
};

t_label* find_label(char *labe);

extern MojiAlati::TLista<t_label> Labele;

#endif
