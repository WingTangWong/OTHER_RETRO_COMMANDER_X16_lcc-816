
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


# y-indirection.

stmt: ASGNU2(ADDP4(reg, const_16_bit), rc) {
    lda %2
    ldy #%1
    sta [%0],y
} 3+1

stmt: ASGNI2(ADDP4(reg, const_16_bit), rc) {
    lda %2
    ldy #%1
    sta [%0],y
} 3+1

stmt: ASGNU1(ADDP4(reg, const_16_bit), rc) {
    lda %2
    ldy #%1
    sep #$20
    sta [%0],y
    rep #$20
} 4+1

stmt: ASGNI1(ADDP4(reg, const_16_bit), rc) {
    lda %2
    ldy #%1
    sep #$20
    sta [%0],y
    rep #$20
} 4+1

# 8-bit offset
stmt: ASGNU1(ADDP4(CVII4(CVUI2(INDIRU1(vregp))), INDIRP4(vregp)), rc) {
    lda %0
    and #$ff
    tay
    lda %2
    sep #$20
    sta [%1],y
    rep #$20
} 7+1

stmt: ASGNI1(ADDP4(CVII4(CVUI2(INDIRU1(vregp))), INDIRP4(vregp)), rc) {
    lda %0
    and #$ff
    tay
    lda %2
    sep #$20
    sta [%1],y
    rep #$20
} 7+1

stmt: ASGNU1(ADDP4(CVUU4(INDIRU2(vregp)), INDIRP4(vregp)), rc) {
    lda %2
    ldy %0
    sep #$20
    sta [%1],y
    rep #$20    
} 5+1

stmt: ASGNI1(ADDP4(CVUU4(INDIRU2(vregp)), INDIRP4(vregp)), rc) {
    lda %2
    ldy %0
    sep #$20
    sta [%1],y
    rep #$20    
} 5+1



# static char buffer; buffer[uint16_t | uint8_t]
stmt: ASGNU1(ADDP4(CVUU4(INDIRU2(vregp)), address), rc) {
    ldx %0
    lda %2
    sep #$20
    sta >%1,x
    rep #$20
} 5

stmt: ASGNU1(ADDP4(CVII4(CVUI2(INDIRU1(vregp))), address), rc) {
    lda %0
    and #$ff
    tax
    lda %2
    sep #$20
    sta >%1,x
    rep #$20
} 6


