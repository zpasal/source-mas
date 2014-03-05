        .device p16c84
start:

.if (.isdef a) | (.isdef b)
.warn OK
.else
.warn NOK
.endif
