/*
     Copyright (C) 2004 Pasalic Zaharije (zaharije@klika.ba, s4063m@pmf.unsa.ba)
     
					Last Revision: 30.06.2004
*/

#ifndef __MAS_H
#define __MAS_H


#define SKIP_SPACE(str) while(isspace(*str)) str++


enum {
	/*si_addlw,  si_andlw,  si_addwf,  si_andwf, si_bcf,  si_btfsc, //5
       si_bsf,    si_btfss,  si_call,   si_clrf,  si_clrw, //10
       si_clrwdt, si_comf,   si_decfsz, si_decf,  si_goto, //15
       si_incf,   si_incfsz, si_iorlw,  si_iorwf, si_movlw, //20
       si_movf,   si_movwf,  si_nop,    si_retfie,si_option, //25
       si_retlw,  si_return, si_rlf,    si_rrf,   si_sleep, //30
       si_sublw,  si_subwf,  si_swapf,  si_tris,  si_xorlw,
       si_xorwf,                                               //36
	*/
	
	si_lo8=0x100, si_hi8, si_lo16, si_hi16,
	si_ror, si_rol,
	si_isdef, si_isndef,
	
	si_define, si_if, si_else, si_endif,
	si_org, si_include, si_macro, si_endm,
	si_rep, si_endrep, si_argc, si_left, si_right,
	si_warn, si_error, si_device,
	
	si_plus, si_minus, si_mul, si_div, si_mod,
	si_assign,
	
	si_and, si_or, si_xor, si_comp, si_not,
	si_shl, si_shr, 
	
	si_less, si_grt, si_lesse, si_grte, 
	si_equ, si_nequ,
	
	si_lpar, si_rpar, si_collon, si_comma,
	si_hash, si_dollar, si_quote,
	
	si_ident, si_number, si_newline, 
	si_eof, si_none
};

#endif
