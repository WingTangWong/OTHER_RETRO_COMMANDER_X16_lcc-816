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

# and #$ff will be optimized out.
reg: LOADI1(const) {
    lda #%0
    ;and #$ff
    sta %c
} 2

reg: LOADU1(const) {
    lda #%0
    ;and #$ff
    sta %c
} 4

# todo ...
reg: LOADI1(reg)  {
    lda %0
    ;and #$ff
    sta %c
}  move(a) + 3

reg: LOADU1(reg)  {
    lda %0
    ;and #$ff
    sta %c
}  move(a) + 3


#pragma mark - P4 / I4 / U4
reg: LOADP4(reg)  {
    lda %0
    sta %c
    lda %0+2
    sta %c+2
}  move(a) + 4


reg: LOADP4(const)  {
    lda #%0
    sta %c
    lda #^%0
    sta %c+2
} 4


reg: LOADI4(reg)  {
    lda %0
    sta %c
    lda %0+2
    sta %c+2
}  move(a) + 4

reg: LOADI4(const)  {
    lda #%0
    sta %c
    lda #^%0
    sta %c+2
} 4


reg: LOADU4(reg)  {
    lda %0
    sta %c
    lda %0+2
    sta %c+2
}  move(a) + 4

reg: LOADU4(const)  {
    lda #%0
    sta %c
    lda #^%0
    sta %c+2
} 4

# prevent extra temporary conversions.

# unsigned xxx(char *cp) { return (unsigned)cp; }
reg: LOADU2(LOADU4(reg)) {
    lda %0
    sta %c
} 2

# int xxx(char *cp) {return (int)cp; }
reg: LOADI2(LOADU4(reg)) {
    lda %0
    sta %c
} 2

reg: LOADU1(LOADU2(reg)) {
    lda %0
    sta %c
} 2    
