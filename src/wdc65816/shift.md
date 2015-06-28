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
        EMIT(_("stz %c"));
        return;
    }
    EMIT("\tlda %0\n");

    if (value >= 8) {

        EMIT(
            _("xba")
            _("and #$00ff")
        );
        value -= 8;
    }

    while (value) {
        EMIT(_("lsr"));
        value--;
    }
    EMIT(_("sta %c"));

} 10

reg: RSHU2(rc, reg) {
    lda %0
    ldx %1
    jsl __rshu2
    sta %c
} 20

reg: RSHI2(rc, reg) {
    lda %0
    ldx %1
    jsl __rshi2
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
        EMIT(_("stz %c"));
        return;
    }
    EMIT(_("lda %0"));

    /*
    if (value == 15) {
        // move bit 1 to bit  16.
        EMIT(
            _("lsr")
            _("lda #0")
            _("ror")
            _("sta %c")
        );
        return;
    }
    */

    if (value >= 8) {

        EMIT(
            _("xba")
            _("and #$ff00")
        );
        value -= 8;
    }

    while (value) {
        EMIT(_("asl"));
        value--;
    }
    EMIT(_("sta %c"));

} 10

reg: LSHI2(reg, const) ^{

    unsigned value = constValue(kids[1]);

    if (value > 16) {
        EMIT(_("stz %c"));
        return;
    }
    EMIT(_("lda %0"));

    /*
    if (value == 15) {
        // move bit 1 to bit  16.
        EMIT(
            _("lsr")
            _("lda #0")
            _("ror")
            _("sta %c")
        );
        return;
    }
    */

    if (value >= 8) {

        EMIT(
            _("xba")
            _("and #$ff00")
        );
        value -= 8;
    }

    while (value) {
        EMIT(_("asl"));
        value--;
    }
    EMIT(_("sta %c"));
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


#pragma mark - 32-bit


reg: RSHI4(reg, const_16) {
    ldx #0
    lda %0+2
    cmp #0
    bpl @ok
    dex
@ok
    sta %c
    stx %c+2
} 7


