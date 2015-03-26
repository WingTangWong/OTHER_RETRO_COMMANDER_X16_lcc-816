#ifndef __STDARG
#define __STDARG

#if !defined(_VA_LIST) && !defined(__VA_LIST_DEFINED)
#define _VA_LIST
#define _VA_LIST_DEFINED
typedef unsigned __va_list;
#endif
typedef __va_list va_list;

void __builtin_va_arg(va_list);
#define __va_size(type) ((sizeof(type) + 1) & ~1)

#define va_arg(ap, type) \
	((type (*)(unsigned))__builtin_va_arg)(ap += __va_size(type))

#define va_start(ap, start) \
	(void)(ap = (__va_list)(&start) + __va_size(start))

#define va_end(ap) ((void)0)
#define va_copy(dest,src) (void)(dest = src)
#endif
