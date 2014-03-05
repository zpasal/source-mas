;-----------------------------------------------------------------------
;
; P17C756A.INC
;
; This is standard include file for P17C756A device. Before including this
; file, chose P17C756A device with .device or with command switch.
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

.if .isndef __P17C756A_INC
.define __P17C756A_INC

.if .isndef __P17C756A
	.warn Select device __P17C756A first
.endif

.define W                    = 0x0
.define F                    = 0x1
.define BANK0                = 0x0
.define BANK1                = 0x1
.define BANK2                = 0x2
.define BANK3                = 0x3
.define BANK4                = 0x4
.define BANK5                = 0x5
.define BANK6                = 0x6
.define BANK7                = 0x7
.define GPR_BANK0            = 0x0
.define GPR_BANK1            = 0x8
.define GPR_BANK2            = 0x10
.define GPR_BANK3            = 0x18

;----- Register Files -----------------------------------------------------

.define INDF0                = 0x0
.define FSR0                 = 0x1
.define PCL                  = 0x2
.define PCLATH               = 0x3
.define ALUSTA               = 0x4
.define T0STA                = 0x5
.define CPUSTA               = 0x6
.define INTSTA               = 0x7
.define INDF1                = 0x8
.define FSR1                 = 0x9
.define WREG                 = 0xA
.define TMR0L                = 0xB
.define TMR0H                = 0xC
.define TBLPTRL              = 0xD
.define TBLPTRH              = 0xE
.define BSR                  = 0xF

;----- Bank 0 -------------------------------------------------------------

.define PORTA                = 0x10
.define DDRB                 = 0x11
.define PORTB                = 0x12
.define RCSTA                = 0x13
.define RCSTA1               = 0x13
.define RCREG                = 0x14
.define RCREG1               = 0x14
.define TXSTA                = 0x15
.define TXSTA1               = 0x15
.define TXREG                = 0x16
.define TXREG1               = 0x16
.define SPBRG                = 0x17
.define SPBRG1               = 0x17

;----- Bank 1 -------------------------------------------------------------

.define DDRC                 = 0x110
.define PORTC                = 0x111
.define DDRD                 = 0x112
.define PORTD                = 0x113
.define DDRE                 = 0x114
.define PORTE                = 0x115
.define PIR                  = 0x116
.define PIR1                 = 0x116
.define PIE                  = 0x117
.define PIE1                 = 0x117

;----- Bank 2 -------------------------------------------------------------

.define TMR1                 = 0x210
.define TMR2                 = 0x211
.define TMR3L                = 0x212
.define TMR3H                = 0x213
.define PR1                  = 0x214
.define PR2                  = 0x215
.define PR3L                 = 0x216
.define PR3H                 = 0x217
.define CA1L                 = 0x216
.define CA1H                 = 0x217

;----- Bank 3 -------------------------------------------------------------

.define PW1DCL               = 0x310
.define PW2DCL               = 0x311
.define PW1DCH               = 0x312
.define PW2DCH               = 0x313
.define CA2L                 = 0x314
.define CA2H                 = 0x315
.define TCON1                = 0x316
.define TCON2                = 0x317

;----- Bank 4 -------------------------------------------------------------

.define PIR2                 = 0x410
.define PIE2                 = 0x411
.define RCSTA2               = 0x413
.define RCREG2               = 0x414
.define TXSTA2               = 0x415
.define TXREG2               = 0x416
.define SPBRG2               = 0x417

;----- Bank 5 -------------------------------------------------------------

.define DDRF                 = 0x510
.define PORTF                = 0x511
.define DDRG                 = 0x512
.define PORTG                = 0x513
.define ADCON0               = 0x514
.define ADCON1               = 0x515
.define ADRESL               = 0x516
.define ADRESH               = 0x517

;----- Bank 6 -------------------------------------------------------------

.define SSPADD               = 0x610
.define SSPCON1              = 0x611
.define SSPCON2              = 0x612
.define SSPSTAT              = 0x613
.define SSPBUF               = 0x614

;----- Bank 7 -------------------------------------------------------------

.define PW3DCL               = 0x710
.define PW3DCH               = 0x711
.define CA3L                 = 0x712
.define CA3H                 = 0x713
.define CA4L                 = 0x714
.define CA4H                 = 0x715
.define TCON3                = 0x716

;----- Unbanked -----------------------------------------------------------

.define PRODL                = 0x18
.define PL                   = 0x18
.define PRODH                = 0x19
.define PH                   = 0x19

;----- Special Function Register Bit Definitions --------------------------


;----- ALUSTA Bits --------------------------------------------------------

.define FS3                  = 0x7
.define FS2                  = 0x6
.define FS1                  = 0x5
.define FS0                  = 0x4
.define OV                   = 0x3
.define Z                    = 0x2
.define DC                   = 0x1
.define C                    = 0x0

;----- CPUSTA Bits --------------------------------------------------------

.define STKAV                = 0x5
.define GLINTD               = 0x4
.define NOT_TO               = 0x3
.define TO                   = 0x3
.define NOT_PD               = 0x2
.define PD                   = 0x2
.define NOT_POR              = 0x1
.define POR                  = 0x1
.define NOT_BOR              = 0x0
.define BOR                  = 0x0

;----- INTSTA Bits --------------------------------------------------------

.define PEIF                 = 0x7
.define T0CKIF               = 0x6
.define T0IF                 = 0x5
.define INTF                 = 0x4
.define PEIE                 = 0x3
.define T0CKIE               = 0x2
.define T0IE                 = 0x1
.define INTE                 = 0x0

;----- PIR1 Bits ----------------------------------------------------------

.define RBIF                 = 0x7
.define TMR3IF               = 0x6
.define TMR2IF               = 0x5
.define TMR1IF               = 0x4
.define CA2IF                = 0x3
.define CA1IF                = 0x2
.define TXIF                 = 0x1
.define TX1IF                = 0x1
.define RCIF                 = 0x0
.define RC1IF                = 0x0

;----- PIE1 Bits -----------------------------------------------------------

.define RBIE                 = 0x7
.define TMR3IE               = 0x6
.define TMR2IE               = 0x5
.define TMR1IE               = 0x4
.define CA2IE                = 0x3
.define CA1IE                = 0x2
.define TXIE                 = 0x1
.define TX1IE                = 0x1
.define RCIE                 = 0x0
.define RC1IE                = 0x0

;----- PORTA Bits ---------------------------------------------------------

.define NOT_RBPU             = 0x7
.define RBPU                 = 0x7

;----- RCSTA1 and 2 Bits --------------------------------------------------

.define SPEN                 = 0x7
.define RX9                  = 0x6
.define RC9                  = 0x6
.define NOT_RC8              = 0x6
.define RC8_9                = 0x6
.define SREN                 = 0x5
.define CREN                 = 0x4
.define FERR                 = 0x2
.define OERR                 = 0x1
.define RX9D                 = 0x0
.define RCD8                 = 0x0

;----- T0STA Bits --------------------------------------------------------

.define INTEDG               = 0x7
.define T0SE                 = 0x6
.define T0CS                 = 0x5
.define T0PS3                = 0x4
.define PS3                  = 0x4
.define T0PS2                = 0x3
.define PS2                  = 0x3
.define T0PS1                = 0x2
.define PS1                  = 0x2
.define T0PS0                = 0x1
.define PS0                  = 0x1

;----- TCON1 Bits ---------------------------------------------------------

.define CA2ED1               = 0x7
.define CA2ED0               = 0x6
.define CA1ED1               = 0x5
.define CA1ED0               = 0x4
.define T16                  = 0x3
.define TMR3CS               = 0x2
.define TMR2CS               = 0x1
.define TMR1CS               = 0x0

;----- TCON2 Bits ---------------------------------------------------------

.define CA2OVF               = 0x7
.define CA1OVF               = 0x6
.define PWM2ON               = 0x5
.define PWM1ON               = 0x4
.define CA1                  = 0x3
.define NOT_PR3              = 0x3
.define PR3                  = 0x3
.define CA1_PR3              = 0x3
.define TMR3ON               = 0x2
.define TMR2ON               = 0x1
.define TMR1ON               = 0x0

;----- PIR2 Bits ----------------------------------------------------------

.define SSPIF                = 0x7
.define BCLIF                = 0x6
.define ADIF                 = 0x5
.define CA4IF                = 0x3
.define CA3IF                = 0x2
.define TX2IF                = 0x1
.define RC2IF                = 0x0

;----- PIE2 Bits ----------------------------------------------------------

.define SSPIE                = 0x7
.define BCLIE                = 0x6
.define ADIE                 = 0x5
.define CA4IE                = 0x3
.define CA3IE                = 0x2
.define TX2IE                = 0x1
.define RC2IE                = 0x0

;----- TXSTA1 and 2 Bits --------------------------------------------------

.define CSRC                 = 0x7
.define TX9                  = 0x6
.define NOT_TX8              = 0x6
.define TX8_9                = 0x6
.define TXEN                 = 0x5
.define SYNC                 = 0x4
.define TRMT                 = 0x1
.define TX9D                 = 0x0
.define TXD8                 = 0x0

;----- ADCON0 Bits --------------------------------------------------------

.define CHS3                 = 0x7
.define CHS2                 = 0x6
.define CHS1                 = 0x5
.define CHS0                 = 0x4
.define GO                   = 0x2
.define NOT_DONE             = 0x2
.define DONE                 = 0x2
.define ADON                 = 0x0

;----- ADCON1 Bits --------------------------------------------------------

.define ADCS1                = 0x7
.define ADCS0                = 0x6
.define ADFM                 = 0x5
.define PCFG3                = 0x3
.define PCFG2                = 0x2
.define PCFG1                = 0x1
.define PCFG0                = 0x0

;----- SSPCON1 Bits -------------------------------------------------------

.define WCOL                 = 0x7
.define SSPOV                = 0x6
.define SSPEN                = 0x5
.define CKP                  = 0x4
.define SSPM3                = 0x3
.define SSPM2                = 0x2
.define SSPM1                = 0x1
.define SSPM0                = 0x0

;----- SSPCON2 Bits -------------------------------------------------------

.define GCEN                 = 0x7
.define ACKSTAT              = 0x6
.define AKSTAT               = 0x6
.define ACKDT                = 0x5
.define AKDT                 = 0x5
.define ACKEN                = 0x4
.define AKEN                 = 0x4
.define RCEN                 = 0x3
.define PEN                  = 0x2
.define RSEN                 = 0x1
.define SEN                  = 0x0

;----- SSPSTAT Bits -------------------------------------------------------

.define SMP                  = 0x7
.define CKE                  = 0x6
.define D                    = 0x5
.define NOT_A                = 0x5
.define D_A                  = 0x5
.define P                    = 0x4
.define S                    = 0x3
.define R                    = 0x2
.define NOT_W                = 0x2
.define R_W                  = 0x2
.define UA                   = 0x1
.define BF                   = 0x0

;----- TCON3 Bits ---------------------------------------------------------

.define CA4OVF               = 0x6
.define CA3OVF               = 0x5
.define CA4ED1               = 0x4
.define CA4ED0               = 0x3
.define CA3ED1               = 0x2
.define CA3ED0               = 0x1
.define PWM3ON               = 0x0

;----- PW2DCL Bit ---------------------------------------------------------

.define TM2PW2               = 0x5

;----- PW3DCL Bit ---------------------------------------------------------

.define TM2PW3               = 0x5
.define _PMC_MODE            = 0x7FAF
.define _XMC_MODE            = 0xFFBF
.define _MC_MODE             = 0xFFEF
.define _MP_MODE             = 0xFFFF
.define _BODEN_OFF           = 0xBFFF
.define _BODEN_ON            = 0xFFFF
.define _WDT_NORM            = 0xFFF3
.define _WDT_OFF             = 0xFFF3
.define _WDT_64              = 0xFFF7
.define _WDT_256             = 0xFFFB
.define _WDT_1               = 0xFFFF
.define _WDT_0               = 0xFFFF
.define _LF_OSC              = 0xFFFC
.define _RC_OSC              = 0xFFFD
.define _XT_OSC              = 0xFFFE
.define _EC_OSC              = 0xFFFF

.endif