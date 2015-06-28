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


#pragma mark - 32 bit
# let the optimizer remove cmp #0?
stmt: NEU4(rc, const_0) {
    lda %0
    ora %0+2
    cmp #%1
    __bne %a
} 5

stmt: NEI4(rc, const_0) {
    lda %0
    ora %0+2
    cmp #%1
    __bne %a
} 5


stmt: EQU4(rc, const_0) {
    lda %0
    ora %0+2
    cmp #%1
    __beq %a
} 5

stmt: EQI4(rc, const_0) {
    lda %0
    ora %0+2
    cmp #%1
    __beq %a
} 5
