/* 
 * This file is part of KongligSK.
 * Copyright (c) 2020 Henrik Karlsson <henrik10@kth.se>.
 * 
 * KongligSK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * KongligSK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with KongligSK.  If not, see <https://www.gnu.org/licenses/>.
 */
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
inline int ksk_YieldTo(int process_id) __ALWAYS_INLINE__;

/*** Pseudo system calls ***/
/**
 * Receive a 16 byte message from any process
 * Returns the sender's process_id on success.
 * Return -1 if all message boxes are empty.
 */
inline int ksk_RecvAny(char message[16]) __ALWAYS_INLINE__;

#endif /* _KONGLIG_API_H */
