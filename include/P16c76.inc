;-----------------------------------------------------------------------
;
; P16c76.inc
;
; This is standard include file for P16C76 device. Before including this
; file, chose P16C76 device with .device or with command switch.
;
; Copyright 2004 by Pasalic Zaharije
;

;
; This file is generated with 'minc2inc' program.
;
; Last Revision: Jun 27 2004
;
;

.if .isndef __P16C76_INC
.define __P16C76_INC

.if .isndef __P16C76
	.warn Select device __P16C76 first
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
.define PORTC                = 0x7
.define PCLATH               = 0xA
.define INTCON               = 0xB
.define PIR1                 = 0xC
.define PIR2                 = 0xD
.define TMR1L                = 0xE
.define TMR1H                = 0xF
.define T1CON                = 0x10
.define TMR2                 = 0x11
.define T2CON                = 0x12
.define SSPBUF               = 0x13
.define SSPCON               = 0x14
.define CCPR1L               = 0x15
.define CCPR1H               = 0x16
.define CCP1CON              = 0x17
.define RCSTA                = 0x18
.define TXREG                = 0x19
.define RCREG                = 0x1A
.define CCPR2L               = 0x1B
.define CCPR2H               = 0x1C
.define CCP2CON              = 0x1D
.define ADRES                = 0x1E
.define ADCON0               = 0x1F
.define OPTION_REG           = 0x81
.define TRISA                = 0x85
.define TRISB                = 0x86
.define TRISC                = 0x87
.define PIE1                 = 0x8C
.define PIE2                 = 0x8D
.define PCON                 = 0x8E
.define PR2                  = 0x92
.define SSPADD               = 0x93
.define SSPSTAT              = 0x94
.define TXSTA                = 0x98
.define SPBRG                = 0x99
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
.define INTE                 = 0x4
.define RBIE                 = 0x3
.define T0IF                 = 0x2
.define INTF                 = 0x1
.define RBIF                 = 0x0

;----- PIR1 Bits ----------------------------------------------------------

.define ADIF                 = 0x6
.define RCIF                 = 0x5
.define TXIF                 = 0x4
.define SSPIF                = 0x3
.define CCP1IF               = 0x2
.define TMR2IF               = 0x1
.define TMR1IF               = 0x0

;----- PIR2 Bits ----------------------------------------------------------

.define CCP2IF               = 0x0

;----- T1CON Bits ---------------------------------------------------------

.define T1CKPS1              = 0x5
.define T1CKPS0              = 0x4
.define T1OSCEN              = 0x3
.define NOT_T1SYNC           = 0x2
.define T1INSYNC             = 0x2
.define TMR1CS               = 0x1
.define TMR1ON               = 0x0

;----- T2CON Bits ---------------------------------------------------------

.define TOUTPS3              = 0x6
.define TOUTPS2              = 0x5
.define TOUTPS1              = 0x4
.define TOUTPS0              = 0x3
.define TMR2ON               = 0x2
.define T2CKPS1              = 0x1
.define T2CKPS0              = 0x0

;----- SSPCON Bits --------------------------------------------------------

.define WCOL                 = 0x7
.define SSPOV                = 0x6
.define SSPEN                = 0x5
.define CKP                  = 0x4
.define SSPM3                = 0x3
.define SSPM2                = 0x2
.define SSPM1                = 0x1
.define SSPM0                = 0x0

;----- CCP1CON Bits -------------------------------------------------------

.define CCP1X                = 0x5
.define CCP1Y                = 0x4
.define CCP1M3               = 0x3
.define CCP1M2               = 0x2
.define CCP1M1               = 0x1
.define CCP1M0               = 0x0

;----- RCSTA Bits ---------------------------------------------------------

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

;----- CCP2CON Bits -------------------------------------------------------

.define CCP2X                = 0x5
.define CCP2Y                = 0x4
.define CCP2M3               = 0x3
.define CCP2M2               = 0x2
.define CCP2M1               = 0x1
.define CCP2M0               = 0x0

;----- ADCON0 Bits --------------------------------------------------------

.define ADCS1                = 0x7
.define ADCS0                = 0x6
.define CHS2                 = 0x5
.define CHS1                 = 0x4
.define CHS0                 = 0x3
.define GO                   = 0x2
.define NOT_DONE             = 0x2
.define GO_DONE              = 0x2
.define ADON                 = 0x0

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

.define ADIE                 = 0x6
.define RCIE                 = 0x5
.define TXIE                 = 0x4
.define SSPIE                = 0x3
.define CCP1IE               = 0x2
.define TMR2IE               = 0x1
.define TMR1IE               = 0x0

;----- PIE2 Bits ----------------------------------------------------------

.define CCP2IE               = 0x0

;----- PCON Bits ----------------------------------------------------------

.define NOT_POR              = 0x1
.define NOT_BO               = 0x0
.define NOT_BOR              = 0x0

;----- SSPSTAT Bits -------------------------------------------------------

.define SMP                  = 0x7
.define CKE                  = 0x6
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

;----- TXSTA Bits ---------------------------------------------------------

.define CSRC                 = 0x7
.define TX9                  = 0x6
.define NOT_TX8              = 0x6
.define TX8_9                = 0x6
.define TXEN                 = 0x5
.define SYNC                 = 0x4
.define BRGH                 = 0x2
.define TRMT                 = 0x1
.define TX9D                 = 0x0
.define TXD8                 = 0x0

;----- ADCON1 Bits --------------------------------------------------------

.define PCFG2                = 0x2
.define PCFG1                = 0x1
.define PCFG0                = 0x0
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