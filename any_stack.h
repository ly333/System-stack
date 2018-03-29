/*************************************************************************
	> File Name: any_stack.h
	> Author: luoyi
	> Mail: 596890983@qq.com
	> Created Time: 2018年02月28日 星期三 10时49分32秒
 ************************************************************************/

#ifndef _ANY_STACK_H
#define _ANY_STACK_H

#include <stdlib.h>
#include <string.h>

#define STACK_OK 1
#define STACK_ERROR 0

typedef struct Stack {
    char *data;
    int top, data_size, size;
} Stack;

#define init_stack(n, T) (__init_stack(n ,sizeof(T)))
#define push_stack(s, data) (__push_stack(s, (char *)(data)))
#define top_stack(s, T) (T *)(__top_stack(s))

Stack *__init_stack(int n, int data_size) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (char *)malloc(data_size * n);
    s->data_size = data_size;
    s->size = n;
    s->top = -1;
    return s;
}

int __push_stack(Stack *s, char *data) {
    if(s->size - 1 == s->top) {
        return STACK_ERROR;
    }
    s->top += 1;
    memcpy(s->data + s->top * s->data_size, data, s->data_size);
    return STACK_OK;
}

int empty_stack(Stack *s) {
    return s->top == -1;
}

int pop_stack(Stack *s) {
    if(empty_stack(s)) {
        return STACK_ERROR;
    }
    s->top--;
    return STACK_OK;
}

char *__top_stack(Stack *s) {
    if(empty_stack(s)) {
        return NULL;
    }
    return s->data + s->top * s->data_size;
}

void clear_stack(Stack *s) {
    if(!s) return;
    free(s->data);
    return;
}

#endif
