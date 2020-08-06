#ifndef _KONGLIG_API_H
#define _KONGLIG_API_H
#define __ALWAYS_INLINE__ __attribute__ ((always_inline))

/* Yield to `zone`. */
inline void ksk_Yield(int zone) __ALWAYS_INLINE__;
/* Read csr. */
inline unsigned long ksk_ReadCSR(int csr_num) __ALWAYS_INLINE__;
/* Write csr. */
inline unsigned long ksk_WriteCSR(int csr_num, long value) __ALWAYS_INLINE__;
/* Clear csr. */
inline unsigned long ksk_ClearCSR(int csr_num, long value) __ALWAYS_INLINE__;
/* Set csr. */
inline unsigned long ksk_SetCSR(int csr_num, long value) __ALWAYS_INLINE__;

#endif /* _KONGLIG_API_H */
