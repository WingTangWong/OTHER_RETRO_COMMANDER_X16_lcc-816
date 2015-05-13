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
			"\t" "lda %0\n"
			"\t" "sta %c\n"
		);
		return;
	}

	EMIT(
		"\t" "lda %0\n"
		"\t" "and #$ff\n"
		"\t" "bit #$80\n"
		"\t" "beq @ok\n"

		"\t" "ora #$ff00\n"

		"@ok\n"
		"\t" "sta %c\n"
	);

}

static void zero_extend_16(Node p, Node *kids, short *nts) {

	int size = opsize(p->x.kids[0]->op);

	if (size >= 2) {
		EMIT(
			"\t" "lda %0\n"
			"\t" "sta %c\n"
		);
		return;
	}

	EMIT(
		"\t" "lda %0\n"
		"\t" "and #$ff\n"
		"\t" "sta %c\n"
	);

}


static void sign_extend_32(Node p, Node *kids, short *nts, unsigned size) {

	if (!size) size = opsize(p->x.kids[0]->op);
	
	if (size >= 4) {
		EMIT(
			"\t" "lda %0\n"
			"\t" "ldx %0+2\n"
			"\t" "sta %c\n"
			"\t" "stx %c+2\n"
		);
		return;	
	}

	if (size == 1) {
		EMIT(
			"\t" "lda %0\n"
			"\t" "ldx #0\n"
			"\t" "and #$ff\n"
			"\t" "bit #$80\n"
			"\t" "beq @ok\n"

			"\t" "ora #$ff00\n"
			"\t" "dex\n"

			"@ok\n"
			"\t" "sta %c\n"
			"\t" "stx %c+2\n"
		);
		return;
	}

	if (size == 2) {
		EMIT(
			"\t" "lda %0\n"
			"\t" "ldx #0\n"
			"\t" "bit #$8000\n"
			"\t" "beq @ok\n"

			"\t" "dex\n"

			"@ok\n"
			"\t" "sta %c\n"
			"\t" "stx %c+2\n"
		);
		return;
	}

	assert("invalid size");

}

static void zero_extend_32(Node p, Node *kids, short *nts, unsigned size) {

	if (!size) size = opsize(p->x.kids[0]->op);
	
	if (size >= 4) {
		EMIT(
			"\t" "lda %0\n"
			"\t" "ldx %0+2\n"
			"\t" "sta %c\n"
			"\t" "stx %c+2\n"
		);
	}

	if (size == 1) {
		EMIT(
			"\t" "lda %0\n"
			"\t" "and #$ff\n"
			"\t" "sta %c\n"
			"\t" "stz %c+2\n"
		);
		return;
	}

	if (size == 2) {
		EMIT(
			"\t" "lda %0\n"
			"\t" "sta %c\n"
			"\t" "stz %c+2\n"
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