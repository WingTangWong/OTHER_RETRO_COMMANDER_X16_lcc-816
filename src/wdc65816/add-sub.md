#pragma mark - add / subtract

reg: ADDU2(rc, rc) {
    lda %0
    clc
    adc %1
    sta %c
} 4+1

reg: ADDI2(rc, rc) {
    lda %0
    clc
    adc %1
    sta %c
} 4+1


reg: ADDU2(rc, const_1) {
    lda %0
    inc
    sta %c
} 3

reg: ADDI2(rc, const_1) {
    lda %0
    inc
    sta %c
} 3

reg: ADDU2(rc, const_2) {
    lda %0
    inc
    inc
    sta %c
} 4

reg: ADDI2(rc, const_2) {
    lda %0
    inc
    inc
    sta %c
} 4

# add, or, and, eor - should prefer
# lda dp
# and #constant
# vs
# lda #constant
# and dp
# since it will make peephole optimizations easier.
# simplify() moves a constant to the right child.

reg: ADDU2(reg, const_1) {
    inc %0
} rmw(a, 1)

reg: ADDI2(reg, const_1) {
    inc %0
} rmw(a, 1)

reg: ADDU2(reg, const_2) {
    inc %0
    inc %0
} rmw(a, 2)

reg: ADDI2(reg, const_2) {
    inc %0
    inc %0
} rmw(a, 2)

reg: SUBU2(reg, const_1) {
    dec %0
} rmw(a, 1)

reg: SUBI2(reg, const_1) {
    dec %0
} rmw(a, 1)

reg: SUBU2(reg, const_2) {
    dec %0
    dec %0
} rmw(a, 2)

reg: SUBI2(reg, const_2) {
    dec %0
    dec %0
} rmw(a, 2)


reg: SUBU2(rc, rc) {
    lda %0
    sec
    sbc %1
    sta %c
} 4

reg: SUBI2(rc, rc) {
    lda %0
    sec
    sbc %1
    sta %c
} 4

reg: SUBU2(rc, const_1) {
    lda %0
    dec
    sta %c
} 3

reg: SUBI2(rc, const_1) {
    lda %0
    dec
    sta %c
} 3



# pointer math.


reg: ADDP4(reg, const) {
    lda %0
    clc
    adc #%1
    sta %c
    lda %0+2
    adc #^%1
    sta %c+2
} 7

reg: ADDP4(reg, reg) {
    lda %0
    clc
    adc %1
    sta %c
    lda %0+2
    adc %1+2
    sta %c+2
} 7


reg: ADDP4(reg, address) {
    lda %0
    clc
    adc #%1
    sta %c
    lda %0+2
    adc #^%1
    sta %c+2
} 7


reg: ADDI4(reg, const) {
    lda %0
    clc
    adc #%1
    sta %c
    lda %0+2
    adc #^%1
    sta %c+2
} 7

reg: ADDI4(reg, reg) {
    lda %0
    clc
    adc %1
    sta %c
    lda %0+2
    adc %1+2
    sta %c+2
} 7


reg: ADDI4(reg, address) {
    lda %0
    clc
    adc #%1
    sta %c
    lda %0+2
    adc #^%1
    sta %c+2
} 7


reg: ADDU4(reg, const) {
    lda %0
    clc
    adc #%1
    sta %c
    lda %0+2
    adc #^%1
    sta %c+2
} 7

reg: ADDU4(reg, reg) {
    lda %0
    clc
    adc %1
    sta %c
    lda %0+2
    adc %1+2
    sta %c+2
} 7


reg: ADDU4(reg, address) {
    lda %0
    clc
    adc #%1
    sta %c
    lda %0+2
    adc #^%1
    sta %c+2
} 7



# combine the conversion and the addition.
reg: ADDP4(CVUU4(INDIRU2(vregp)), INDIRP4(vregp)) {
    lda %0
    clc
    adc %1
    sta %c
    lda #0
    adc %1+2
    sta %c+2
} 7

reg: ADDP4(CVUU4(INDIRU2(vregp)), address) {
    lda %0
    clc
    adc #%1
    sta %c
    lda #0
    adc #^%1
    sta %c+2
} 7


reg: ADDP4(CVII4(INDIRI2(vregp)), INDIRP4(vregp)) {
    ldx #0
    lda %0
    cmp #0
    bpl @ok
    dex
@ok
    clc
    adc %1
    sta %c
    txa
    adc %1+2
    sta %c+2
} 11



reg: ADDP4(CVII4(const_negative), reg) {
    lda %1
    clc
    adc #%0
    sta %c
    lda %1+2
    adc #-1
    sta %c+2
} 7


# combine shift and add
# int address[] = {...}
# int n;
# address[n]
reg: ADDP4(CVII4(LSHI2(INDIRI2(vregp), const_1)), address) {
    ldx #0
    lda %0
    asl
    bcc @ok
    dex
    clc
@ok
    adc #%2
    sta %c
    txa
    adc #^%2
    sta %c+2
} 11



reg: ADDI4(reg, const) {
    lda %0
    clc
    adc #%1
    sta %c
    lda %0+2
    adc #^%1
    sta %c+2
} 7

reg: ADDI4(reg, reg) {
    lda %0
    clc
    adc %1
    sta %c
    lda %0+2
    adc %1+2
    sta %c+2
} 7


reg: ADDI4(reg, address) {
    lda %0
    clc
    adc #%1
    sta %c
    lda %0+2
    adc #^%1
    sta %c+2
} 7
