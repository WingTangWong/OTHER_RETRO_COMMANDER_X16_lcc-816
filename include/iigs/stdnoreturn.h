#ifndef __stdnoreturn_h__
#define __stdnoreturn_h__

#if __STDC__ < 199901
#define noreturn
#else
#define noreturn _Noreturn
#endif

#define __noreturn_is_defined 1

#endif
