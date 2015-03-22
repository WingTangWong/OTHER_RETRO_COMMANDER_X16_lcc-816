#pragma mark - bit shift

reg: RSHU2(reg, const_1) {
    lsr %c    
} rmw(a, 1)

reg: RSHU2(reg, const_2) {
    lsr %c
    lsr %c
} rmw(a, 2)

reg: RSHU2(reg, const) ^{

    unsigned value = constValue(kids[1]);

    if (value > 16) {
        EMIT("\tstz %c\n");
        return;
    }
    EMIT("\tlda %0\n");

    if (value >= 8) {

        EMIT("\txba\n\tand #$00ff\n");
        value -= 8;
    }

    while (value) {
        EMIT("\tlsr a\n");
        value--;
    }
    EMIT("\tsta %c\n");

} 10

reg: RSHU2(rc, reg) {
    lda %0
    ldx %1
    jsl ~rshu2
    sta %c
} 20

reg: RSHI2(rc, reg) {
    lda %0
    ldx %1
    jsl ~rshi2
    sta %c
} 20

reg: LSHU2(reg, const_1) {
    asl %c    
} rmw(a, 1)

reg: LSHI2(reg, const_1) {
    asl %c    
} rmw(a, 1)


reg: LSHU2(reg, const_2) {
    asl %c
    asl %c
} rmw(a, 2)

reg: LSHI2(reg, const_2) {
    asl %c
    asl %c
} rmw(a, 2)

reg: LSHU2(reg, const) ^{

    unsigned value = constValue(kids[1]);

    if (value > 16) {
        EMIT("\tstz %c\n");
        return;
    }
    EMIT("\tlda %0\n");

    /*
    if (value == 15) {
        // move bit 1 to bit  16.
        EMIT("\tlsr a\n\tlda #0\n\tror a\n\tsta %c\n);
        return;
    }
    */

    if (value >= 8) {

        EMIT("\txba\n\tand #$ff00\n");
        value -= 8;
    }

    while (value) {
        EMIT("\tasl a\n");
        value--;
    }
    EMIT("\tsta %c\n");

} 10

reg: LSHI2(reg, const) ^{

    unsigned value = constValue(kids[1]);

    if (value > 16) {
        EMIT("\tstz %c\n");
        return;
    }
    EMIT("\tlda %0\n");

    /*
    if (value == 15) {
        // move bit 1 to bit  16.
        EMIT("\tlsr a\n\tlda #0\n\tror a\n\tsta %c\n);
        return;
    }
    */

    if (value >= 8) {

        EMIT("\txba\n\tand #$ff00\n");
        value -= 8;
    }

    while (value) {
        EMIT("\tasl a\n");
        value--;
    }
    EMIT("\tsta %c\n");

} 10


reg: LSHU2(rc, reg) {
    lda %0
    ldx %1
    jsl ~lshu2
    sta %c
} 20

reg: LSHI2(rc, reg) {
    lda %0
    ldx %1
    jsl ~lshi2
    sta %c
} 20
