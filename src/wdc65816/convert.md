# conversion
#pragma mark - to int

# CVI -> convert from signed integer
# CVU -> convert from unsigned integer
# CVP -> convert from pointer
# CVF -> convert from float


%{

static void sign_extend_16(Node p, Node *kids, short *nts) {
	int size = opsize(p->x.kids[0]->op);

	if (size >= 2) {
		EMIT(
			_("lda %0")
			_("sta %c")
		);
		return;
	}

	EMIT(
		_("lda %0")
		_("and #$ff")
		_("bit #$80")
		_("beq @ok")

		_("ora #$ff00")

		__("@ok")
		_("sta %c")
	);

}

static void zero_extend_16(Node p, Node *kids, short *nts) {

	int size = opsize(p->x.kids[0]->op);

	if (size >= 2) {
		EMIT(
			_("lda %0")
			_("sta %c")
		);
		return;
	}

	EMIT(
		_("lda %0")
		_("and #$ff")
		_("sta %c")
	);

}


static void sign_extend_32(Node p, Node *kids, short *nts, unsigned size) {

	if (!size) size = opsize(p->x.kids[0]->op);
	
	if (size >= 4) {
		EMIT(
			_("lda %0")
			_("ldx %0+2")
			_("sta %c")
			_("stx %c+2")
		);
		return;	
	}

	if (size == 1) {
		EMIT(
			_("lda %0")
			_("ldx #0")
			_("and #$ff")
			_("bit #$80")
			_("beq @ok")

			_("ora #$ff00")
			_("dex")

			__("@ok")
			_("sta %c")
			_("stx %c+2")
		);
		return;
	}

	if (size == 2) {
		EMIT(
			_("lda %0")
			_("ldx #0")
			_("cmp #0")
			_("__bpl @ok")

			_("dex")

			__("@ok")
			_("sta %c")
			_("stx %c+2")
		);
		return;
	}

	assert("invalid size");

}

static void zero_extend_32(Node p, Node *kids, short *nts, unsigned size) {

	if (!size) size = opsize(p->x.kids[0]->op);
	
	if (size >= 4) {
		EMIT(
			_("lda %0")
			_("ldx %0+2")
			_("sta %c")
			_("stx %c+2")
		);
	}

	if (size == 1) {
		EMIT(
			_("lda %0")
			_("and #$ff")
			_("sta %c")
			_("stz %c+2")
		);
		return;
	}

	if (size == 2) {
		EMIT(
			_("lda %0")
			_("sta %c")
			_("stz %c+2")
		);
		return;
	}

	assert("invalid size");
}

%}

# INDIRI1(vregp)
reg: CVII2(reg) ^{
	sign_extend_16(p, kids, nts);
} 6

# INDIRU1(vregp)
reg: CVIU2(reg) ^{
	sign_extend_16(p, kids, nts);
} 6

# INDIRU1(vregp)
reg: CVUI2(reg) ^{
	zero_extend_16(p, kids, nts);
} 3

# INDIRI1(vregp)
reg: CVUU2(reg) ^{
	zero_extend_16(p, kids, nts);
} 3

#pragma mark - to long

# INDIRI2(vregp)
reg: CVII4(reg) ^{
	sign_extend_32(p, kids, nts, 0);
} 7

reg: CVIU4(reg) ^{
	sign_extend_32(p, kids, nts, 0);
} 7

reg: CVUI4(reg) ^{
	zero_extend_32(p, kids, nts, 0);
} 4

reg: CVUU4(reg) ^{
	zero_extend_32(p, kids, nts, 0);
} 4



# uint32_t = uint8_t
reg: CVIU4(CVUI2(INDIRU1(vregp))) ^{
	zero_extend_32(p, kids, nts, 1);
} 4

# int32_t = int8_t
reg: CVII4(CVII2(INDIRI1(vregp))) ^{
	sign_extend_32(p, kids, nts, 1);
} 7


reg: CVII4(CVUI2(INDIRU1(vregp))) ^{
	zero_extend_32(p, kids, nts, 1);
} 4


#
# int bleh[] = {..}
# int n
# bleh[n]
reg: CVII4(LSHI2(INDIRI2(vregp), const_1)) {
        ldx #0
        lda %0
        asl 
        bcc @ok
        dex
@ok
        sta %c
        stx %c+2
} 8



