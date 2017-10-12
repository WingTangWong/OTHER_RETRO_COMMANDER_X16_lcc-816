#ifndef __stdbool_h__
#define __stdbool_h__

#if __STDC__ < 199901
typedef unsigned short _Bool;
#endif
 
#define bool _Bool
#define true 1
#define false 0

#define __bool_true_false_are_defined 1

#endif

