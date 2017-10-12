# -*- lburg -*-

# call.md

%{

#define EMIT2(x) emitstring(x, p, NULL, NULL)
#define STACK_REPAIR_PLY_LIMIT 6
#define STACK_REPAIR_ADC_MIN 254


/*
 * cdecl api:
 * 16-bit: returned in a
 * 32-bit: returned in x:a
 * 64-bit: ????
 * struct/union: pass secret pointer parameter, return w/ pointer
 * float/double/extended... ??? like struct/union?
 *
 * pascal api:
 * return everything via stack.
 * struct/union currently broken...
 */


static unsigned function_is_pascal(Node p) {

	Type t = p->syms[1] ? p->syms[1]->type : NULL;

	FunctionAttr *attr = t && t->u.f.attr ? t->u.f.attr : NULL;

	if (attr && attr->pascal) return 1;
	return 0;
}

static unsigned function_is_stdcall(Node p) {

	Type t = p->syms[1] ? p->syms[1]->type : NULL;

	FunctionAttr *attr = t && t->u.f.attr ? t->u.f.attr : NULL;

	if (attr && attr->stdcall) return 1;
	return 0;
}

static unsigned function_is_cdecl(Node p) {

	Type t = p->syms[1] ? p->syms[1]->type : NULL;

	FunctionAttr *attr = t && t->u.f.attr ? t->u.f.attr : NULL;

	if (attr && attr->pascal) return 0;
	if (attr && attr->stdcall) return 0;
	return 1;
}

static unsigned function_return_size(Node p) {

	Type t = p->syms[1] ? p->syms[1]->type : NULL;
	FunctionAttr *attr = t && t->u.f.attr ? t->u.f.attr : NULL;
	Type rt = freturn(t);
	unsigned size;

	size = (rt->size + 1) & ~0x01;
	if (isstruct(rt)) {
		if (!attr || !attr->pascal) size = 0;
	}

	return size;
}


/* returns 1 if this is a tool dispatch */
static unsigned tool_dispatch(Node p, Type t, FunctionAttr *attr) {

	
	if (attr && attr->function_vector) {

		if (attr->registerX) {
			const char *op = "ldx";

			// special case -- gs/os dispatcher pushes x instead of loading it.
			if (attr->function_vector == 0xE100B0) op = "pea";
			print("\t%s #$%x\n", op, attr->registerX);
		}

		print("\tjsl $%x\n", attr->function_vector);
		print("\tsta >_toolErr\n");

		return 1;
	}
	return 0;
}

static void return_value(Node p, Type t, FunctionAttr *attr) {

	// see emitstring()
	Type rt = NULL;
	const char *rv;
	unsigned pascal = 0;
	int return_size = 0;

	if (p->op == CALL+V) return;
	if (p->op == CALL+B) return;

	// CALLB doesn't return via %c.


	if (attr && attr->pascal) pascal = 1;

	rv = p->syms['c' - 'a']->x.name;

	rt = freturn(t);

	if (rt) {
		return_size = rt->size;
		if (isstruct(rt) && !pascal) return_size = 0;
	}

	if (!return_size) return;

	if (pascal) {
		unsigned i;
		for(i = 0; i < return_size; i += 2) {
			print("\tpla\n");
			print("\tsta %s+%d\n", rv, i);
		}
		return;
	}

	// cdecl - return via a or a/x
	print("\tsta %s\n", rv);
	if (return_size == 4)
		print("\tstx %s+2\n", rv);
}

static void repair_stack(Node p, Type t, FunctionAttr *attr) {
	// for a cdecl call, fix the stack.

	Type rt = freturn(t);

	int arg_size = p->syms[0] ? p->syms[0]->u.c.v.i : 0;

	if (attr) {
		if (attr->pascal) return;
		if (attr->noreturn) return; // noreturn? return!

		if (attr->stdcall) return; // unless variadic...
		//stdcall  - caller cleans up, unless variadic.
	}

	if (isstruct(rt)) arg_size += 4;



	// if > 254 args, need to adjust the stack w/ math.
	if (arg_size >= STACK_REPAIR_ADC_MIN) {
		print( "\ttsc\n" "\tsec\n" "\tsbc #%d\n" "\ttcs\n", arg_size);
		return;
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
	FunctionAttr *attr = t && t->u.f.attr ? t->u.f.attr : NULL;

	
	if (attr && attr->near) {
		EMIT("\tldx %0\n");
		EMIT("\tjsr (0,x)\n");
	}
	else {
		// a couple cycles slower, but won't interfere w/ optimizer.
		EMIT("\tldx %0+2\n");
		EMIT("\tlda %0\n");
		EMIT("\tjsl __builtin_jsl_ax\n");
	}

	// if not CALLV, handle the return address
	return_value(p, t, attr);

	// clean up the stack.
	repair_stack(p, t, attr);
}

/* CALLx(address) or CALLx(const) */
static void call_direct(Node p, Node *kids, short *nts) {
	
	Type t = p->syms[1] ? p->syms[1]->type : NULL;

	FunctionAttr *attr = t && t->u.f.attr ? t->u.f.attr : NULL;


	if (!tool_dispatch(p, t, attr)) {

		if (attr && attr->near) EMIT("\tjsr %0\n");
		else EMIT("\tjsl %0\n");
	}
	// if not CALLV, handle the return address
	return_value(p, t, attr);

	// clean up the stack.
	repair_stack(p, t, attr);
}

%}


stmt: XCALLV ^{
	/* set up parameters for function call */
	Type t = NULL;
	Type rt = NULL;
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

	if (t) rt = freturn(t);



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

	if (cdecl || stdcall) {
		// structs returned via secret pointer.
		// todo -- same for extended, double, uint64_t, etc.
		if (isstruct(rt)) arg_size += 4;
	}

	if (rt) {
		return_size = rt->size;
		if (isstruct(rt) && !pascal) return_size = 0;
	}
	//return_size =  rt ? rt->size : 0; //opsize(p->op);



	if (pascal /* || return_size > 4 */)
	{
		// todo -- what about struct returns (toolbox)
		while (return_size > 0) {
			print("\tpha\n");
			return_size -= 2;
		}
	}

	if (attr && attr->noreturn) return;

	if (cdecl && arg_size > STACK_REPAIR_PLY_LIMIT && arg_size < STACK_REPAIR_ADC_MIN) {
		print("\t; save stack\n" "\ttsx\n" "\tphx\n");
	}
}

const_or_address: const "%a"
const_or_address: address "%a"

stmt: CALLV(const_or_address) ^{
	call_direct(p, kids, nts);
} 1



reg: CALLI2(const_or_address) ^{
	call_direct(p, kids, nts);
} 1




reg: CALLU2(const_or_address) ^{
	call_direct(p, kids, nts);
} 1


reg: CALLU4(const_or_address) ^{
	call_direct(p, kids, nts);
} 1


reg: CALLI4(const_or_address) ^{
	call_direct(p, kids, nts);
} 1




reg: CALLP4(const_or_address) ^{
	call_direct(p, kids, nts);
} 1


# %a = ?
# %b = size of struct...
#
# assert(p->syms[1] && p->syms[1]->type && isfunc(p->syms[1]->type));
# p->syms[1] = intconst(freturn(p->syms[1]->type)->size);
#
# second argument is location (vregp, addrl, addrg) for the return value.
# if pascal, pull and store after the call.
# if cdecl, push pointer before the call.


# callb argument may be ADDRLP4, ADDRGP4, VREGP, or INDIRP4(VREGP)
# ADDRGP and INDIRP4 are pointers.

call_b_stack_parm: VREGP "%a" 0
#call_b_stack_parm: INDIRP4(call_b_stack_parm) "%0" 0
call_b_stack_parm: ADDRLP4 "%a" 0
call_b_stack_parm: ADDRFP4 "%a" 0

# this is sucky.  is there a way for the CALLB argument to know if the function
# is pascal or cdecl? CALLB(...) is_pascal() and CALLB(...) is_not_pascal?

stmt: CALLB(const_or_address, call_b_stack_parm) ^{

	int pascal = function_is_pascal(p);
	int size = function_return_size(p);



	if (!pascal) {
		// lp or vregp
		EMIT(
			_("pea 0")
			_("tdc")
			_("clc")
			_("adc #%1")
			_("pha")
		);
	}

	call_direct(p, kids, nts);
	// if pascal, pull into vregp.
	if (pascal) {
		int i;
		int ofs = framesize;
		for (i = 0; i < size; i += 2) {
			framesize = i;
			EMIT(
				_("pla")
				_("sta %1+%F")
			);
		}
		framesize = ofs;
	}
} 1


stmt: CALLB(const_or_address, const_or_address) ^{

	int pascal = function_is_pascal(p);
	int size = function_return_size(p);



	if (!pascal) {
		// lp or vregp
		EMIT(
			_("pea %1")
			_("pea ^%1")
		);
	}

	call_direct(p, kids, nts);
	// if pascal, pull into vregp.
	if (pascal) {
		int i;
		int ofs = framesize;
		for (i = 0; i < size; i += 2) {
			framesize = i;
			EMIT(
				_("pla")
				_("sta %1+%F")
			);
		}
		framesize = ofs;
	}
} 1

stmt: CALLB(const_or_address, reg) ^{

	int pascal = function_is_pascal(p);
	int size = function_return_size(p);



	if (!pascal) {
		// lp or vregp
		EMIT(
			_("pei %1+2")
			_("pei %1")
		);
	}

	call_direct(p, kids, nts);
	// if pascal, pull into vregp.
	if (pascal) {
		int i;
		int ofs = framesize;
		for (i = 0; i < size; i += 2) {
			framesize = i;
			EMIT(
				_("pla")
				_("sta %1+%F")
			);
		}
		framesize = ofs;
	}
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



