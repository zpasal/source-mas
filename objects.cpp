#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <cctype>
#include "config.h"
#include "parser.h"
#include "pass1.h"
#include "pass2.h"
#include "objects.h"

#define OBJ_BINT 0
#define OBJ_BIN  1
#define OBJ_IHEX 2

void output_bint()
{
int base, b;
unsigned short op;
	base = (int)pow(2, device_bits-1);
	for(int i=0; i<emit_index; i++) {
		fprintf(outdat, "%04X ", emit_buffer[i*4+1]);
		b = base;
		op = emit_buffer[i*4];
		for(int j=0; j<device_bits; j++, b>>=1)
			if (op & b) fprintf(outdat, "1");
			else fprintf(outdat, "0");
		fprintf(outdat, "\n");
	}
}

// 0 1 100 101 102 300 400
void output_bin()
{
int size;
unsigned short mem[size = emit_buffer[(emit_index-1)*4+1]];
int writeoffset = emit_buffer[1];
	for(int i=0; i<emit_index; i++) {
		while(writeoffset != emit_buffer[i*4+1]) {
			mem[writeoffset] = 0x0000;  // put NOP's
			writeoffset++;
		}
		mem[writeoffset++] = emit_buffer[i*4];
	}
	fwrite(mem, sizeof(unsigned short)*size, 1, outdat);
}

// Intel Hex format (pure text file). Every line:
// :llaaaa[ddd...d]cc
//     :    - start of line
//     ll   - length of data in bytes
//     aaaa - start address of data (byte aligned)
//     dd..d- data
//     cc   - data checksum in two's complement


void output_ihex()
{
unsigned short start_address;
unsigned short index = 0, i;
unsigned short address;
unsigned short out[8];
unsigned char *ptr;
unsigned long crc;
t_ihex hex[max_mem], tmp;
int hex_index = 0;
	if (!emit_index) return;
       while(index < emit_index) {
              start_address = address = emit_buffer[index*4+1];
              for(i=0; i<8; ) {
                     out[i++] = emit_buffer[index*4];
                     start_address = emit_buffer[index*4+1];
                     index++;
                     if (index > emit_index) break;
                     if (emit_buffer[index*4+1] != start_address + 1)
                            break;
              }
              // pokupimo liniju u niz t_ihex
              hex[hex_index].len = (i<<1) & 0xFF;
              hex[hex_index].address = address*2;
              hex[hex_index].type = 0;
              ptr = (unsigned char*)out;
              crc = (i<<1) & 0xFF;
              crc += (address*2)>>8;
              crc += (address*2) & 0xFF;
              for(int j=0; j<i*2; j++) {
                     hex[hex_index].data[j] = ptr[j];
                     crc += ptr[j];
              }
              hex[hex_index++].crc = 0x100 - (crc & 0xFF);
       }
       for(int i=0; i<hex_index; i++)
		for(int j=i+1; j<hex_index; j++) {
			if (hex[i].address > hex[j].address) {
				tmp = hex[i];
				hex[i] = hex[j];
				hex[j] = tmp;
			}
		}
       for(i=0; i<hex_index; i++) {
              fprintf(outdat, ":%02X%04X%02X", hex[i].len & 0xFF, hex[i].address, hex[i].type & 0xFF);
              for(int j=0; j< hex[i].len; j++)
                     fprintf(outdat, "%02X", hex[i].data[j] & 0xFF);
              fprintf(outdat, "%02X\n", hex[i].crc & 0xFF);
       }
       fprintf(outdat, ":00000001FF");
}

/*
FFFF OOOO X VVVV

X - MACRO
    CONST
    IDENT
    LABEL
    CODE

V  vrijednost
*/

void make_list(char *file)
{
FILE *dat = fopen(module_file, "r");
FILE *odat = fopen(file, "w");
int line, off, op, dline = 0;
char datline[MAXLINELEN+1];
bool inm;
char *ptr;
time_t now;
	if (odat == 0) 
		error(MSG_FATAL, "can not open file %s", file);
	
	fprintf(odat, "\t\tMAS Listing File\n\n");
	fprintf(odat, "\t\tListing for module: %s\n", module_file);
	fprintf(odat, "\t\t%s\n\n", asctime(localtime(&now)));
	fprintf(odat, "OFFS OPCD TYPE  LISTING\n");
	fprintf(odat, "---- ---- ----  -------------------------------\n\n");
	for(int i=0; i<emit_index; i++) {
		op = emit_buffer[i*4];
		off = emit_buffer[i*4+1];
		line = emit_buffer[i*4+2];
		inm = emit_buffer[i*4+3];
		if (inm) {
			// dali na toj liniji ima makro
				fgets(datline, MAXLINELEN, dat);
				dline++;
				if((ptr = strchr(datline, '(')) != 0) {
					ptr--;
					while(*ptr == ' ') ptr--;
					if (!isalpha(*ptr)) goto __fuck_it;
					fprintf(odat, "%04X %04X MACRO %s", off, op, datline);
					i++; 
					while(emit_buffer[i*4+3] && emit_buffer[i*4+2] == line+1) {
						fprintf(odat, "%04X %04X MACRO\n", emit_buffer[i*4+1], emit_buffer[i*4]);
						i++; line++;
					}
				}
				else {
					__fuck_it:;
					fprintf(odat, "                  %s", datline);
				}
				i--;
		}
		else {
			while(dline < line) {
				fgets(datline, MAXLINELEN, dat);
				dline++;
				if (dline != line) 
					fprintf(odat, "                  %s", datline);
			}
			fprintf(odat, "%04X %04X CODE  %s", off, op, datline);
		}
	}
	fclose(dat);
	fclose(odat);
}

void make_output(int type)
{
	if (type == OBJ_BINT)
		output_bint();
	else if (type == OBJ_BIN)
		output_bin();
	else if (type == OBJ_IHEX)
		output_ihex();
	else error(MSG_FATAL, "bad format, I gess?");
}
