#pragma mark - branching

# 
# assembler will extend if branch is too far.
#

stmt: JUMPV(address) {
    __bra %0
} 1



#pragma mark - comparison

stmt: EQI2(rc, rc) {
    lda %0
    cmp %1
    __beq %a
} 3


stmt: EQU2(rc, rc) {
    lda %0
    cmp %1
    __beq %a
} 3

stmt: NEI2(rc, rc) {
    lda %0
    cmp %1
    __bne %a
} 3

stmt: NEU2(rc, rc) {
    lda %0
    cmp %1
    __bne %a
} 4


stmt: GEU2(rc, rc) {
    lda %0
    cmp %1
    __buge %a
} 4

stmt: LEU2(rc, rc) {
    lda %0
    cmp %1
    __bule %a
} 4

# reversed order ?
stmt: GTU2(rc, rc) {
    lda %0
    cmp %1
    __bugt %a
} 4

stmt: LTU2(rc, rc) {
    lda %0
    cmp %1
    __bult %a
} 4


# signed - {0--0x7fff} > {0x8000-0xffff}
# 

stmt: LTI2(rc, const_positive) {
    lda %0
    cmp #0
    __bmi %a
    cmp #%1
    __bcc %a
} 5

stmt: LTI2(rc, const_0) {
    lda %0
    cmp #0
    __bmi %a
} 3

stmt: LEI2(rc, const_positive) {
    lda %0
    cmp #0
    __bmi %a
    cmp #%1+1
    __bcc %a
} 5


# http://www.6502.org/tutorials/compare_instructions.html
stmt: LTI2(rc, rc) {
    lda %0
    sec
    sbc %1
    __bslt %a
} 10



stmt: LEI2(rc, rc) {
    lda %0
    sec
    sbc %1
    __bsle %a
} 10

stmt: GTI2(rc, rc) {
    lda %0
    sec
    sbc %1
    __bsgt %a
} 10


stmt: GEI2(rc, rc) {
    lda %0
    sec
    sbc %1
    __bsge %a
} 10

stmt: GEI2(rc, const_0) {
    lda %0
    cmp #0
    __bpl %a
} 3


#pragma mark - 32 bit


stmt: NEU4(reg, reg) {
    lda %0
    cmp %1
    __bne %a
    lda %0+2
    cmp %1+2
    __bne %a
} 6

stmt: NEI4(reg, reg) {
    lda %0
    cmp %1
    __bne %a
    lda %0+2
    cmp %1+2
    __bne %a
} 6

stmt: NEU4(reg, const) {
    lda %0
    cmp #%1
    __bne %a
    lda %0+2
    cmp #^%1
    __bne %a
} 6

stmt: NEI4(reg, const) {
    lda %0
    cmp #%1
    __bne %a
    lda %0+2
    cmp #^%1
    __bne %a
} 6


stmt: NEU4(LOADU4(INDIRP4(reg)),const_0) {
    ldy #2
    lda [%0]
    ora [%0],y
    cmp #0
    __bne %a
} 5

stmt: EQU4(LOADU4(INDIRP4(reg)),const_0) {
    ldy #2
    lda [%0]
    ora [%0],y
    cmp #0
    __beq %a
} 5


# let the optimizer remove cmp #0?
stmt: NEU4(reg, const_0) {
    lda %0
    ora %0+2
    cmp #%1
    __bne %a
} 4

stmt: NEI4(reg, const_0) {
    lda %0
    ora %0+2
    cmp #%1
    __bne %a
} 4


stmt: EQU4(reg, const_0) {
    lda %0
    ora %0+2
    cmp #0
    __beq %a
} 4

stmt: EQI4(reg, const_0) {
    lda %0
    ora %0+2
    cmp #0
    __beq %a
} 4


stmt: EQU4(reg, const) {
    lda %0
    cmp #%1
    __bne @no
    lda %0+2
    cmp #^%1
    __beq %a
@no
} 6




