#ifndef __stdarg__
#define __stdarg__

typedef unsigned va_list;

void __builtin_va_arg(va_list, va_list);
va_list __builtin_va_start(void *);

#define __va_size(type) ((sizeof(type) + 1) & ~1)

// n.b. -- structs?
#define va_arg(ap, type) \
((type (*)(va_list, va_list))__builtin_va_arg)(ap += __va_size(type), ap)

#define va_start(ap, start) \
(void)(ap = __builtin_va_start(&start) + __va_size(start))

#define va_end(ap) ((void)0)
#define va_copy(dest, src) (void)(dest = src)
endif

