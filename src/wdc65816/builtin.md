# builtin functions.  arguments are pushed as normal,
# code should pull from the stack 
# __attribute__(builtin) to pass via a register?

%{
static char *iigs_bswap16;
static char *iigs_bswap32;
static char *iigs_va_arg;
static char *iigs_va_start;
static char *iigs_trap;
static char *iigs_sei;
static char *iigs_cli;
static char *iigs_nop;
static char *iigs_stp;
static char *iigs_wai;
static char *iigs_bcd_add;
static char *iigs_bcd_sub;

#define STRINGN(string) stringn("" string "" , sizeof(string) - 1)

static void init_builtins(void) {
	iigs_bswap16 = STRINGN("__builtin_bswap16");
	iigs_bswap32 = STRINGN("__builtin_bswap32");
	iigs_va_arg = STRINGN("__builtin_va_arg");
	iigs_va_start = STRINGN("__builtin_va_start");
	iigs_trap = STRINGN("__builtin_trap");
	iigs_nop = STRINGN("__builtin_nop");
	iigs_sei = STRINGN("__builtin_sei");
	iigs_cli = STRINGN("__builtin_cli");
	iigs_stp = STRINGN("__builtin_stp");
	iigs_wai = STRINGN("__builtin_wai");
	iigs_bcd_add = STRINGN("__builtin_bcd_add");
	iigs_bcd_sub = STRINGN("__builtin_bcd_sub");
}

static int is_builtin(Node p, const char *fx) {
	Node arg = p->kids[0];
	if (generic(arg->op) == ADDRG 
		&& arg->syms[0] 
		&& arg->syms[0]->name == fx) return 0;

	return LBURG_MAX;
}

%}

reg: CALLU2(address) {
	; %0
	pla
	xba
	sta %c
} is_builtin(a, iigs_bswap16)

reg: CALLI2(address) {
	; %0
	pla
	xba
	sta %c
} is_builtin(a, iigs_bswap16)

reg: CALLU4(address) {
	; %0
	pla
	xba
	sta %c+2
	pla
	xba
	sta %c
} is_builtin(a, iigs_bswap32)

# ap = __builtin_va_start(&fmt) + __va_sizeof(fmt) 
reg: CALLU2(address) {
	; %0
	pla ; 
	ply ; drop
	sta %c
} is_builtin(a, iigs_va_start)

# __builtin_va_arg(dummy, ap)
reg: CALLU2(address) {
	; %0
	plx
	plx
	;lda >$000000-2,x
	lda >$000000,x
	sta %c
} is_builtin(a, iigs_va_arg)

reg: CALLI2(address) {
	; %0
	plx
	plx
	;lda >$000000-2,x
	lda >$000000,x
	sta %c
} is_builtin(a, iigs_va_arg)

# void __builtin_trap(void);
stmt: CALLV(address) {
	; %0
	brk $ea
} is_builtin(a, iigs_trap)

# void __builtin_cli(void)
stmt: CALLV(address) {
	; %0
	cli
} is_builtin(a, iigs_cli)

# void __builtin_sei(void)
stmt: CALLV(address) {
	; %0
	sei
} is_builtin(a, iigs_sei)

# void __builtin_stp(void)
stmt: CALLV(address) {
	; %0
	stp
} is_builtin(a, iigs_stp)

# void __builtin_wai(void)
stmt: CALLV(address) {
	; %0
	wai
} is_builtin(a, iigs_wai)

# void __builtin_nop(void)
stmt: CALLV(address) {
	; %0
	nop
} is_builtin(a, iigs_nop)

# void __builtin_bcd_add(unsigned, unsigned) 
reg: CALLU2(address) {
	; %0
	pla
	sed
	clc
	adc 1,s
	ply
	cld
	sta %c
} is_builtin(a, iigs_bcd_add)

# void __builtin_bcd_sub(unsigned, unsigned) 
reg: CALLU2(address) {
	; %0
	pla
	sed
	sec
	sbc 1,s
	ply
	cld
	sta %c
} is_builtin(a, iigs_bcd_add)


