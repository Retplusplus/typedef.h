#pragma once

#include<assert.h>

#define MAXSIZE 100

typedef void* SDataType;

typedef struct Stack
{
	SDataType array[MAXSIZE];
	int top;
}Stack;

void StackInit(Stack* ps)//初始化
{
	ps->top = 0;
}

//删除
void StackDestroy(Stack *ps)
{
	ps->top = 0;
}

//尾插
void StackPush(Stack* ps, SDataType data)
{
	assert(ps->top < MAXSIZE);
	ps->array[ps->top++] = data;
}

//尾删
void StackPop(Stack *ps)
{
	assert(ps->top > 0);
	ps->top--;
}


//返回栈顶元素
SDataType StackTop(const Stack *ps)
{
	assert(ps->top>0);
	return ps->array[ps->top-1];//个数并不等于下标，所以需要减1,不能减减，会改变自身大小
}

//栈内元素个数
int StackSize(const Stack *ps)
{
	return ps->top;
}

//栈是否为空
int StackEmpty(const Stack *ps)
{
	return ps->top == 0 ? 1 : 0;
}

