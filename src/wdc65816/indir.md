#pragma mark indirection
# need flag for short/long addressing...

reg: INDIRU2(address) {
	lda |%0
	sta %c
} 2

reg: INDIRI2(address) {
    lda |%0
    sta %c
} 2


reg: INDIRU2(address) {
	lda >%0
	sta %c
} 3

reg: INDIRI2(address) {
    lda >%0
    sta %c
} 3

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



#pragma mark - 8-bit

reg: INDIRU1(address) {
    sep #$20
    lda |%0
    sta %c
    rep #$20
} 4

reg: INDIRI1(address) {
    sep #$20
    lda |%0
    sta %c
    rep #$20
} 4

reg: INDIRU1(address) {
    sep #$20
    lda >%0
    rep #$20
    sta %c
} 4+1

reg: INDIRI1(address) {
    sep #$20
    lda >%0
    rep #$20
    sta %c
} 4+1

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
