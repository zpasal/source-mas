;-----------------------------------------------------------------------
;
; p12ce673.inc
;
; This is standard include file for P12CE673 device. Before including this
; file, chose P12CE673 device with .device or with command switch.
;
; Copyright 2004 by Pasalic Zaharije
;

;
; This file is generated with 'minc2inc' program.
;
; Last Revision: Jun 27 2004
;
;

.if .isndef __P12CE673_INC
.define __P12CE673_INC

.if .isndef __P12CE673
	.warn Select device __P12CE673 first
.endif

.define W                    = 0x0
.define F                    = 0x1

;----- Register Files------------------------------------------------------

.define INDF                 = 0x0
.define TMR0                 = 0x1
.define PCL                  = 0x2
.define STATUS               = 0x3
.define FSR                  = 0x4
.define GPIO                 = 0x5
.define PCLATH               = 0xA
.define INTCON               = 0xB
.define PIR1                 = 0xC
.define ADRES                = 0x1E
.define ADCON0               = 0x1F
.define OPTION_REG           = 0x81
.define TRISIO               = 0x85
.define PIE1                 = 0x8C
.define PCON                 = 0x8E
.define OSCCAL               = 0x8F
.define ADCON1               = 0x9F

;----- STATUS Bits --------------------------------------------------------

.define IRP                  = 0x7
.define RP1                  = 0x6
.define RP0                  = 0x5
.define NOT_TO               = 0x4
.define NOT_PD               = 0x3
.define Z                    = 0x2
.define DC                   = 0x1
.define C                    = 0x0

;----- ADCON0 Bits --------------------------------------------------------

.define ADCS1                = 0x7
.define ADCS0                = 0x6
.define CHS1                 = 0x4
.define CHS0                 = 0x3
.define GO                   = 0x2
.define NOT_DONE             = 0x2
.define GO_DONE              = 0x2
.define ADON                 = 0x0

;----- INTCON Bits --------------------------------------------------------

.define GIE                  = 0x7
.define PEIE                 = 0x6
.define T0IE                 = 0x5
.define INTE                 = 0x4
.define GPIE                 = 0x3
.define T0IF                 = 0x2
.define INTF                 = 0x1
.define GPIF                 = 0x0

;----- PIR1 Bits ----------------------------------------------------------

.define ADIF                 = 0x6

;----- OPTION Bits --------------------------------------------------------

.define NOT_GPPU             = 0x7
.define INTEDG               = 0x6
.define T0CS                 = 0x5
.define T0SE                 = 0x4
.define PSA                  = 0x3
.define PS2                  = 0x2
.define PS1                  = 0x1
.define PS0                  = 0x0

;----- PIE1 Bits ----------------------------------------------------------

.define ADIE                 = 0x6

;----- PCON Bits ----------------------------------------------------------

.define NOT_POR              = 0x1

;----- OSCCAL Bits --------------------------------------------------------

.define CAL3                 = 0x7
.define CAL2                 = 0x6
.define CAL1                 = 0x5
.define CAL0                 = 0x4
.define CALFST               = 0x3
.define CALSLW               = 0x2

;----- ADCON1 Bits --------------------------------------------------------

.define PCFG2                = 0x2
.define PCFG1                = 0x1
.define PCFG0                = 0x0
.define _MCLRE_ON            = 0x3FFF
.define _MCLRE_OFF           = 0x3F7F
.define _CP_ALL              = 0x9F
.define _CP_75               = 0x15BF
.define _CP_50               = 0x2ADF
.define _CP_OFF              = 0x3FFF
.define _PWRTE_OFF           = 0x3FFF
.define _PWRTE_ON            = 0x3FEF
.define _WDT_ON              = 0x3FFF
.define _WDT_OFF             = 0x3FF7
.define _LP_OSC              = 0x3FF8
.define _XT_OSC              = 0x3FF9
.define _HS_OSC              = 0x3FFA
.define _INTRC_OSC           = 0x3FFC
.define _INTRC_OSC_NOCLKOUT  = 0x3FFC
.define _INTRC_OSC_CLKOUT    = 0x3FFD
.define _EXTRC_OSC           = 0x3FFE
.define _EXTRC_OSC_NOCLKOUT  = 0x3FFE
.define _EXTRC_OSC_CLKOUT    = 0x3FFF

.endif