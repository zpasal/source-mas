;-----------------------------------------------------------------------
;
; p14000.inc
;
; This is standard include file for P14000 device. Before including this
; file, chose P14000 device with .device or with command switch.
;
; Copyright 2004 by Pasalic Zaharije
;

;
; This file is generated with 'minc2inc' program.
;
; Last Revision: Jun 27 2004
;
;

.if .isndef __P14000_INC
.define __P14000_INC

.if .isndef __P14000
	.warn Select device __P14000 first
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
.define PORTC                = 0x7
.define PORTD                = 0x8
.define PCLATH               = 0xA
.define INTCON               = 0xB
.define PIR1                 = 0xC
.define ADTMRL               = 0xE
.define ADTMRH               = 0xF
.define I2CBUF               = 0x13
.define I2CCON               = 0x14
.define ADCAPL               = 0x15
.define ADCAPH               = 0x16
.define ADCON0               = 0x1F
.define OPTION_REG           = 0x81
.define TRISA                = 0x85
.define TRISC                = 0x87
.define TRISD                = 0x88
.define PIE1                 = 0x8C
.define PCON                 = 0x8E
.define SLPCON               = 0x8F
.define I2CADD               = 0x93
.define I2CSTAT              = 0x94
.define LDACA                = 0x9B
.define PREFA                = 0x9B
.define LDACB                = 0x9C
.define PREFB                = 0x9C
.define CHGCON               = 0x9D
.define CMCON                = 0x9D
.define MISC                 = 0x9E
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

;----- INTCON Bits --------------------------------------------------------

.define GIE                  = 0x7
.define PEIE                 = 0x6
.define T0IE                 = 0x5
.define T0IF                 = 0x2

;----- PIR1 Bits ----------------------------------------------------------

.define WUIF                 = 0x7
.define CMIF                 = 0x7
.define PBIF                 = 0x4
.define I2CIF                = 0x3
.define RCIF                 = 0x2
.define ADCIF                = 0x1
.define OVFIF                = 0x0

;----- I2CCON Bits --------------------------------------------------------

.define WCOL                 = 0x7
.define I2COV                = 0x6
.define I2CEN                = 0x5
.define CKP                  = 0x4
.define I2CM3                = 0x3
.define I2CM2                = 0x2
.define I2CM1                = 0x1
.define I2CM0                = 0x0

;----- ADCON0 Bits --------------------------------------------------------

.define ADCS3                = 0x7
.define ADCS2                = 0x6
.define ADCS1                = 0x5
.define ADCS0                = 0x4
.define AMUXOE               = 0x2
.define ADRST                = 0x1
.define ADZERO               = 0x0

;----- OPTION Bits --------------------------------------------------------

.define NOT_RCPU             = 0x7
.define T0CS                 = 0x5
.define T0SE                 = 0x4
.define PSA                  = 0x3
.define PS2                  = 0x2
.define PS1                  = 0x1
.define PS0                  = 0x0

;---- PIE1 Bits ----------------------------------------------------------

.define WUIE                 = 0x7
.define CMIE                 = 0x7
.define PBIE                 = 0x4
.define I2CIE                = 0x3
.define RCIE                 = 0x2
.define ADCIE                = 0x1
.define OVFIE                = 0x0

;----- PCON Bits ----------------------------------------------------------

.define NOT_POR              = 0x1
.define NOT_LVD              = 0x0

;----- SLPCON -------------------------------------------------------------

.define HIBEN                = 0x7
.define REFOFF               = 0x5
.define BIASOFF              = 0x4
.define LSOFF                = 0x4
.define OSCOFF               = 0x3
.define CWUOFF               = 0x2
.define CMOFF                = 0x2
.define TEMPOFF              = 0x1
.define ADOFF                = 0x0

;----- I2CSTAT Bits -------------------------------------------------------

.define D                    = 0x5
.define I2C_DATA             = 0x5
.define NOT_A                = 0x5
.define NOT_ADDRESS          = 0x5
.define D_A                  = 0x5
.define DATA_ADDRESS         = 0x5
.define P                    = 0x4
.define I2C_STOP             = 0x4
.define S                    = 0x3
.define I2C_START            = 0x3
.define R                    = 0x2
.define I2C_READ             = 0x2
.define NOT_W                = 0x2
.define NOT_WRITE            = 0x2
.define R_W                  = 0x2
.define READ_WRITE           = 0x2
.define UA                   = 0x1
.define BF                   = 0x0

;----- CMCON --------------------------------------------------------------

.define CCOMPB               = 0x6
.define CMBOUT               = 0x6
.define CCBEN                = 0x5
.define CMBOE                = 0x5
.define CPOLB                = 0x4
.define CCOMPA               = 0x2
.define CMAOUT               = 0x2
.define CCAEN                = 0x1
.define CMAOE                = 0x1
.define CPOLA                = 0x0

;----- MISC Bits ----------------------------------------------------------

.define SMHOG                = 0x7
.define SPGNDB               = 0x6
.define SPGNDA               = 0x5
.define I2CSEL               = 0x4
.define SMBUS                = 0x3
.define INCLKEN              = 0x2
.define OSC2                 = 0x1
.define OSC1                 = 0x0

;----- ADCON1 Bits --------------------------------------------------------

.define ADDAC3               = 0x7
.define ADDAC2               = 0x6
.define ADDAC1               = 0x5
.define ADDAC0               = 0x4
.define ACFG3                = 0x3
.define PCFG3                = 0x3
.define ACFG2                = 0x2
.define PCFG2                = 0x2
.define ACFG1                = 0x1
.define ACFG1                = 0x1
.define ACFG0                = 0x0
.define ACFG0                = 0x0
.define _CPC_ON              = 0x1E7F
.define _CPC_OFF             = 0x3FFF
.define _CPU_ON              = 0x2DDF
.define _CPU_OFF             = 0x3FFF
.define _CPP_ON              = 0x33EF
.define _CPP_OFF             = 0x3FFF
.define _PWRTE_ON            = 0x3FF7
.define _PWRTE_OFF           = 0x3FFF
.define _WDT_ON              = 0x3FFF
.define _WDT_OFF             = 0x3FFB
.define _FOSC_HS             = 0x3FFE
.define _FOSC_RC             = 0x3FFF

.endif