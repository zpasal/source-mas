;-----------------------------------------------------------------------
;
; P16C505.INC
;
; This is standard include file for P16C505 device. Before including this
; file, chose P16C505 device with .device or with command switch.
;
; Copyright 2004 by Pasalic Zaharije
;

;
; This file is generated with 'minc2inc' program.
;
; Last Revision: Jun 27 2004
;
;

.if .isndef __P16C505_INC
.define __P16C505_INC

.if .isndef __P16C505
	.warn Select device __P16C505 first
.endif

.define W                    = 0x0
.define F                    = 0x1

;----- Register Files -----------------------------------------------------

.define INDF                 = 0x0
.define TMR0                 = 0x1
.define PCL                  = 0x2
.define STATUS               = 0x3
.define FSR                  = 0x4
.define OSCCAL               = 0x5
.define PORTB                = 0x6
.define PORTC                = 0x7

;----- STATUS Bits --------------------------------------------------------

.define RBWUF                = 0x7
.define PA0                  = 0x5
.define NOT_TO               = 0x4
.define NOT_PD               = 0x3
.define Z                    = 0x2
.define DC                   = 0x1
.define C                    = 0x0

;----- OPTION Bits --------------------------------------------------------

.define NOT_RBWU             = 0x7
.define NOT_RBPU             = 0x6
.define T0CS                 = 0x5
.define T0SE                 = 0x4
.define PSA                  = 0x3
.define PS2                  = 0x2
.define PS1                  = 0x1
.define PS0                  = 0x0

;----- OSCCAL Bits --------------------------------------------------------

.define CAL5                 = 0x7
.define CAL4                 = 0x6
.define CAL3                 = 0x5
.define CAL2                 = 0x4
.define CAL1                 = 0x3
.define CAL0                 = 0x2
.define _MCLRE_ON            = 0xFFF
.define _MCLRE_OFF           = 0xFDF
.define _CP_ON               = 0x2F
.define _CP_OFF              = 0xFFF
.define _WDT_ON              = 0xFFF
.define _WDT_OFF             = 0xFF7
.define _LP_OSC              = 0xFF8
.define _XT_OSC              = 0xFF9
.define _HS_OSC              = 0xFFA
.define _IntRC_OSC_RB4EN     = 0xFFC
.define _IntRC_OSC_CLKOUTEN  = 0xFFD
.define _ExtRC_OSC_RB4EN     = 0xFFE
.define _ExtRC_OSC_CLKOUTEN  = 0xFFF

.endif