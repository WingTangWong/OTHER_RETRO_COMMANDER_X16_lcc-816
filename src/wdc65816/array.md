#
# optimizations for array access.
# is_array_address checks for a static array where sizeof() is 16-bit.
# therefore, 16-bit unsigned index access is ok.	
#

%{
static int is_array_address(Node p) {
	Type t = p->syms[0]->type;
	return t->op == ARRAY && t->size <= 0xffff ? 1 : LBURG_MAX;
}
%}

array_address: ADDRGP4 "%a" is_array_address(a)

reg_x: LSHI4(CVII4(INDIRI2(vregp)), const_1) {
	lda %0
	asl
	tax
} 3

reg_x: LSHI4(CVUI4(INDIRU2(vregp)), const_1) {
	lda %0
	asl
	tax
} 3

reg_x: LSHI4(CVII4(INDIRI2(vregp)), const_2) {
	lda %0
	asl
	asl
	tax
} 4

reg_x: LSHI4(CVUI4(INDIRU2(vregp)), const_2) {
	lda %0
	asl
	asl
	tax
} 4

reg_x: LSHI4(CVII4(INDIRI2(vregp)), const_3) {
	lda %0
	asl
	asl
	asl
	tax
} 5

reg_x: LSHI4(CVUI4(INDIRU2(vregp)), const_3) {
	lda %0
	asl
	asl
	asl
	tax
} 5

reg_x: LSHI4(CVII4(INDIRI2(vregp)), const_4) {
	lda %0
	asl
	asl
	asl
	asl
	tax
} 6

reg_x: LSHI4(CVUI4(INDIRU2(vregp)), const_4) {
	lda %0
	asl
	asl
	asl
	asl
	tax
} 6


reg_x: CVII4(reg) {
	ldx %0
} 1

reg: INDIRI2(ADDP4(reg_x,array_address)) {
	lda %1,x
	sta %c
} 2

reg: INDIRU2(ADDP4(reg_x,array_address)) {
	lda %1,x
	sta %c
} 2

reg: INDIRI4(ADDP4(reg_x,array_address)) {
	lda %1,x
	sta %c
	lda %1+2,x
	sta %c+2
} 4

reg: INDIRU4(ADDP4(reg_x,array_address)) {
	lda %1,x
	sta %c
	lda %1+2,x
	sta %c+2
} 2
