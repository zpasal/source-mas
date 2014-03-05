;-----------------------------------------------------------------------
;
; p16c5x.inc
;
; This is standard include file for P16C5x devices:
;
;        PIC16C54
;        PIC16C54A
;        PIC16C55
;        PIC16C56
;        PIC16C56A
;        PIC16C57
;        PIC16C57C
;        PIC16C58A
;        PIC16C58B
;
; Before including this file, chose P16C5X device with
; .device or with command switch.
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
; This file is generated with 'minc2inc' program.
;
; Last Revision: Jun 27 2004
;
;

.if .isndef __P16C5X_INC
.define __P16C5X_INC

.if .isndef __P16C5X
	.warn Select device __P16C5X first
.endif

.define W                    = 0x0
.define F                    = 0x1

;----- Register Files -----------------------------------------------------

.define INDF                 = 0x0
.define TMR0                 = 0x1
.define PCL                  = 0x2
.define STATUS               = 0x3
.define FSR                  = 0x4
.define PORTA                = 0x5
.define PORTB                = 0x6

;----- STATUS Bits --------------------------------------------------------

.define PA2                  = 0x7
.define PA1                  = 0x6
.define PA0                  = 0x5
.define NOT_TO               = 0x4
.define NOT_PD               = 0x3
.define Z                    = 0x2
.define DC                   = 0x1
.define C                    = 0x0

;----- OPTION Bits --------------------------------------------------------

.define T0CS                 = 0x5
.define T0SE                 = 0x4
.define PSA                  = 0x3
.define PS2                  = 0x2
.define PS1                  = 0x1
.define PS0                  = 0x0

;--------------------------------------------------------------------------


;--------------------------------------------------------------------------


;--------------------------------------------------------------------------


;--------------------------------------------------------------------------


;--------------------------------------------------------------------------


;--------------------------------------------------------------------------


;--------------------------------------------------------------------------

.define PORTC                = 0x7

;--------------------------------------------------------------------------


;--------------------------------------------------------------------------


;--------------------------------------------------------------------------


;--------------------------------------------------------------------------

.define PORTC                = 0x7

;--------------------------------------------------------------------------

.define PORTC                = 0x7

;--------------------------------------------------------------------------

.define PORTC                = 0x7

;--------------------------------------------------------------------------


;--------------------------------------------------------------------------


;--------------------------------------------------------------------------


;--------------------------------------------------------------------------

.define _CP_ON               = 0xFF7
.define _CP_OFF              = 0xFFF
.define _WDT_ON              = 0xFFF
.define _WDT_OFF             = 0xFFB
.define _LP_OSC              = 0xFFC
.define _XT_OSC              = 0xFFD
.define _HS_OSC              = 0xFFE
.define _RC_OSC              = 0xFFF
.define _CP_ON               = 0x7
.define _CP_OFF              = 0xFFF
.define _WDT_ON              = 0xFFF
.define _WDT_OFF             = 0xFFB
.define _LP_OSC              = 0xFFC
.define _XT_OSC              = 0xFFD
.define _HS_OSC              = 0xFFE
.define _RC_OSC              = 0xFFF
.define _CP_ON               = 0xFF7
.define _CP_OFF              = 0xFFF
.define _XT_OSC              = 0xFFD
.define _RC_OSC              = 0xFFF

.endif
