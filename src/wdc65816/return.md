#pragma mark - return

stmt: RETU2(rc) {
    lda %0
} 1

stmt: RETI2(rc) {
    lda %0
} 1

stmt: RETU2(LOADU2(const)) {
    lda #%0
} 1

stmt: RETI2(LOADI2(const)) {
    lda #%0
} 1


# stmt: RETI2(INDIRI2(address)) {
#    lda |%0
# } 2

# stmt: RETU2(INDIRU2(address)) {
#     lda |%0
# } 2

stmt: RETU4(const) {
    lda #%0
    ldx #^%0
} 2

stmt: RETI4(const) {
    lda #%0
    ldx #^%0
} 2

stmt: RETU4(reg) {
    lda %0
    ldx %0+2
} 2

stmt: RETI4(reg) {
    lda %0
    ldx %0+2
} 2
