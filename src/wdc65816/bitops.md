#pragma mark - bitops

# modify the dp directly for a = a op b

reg: BORU2(reg, rc) {
    lda %1
    tsb %0
} rmw(a, 2)

reg: BORI2(reg, rc) {
    lda %1
    tsb %0
} rmw(a, 2)


reg: BANDU2(reg, rc) {
    lda %1
    trb %0
} rmw(a, 2)

reg: BANDI2(reg, rc) {
    lda %1
    trb %0
} rmw(a, 2)


reg: BANDU2(rc, rc) {
    lda %0
    and %1
    sta %c
} 3

reg: BANDI2(rc, rc) {
    lda %0
    and %1
    sta %c
} 3


reg: BORU2(rc, rc) {
    lda %0
    ora %1
    sta %c
} 3

reg: BORI2(rc, rc) {
    lda %0
    ora %1
    sta %c
} 3


reg: BXORU2(rc, rc) {
    lda %0
    eor %1
    sta %c
} 3

reg: BXORI2(rc, rc) {
    lda %0
    eor %1
    sta %c
} 3

reg: BCOMU2(reg) {
    lda %0
    eor #$ffff
    sta %c
} 3

reg: BCOMI2(reg) {
    lda %0
    eor #$ffff
    sta %c
} 3

reg: NEGI2(reg) {
    lda %0
    eor #$ffff
    inc
    sta %c
} 4


reg: BANDI4(reg, reg) {
    lda %0
    and %1
    sta %c
    lda %0+2
    and %1+2
    sta %c+2
} 6


reg: BANDU4(reg, reg) {
    lda %0
    and %1
    sta %c
    lda %0+2
    and %1+2
    sta %c+2
} 6


reg: BANDI4(reg, const) {
    lda %0
    and #%1
    sta %c
    lda %0+2
    and #^%1
    sta %c+2
} 6

reg: BANDU4(reg, const) {
    lda %0
    and #%1
    sta %c
    lda %0+2
    and #^%1
    sta %c+2
} 6


reg: BORI4(reg, reg) {
    lda %0
    ora %1
    sta %c
    lda %0+2
    ora %1+2
    sta %c+2
} 6


reg: BORU4(reg, reg) {
    lda %0
    ora %1
    sta %c
    lda %0+2
    ora %1+2
    sta %c+2
} 6


reg: BORI4(reg, const) {
    lda %0
    ora #%1
    sta %c
    lda %0+2
    ora #^%1
    sta %c+2
} 6

reg: BORU4(reg, const) {
    lda %0
    ora #%1
    sta %c
    lda %0+2
    ora #^%1
    sta %c+2
} 6

reg: BXORI4(reg, reg) {
    lda %0
    eor %1
    sta %c
    lda %0+2
    eor %1+2
    sta %c+2
} 6


reg: BXORU4(reg, reg) {
    lda %0
    eor %1
    sta %c
    lda %0+2
    eor %1+2
    sta %c+2
} 6


reg: BXORI4(reg, const) {
    lda %0
    eor #%1
    sta %c
    lda %0+2
    eor #^%1
    sta %c+2
} 6

reg: BXORU4(reg, const) {
    lda %0
    eor #%1
    sta %c
    lda %0+2
    eor #^%1
    sta %c+2
} 6