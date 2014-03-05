;-----------------------------------------------------------------------
;
; checksum.inc
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
;                - Added CheckSum16
;                - some modification to CheckSum8


.if .isndef __CHECKSUM_INC
.define __CHECKSUM_INC

.macro CheckSum8 0
       CheckSumRet8 = 0
       .rep .argc
            CheckSumRet8 = CheckSumRet8 + #0
            .left
       .endrep
       CheckSumRet8 = ((CheckSumRet8 >> 8) & 0xFF) + (CheckSumRet8 & 0xFF)
       CheckSumRet8 = CheckSumRet8 + ((CheckSumRet8 >> 8) & 0xFF)
       CheckSumRet8 = .lo8(~CheckSumRet8)
.endm


.macro CheckSum16 0
       CheckSumRet16 = 0
       .rep .argc
            CheckSumRet16 = CheckSumRet16 + #0
            .left
       .endrep
       CheckSumRet16 = .hi16(CheckSumRet16) + (CheckSumRet16 & 0xFFFF)
       CheckSumRet16 = CheckSumRet16 + .hi16(CheckSumRet16)
       CheckSumRet16 = .lo16(~CheckSumRet16)
.endm


.endif
