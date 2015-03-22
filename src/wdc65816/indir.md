#pragma mark indirection

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


