#ifndef _KONGLIG_API_H
#define _KONGLIG_API_H
#define __ALWAYS_INLINE__ __attribute__ ((always_inline))

/*** Base system calls ***/
/* Yield to `zone`. */
inline void ksk_YieldTo(int zone) __ALWAYS_INLINE__;
/* Atomically read and write to csr. */
inline unsigned long ksk_CSRRW(int csr_num, long value) __ALWAYS_INLINE__;
/* Atomically read and set to csr. */
inline unsigned long ksk_CSRRS(int csr_num, long value) __ALWAYS_INLINE__;
/* Atomically read and clear to csr. */
inline unsigned long ksk_CSRRC(int csr_num, long value) __ALWAYS_INLINE__;

/*** Pseudo system calls ***/
/* Read csr. */
inline unsigned long ksk_CSRR(int csr_num) __ALWAYS_INLINE__;
/* Write csr. */
inline void ksk_CSRW(int csr_num, long value) __ALWAYS_INLINE__;
/* Set csr. */
inline void ksk_CSRS(int csr_num, long value) __ALWAYS_INLINE__;
/* Clear csr. */
inline void ksk_CSRC(int csr_num, long value) __ALWAYS_INLINE__;

#endif /* _KONGLIG_API_H */
