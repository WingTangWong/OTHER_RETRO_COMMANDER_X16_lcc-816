# call.md

%{

#define EMIT2(x) emitstring(x, p, NULL, NULL)
#define STACK_REPAIR_PLY_LIMIT 4

/* returns 1 if this is a tool dispatch */
static unsigned tool_dispatch(Node p, Type t, FunctionAttr *attr) {

	
	if (attr && attr->function_vector) {

		if (attr->registerX) {
			print("\tldx #$%x\n", attr->registerX);
		}

		print("\tjsl $%x\n", attr->function_vector);
		print("\tsta >_toolErr\n");

		return 1;
	}
	return 0;
}

static void return_value(Node p, Type t, FunctionAttr *attr) {

	// see emitstring()
	const char *rv;
	unsigned pascal = 0;

	if (p->op == CALL+V) return;

	if (attr && attr->pascal) pascal = 1;

	rv = p->syms['c' - 'a']->x.name;

	unsigned size = opsize(p->op);

	if (pascal || size > 4) {
		unsigned i;
		for(i = 0; i < size; i += 2) {
			print("\tpla\n");
			print("\tsta %s+%d\n", rv, i);
		}
		return;
	}

	// cdecl - return via a or a/x
	print("\tsta %s\n", rv);
	if (size == 4)
		print("\tstx %s+2\n", rv);
}

static void repair_stack(Node p, Type t, FunctionAttr *attr) {
	// for a cdecl call, fix the stack.
	int arg_size = p->syms[0] ? p->syms[0]->u.c.v.i : 0;

	if (attr) {
		if (attr->pascal) return;
		//stdcall  - caller cleans up, unless variadic.
	}


	if (arg_size > STACK_REPAIR_PLY_LIMIT) {
		print("\tlda %d,s\n", arg_size + 1);
		print("\ttcs\n");
		return;
	}

	while (arg_size > 0) {
		print("\tply\n");
		arg_size -= 2;
	}
}


/* CALLx(reg) */
static void call_indirect(Node p, Node *kids, short *nts) {
	// &MMStartUp doesn't make much sense

	Type t = p->syms[1] ? p->syms[1]->type : NULL;


    int lab = genlabel(1);

    // generate an rtl address
    EMIT("\tphk\n");
    print("\tpea L%d-1\n", lab);

    // jsl address = rtl address - 1
    // 
    EMIT("\tpei %0+1\n");
    EMIT("\tphb\n"); // 1 byte placeholder
    EMIT("\tlda %0\n");
    EMIT("\tdec a\n");
    EMIT("\tsta 1,s\n");
    EMIT("\trtl\n");
    print("L%d:\n", lab); // label for rtl.

	// if not CALLV, handle the return address
	return_value(p, t, NULL);

	// clean up the stack.
	repair_stack(p, t, NULL);
}

/* CALLx(address) or CALLx(const) */
static void call_direct(Node p, Node *kids, short *nts) {
	
	Type t = p->syms[1] ? p->syms[1]->type : NULL;

	FunctionAttr *attr = t && t->u.f.attr ? t->u.f.attr : NULL;


	if (!tool_dispatch(p, t, attr))
		EMIT("\tjsl %0\n");

	// if not CALLV, handle the return address
	return_value(p, t, attr);

	// clean up the stack.
	repair_stack(p, t, attr);
}

%}


stmt: XCALLV ^{
	/* set up parameters for function call */
	Type t = NULL;
	FunctionAttr *attr = NULL;

	int arg_size = 0;
	int return_size = 0;

	unsigned pascal = 0;
	unsigned stdcall = 0;
	unsigned cdecl = 1;
	unsigned xcall = 0;


	// scan forward to find the call.
	//p = p->x.next; // skip current node since it's an xcall.
	while(p) {
		if (generic(p->op) == XCALL)
			xcall++;

		if (generic(p->op) == CALL)
			if (--xcall == 0) break;
		
		p = p->x.next;
	}


	if (!p) return; //!

	if (p->syms[0]) arg_size = p->syms[0]->u.c.v.i;
	if (p->syms[1]) t = p->syms[1]->type;
	if (t && t->u.f.attr) attr = t->u.f.attr;

	return_size = opsize(p->op);

	if (attr && attr->pascal) {
		pascal = 1;
		stdcall = 0;
		cdecl = 0;
	}

	if (attr && attr->stdcall) {
		stdcall = 1;
		pascal = 0;
		cdecl = 0;
		if (variadic(t) || !t->u.f.proto) {
			stdcall = 0;
			cdecl = 1;
		}
	}

	if (pascal || return_size > 4)
	{
		// todo -- what about struct returns (toolbox)
		while (return_size > 0) {
			print("\tpha\n");
			return_size -= 2;
		}
	}

	if (cdecl && arg_size > STACK_REPAIR_PLY_LIMIT) {
		print("\t; save stack\n" "\ttsx\n" "\tphx\n");
	}
}

stmt: CALLV(address) ^{
	call_direct(p, kids, nts);
} 1

stmt: CALLV(const) ^{
	call_direct(p, kids, nts);
} 1



reg: CALLI2(address) ^{
	call_direct(p, kids, nts);
} 1

reg: CALLI2(const) ^{
	call_direct(p, kids, nts);
} 1



reg: CALLU2(address) ^{
	call_direct(p, kids, nts);
} 1

reg: CALLU2(const) ^{
	call_direct(p, kids, nts);
} 1

reg: CALLU4(address) ^{
	call_direct(p, kids, nts);
} 1

reg: CALLU4(const) ^{
	call_direct(p, kids, nts);
} 1

reg: CALLI4(address) ^{
	call_direct(p, kids, nts);
} 1

reg: CALLI4(const) ^{
	call_direct(p, kids, nts);
} 1



reg: CALLP4(address) ^{
	call_direct(p, kids, nts);
} 1

reg: CALLP4(const) ^{
	call_direct(p, kids, nts);
} 1


reg: CALLV(reg) ^{
	call_indirect(p, kids, nts);
} 10

reg: CALLI2(reg) ^{
	call_indirect(p, kids, nts);
} 10

reg: CALLU2(reg) ^{
	call_indirect(p, kids, nts);
} 10

reg: CALLP4(reg) ^{
	call_indirect(p, kids, nts);
} 10
