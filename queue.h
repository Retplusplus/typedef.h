#pragma once

#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
typedef void * QDataType;

typedef struct Qnode {
	struct Qnode *next;
	QDataType data;
}Qnode;

typedef struct Queue {
	Qnode *front;
	Qnode *rear;
	int size;
}Queue;

void QueueInit(Queue *pQ)
{
	assert(pQ != NULL);
	pQ->size++;
	pQ->front = pQ->rear = NULL;
}

//����
void QueueDestroy(Queue *pQ)
{
	Qnode *cur, *next;
	for (cur = pQ->front; cur != NULL; cur = next)
	{
		next = cur->next;
		
		free(cur);
	}
	pQ->front = pQ->rear = NULL;

}


//����
void QueuePush(Queue *pQ, QDataType data)
{
	Qnode *node = (Qnode*)malloc(sizeof(Qnode));
	node->data = data;
	node->next = NULL;
	if (pQ->rear == NULL)
	{
		pQ->front = node;
		pQ->rear = node;
		return;
	}
	pQ->rear->next = node;
	pQ->rear = node;
}


//ɾ��
void QueuePop(Queue *pQ)
{
	assert(pQ != NULL);
	assert(pQ->front != NULL);
	pQ->size--;
	if (pQ->front == pQ->rear)
	{
		free(pQ->front);
		pQ->front = pQ->rear = NULL;
	}
	else
	{
		Qnode *cur = pQ->front;
		pQ->front = pQ->front->next;
		free(cur);
	}
}

//��Ԫ�ص�ֵ
QDataType QueueFront(const Queue *pQ)
{
	assert(pQ != NULL);
	assert(pQ->front != NULL);
	return pQ->front->data;
}

//�Ƿ�Ϊ�ն���
int QueueEmpty(const Queue *pQ)
{
	return pQ->front == NULL ? 1 : 0;
}

//���д�С
int QueueSize(const Queue *pQ)
{
	return pQ->size;
}