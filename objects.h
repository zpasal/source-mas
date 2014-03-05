/*
     Copyright (C) 2004 Pasalic Zaharije (zaharije@klika.ba, s4063m@pmf.unsa.ba)

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
