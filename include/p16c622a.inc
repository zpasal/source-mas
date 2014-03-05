;-----------------------------------------------------------------------
;
; p16c622a.inc
;
; This is standard include file for P16C622A device. Before including this
; file, chose P16C622A device with .device or with command switch.
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

.if .isndef __P16C622A_INC
.define __P16C622A_INC

.if .isndef __P16C622A
	.warn Select device __P16C622A first
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
.define PIR1                 = 0xC
.define CMCON                = 0x1F
.define OPTION_REG           = 0x81
.define TRISA                = 0x85
.define TRISB                = 0x86
.define PIE1                 = 0x8C
.define PCON                 = 0x8E
.define VRCON                = 0x9F

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
.define PEIE                 = 0x6
.define T0IE                 = 0x5
.define INTE                 = 0x4
.define RBIE                 = 0x3
.define T0IF                 = 0x2
.define INTF                 = 0x1
.define RBIF                 = 0x0

;----- PIR1 Bits ----------------------------------------------------------

.define CMIF                 = 0x6

;----- CMCON Bits ---------------------------------------------------------

.define C2OUT                = 0x7
.define C1OUT                = 0x6
.define CIS                  = 0x3
.define CM2                  = 0x2
.define CM1                  = 0x1
.define CM0                  = 0x0

;----- OPTION Bits --------------------------------------------------------

.define NOT_RBPU             = 0x7
.define INTEDG               = 0x6
.define T0CS                 = 0x5
.define T0SE                 = 0x4
.define PSA                  = 0x3
.define PS2                  = 0x2
.define PS1                  = 0x1
.define PS0                  = 0x0

;----- PIE1 Bits ----------------------------------------------------------

.define CMIE                 = 0x6

;----- PCON Bits ----------------------------------------------------------

.define NOT_POR              = 0x1
.define NOT_BO               = 0x0
.define NOT_BOR              = 0x0

;----- VRCON Bits ---------------------------------------------------------

.define VREN                 = 0x7
.define VROE                 = 0x6
.define VRR                  = 0x5
.define VR3                  = 0x3
.define VR2                  = 0x2
.define VR1                  = 0x1
.define VR0                  = 0x0
.define _BODEN_ON            = 0x3FFF
.define _BODEN_OFF           = 0x3FBF
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