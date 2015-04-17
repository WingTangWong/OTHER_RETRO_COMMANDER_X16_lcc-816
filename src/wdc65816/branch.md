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
    blt %a
    beq %a
} 4

# reversed order
stmt: GTU2(rc, rc) {
    lda %1
    cmp %0
    blt %a
} 3

stmt: LTU2(rc, rc) {
    lda %0
    cmp %1
    blt %a
} 3


# signed - {0--0x7fff} > {0x8000-0xffff}
# 

# http://www.6502.org/tutorials/compare_instructions.html
stmt: LTI2(rc, rc) {
	lda %0
	cmp %1
	bmi %a
} 3

stmt: LEI2(rc, rc) {
	lda %0
	cmp %1
	bmi %a
	beq %a
} 4

stmt: GTI2(rc, rc) {
	lda %0
	cmp %1
	beq @ok
	bpl %a
@ok
} 4

stmt: GEI2(rc, rc) {
	lda %0
	cmp %1
	bpl %a
} 3


