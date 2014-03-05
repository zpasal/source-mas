;-----------------------------------------------------------------------
;
; p10f204.inc
;
; This is standard include file for P10F204 device. Before including this
; file, chose P10F204 device with .device or with command switch.
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
; Last Revision: Jul 8 2004
;
;

.if .isndef __P10F204_INC
.define __P10F204_INC

.if .isndef __P10F204
	.warn Select device __P10F204 first
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
