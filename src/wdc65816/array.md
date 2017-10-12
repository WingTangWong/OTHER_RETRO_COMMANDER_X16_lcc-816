#
# optimizations for array access.
# is_array_address checks for a static array where sizeof() is 16-bit.
# therefore, 16-bit unsigned index access is ok.	
#

%{

static int is_array_address(Node p) {
	Type t = p->syms[0]->type;

	return t && t->op == ARRAY && t->size <= 0xffff ? 1 : LBURG_MAX;
}

static int is_not_array_address(Node p) {
	Type t = p->syms[0]->type;

	return t && t->op == ARRAY && t->size <= 0xffff ? LBURG_MAX : 1;
}

%}

# static array
array_address: ADDRGP4 "%a" is_array_address(a)

# auto array
array_address: VREGP "%a"

#???
#reg_a_index: regA ""

reg_a_index: ADDI2(rc, rc) {
	lda %0
	clc
	adc %1
} 3

reg_a_index: ADDU2(rc, rc) {
	lda %0
	clc
	adc %1
} 3

reg_a_index: CVII4(reg_a_index) "" 0
reg_a_index: CVUI4(reg_a_index) "" 0

reg_a_index: CVII4(INDIRI2(vregp)) {
	lda %0	
} 1

reg_a_index: CVUI4(INDIRU2(vregp)) {
	lda %0	
} 1


reg_a_index: CVII4(CVUI2(INDIRU1(vregp))) {
	lda %0
	and #$ff
} 2

reg_a_index: CVII4(CVUI2(INDIRU1(vregp))) {
	lda %0
	and #$ff
} 2


reg_a_index: CVII4(CVII2(INDIRI1(vregp))) {
	lda %0
	and #$ff
} 2


reg_a_index: LSHI4(reg_a_index, const_1) {
	asl
} 1


reg_a_index: LSHI4(reg_a_index, const_2) {
	asl
	asl
} 2


reg_a_index: LSHI4(reg_a_index, const_3) {
	asl
	asl
	asl
} 3


reg_a_index: LSHI4(reg_a_index, const_4) {
	asl
	asl
	asl
	asl
} 4



reg: INDIRI1(ADDP4(reg_a_index,array_address)) {
	tax
	sep #$20
	lda %1,x
	rep #$20
	sta %c
} 5

reg: INDIRU1(ADDP4(reg_a_index,array_address)) {
	tax
	sep #$20
	lda %1,x
	rep #$20
	sta %c
} 5


reg: INDIRI2(ADDP4(reg_a_index,array_address)) {
	tax
	lda %1,x
	sta %c
} 3

reg: INDIRU2(ADDP4(reg_a_index,array_address)) {
	tax
	lda %1,x
	sta %c
} 3

reg: INDIRI4(ADDP4(reg_a_index,array_address)) {
	tax
	lda %1,x
	sta %c
	lda %1+2,x
	sta %c+2
} 5

reg: INDIRU4(ADDP4(reg_a_index,array_address)) {
	tax
	lda %1,x
	sta %c
	lda %1+2,x
	sta %c+2
} 5

#
# since this is a 16-bit array, negative indexes are undefined/illegal.
# (used when simplify ADD+P was in effect)
#reg: INDIRU1(ADDP4(reg, ADDP4(array_address, const_positive))) {
#	lda %0
#	clc
#	adc #%2
#	tax
#	sep #$20
#	lda %1,x
#	rep #$20
#	sta %c
#} 8

