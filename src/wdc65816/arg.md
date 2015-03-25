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

stmt: ARGP4(INDIRP4(vregp)) {
    pei %0
    pei %0+2
} 2



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
