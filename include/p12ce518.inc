;-----------------------------------------------------------------------
;
; p12ce518.inc
;
; This is standard include file for P12CE518 device. Before including this
; file, chose P12CE518 device with .device or with command switch.
;
; Copyright 2004 by Pasalic Zaharije
;

;
; This file is generated with 'minc2inc' program.
;
; Last Revision: Jun 27 2004
;
;

.if .isndef __P12CE518_INC
.define __P12CE518_INC

.if .isndef __P12CE518
	.warn Select device __P12CE518 first
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
.define GPIO                 = 0x6

;----- STATUS Bits --------------------------------------------------------

.define GPWUF                = 0x7
.define PA0                  = 0x5
.define NOT_TO               = 0x4
.define NOT_PD               = 0x3
.define Z                    = 0x2
.define DC                   = 0x1
.define C                    = 0x0

;----- OPTION Bits --------------------------------------------------------

.define NOT_GPWU             = 0x7
.define NOT_GPPU             = 0x6
.define T0CS                 = 0x5
.define T0SE                 = 0x4
.define PSA                  = 0x3
.define PS2                  = 0x2
.define PS1                  = 0x1
.define PS0                  = 0x0
.define _MCLRE_ON            = 0xFFF
.define _MCLRE_OFF           = 0xFEF
.define _CP_ON               = 0xFF7
.define _CP_OFF              = 0xFFF
.define _WDT_ON              = 0xFFF
.define _WDT_OFF             = 0xFFB
.define _LP_OSC              = 0xFFC
.define _XT_OSC              = 0xFFD
.define _IntRC_OSC           = 0xFFE
.define _ExtRC_OSC           = 0xFFF

.endif