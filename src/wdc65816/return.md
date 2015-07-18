#pragma mark - return

%{
    
#define pascal_return(p) cfunc_attr && cfunc_attr->pascal ? 0 : LBURG_MAX
#define no_pascal_return(p) cfunc_attr && cfunc_attr->pascal ? LBURG_MAX : 0
%}

# pascal return handled via rtarget.  

stmt: RETU2(reg) "# pascal return\n" pascal_return(a)
stmt: RETI2(reg) "# pascal return\n" pascal_return(a)
stmt: RETU4(reg) "# pascal return\n" pascal_return(a)
stmt: RETP4(reg) "# pascal return\n" pascal_return(a)
stmt: RETI4(reg) "# pascal return\n" pascal_return(a)
stmt: RETF4(reg) "# pascal return\n" pascal_return(a)
stmt: RETF8(reg) "# pascal return\n" pascal_return(a)
stmt: RETF10(reg) "# pascal return\n" pascal_return(a)




stmt: RETU2(rc) {
    lda %0
} no_pascal_return(a)

stmt: RETI2(rc) {
    lda %0
} no_pascal_return(a)

stmt: RETU2(LOADU2(const)) {
    lda #%0
} no_pascal_return(a)

stmt: RETI2(LOADI2(const)) {
    lda #%0
} no_pascal_return(a)


# stmt: RETI2(INDIRI2(address)) {
#    lda |%0
# } 2

# stmt: RETU2(INDIRU2(address)) {
#     lda |%0
# } 2

stmt: RETU4(const) {
    lda #%0
    ldx #^%0
} no_pascal_return(a)

stmt: RETI4(const) {
    lda #%0
    ldx #^%0
} no_pascal_return(a)

stmt: RETU4(reg) {
    lda %0
    ldx %0+2
} no_pascal_return(a)

stmt: RETI4(reg) {
    lda %0
    ldx %0+2
} no_pascal_return(a)

stmt: RETP4(reg) {
    lda %0
    ldx %0+2
} no_pascal_return(a)
