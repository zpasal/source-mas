/*

     pass1.cpp

     Main file of mas.

	usage: mas [options] file

	options:
		-h			(help)
		-o ident		(output file name)
		-s ident		(symbol file name)
		-l ident		(list file name)
		-f ident 		(bin,bt,hex)
		-d ident		(dump spec for device 'ident')
		-I path		(include dir)
		-i path		(device dir)
		-v			(mas info)


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
#include "tools/Lista.hpp"
#include "config.h"
#include "pass1.h"
#include "pass2.h"
#include "objects.h"

/*
	Parametar parsing
*/

char input_file[128];
bool do_input = false;
char object_format[7];
bool do_object = false;
char output_file[128];
bool do_output = false;
char sym_file[128];
bool do_sym = false;
char list_file[128];
bool do_list = false;
int object = OBJ_IHEX;
char device_dump[32];
bool do_device = false;


void get_string(char *where, char *from)
{
       *where = '\0';
       while(*from != ' ') {
              *where++ = *from;
              if (*from == '\0') break;
              from++;
       }
}


void dump_help()
{
	puts("Usage: mas [options] file");
	puts("Options:");
	puts("\t-h\t\thelp info");
	puts("\t-v\t\tmas version info");
	puts("\t-o file\t\tname of output file");
	puts("\t-f format\tformat of output file");
	puts("\t\t\tSupported:");
	puts("\t\t\t\tbt  binary text");
	puts("\t\t\t\tbin flat binary");
	puts("\t\t\t\thex Intel Hex (IHex)");
	puts("\t-s file\t\tsymbol file name");
	puts("\t-l file\t\tlist file name");
	puts("\t-d device\tdump info for device");
	puts("\t-I path\t\tinclude directory path");
	puts("\t-i path\t\tdirectory path for device(s)");
}

void dump_info()
{
	printf("mas v1.0.1 compiled at %s %s\n", __DATE__, __TIME__);
}


void dump_sym()
{
MojiAlati::TListaNode<t_label> *p = Labele.UzmiBazu();
FILE *dat;
int t;
	dat = fopen(sym_file, "w");
	if (dat == 0) {
		fprintf(stderr, "mas: can not create sym file %s\n", sym_file);
		return;
	}
	fprintf(dat, "\tSymbols for %s\n\n", input_file);
	while(p != 0) {
		t = p->Vrijednost.type;
		if (t == L_LABEL)      fprintf(dat, "LABEL    ");
		else if (t == L_IDENT) fprintf(dat, "VARIABLE ");
		else if (t == L_CONST) fprintf(dat, "CONST    ");
		else if (t == L_MACRO) fprintf(dat, "MACRO    ");
		if (t != L_MACRO)
			fprintf(dat, "0x%08X  ", p->Vrijednost.val);
		else   fprintf(dat, "            ");
		fprintf(dat, "%-32s\n", p->Vrijednost.name);
		p = p->Slijedeci;
	}		
	fclose(dat);
}

bool params(int argc, char **argv)
{
char *ptr;
       for(int i=1; i<argc; i++) {
              ptr = argv[i];
              if (*ptr != '-') { // file name
                     if (do_input)
                            fprintf(stderr, "mas: redeclaration of input file\n");
                     get_string(input_file, ptr);
                     do_input = true;
              }
              else {
                     ptr++;
                     switch(*ptr) {
                            case 'h': dump_help();
                                      break;
                            case 'v': dump_info();
                                      exit(0);
                            case 'f': ptr++;
                                      if (*ptr == '\0') { // novi argv
                                          if (argv[i+1] != NULL && argv[i+1][0] != '-')
                                             ptr = argv[++i];
                                          else {
                                             fprintf(stderr, "mas: bad option\n");
                                             return false;
                                          }
                                      }
                                      get_string(object_format, ptr);
                                      do_object = true;
                                      break;
                            case 'o': ptr++;
                                      if (*ptr == '\0') { // novi argv
                                          if (argv[i+1] != NULL && argv[i+1][0] != '-')
                                             ptr = argv[++i];
                                          else {
                                             fprintf(stderr, "mas: bad option\n");
                                             return false;
                                          }
                                      }
                                      get_string(output_file, ptr);
                                      do_output = true;
                                      break;
                            case 's': ptr++;
                                      if (*ptr == '\0') { // novi argv
                                          if (argv[i+1] != NULL && argv[i+1][0] != '-')
                                             ptr = argv[++i];
                                          else {
                                             fprintf(stderr, "mas: bad option\n");
                                             return false;
                                          }
                                      }
                                      get_string(sym_file, ptr);
                                      do_sym = true;
                                      break;
                            case 'l': ptr++;
                                      if (*ptr == '\0') { // novi argv
                                          if (argv[i+1] != NULL && argv[i+1][0] != '-')
                                             ptr = argv[++i];
                                          else {
                                             fprintf(stderr, "mas: bad option\n");
                                             return false;
                                          }
                                      }
                                      get_string(list_file, ptr);
                                      do_list = true;
                                      break;
                            case 'd': ptr++;
                                      if (*ptr == '\0') { // novi argv
                                          if (argv[i+1] != NULL && argv[i+1][0] != '-')
                                             ptr = argv[++i];
                                          else {
                                             fprintf(stderr, "mas: bad option\n");
                                             return false;
                                          }
                                      }
                                      get_string(device_dump, ptr);
                                      do_device = true;
                                      break;
                            case 'I': ptr++;
                                      if (*ptr == '\0') { // novi argv
                                          if (argv[i+1] != NULL && argv[i+1][0] != '-')
                                             ptr = argv[++i];
                                          else {
                                             fprintf(stderr, "mas: bad option\n");
                                             return false;
                                          }
                                      }
                                      get_string(include_dir, ptr);
                                      break;
                            case 'i': ptr++;
                                      if (*ptr == '\0') { // novi argv
                                          if (argv[i+1] != NULL && argv[i+1][0] != '-')
                                             ptr = argv[++i];
                                          else {
                                             fprintf(stderr, "mas: bad option\n");
                                             return false;
                                          }
                                      }
                                      get_string(config_dir, ptr);
                                      break;
				default:  fprintf(stderr,"mas: unknown option\n");
                                      dump_help();
                                      break;
                     }
              }
       }
	if (do_device) {
		open_config(device_dump);
		pars_config();
		dump_config();
		exit(0);
	}
	if(!do_input) {
		fprintf(stderr, "mas: no input file\n");
		return false;
	}
	if (!do_object)
		strcpy(object_format, "hex");
	else {
		if (!strcmp(object_format, "bin")) 
			object = OBJ_BIN;
		else if (!strcmp(object_format, "bt"))
			object = OBJ_BINT;
		else if (!strcmp(object_format, "hex"))
			object = OBJ_IHEX;
		else {
			fprintf(stderr, "mas: unimplemented foramt '%s'", object_format);
			return false;
		}
	}
	if (!do_output) {
		strcpy(output_file, input_file);
		char *ptr = strchr(output_file, '.');
		if (ptr) *ptr = 0;
		strcat(output_file, ".");
		strcat(output_file, object_format);
	}
	strcpy(module_file, input_file);
return true;
}


void compile()
{
char tmp[128];
//pass1
	current_offset = 0;
	current_line = 0;
	do_pass1();
	if (error_number) {
		error(MSG_ERROR, "errors in pass1");
		return;
	}
	fclose(outdat);
	fclose(indat);
// pass2
	// no .device, default to P16C84
	sprintf(tmp, "%s.$$$", input_file);
	indat = fopen(tmp, "r");
	if (object != OBJ_BIN)
		outdat = fopen(output_file, "w");
	else 
		outdat = fopen(output_file, "wb");
	current_offset = 0;
	current_line = 0;
	init_emit_buffer();
	mass_line_count = 0;
	do_pass2();
	if (!error_number) {
		printf("Lines compiled : %i.\n", mass_line_count);
		kill_config();
		make_output(object);
		if (do_sym)
			dump_sym();
		//if (do_list)
		//	make_list(list_file); NOT GOOD ALGO - IN LATER VERSION
		fclose(indat);
		fclose(outdat);
	}
}

void load_config()
{
FILE *dat = fopen("mas.ini", "r");
char *ptr;
	if (!dat) {
		error(MSG_WARN, "no mas.ini - defaulting include/ and device/");
		strcpy(include_dir, "include/");
		strcpy(config_dir, "device/");
		return;
	}
	fgets(include_dir, 127, dat);
	if((ptr = strchr(include_dir, '\n')) != 0)
		*ptr = 0;
	fgets(config_dir, 127, dat);
	if ((ptr = strchr(config_dir, '\n')) != 0)
		*ptr = 0;
	fclose(dat);
}

int main(int argc, char **argv)
{
char tmp[128];
	load_config();
	if(!params(argc, argv))
		return 1;
	indat = fopen(input_file, "r");
	if (indat == 0) {
		error(MSG_FATAL, "can not open file %s", input_file);
		return 1;
	}
	sprintf(tmp, "%s.$$$", input_file);
	outdat = fopen(tmp, "w");
	compile();
	if (remove(tmp))
		error(MSG_WARN, "can not remove temporaly file");
return 0;
}
