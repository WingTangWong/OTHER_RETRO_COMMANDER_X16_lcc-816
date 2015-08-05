#
# loads a result into registers A and X.
# Need to be careful, though, so only use for unary ops or if other argument won't clobber it.
#
#


regA: LOADI2(reg) {
	lda %0
} 1

regA: LOADU2(reg) {
	lda %0
} 1


regA: LOADI2(const) {
	lda #%0
} 1

regA: LOADU2(const) {
	lda #%0
} 1

# address ? need to check short/long m...


regAX: vregp {
    tdc
    clc
    adc #%0
    ldx #0
}  4

regAX: LOADI4(reg)  {
    lda %0
    ldx %0+2
}  2

regAX: LOADU4(reg)  {
    lda %0
    ldx %0+2
}  2

regAX: LOADP4(reg)  {
    lda %0
    ldx %0+2
}  2

regAX: LOADI4(vregp)  {
    tdc
    clc
    adc #%0
    ldx #0
}  4

regAX: LOADU4(vregp)  {
    tdc
    clc
    adc #%0
    ldx #0
}  4

regAX: LOADP4(vregp)  {
    tdc
    clc
    adc #%0
    ldx #0
}  4


regAX: LOADI4(const)  {
    lda #%0
    ldx #^%0
}  2

regAX: LOADU4(const)  {
    lda #%0
    ldx #^%0
}  2

regAX: LOADP4(const)  {
    lda #%0
    ldx #^%0
}  2


regAX: address {
	lda #%0
	ldx #^%0
} 2

regAX: reg {
	lda %0
	ldx %0+2
} 2


stmt: ARGI2(regA) {
	pha
} 1

stmt: ARGU2(regA) {
	pha
} 1


stmt: ARGI4(regAX) {
	phx
	pha
} 2

stmt: ARGU4(regAX) {
	phx
	pha
} 2

stmt: ARGP4(regAX) {
	phx
	pha
} 2
