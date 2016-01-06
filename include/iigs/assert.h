
#ifndef __assert_h__
#define __assert_h__

void assert(unsigned);
extern void __assert(const char *e, const char *file, unsigned line);

#define static_assert _Static_assert

#endif

#undef assert
#ifdef NDEBUG
#define assert(ignore) ((void)0)
#else
#define assert(e) ((void)((e)||__assert(#e, __FILE__, __LINE__)))
#endif

