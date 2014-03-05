.if .isndef __PARALAX_INC
.define __PARALAX_INC

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; AddFL(freg, lit)
;	freg = freg + lit
;
; Affects: W, C, DC, Z
; Cycles : 2 
.macro AddFL 2
	movlw #1 
	addwf #0, F
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; AddFF(freg1, freg2)
;	freg1 = freg1 + freg2
;
; Affects: W, C, DC, Z
; Cycles : 2
.macro AddFF 2
	movf #1, W
	addwf #0, F
.endm


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; AndFL(freg, lit)
;	freg = freg and W
; 
; Affects: W, Z
; Cycles : 2
.macro AndFL 2
	movlw #1
	andwf #0, F
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; AndFF(freg1, freg2)
;	freg1 = freg1 and freg2
; 
; Affects: W, Z
; Cycles : 2
.macro AndFF 2
	movf #1, W
	andwf #0, F
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; JmpFAL(freg, lit, address)
;       if (freg > lit) goto address
; 
; Affects: W, C, DC, Z
; Cycles : 4/5
.macro JmpFAL 3
	movlw #1
	addwf #0, W
	btfsc STATUS, C
	goto #2
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; JmpFAF(freg1, freg2, address)
;	if (freg1 > freg2) goto address
; 
; Affects: W, C, DC, Z
; Cycles : 4/5
.macro JmpFAF 3
	movf #0, W
	subwf #1, W
	btfss STATUS, C
	goto #2
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; JmpFAEL(freg, lit, address)
;	if (freg >= lit) goto address
; 
; Affects: W, C, DC, Z
; Cycles : 4/5
.macro JmpFAEL 3
	movlw #1
	subwf #0, W
	btfsc STATUS, C
	goto #2
.endm
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; JmpFAEF(freg1, freg2, address) 
;	if (freg1 >= freg2) goto address
; 
; Affects: W, C, DC, Z
; Cycles : 4/5
.macro JmpFAEF 3
	movf #1, W
	subwf #0, W
	btfsc STATUS, C
	goto #2
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; JmpFBL(freg, lit, addr)
;	if (freg < lit) goto addr
; 
; Affects: W, C, DC, Z
; Cycles : 4/5
.macro JmpFBL 3
	movlw #1
	subwf #0, W
	btfss STATUS, C
	goto #2
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; JmpFBF(freg1, freg2, addr)
;	if (freg1 < freg2) goto addr
; 
; Affects: W, C, DC, Z
; Cycles : 4/5
.macro JmpFBF 3
	movf #1, W
	subwf #0, W
	btfss STATUS, C
	goto #2
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; JmpFBEL(freg1, lit, addr)
;	if (freg1 <= lit) goto addr
; 
; Affects: W, C, DC, Z
; Cycles : 4/5
.macro JmpFBEL 3
	movlw #1
	addwf #0, W
	btfss STATUS, C
	goto #2
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; JmpFBEF(freg1, freg2, addr)
;	if (freg1 <= freg2) goto addr
; 
; Affects: W, C, DC, Z
; Cycles : 4/5
.macro JmpFBEF 3
	movf #0, W
	subwf #1, W
	btfsc STATUS, C
	goto #2
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; JmpFEL(freg, lit, addr)
;	if (freg == lit) goto addr
; 
; Affects: W, C, DC, Z
; Cycles : 4/5
.macro JmpFEL 3
	movlw #1
	subwf #0, W
	btfsc STATUS, Z
	goto #2
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; JmpFEF(freg1, freg2, addr)
;	if (freg1 == freg2) goto addr
; 
; Affects: W, C, DC, Z
; Cycles : 4/5
.macro JmpFEF 3
	movf #1, W
	subwf #0, W
	btfsc STATUS, Z
	goto #2
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; JmpFNEL(freg, lit, addr)
;	if (freg != lit) goto addr
; 
; Affects: W, C, DC, Z
; Cycles : 4/5
.macro JmpFNEL 3
	movlw #1
	subwf #0, W
	btfss STATUS, Z
	goto #2
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; JmpFNEF(freg1, freg2, addr)
;	if (freg1 != freg2) goto addr
; 
; Affects: W, C, DC, Z
; Cycles : 4/5
.macro JmpFNEF 3
	movf #1, W
	subwf #0, W
	btfss STATUS, Z
	goto #2
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; SkipFAL(freg, lit)
;	if (freg > lit) skip_next_inst
; 
; Affects: W, C, DC, Z
; Cycles : 3/4
.macro SkipFAL 2
	movlw #1
	addwf #0, W
	btfss STATUS, C
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; SkipFAF(freg1, freg2)
;	if (freg1 > freg2) skip_next_inst
; 
; Affects: W, C, DC, Z
; Cycles : 3/4
.macro SkipFAF 2
	movf #0, W
	subwf #1, W
	btfsc STATUS, C
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; SkipFAEL(freg, lit)
;	if (freg >= lit) skip_next_inst
; 
; Affects: W, C, DC, Z
; Cycles : 3/4
.macro SkipFAEL 2
	movlw #1
	subwf #0, W
	btfss STATUS, C
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; SkipFAEF(freg1, freg2)
;	if (freg1 > freg2) skip_next_inst
; 
; Affects: W, C, DC, Z
; Cycles : 3/4
.macro SkipFAEF 2
	movf #1, W
	subwf #0, W
	btfss STATUS, C
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; SkipFBL(freg, lit)
;	if (freg < lit) skip_next_inst
; 
; Affects: W, C, DC, Z
; Cycles : 3/4
.macro SkipFBL 2
	movlw #1
	subwf #0, W
	btfsc STATUS, C
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; SkipFBF(freg1, freg2)
;	if (freg1 < freg2) skip_next_inst
; 
; Affects: W, C, DC, Z
; Cycles : 3/4
.macro SkipFBF 2
	movf #1, W
	subwf #0, W
	btfsc STATUS, C
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; SkipFBEL(freg, lit)
;	if (freg < lit) skip_next_inst
; 
; Affects: W, C, DC, Z
; Cycles : 3/4
.macro SkipFBEL 2
	movlw #1
	addwf #0, W
	btfsc STATUS, C
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; SkipFBEF(freg1, freg2)
;	if (freg1 < freg2) skip_next_inst
; 
; Affects: W, C, DC, Z
; Cycles : 3/4
.macro SkipFBEF 2
	movf #0, W
	subwf #1, W
	btfss STATUS, C
.endm


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; SkipFEL(freg, lit)
;	if (freg == lit) skip_next_inst
; 
; Affects: W, C, DC, Z
; Cycles : 3/4
.macro SkipFEL 2
	movlw #1
	subwf #0, W
	btfss STATUS, Z
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; SkipFEF(freg1, freg2)
;	if (freg1 == freg2) skip_next_inst
; 
; Affects: W, C, DC, Z
; Cycles : 3/4
.macro SkipFEF 2
	movf #1, W
	subwf #0, W
	btfss STATUS, Z
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; SkipFNEL(freg, lit)
;	if (freg != lit) skip_next_inst
; 
; Affects: W, C, DC, Z
; Cycles : 3/4
.macro SkipFNEL 2
	movlw #1
	subwf #0, W
	btfsc STATUS, Z
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; SkipFNEF(freg1, freg2)
;	if (freg1 != freg2) skip_next_inst
; 
; Affects: W, C, DC, Z
; Cycles : 3/4
.macro SkipFNEF 2
	movf #1, W
	subwf #0, W
	btfsc STATUS, Z
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; IncJmpNZ(freg, addr)
;	if (++freg != 0) goto addr
; 
; Affects:
; Cycles : 2/3
.macro IncJmpNZ 2
	incfsz #0, F
	goto #1
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; DecJmpNZ(freg, addr)
;	if (--freg != 0) goto addr
; 
; Affects:
; Cycles : 2/3
.macro DecJmpNZ 2
	decfsz #0, F
	goto #1
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; JmpB(freg, bit, addr)
;	if (freg[bit] == 1) goto addr
; 
; Affects: 
; Cycles : 2/3
.macro JmpB 3
	btfsc #0, #1
	goto #2
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; JmpNB(freg, bit, addr)
;	if (freg[bit] == 0) goto addr
; 
; Affects: 
; Cycles : 2/3
.macro JmpNB 3
	btfss #0, #1
	goto #2
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; JmpC(addr)
;	if (C == 1) goto addr
; 
; Affects:
; Cycles : 2/3
.macro JmpC 1
	btfsc STATUS, C
	goto #0
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; JmpNC(addr)
;	if (C == 0) goto addr
; 
; Affects:
; Cycles : 2/3
.macro JmpNC 1
	btfss STATUS, C
	goto #0
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; JmpZ(addr)
;	if (Z == 1) goto addr
; 
; Affects:
; Cycles : 2/3
.macro JmpZ 1
	btfsc STATUS, Z
	goto #0
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; JmpNZ(addr)
;	if (Z == 0) goto addr
; 
; Affects:
; Cycles : 2/3
.macro JmpNZ 1
	btfss STATUS, Z
	goto #0
.endm


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; MovFL(freg, lit)
;	freg = lit
; 
; Affects: W
; Cycles : 2
.macro MovFL 2
	movlw #1
	movwf #0
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; MovFF(freg1, freg2)
;	freg1 = freg2
; 
; Affects: W
; Cycles : 2
.macro MovFF 2
	movf #1, W
	movwf #0
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; NegF(freg)
;	freg = neg freg
; 
; Affects: Z
; Cycles : 2
.macro NegF 1
	comf #0, F
	incf #0, F
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; OrFL(freg, lit)
;	freg = freg or lit
; 
; Affects: W, Z
; Cycles : 2 
.macro OrFL 2
	movlw #1
	iorwf #0, F
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; OrFF(freg1, freg2) 
;	freg1 = freg1 or freg2
; 
; Affects: W, Z
; Cycles : 2
.macro OrFF 2
	movf #1, W
	iorwf #0, F
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; SubFL(freg, lit)
;	freg = freg - lit
; 
; Affects: W, C, DC, Z
; Cycles : 2 
.macro SubFL 2
	movlw #1
	subwf #0, F
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; SubFF(freg1, freg2)
;	freg1 = freg1 - freg2
; 
; Affects: W, C, DC, Z
; Cycles : 2
.macro SubFF 2
	movf #1, W
	subwf #0, F
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; XorFL(freg, lit)
;	freg = freg xor lit
; 
; Affects: W, Z
; Cycles : 2
.macro XorFL 2
	movlw #1
	xorwf #0, F
.endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; XorFF(freg1, freg2)
;	freg1 = freg1 xor freg2
; 
; Affects: W, Z
; Cycles : 2
.macro XorFF 2
	movf #1, W
	xorwf #0, F
.endm

.endif