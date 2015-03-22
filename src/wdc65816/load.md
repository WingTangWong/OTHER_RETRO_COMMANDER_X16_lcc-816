reg: LOADI2(reg) {
    lda %0
    sta %c
}  move(a) + 1


reg: LOADU2(reg)  {
    lda %0
    sta %c
}  move(a) + 1

reg: LOADI2(const) {
    lda #%0
    sta %c
} 2


reg: LOADU2(const)  {
    lda #%0
    sta %c
} 2


reg: LOADI1(const) {
    sep #$20
    lda #%0
    sta %c
    rep #$20
} 2

reg: LOADU1(const) {
    sep #$20
    lda #%0
    sta %c
    rep #$20
} 4

# todo ...
reg: LOADI1(reg)  {
    sep #$20
    lda %0
    sta %c
    rep #$20
}  move(a) + 3

reg: LOADU1(reg)  {
    sep #$20
    lda %0
    sta %c
    rep #$20
}  move(a) + 3
