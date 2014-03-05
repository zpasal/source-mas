;-----------------------------------------------------------------------
;
; eeprom.inc
;
; This is standard include file for mas assembler.
;
; Copyright 2004 by Pasalic Zaharije
;

;
; Last Revision: 29.08.2004
; Revision   by: Even S. F.
;                - Whole implementation 


.if .isndef __EEPROM_INC
.define __EEPROM_INC

.if .isndef __EEPROM8
    .if .isndef __EEPROM16
        .warn select device __EEPROM8 or __EEPROM16 first
    .endif
.endif



.macro Declare 0
   .rep .argc
        decl #0
        .left
   .endrep
.endm

.endif
