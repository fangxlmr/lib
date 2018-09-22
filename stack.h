/*
 * stack.h
 *
 * Written by fangxl (fangxlmr@foxmail.com) on 22/09/2018.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3.0 of the License, or
 * (at your option) any later version.
 *   
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *     
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see the file COPYING, or write
 * to the Free Software Foundation, Inc.
 */

#ifndef BULLET_STACK_H
#define BULLET_STACK_H

#include <stdlib.h>

/**
 * define a stack_t structure
 */
typedef struct _stack stack_t;

/**
 * stack_new - Create a new stack
 *
 * Return a stack_t pointer if success,
 * NULL pointer otherwise.
 */
extern stack_t *stack_new(void);

/**
 * stack_free - Destroy a stack
 *
 * @stack: a stack to be destroyed
 */
extern void stack_free(stack_t *stack);

/**
 * stack_push - Stack push
 *
 * @stack: the stack
 * @x: value to be stored
 *
 * Return 0 if success, -1 otherwise.
 *
 * Note that NULL stack or NULL x are invalid.
 */
extern int stack_push(stack_t *stack, const void *x);

/**
 * stack_pop - Stack pop
 *
 * @stack: the stack
 *
 * Return stack top value, NULL pointer if the stack is empty.
 *
 * The top entry (if exists) of the stack will be
 * removed after this operation. 
 */
extern void *stack_pop(stack_t *stack);

/**
 * stack_peek - Peek top value of the stack
 *
 * @stack: the stack
 *
 * Return stack top value, NULL pointer if the stack is empty.
 *
 * The top entry (if exists) of the stack will not be
 * remove unlike function stack_pop(), so that the
 * stack will remain unchanged.
 */
extern void *stack_peek(stack_t *stack);

/**
 * stack_isempty - Check stack is empty or not
 *
 * @stack: the stack
 *
 * Return 0 if the stack is empty, -1 if not.
 */
extern int stack_isempty(stack_t *stack);

/**
 * stack_size - Get size of the stack
 *
 * @stack: the stack
 *
 * Return size of the stack. Return 0 if stack is empty.
 */
extern size_t stack_size(stack_t *stack);

#endif /* BULLET_STACK_H */
