#
# structs and such
#
#

%{
#define struct_size_is(p,x) (p->syms[0] && p->syms[0]->u.c.v.i == x ? 0 : LBURG_MAX)
%}


# *struct = struct
stmt: ASGNB(INDIRP4(vregp),INDIRB(vregp)) {
	; asgnb 
	ldx #0

@loop:
	txy
	lda %1,x
	sta [%0],y
	inx
	inx
	cpx #%a
	bne @loop
} 20


stmt: ASGNB(INDIRP4(vregp),INDIRB(vregp)) {
	lda %1
	sta [%0]
} struct_size_is(a, 2)

stmt: ASGNB(INDIRP4(vregp),INDIRB(vregp)) {
	lda %1
	sta [%0]
	
	lda %1+2
	ldy #2
	sta [%0],y
} struct_size_is(a, 4)

stmt: ASGNB(INDIRP4(vregp),INDIRB(vregp)) {
	lda %1
	sta [%0]

	lda %1+2
	ldy #2
	sta [%0],y

	lda %1+4
	ldy #4
	sta [%0],y
} struct_size_is(a, 6)

stmt: ASGNB(INDIRP4(vregp),INDIRB(vregp)) {
	lda %1
	sta [%0]

	lda %1+2
	ldy #2
	sta [%0],y

	lda %1+4
	ldy #4
	sta [%0],y

	lda %1+6
	ldy #6
	sta [%0],y
} struct_size_is(a, 8)


stmt: ARGB(INDIRB(vregp)) {
	; argb
	ldx #0

@loop:
	lda %0,x
	pha
	inx
	inx
	cpx #%a
	bne @loop
} 20

stmt: ARGB(INDIRB(vregp)) {
	; argb %a
	pei %0
} struct_size_is(a, 2)

stmt: ARGB(INDIRB(vregp)) {
	; argb %a
	pei %0
	pei %0+2
} struct_size_is(a, 4)

stmt: ARGB(INDIRB(vregp)) {
	; argb %a
	pei %0
	pei %0+2
	pei %0+4
} struct_size_is(a, 6)

stmt: ARGB(INDIRB(vregp)) {
	; argb %a
	pei %0
	pei %0+2
	pei %0+4
	pei %0+8
} struct_size_is(a, 8)
