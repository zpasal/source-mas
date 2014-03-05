;-----------------------------------------------------------------------
;
; p10f206.inc
;
; This is standard include file for P10F206 device. Before including this
; file, chose P10F206 device with .device or with command switch.
;
; Copyright 2004 by Pasalic Zaharije
;

;
; Last Revision: Jul 8 2004
;
;

.if .isndef __P10F206_INC
.define __P10F206_INC

.if .isndef __P10F206
	.warn Select device __P10F206 first
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
.define CWUF                 = 0x6
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

.endif
