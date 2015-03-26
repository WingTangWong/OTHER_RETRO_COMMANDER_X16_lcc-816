# builtin functions.  arguments are pushed as normal,
# code should pull from the stack 
# __attribute__(builtin) to pass via a register?

%{
static char *iigs_bswap16;
static char *iigs_va_arg;

#define STRINGN(string) stringn("" string "" , sizeof(string) - 1)

static void init_builtins(void) {
	iigs_bswap16 = STRINGN("__builtin_bswap16");
	iigs_va_arg = STRINGN("__builtin_va_arg");
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

reg: CALLU2(address) {
	; %0
	plx
	lda >$000000-2,x
	sta %c
} is_builtin(a, iigs_va_arg)

