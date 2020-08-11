#ifndef _UTIL_H
#define _UTIL_H

#define NO_RETURN __attribute__ ((noreturn))
#define ALWAYS_INLINE __attribute__ ((always_inline))
#define HOT __attribute__ ((cold))
#define COLD __attribute__ ((cold))


#if __riscv_xlen == 32
#define SEL(a, b) a
#else
#define SEL(a, b) b
#endif

#define SREG    SEL(sw, sd)
#define LREG    SEL(lw, ld)
#define REG_SIZE SEL(4, 8)

#endif /* _UTIL_H */
