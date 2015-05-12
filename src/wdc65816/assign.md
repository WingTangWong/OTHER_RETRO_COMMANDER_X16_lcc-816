
# 8-bits

stmt: ASGNI1(vregp, rc) {
    ;sep #$20
    lda %1
    ;rep #$20
    sta %0
} 4

stmt: ASGNU1(vregp, rc) {
    ;sep #$20
    lda %1
    ;rep #$20
    sta %0
} 4

#16-bit

stmt: ASGNU2(vregp, rc) {
    lda %1
    sta %0
} 2

stmt: ASGNI2(vregp, rc) {
    lda %1
    sta %0
} 2

# 32-bits
# need separate const vs reg for high-word

stmt: ASGNP4(vregp, const) {
    lda #%1
    sta %0
    lda #^%1
    sta %0+2
} 4

stmt: ASGNU4(vregp, const) {
    lda #%1
    sta %0
    lda #^%1
    sta %0+2
} 4

stmt: ASGNI4(vregp, const) {
    lda #%1
    sta %0
    lda #^%1
    sta %0+2
} 4


stmt: ASGNP4(vregp, reg) {
    lda %1
    sta %0
    lda %1+2
    sta %0+2
} 4


stmt: ASGNU4(vregp, reg) {
    lda %1
    sta %0
    lda %1+2
    sta %0+2
} 4

stmt: ASGNI4(vregp, reg) {
    lda %1
    sta %0
    lda %1+2
    sta %0+2
} 4

stmt: ASGNP4(vregp, reg) {
    lda %1
    sta %0
    lda %1+2
    sta %0+2
} 4



# 0-optimizations.


stmt: ASGNU1(vregp, const_0) {
    stz %0
} 1

stmt: ASGNI1(vregp, const_0) {
    stz %0
} 1

stmt: ASGNU2(vregp, const_0) {
    stz %0
} 1

stmt: ASGNI2(vregp, const_0) {
    stz %0
} 1

stmt: ASGNU2(vregp, const_1) {
    stz %0
    inc %0
} 2

stmt: ASGNI2(vregp, const_1) {
    stz %0
    inc %0
} 2

stmt: ASGNU2(addressDP, reg) {
    lda %1
    sta %0
} 2

stmt: ASGNI2(addressDP, reg) {
    lda %1
    sta %0
} 2

# indirection...

stmt: ASGNI2(reg, rc) {
    lda %1
    sta [%0]
} 2+1

stmt: ASGNU2(reg, rc) {
    lda %1
    sta [%0]
} 2+1


stmt: ASGNI1(reg, rc) {
    lda %1
    sep #$20
    sta [%0]
    rep #$20
} 4+1

stmt: ASGNU1(reg, rc) {
    lda %1
    sep #$20
    sta [%0]
    rep #$20
} 4+1
