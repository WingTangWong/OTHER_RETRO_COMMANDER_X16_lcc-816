#pragma mark - multiplication

reg: MULU2(rc, rc) {

    lda %0
    ldx %1
    jsl __mulu2
    sta %c
} 20


reg: MULI2(rc, rc) {

    lda %0
    ldx %1
    jsl __muli2
    sta %c
} 20


# x * 3 = (x * 2) + x
#
# simplify leaves constant in left side for multiplication.
#
reg: MULU2(reg, const_3) {
    lda %0
    asl
    clc
    adc %0
    sta %c
} 5

reg: MULU2(const_3, reg) {
    lda %1
    asl
    clc
    adc %1
    sta %c
} 5

reg: MULU2(reg, const_5) {
    lda %0
    asl
    asl
    clc
    adc %0
    sta %c
} 6

reg: MULU2(const_5, reg) {
    lda %1
    asl
    asl
    clc
    adc %1
    sta %c
} 6

reg: MULU2(reg, const_10) {
    lda %0
    asl
    asl
    clc
    adc %0
    asl
    sta %c
} 7

reg: MULU2(const_10, reg) {
    lda %1
    asl
    asl
    clc
    adc %1
    asl
    sta %c
} 7

#pragma mark - division

reg: DIVU2(rc, rc) {

    lda %0
    ldx %1
    jsl __divu2
    sta %c
} 20

reg: DIVI2(rc, rc) {

    lda %0
    ldx %1
    jsl __divi2
    sta %c
} 20

#pragma mark - modulo

reg: MODU2(rc, rc) {

    lda %0
    ldx %1
    jsl __modu2
    sta %c
} 20

reg: MODI2(rc, rc) {

    lda %0
    ldx %1
    jsl __modi2
    sta %c
} 20




# 32-bit

reg: DIVI4(rc, rc) {
    tsx
    phx
    pei %0
    pei %0+2
    pei %1
    pei %1+2
    jsl __divi4
    sta %c
    stx %c+2
    lda 9,s
    tcs
} 40
