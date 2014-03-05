;-----------------------------------------------------------------------
;
; p16c558a.inc
;
; This is standard include file for P16C558A device. Before including this
; file, chose P16C558A device with .device or with command switch.
;
; Copyright 2004 by Pasalic Zaharije
;

;
; This file is generated with 'minc2inc' program.
;
; Last Revision: Jun 27 2004
;
;

.if .isndef __P16C558A_INC
.define __P16C558A_INC

.if .isndef __P16C558A
	.warn Select device __P16C558A first
.endif

.define W                    = 0x0
.define F                    = 0x1

;----- Register Files------------------------------------------------------

.define INDF                 = 0x0
.define TMR0                 = 0x1
.define PCL                  = 0x2
.define STATUS               = 0x3
.define FSR                  = 0x4
.define PORTA                = 0x5
.define PORTB                = 0x6
.define PCLATH               = 0xA
.define INTCON               = 0xB
.define OPTION_REG           = 0x81
.define TRISA                = 0x85
.define TRISB                = 0x86
.define PCON                 = 0x8E

;----- STATUS Bits --------------------------------------------------------

.define IRP                  = 0x7
.define RP1                  = 0x6
.define RP0                  = 0x5
.define NOT_TO               = 0x4
.define NOT_PD               = 0x3
.define Z                    = 0x2
.define DC                   = 0x1
.define C                    = 0x0

;----- INTCON Bits --------------------------------------------------------

.define GIE                  = 0x7
.define T0IE                 = 0x5
.define INTE                 = 0x4
.define RBIE                 = 0x3
.define T0IF                 = 0x2
.define INTF                 = 0x1
.define RBIF                 = 0x0

;----- OPTION Bits --------------------------------------------------------

.define NOT_RBPU             = 0x7
.define INTEDG               = 0x6
.define T0CS                 = 0x5
.define T0SE                 = 0x4
.define PSA                  = 0x3
.define PS2                  = 0x2
.define PS1                  = 0x1
.define PS0                  = 0x0

;----- PCON Bits ----------------------------------------------------------

.define NOT_POR              = 0x1
.define _CP_ALL              = 0xCF
.define _CP_75               = 0x15DF
.define _CP_50               = 0x2AEF
.define _CP_OFF              = 0x3FFF
.define _PWRTE_OFF           = 0x3FFF
.define _PWRTE_ON            = 0x3FF7
.define _WDT_ON              = 0x3FFF
.define _WDT_OFF             = 0x3FFB
.define _LP_OSC              = 0x3FFC
.define _XT_OSC              = 0x3FFD
.define _HS_OSC              = 0x3FFE
.define _RC_OSC              = 0x3FFF

.endif