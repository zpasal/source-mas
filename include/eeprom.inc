;-----------------------------------------------------------------------
;
; eeprom.inc
;
; This is standard include file for mas assembler.
;
; Copyright 2004 by Pasalic Zaharije
;
; This program is free software; you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation; either version 2 of the License, or
; any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program; if not, write to the Free Software
; Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
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
