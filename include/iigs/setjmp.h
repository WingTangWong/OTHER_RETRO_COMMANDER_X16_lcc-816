#ifndef __setjmp_h__
#define __setjmp_h__

#include <stdnoreturn.h>

/* s, d, pc, k, b, signal mask */
typedef unsigned[6] jmp_buf;
typedef unsigned[7] sigjmp_buf;

int setjmp(jmp_buf env);
noreturn void longjmp(jmp_buf env, int val);

int _setjmp(jmp_buf env);
noreturn void _longjmp(jmp_buf env, int val);

int sigsetjmp(sigjmp_buf env, int savemask);
noreturn void siglongjmp(sigjmp_buf env, int val);


void longjmperror(void);

#endif

