#pragma mark - branching

# 
# assembler will extend if branch is too far.
#

stmt: JUMPV(address) {
    branch %0
} 1



#pragma mark - comparison

stmt: EQI2(rc, rc) {
    lda %0
    cmp %1
    branch eq, %a
} 3


stmt: EQU2(rc, rc) {
    lda %0
    cmp %1
    branch eq, %a
} 3

stmt: NEI2(rc, rc) {
    lda %0
    cmp %1
    branch ne, %a
} 3

stmt: NEU2(rc, rc) {
    lda %0
    cmp %1
    branch ne, %a
} 4


stmt: GEU2(rc, rc) {
    lda %0
    cmp %1
    branch unsigned ge, %a
} 4

stmt: LEU2(rc, rc) {
    lda %0
    cmp %1
    branch unsigned le, %a
} 4

# reversed order ?
stmt: GTU2(rc, rc) {
    lda %0
    cmp %1
    branch unsigned gt, %a
} 4

stmt: LTU2(rc, rc) {
    lda %0
    cmp %1
    branch unsigned lt, %a
} 4


# signed - {0--0x7fff} > {0x8000-0xffff}
# 

stmt: LTI2(rc, const_positive) {
    lda %0
    cmp #0
    branch mi, %a
    cmp #%1
    branch cc, %a
} 5

stmt: LTI2(rc, const_0) {
    lda %0
    cmp #0
    branch mi, %a
} 3

stmt: LEI2(rc, const_positive) {
    lda %0
    cmp #0
    branch mi, %a
    cmp #%1+1
    branch cc, %a
} 5


# http://www.6502.org/tutorials/compare_instructions.html
stmt: LTI2(rc, rc) {
    lda %0
    sec
    sbc %1
    branch signed lt, %a
} 10



stmt: LEI2(rc, rc) {
    lda %0
    sec
    sbc %1
    branch signed le, %a
} 10

stmt: GTI2(rc, rc) {
    lda %0
    sec
    sbc %1
    branch signed gt, %a
} 10


stmt: GEI2(rc, rc) {
    lda %0
    sec
    sbc %1
    branch signed ge, %a
} 10

stmt: GEI2(rc, const_0) {
    lda %0
    cmp #0
    branch pl, %a
} 3


#pragma mark - 32 bit


stmt: NEU4(reg, reg) {
    lda %0
    cmp %1
    branch ne, %a
    lda %0+2
    cmp %1+2
    branch ne, %a
} 6

stmt: NEI4(reg, reg) {
    lda %0
    cmp %1
    branch ne, %a
    lda %0+2
    cmp %1+2
    branch ne, %a
} 6

stmt: NEU4(reg, const) {
    lda %0
    cmp #%1
    branch ne, %a
    lda %0+2
    cmp #^%1
    branch ne, %a
} 6

stmt: NEI4(reg, const) {
    lda %0
    cmp #%1
    branch ne, %a
    lda %0+2
    cmp #^%1
    branch ne, %a
} 6


stmt: NEU4(LOADU4(INDIRP4(reg)),const_0) {
    ldy #2
    lda [%0]
    ora [%0],y
    cmp #0
    branch ne, %a
} 5

stmt: EQU4(LOADU4(INDIRP4(reg)),const_0) {
    ldy #2
    lda [%0]
    ora [%0],y
    cmp #0
    branch eq, %a
} 5


# let the optimizer remove cmp #0?
stmt: NEU4(reg, const_0) {
    lda %0
    ora %0+2
    cmp #%1
    branch ne, %a
} 4

stmt: NEI4(reg, const_0) {
    lda %0
    ora %0+2
    cmp #%1
    branch ne, %a
} 4


stmt: EQU4(reg, const_0) {
    lda %0
    ora %0+2
    cmp #0
    branch eq, %a
} 4

stmt: EQI4(reg, const_0) {
    lda %0
    ora %0+2
    cmp #0
    branch eq, %a
} 4


stmt: EQU4(reg, const) {
    lda %0
    cmp #%1
    branch ne, @no
    lda %0+2
    cmp #^%1
    branch eq, %a
@no
} 6




