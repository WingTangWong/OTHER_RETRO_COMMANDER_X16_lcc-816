#pragma mark - branching

# 
# assembler will extend if branch is too far.
#

stmt: JUMPV(address) {
    bra %0
} 1



#pragma mark - comparison

stmt: EQI2(rc, rc) {
    lda %0
    cmp %1
    beq %a
} 3


stmt: EQU2(rc, rc) {
    lda %0
    cmp %1
    beq %a
} 3

stmt: NEI2(rc, rc) {
    lda %0
    cmp %1
    bne %a
} 3

stmt: NEU2(rc, rc) {
    lda %0
    cmp %1
    bne %a
} 3


stmt: GEU2(rc, rc) {
    lda %0
    cmp %1
    bge %a
} 3

stmt: LEU2(rc, rc) {
    lda %0
    cmp %1
    ble %a
} 4

# reversed order
stmt: GTU2(rc, rc) {
    lda %0
    cmp %1
    bgt %a
} 3

stmt: LTU2(rc, rc) {
    lda %0
    cmp %1
    blt %a
} 3


# signed - {0--0x7fff} > {0x8000-0xffff}
# 

# annotate as lda.cc for optimizer?
# negative numbers are always < const positives.
stmt: LTI2(reg, const_positive) {
    lda %0
    bmi %a
    cmp #%1
    blt %a
} 4

stmt: LEI2(reg, const_positive) {
    lda %0
    bmi %a
    cmp #%1
    ble %a
} 4

stmt: GTI2(reg, const_negative) {
    lda %0
    bpl %a
    cmp #%1
    bgt %a ; macro
} 4

#todo -- incomplete.
# since the comparison is negative numbers, blt is 
# correct.
# $ffff = - 1, $8000 = -32768
# -1 >= -32768
# $ffff >= $8000 
stmt: GEI2(reg, const_negative) {
    lda %0
    bpl %a
    cmp #%1
    bge %a
} 4

# need special macro for these since 
# we dont know the sign of either.
stmt: LTI2(rc, rc) {
    lda %0
    sec
    sbc %1
    blts %a
} 8

stmt: LEI2(rc, rc) {
    lda %0
    sec
    sbc %1
    bles %a
} 8

stmt: GTI2(rc, rc) {
    lda %0
    sec
    sbc %1
    bgts %a
} 8

stmt: GEI2(rc, rc) {
    lda %0
    sec
    sbc %1
    bges %a
} 8
