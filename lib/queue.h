 
/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define WAIT_NONE     0
#define WAIT_FOREVER  -1

/**
 * @file queue.h
 * @brief Thread Safe FIFO bounded queue
 * @note Since most implementations of the queue are backed by a condition
 * variable implementation, it isn't available on systems without threads.
 * Although condition variables are sometimes available without threads.
 */

/**
 * @defgroup Util_FIFO Thread Safe FIFO bounded queue
 * @ingroup Util
 * @{
 */

/**
 * opaque structure
 */
typedef struct queue_t queue_t;

/**
 * create a FIFO queue
 * @param queue The new queue
 * @param queue_capacity maximum size of the queue
 * @param a pool to allocate queue from
 */
bool queue_create(queue_t **queue, uint32_t queue_capacity);

/**
 * push/add an object to the queue, blocking if the queue is already full
 *
 * @param queue the queue
 * @param data the data
 * @returns EINTR the blocking was interrupted (try again)
 * @returns EOF the queue has been terminated
 * @returns SUCCESS on a successful push
 */
bool queue_push(queue_t *queue, void *data);

/**
 * push/add an object to the queue, blocking if the queue is already full
 *
 * @param queue         the queue
 * @param data          the data
 * @param wait_ms       milliseconds to wait
 * @returns EINTR   the blocking was interrupted (try again)
 * @returns EOF     the queue has been terminated
 * @returns SUCCESS on a successful push
 */
bool queue_timedpush(queue_t *queue, void *data, int wait_ms);

/**
 * pop/get an object from the queue, blocking if the queue is already empty
 *
 * @param queue the queue
 * @param data the data
 * @returns EINTR the blocking was interrupted (try again)
 * @returns EOF if the queue has been terminated
 * @returns SUCCESS on a successful pop
 */
bool queue_pop(queue_t *queue, void **data);

/**
 * pop/get an object from the queue, blocking if the queue is already empty
 *
 * @param queue         the queue
 * @param data          the data
 * @param wait_ms       milliseconds to wait
 * @returns EINTR   the blocking was interrupted (try again)
 * @returns EOF     if the queue has been terminated
 * @returns SUCCESS on a successful pop
 */
bool queue_timedpop(queue_t *queue, void **data, int wait_ms);

/**
 * push/add an object to the queue, returning immediately if the queue is full
 *
 * @param queue the queue
 * @param data the data
 * @returns EINTR the blocking operation was interrupted (try again)
 * @returns EAGAIN the queue is full
 * @returns EOF the queue has been terminated
 * @returns SUCCESS on a successful push
 */
bool queue_trypush(queue_t *queue, void *data);

/**
 * pop/get an object to the queue, returning immediately if the queue is empty
 *
 * @param queue the queue
 * @param data the data
 * @returns EINTR the blocking operation was interrupted (try again)
 * @returns EAGAIN the queue is empty
 * @returns EOF the queue has been terminated
 * @returns SUCCESS on a successful pop
 */
bool queue_trypop(queue_t *queue, void **data);

/**
 * returns the size of the queue.
 *
 * @warning this is not threadsafe, and is intended for reporting/monitoring
 * of the queue.
 * @param queue the queue
 * @returns the size of the queue
 */
uint32_t queue_size(queue_t *queue);

/**
 * interrupt all the threads blocking on this queue.
 *
 * @param queue the queue
 */
bool queue_interrupt_all(queue_t *queue);

/**
 * terminate the queue, sending an interrupt to all the
 * blocking threads
 *
 * @param queue the queue
 */
bool queue_term(queue_t *queue);

/**
 * destroy queue
 * @param  queue
 * @return     always true
 */
void queue_destroy(queue_t * queue);

#endif /* RPAQUEUE_H */