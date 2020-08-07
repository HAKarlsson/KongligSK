#ifndef _KONGLIG_API_H
#define _KONGLIG_API_H
#define __ALWAYS_INLINE__ __attribute__ ((always_inline))

/*** Base system calls ***/
/** 
 * Send a 16 byte message from process. 
 * Returns the receivers process_id on success. 
 * Returns -1 if receiver's message box is full. 
 */
inline int ksk_Send(int process_id, char message[16]) __ALWAYS_INLINE__;

/** 
 * Receive a 16 byte message from process. 
 * If process_id is -1, then receive a message from any process.
 * Returns the senders process_id on success. 
 * Returns -1 if the message box is empty. 
 */
inline int ksk_Recv(int process_id, char message[16]) __ALWAYS_INLINE__;

/**
 * Yield the remaining time slice to process. 
 */
inline void ksk_YieldTo(int process_id) __ALWAYS_INLINE__;

/*** Pseudo system calls ***/
/**
 * Receive a 16 byte message from any process
 * Returns the sender's process_id on success.
 * Return -1 if all message boxes are empty.
 */
inline int ksk_RecvAny(char message[16]) __ALWAYS_INLINE__;

#endif /* _KONGLIG_API_H */
