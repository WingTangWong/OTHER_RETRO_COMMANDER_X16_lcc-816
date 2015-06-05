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


#reg: INDIRU2(address) {
#    lda >%0
#    sta %c
#} 3

#reg: INDIRI2(address) {
#    lda >%0
#    sta %c
#} 3


reg: INDIRU2(addressDP) {
    lda <%0
    sta %c
} 2

reg: INDIRI2(addressDP) {
    lda <%0
    sta %c
} 2

# *(unsigned *)0x123456

reg: INDIRU2(const) {
    lda >%0
    sta %c
} 2

reg: INDIRI2(const) {
    lda >%0
    sta %c
} 2


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

reg: INDIRP4(reg) {
    lda [%0]
    sta %c
    ldy #2
    lda [%0],y
    sta %c+2
} 5

reg: INDIRU4(reg) {
    lda [%0]
    sta %c
    ldy #2
    lda [%0],y
    sta %c+2
} 5

reg: INDIRI4(reg) {
    lda [%0]
    sta %c
    ldy #2
    lda [%0],y
    sta %c+2
} 5


# ASGNP4(VREGP(s), INDIRP4(ADDP4(reg, CNSTI4(4))))
reg: INDIRP4(ADDP4(reg, const_16_bit_minus_4)) {
    ldy #%1
    lda [%0],y
    sta %c
    ldy #%1+2
    lda [%0],y
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


reg: INDIRU1(const) {
    sep #$20
    lda >%0
    rep #$20
    sta %c
} 4+1

reg: INDIRI1(const) {
    sep #$20
    lda >%0
    rep #$20
    sta %c
} 4+1


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
reg: INDIRU1(ADDP4(CVUU4(INDIRU2(vregp)), address_with_modifier)) {
    ldx %0
    sep #$20
    lda %1,x
    rep #$20
    sta %c
} 5


# could wrap in sep #$30 to use 8-bit x.
reg: INDIRU1(ADDP4(CVII4(CVUI2(INDIRU1(vregp))), address_with_modifier)) {
    lda %0
    and #$ff
    tax
    sep #$20
    lda %1,x
    rep #$20
    sta %c 
} 5
