;-----------------------------------------------------------------------
;
; checksum.inc
;
; This is standard include file for mas assembler.
;
; Copyright 2004 by Pasalic Zaharije
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
