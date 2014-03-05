/*
     labels.cpp

     Implementation for class t_label (struct) for us with
     'alati' template lib.

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

#include "labels.h"

// Linked list of t_label's
MojiAlati::TLista<t_label> Labele;

// constructor for t_label
// 'n' name, 't' type, 'v' value, 'l' line
t_label::t_label(char *n, int t, int v, int l) 
{
	name = new char[strlen(n)+1];
	strcpy(name, n);
	macro_line = 0;
	type = t;
	val = v;
	line = l;
}

// copy constructor
t_label::t_label(t_label &lab) {
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
}


// finding labels
t_label* find_label(char *labe) 
{
MojiAlati::TListaNode<t_label> *p = Labele.UzmiBazu();
	while(p != 0) {
		if (!strcmp(p->Vrijednost.name, labe)) {
			return &p->Vrijednost;
		}
		p = p->Slijedeci;
	}
return 0;
}
