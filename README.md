SOURCE-MAS
==========

Source-mas is generic assembler for PICxxx family of microcontrollers that can generate code 
for more than 90 different icrocontrollers.

## NOTE!!!

This is resurected project from 2004. Originaly it was under GPL but I changed it to MIT license. If you
wanna to continue using GPL license please visit http://sourceforge.net/projects/mas-pic16c84/ or send me email.


## FEATURES

* about 90 microcont. and eeprom8/16 supported
* 2 pass assembly
* conditional assembly
* simple, but powerful macros
* different file formats for output
* easy configuration for another PICxxx families (generic assembler devices)
* compilation speed
* standard include files that can save some time while programming
* highly portable across platforms that supports C++
* MIT license

## Supported devices

Currently there is support for about 90 microcontrollers. Every device is described by configuration files
inside device/ folder. More devices can be easily added.


### Family - PIC10xxx

* 10F200
* 10F202
* 10F204
* 10F206

### Familiy - PIC12xxx

* 12C508
* 12C672
* 12C508A
* 12CE518
* 12C509
* 12CE519
* 12C509A
* 12CE673
* 12C671
* 12CE674

### Family - PIC16xxx

* 16C432
* 16C57
* 16C62A
* 16C66 
* 16C73A
* 16CE623
* 16F83
* 16C505 
* 16C57C
* 16C62B
* 16C662
* 16C73B 
* 16CE624
* 16F84
* 16C554
* 16C58A 
* 16C63
* 16C67
* 16C74
* 16CE625
* 16C558
* 16C58B
* 16C63A
* 16C71 
* 16C74A
* 16CR62
* 16C558A
* 16C620 
* 16C64
* 16C710
* 16C74B
* 16CR63
* 16C54
* 16C620A
* 16C642
* 16C711 
* 16C76
* 16CR64
* 16C54A
* 16C621 
* 16C64A
* 16C715
* 16C77
* 16CR65
* 16C55
* 16C621A
* 16C65
* 16C72 
* 16C84
* 16CR72
* 16C56
* 16C622 
* 16C65A
* 16C72A
* 16C923
* 16CR83
* 16C56A
* 16C622A
* 16C65B
* 16C73 
* 16C924 
* 16CR84

### Family - PIC17xxx

* 17C42
* 17C752
* 17C766
* 17C42A 
* 17C756
* 17CR42
* 17C43
* 17C756A 
* 17CR43
* 17C44
* 17C762

### Misc

* P14000
* EEPROM8  (8bit eeprom)
* EEPROM16 (16bit eeprom)

In all mas can generate code for exactly 90 different devices from PICxxx family of microcontrollers.