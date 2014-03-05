        .device p16c84
	 .include <p16c84.inc>
	 .include <paralax.inc>

.macro Sum 0
	.if (.argc <= 0)
		.error Jedan ili vise parametara
	.else
		movf #0, W
		.rep (.argc - 1)
			.left
			addwf #0, W
		.endrep
	.endif
.endm
	 
.define mulcnd = 0x20  ; 8 bit multiplicand 
.define mulplr = 0x21  ; 8 bit multiplier 
.define H_byte = 0x22  ; gornji 8 bita ezultata
.define L_byte = 0x23  ; donji 8bita rezultata
.define count  = 0x24  

mpy:
	clrf 	H_byte 
	clrf 	L_byte 
	movlw 	8 
	movwf 	count 
	movf 	mulcnd, W 
	bcf 	STATUS, C

loop:  rrf mulplr,F 

	btfsc 	STATUS, C 
	addwf 	H_byte, F 
	rrf 	H_byte, F 
	rrf 	L_byte, F 
	decfsz count, F 
	goto 	loop 
	retlw 	0 

;******************************************************* 
; Test Program 

start:
	clrw 
	option 
main:
	movf 	PORTB,W
	movwf 	mulplr   	; multiplier = 05 
	movf 	PORTB,W 
	movwf 	mulcnd 
	call 	mpy 		; Rezultat u F12 & F13 

	goto main 
	
	.org 0x1FF 
	
	goto start 