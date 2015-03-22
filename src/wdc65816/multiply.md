#pragma mark - multiplication

reg: MULU2(rc, rc) {

    lda %0
    ldx %1
    jsl ~mulu2
    sta %c
} 20


reg: MULI2(rc, rc) {

    lda %0
    ldx %1
    jsl ~muli2
    sta %c
} 20


# x * 3 = (x * 2) + x
reg: MULU2(reg, const_3) {
    lda %0
    asl a
    clc
    adc %0
    sta %c
} 5

reg: MULU2(reg, const_5) {
    lda %0
    asl a
    asl a
    clc
    adc %0
    sta %c
} 6

reg: MULU2(reg, const_10) {
    lda %0
    asl a
    asl a
    clc
    adc %0
    asl a
    sta %c
} 7

#pragma mark - division

reg: DIVU2(rc, rc) {

    lda %0
    ldx %1
    jsl ~divu2
    sta %c
} 20

reg: DIVI2(rc, rc) {

    lda %0
    ldx %1
    jsl ~divi2
    sta %c
} 20

#pragma mark - modulo

reg: MODU2(rc, rc) {

    lda %0
    ldx %1
    jsl ~modu2
    sta %c
} 20

reg: MODI2(rc, rc) {

    lda %0
    ldx %1
    jsl ~modi2
    sta %c
} 20
