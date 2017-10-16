#
# read-modify-write optimizations.
#
# |absolute and <dp rmw:
# ASL, DEC, INC, LSR, ROL, ROR, TRB, TSB
#
# |absolute,x and <dp,x rmw:
# ASL, DEC, INC, LSR, ROL, ROR

stmt: ASGNU2(address, ADDU2(INDIRU2(address), const_1)) {
    inc |%0
} memop(a, short_mm_only(1))

stmt: ASGNI2(address, ADDI2(INDIRI2(address), const_1)) {
    inc |%0
} memop(a, short_mm_only(1))

stmt: ASGNU2(address, SUBU2(INDIRU2(address), const_1)) {
    dec |%0
} memop(a, short_mm_only(1))

stmt: ASGNI2(address, SUBI2(INDIRI2(address), const_1)) {
    dec |%0
} memop(a, short_mm_only(1))


stmt: ASGNU2(address, LSHU2(INDIRU2(address), const_1)) {
    asl |%0
} memop(a, short_mm_only(1))

stmt: ASGNI2(address, LSHI2(INDIRI2(address), const_1)) {
    asl |%0
} memop(a, short_mm_only(1))


stmt: ASGNU2(address, RSHU2(INDIRU2(address), const_1)) {
    lsr |%0
} memop(a, short_mm_only(1))



stmt: ASGNI2(address, BANDI2(INDIRI2(address), rc)) {
	lda %2
	trb |%0
} memop(a, short_mm_only(2))

stmt: ASGNU2(address, BANDU2(INDIRU2(address), rc)) {
	lda %2
	trb |%0
} memop(a, short_mm_only(2))

stmt: ASGNI2(address, BORI2(INDIRI2(address), rc)) {
	lda %2
	tsb |%0
} memop(a, short_mm_only(2))

stmt: ASGNU2(address, BORU2(INDIRU2(address), rc)) {
	lda %2
	tsb |%0
} memop(a, short_mm_only(2))
