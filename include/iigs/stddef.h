#ifndef __STDDEF
#define __STDDEF

#ifndef NULL
#define NULL ((void*)0)
#endif

#if __STDC__ < 199901
#define restrict
#endif


#define offsetof(type, member) __offsetof(type, member)

typedef long ptrdiff_t;
typedef unsigned max_align_t;

#ifndef __size_t__
#define __size_t__
typedef unsigned long size_t;
#endif


#ifndef __wchar_t__
#define __wchar_t__
typedef unsigned short wchar_t;
#endif

#endif
