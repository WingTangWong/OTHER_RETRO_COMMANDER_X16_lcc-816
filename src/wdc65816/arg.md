#pragma mark - functions and parameters

#// todo -- will this always be correct?
#// address of reg vs pushing a ptr...
stmt: ARGP4(vregp) {
    pea 0
    tdc
    clc
    adc #%0
    pha
} 5

#stmt: ARGP4(INDIRP4(vregp)) {
#    pei %0+2
#    pei %0
#} 2



stmt: ARGU2(reg) {
    pei %0
} 1

stmt: ARGI2(reg) {
    pei %0
} 1

stmt: ARGU2(const) {
    pea %0
} 1


stmt: ARGI2(const) {
    pea %0
} 1




stmt: ARGU4(const) {
    pea ^%0
    pea %0
} 2

stmt: ARGI4(const) {
    pea ^%0
    pea %0
} 2

stmt: ARGP4(const) {
    pea ^%0
    pea %0
} 2

stmt: ARGP4(address) {
    pea ^%0
    pea %0
} 2

stmt: ARGU4(reg) {
    pei %0+2
    pei %0
} 2

stmt: ARGI4(reg) {
    pei %0+2
    pei %0
} 2

stmt: ARGP4(reg) {
    pei %0+2
    pei %0
} 2


#pragma mark - floating point

stmt: ARGF4(reg) {
    pei %0+2
    pei %0
} 2

stmt: ARGF4(CNSTF4) ^{
    // p->kids[0] = CNSTF4
    // p->kids[0]->syms[0]->u.c.v.d = long double value.

    unsigned char buffer[sizeof(float)];
    float d = p->kids[0]->syms[0]->u.c.v.d;
    int i;

    memcpy(buffer, &d, sizeof(d));

    // todo -- endian!
    for (i = 0; i < 4; i += 2) {
        printf(_("pea %02x%02x"), buffer[4-i-2], buffer[4-i-1]);
    }
}

# todo -- consts...
stmt: ARGF8(reg) {
    pei %0+6
    pei %0+4
    pei %0+2
    pei %0
} 2

#cnstf8: CNSTF8 "%a"

stmt: ARGF8(CNSTF8) ^{
    // p->kids[0] = CNSTF8
    // p->kids[0]->syms[0]->u.c.v.d = long double value.

    unsigned char buffer[sizeof(double)];
    double d = p->kids[0]->syms[0]->u.c.v.d;
    int i;

    memcpy(buffer, &d, sizeof(d));

    // todo -- endian!
    for (i = 0; i < 8; i += 2) {
        printf(_("pea %02x%02x"), buffer[8-i-2], buffer[8-i-1]);
    }
}

stmt: ARGF10(reg) {
    pei %0+8
    pei %0+6
    pei %0+4
    pei %0+2
    pei %0
} 2

stmt: ARGF10(CNSTF10) ^{
    // p->kids[0] = CNSTF10
    // p->kids[0]->syms[0]->u.c.v.d = long double value.

    unsigned char buffer[sizeof(long double)];
    long double d = p->kids[0]->syms[0]->u.c.v.d;
    int i;

    memcpy(buffer, &d, sizeof(d));

    // todo -- endian!
    for (i = 0; i < 10; i += 2) {
        printf(_("pea %02x%02x"), buffer[10-i-2], buffer[10-i-1]);
    }
}
