/*
 * This file is part of KongligSK.
 * Copyright (c) 2020 Henrik Karlsson <henrik10@kth.se>.
 *
 * KongligSK is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * KongligSK is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with KongligSK.  If not, see
 * <https://www.gnu.org/licenses/>.
 */
#ifndef _KONGLIG_API_H
#define _KONGLIG_API_H

// Yield remaining time slice to another partition.
//
// Parameters:
//	partition_id: other partition's id
//
// Returns:
//	0 if yielded
//	2 if partition_id is invalid
long ksk_YieldTo(long partition_id);

// Send a message to another partition, returns 0 if the
// message was delivered, returns 1 if destination inbox was
// full.
//
// Parameters:
//	partition_id: destination partition's ID
//	msgs: message buffer
//
// Returns:
//	0 if message was sent
//	1 if destination inbox was full
//	2 if partition_id is invalid
long ksk_Send(long partition_id, long msgs[4]);

// Receive a message from another partition, returns 0 if a
// message was received, returns 1 if there is no new
// message.
//
// Parameters:
//  partition_id: sender's partition ID
//  msgs: message buffer
//
// Returns:
//	0 if message was received
//	1 if inbox is empty
//	2 if partition_id is invalid
long ksk_Recv(long partition_id, long msgs[4]);

// Send a message to another partition, yields to the other
// partition until the message can be delivered. Fails if
// partition_id is invalid.
//
// Parameters:
//	partition_id: receiver's partition ID
//	msgs: message buffer
//
// Returns:
//	0 if message was sent
//	2 if partition_id is invalid
long ksk_WaitSend(long partition_id, long msgs[4]);

// Receive a message from another partition, yields to the
// other partition until a message has arrived. Fails if
// partition_id is invalid.
//
// Parameters:
//	partition_id: sender's partition ID
//	msgs: message buffer
//
// Returns:
//	0 if message was received
//	2 if partition_id is invalid
long ksk_WaitRecv(long partition_id, long msgs[4]);

#endif /* _KONGLIG_API_H */
