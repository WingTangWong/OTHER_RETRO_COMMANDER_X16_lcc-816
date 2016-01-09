#pragma mark indirection
# need flag for short/long addressing...

reg: INDIRU2(address_with_modifier) {
	lda %0
	sta %c
} 2

reg: INDIRI2(address_with_modifier) {
    lda %0
    sta %c
} 2


reg: INDIRU4(address_with_modifier) {
    lda %0
    ldx %0+2
    sta %c
    stx %c+2
} 4

reg: INDIRI4(address_with_modifier) {
    lda %0
    ldx %0+2
    sta %c
    stx %c+2
} 4

reg: INDIRP4(address_with_modifier) {
    lda %0
    ldx %0+2
    sta %c
    stx %c+2
} 4


#reg: INDIRU2(address) {
#    lda >%0
#    sta %c
#} 3

#reg: INDIRI2(address) {
#    lda >%0
#    sta %c
#} 3


#reg: INDIRU2(addressDP) {
#    lda <%0
#    sta %c
#} 2

#reg: INDIRI2(addressDP) {
#    lda <%0
#    sta %c
#} 2

# *(unsigned *)0x123456

# reg: INDIRU2(const) {
#     lda >%0
#     sta %c
# } 2# 

# reg: INDIRI2(const) {
#     lda >%0
#     sta %c
# } 2


reg: INDIRU2(reg) {
    lda [%0]
    sta %c
} 2+2

reg: INDIRI2(reg) {
    lda [%0]
    sta %c
} 2+2

reg: INDIRU2(ADDP4(reg, const_16_bit)) {
    ldy #%1
    lda [%0],y
    sta %c
} 3+2

reg: INDIRI2(ADDP4(reg, const_16_bit)) {
    ldy #%1
    lda [%0],y
    sta %c
} 3+2

#pragma mark - 32 bit
# could be %t0 = *%t0, so don't update %c until the end.
reg: INDIRP4(reg) {
    lda [%0]
    tax
    ldy #2
    lda [%0],y
    stx %c
    sta %c+2
} 5

reg: INDIRU4(reg) {
    lda [%0]
    tax
    ldy #2
    lda [%0],y
    stx %c
    sta %c+2
} 5

reg: INDIRI4(reg) {
    lda [%0]
    tax
    ldy #2
    lda [%0],y
    stx %c
    sta %c+2
} 5




# ASGNP4(VREGP(s), INDIRP4(ADDP4(reg, CNSTI4(4))))
reg: INDIRP4(ADDP4(reg, const_16_bit_minus_4)) {
    ldy #%1
    lda [%0],y
    tax
    ldy #%1+2
    lda [%0],y
    stx %c
    sta %c+2
} 6

#pragma mark - 8-bit

reg: INDIRU1(address_with_modifier) {
    sep #$20
    lda %0
    sta %c
    rep #$20
} 4

reg: INDIRI1(address_with_modifier) {
    sep #$20
    lda %0
    sta %c
    rep #$20
} 4


#reg: INDIRU1(const) {
#    sep #$20
#    lda >%0
#    rep #$20
#    sta %c
#} 4+1

#reg: INDIRI1(const) {
#    sep #$20
#    lda >%0
#    rep #$20
#    sta %c
#} 4+1


reg: INDIRU1(reg) {
    sep #$20
    lda [%0]
    rep #$20
    sta %c
} 4

reg: INDIRI1(reg) {
    sep #$20
    lda [%0]
    rep #$20
    sta %c
} 4

reg: INDIRU1(ADDP4(reg, const_16_bit)) {
    ldy #%1
    sep #$20
    lda [%0],y
    rep #$20
    sta %c
} 5

reg: INDIRI1(ADDP4(reg, const_16_bit)) {
    ldy #%1
    sep #$20
    lda [%0],y
    rep #$20
    sta %c
} 5



# static char buffer[]; x = buffer[uint16_t]
# safe regardless of memory model
reg: INDIRU1(ADDP4(CVUU4(INDIRU2(vregp)), address_with_modifier)) {
    ldx %0
    sep #$20
    lda %1,x
    rep #$20
    sta %c
} 5


# could wrap in sep #$30 to use 8-bit x.
# safe regardless of memory model
reg: INDIRU1(ADDP4(CVII4(CVUI2(INDIRU1(vregp))), address_with_modifier)) {
    lda %0
    and #$ff
    tax
    sep #$20
    lda %1,x
    rep #$20
    sta %c 
} 5


#
# small memory model:
# assume all arrays, mallocs, NewHandles, etc are 16-bit addressable.
# for an array, a negative index is treated as undefined, therefore
# always treat as unsigned. (not true for pointers -- cp[-1] is common. )

address: ADDP4(address, const) "%0+%1"
address_with_modifier: ADDP4(address_with_modifier, const) "%0+%1"

# small-memory model read
# int x; __ctype[x+1]
# can't use address_with_modifier -- could include >0xconstant.
reg: INDIRU1(ADDP4(CVII4(INDIRI2(vregp)), address)) {
    ldx %0
    sep #$20
    lda |%1,x
    rep #$20
    sta %c
} short_mm_only(5)

reg: INDIRU1(ADDP4(CVII4(reg), address)) {
    ldx %0
    sep #$20
    lda |%1,x
    rep #$20
    sta %c
} short_mm_only(5)

index_x: CVUU4(INDIRU2(vregp)) {
    ldx %0
} 1

index_x: CVII4(CVUI2(INDIRU1(vregp))) {
    lda %0
    and #$ff
    tax 
} 3

index_x: CVII4(LSHI2(INDIRI2(vregp), const_1)) {
    lda %0
    asl
    tax
} short_mm_only(3)

index_x: CVII4(LSHI2(INDIRI2(vregp), const_2)) {
    lda %0
    asl
    asl
    tax
} short_mm_only(4)

index_x: CVUU4(LSHU2(INDIRU2(vregp), const_1)) {
    lda %0
    asl
    tax
} short_mm_only(3)

index_x: CVUU4(LSHU2(INDIRU2(vregp), const_2)) {
    lda %0
    asl
    tax
} short_mm_only(4)

reg: INDIRU2(ADDP4(index_x, address)) {
    lda |%2,x
    sta %c+2
} short_mm_only(2)

reg: INDIRI2(ADDP4(index_x, address)) {
    lda |%2,x
    sta %c+2
} short_mm_only(2)

