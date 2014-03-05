/*     
     Copyright (C) 2004 Pasalic Zaharije (zaharije@klika.ba, s4063m@pmf.unsa.ba)

					Last Revision: 30.06.2004
*/

#ifndef __PASS1_H
#define __PASS1_H

extern int current_offset;
extern char include_dir[128];
extern bool config_ok;

void do_labelinst(char *label_name);
void do_assign(char *label_name);
void do_define();
void do_if(bool enter_if);
void do_include();
void do_assignlabel();
void do_pass1();
void do_org(bool);
	
#endif
