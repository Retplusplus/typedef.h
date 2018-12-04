#pragma once

#include<assert.h>

#define MAXSIZE 100

typedef void* SDataType;

typedef struct Stack
{
	SDataType array[MAXSIZE];
	int top;
}Stack;

void StackInit(Stack* ps)//��ʼ��
{
	ps->top = 0;
}

//ɾ��
void StackDestroy(Stack *ps)
{
	ps->top = 0;
}

//β��
void StackPush(Stack* ps, SDataType data)
{
	assert(ps->top < MAXSIZE);
	ps->array[ps->top++] = data;
}

//βɾ
void StackPop(Stack *ps)
{
	assert(ps->top > 0);
	ps->top--;
}


//����ջ��Ԫ��
SDataType StackTop(const Stack *ps)
{
	assert(ps->top>0);
	return ps->array[ps->top-1];//�������������±꣬������Ҫ��1,���ܼ�������ı������С
}

//ջ��Ԫ�ظ���
int StackSize(const Stack *ps)
{
	return ps->top;
}

//ջ�Ƿ�Ϊ��
int StackEmpty(const Stack *ps)
{
	return ps->top == 0 ? 1 : 0;
}

