#ifndef __builtin__
#define __builtin__

void __builtin_trap(void); /* brk $42 */
void __builtin_nop(void);
void __builtin_cli(void);
void __builtin_sei(void);
void __builtin_wai(void);
void __builtin_stp(void);

unsigned __builtin_bswap16(unsigned);
unsigned long __builtin_bswap32(unsigned long);

unsigned __builtin_bcd_add(unsigned, unsigned);
unsigned __builtin_bcd_sub(unsigned, unsigned);

#endif

