#pragma once

//��ͷ�ڵ㵥������
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
typedef int DataType;

typedef struct Node {
	DataType data;
	struct Node* next;
}Node;

static Node* BuyNode(DataType data)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	return node;
}

void SListInit(Node **ppfirst)
{
	assert(ppfirst != NULL);
	*ppfirst = NULL;
}
//ͷ��
void SListPushFront(Node **ppfirst, DataType data)
{
	assert(ppfirst != NULL);
	Node* node = BuyNode(data);
	*ppfirst = node;

}
//β��
void SListPushBack(Node** ppfirst, DataType data)
{
	assert(ppfirst != NULL);//ppfirst�����ĵ�ַ��Ϊ��
	if (*ppfirst == NULL)//������һ��������
	{
		*ppfirst = BuyNode(data);
		return;
	}
	Node* node = BuyNode(data);//Ϊ�ڵ�����ռ�
	Node* pre = *ppfirst;
	while (pre->next!=NULL)
	{
		pre = pre->next;
	}
	pre->next = node;
	pre->next->data = data;
	node->next = NULL;
}
//ͷɾ
void SListPopFront(Node** ppfirst)
{
	assert(ppfirst!=NULL);
	assert(*ppfirst != NULL);
	Node *cur = *ppfirst;
	*ppfirst = (*ppfirst)->next;
	free(cur);
}

//βɾ
void SListPopBack(Node **ppfirst)
{
	assert(ppfirst != NULL);
	Node* cur = *ppfirst;
	if ((*ppfirst)->next == NULL)
	{
		free(ppfirst);
		ppfirst = NULL;
	}
	while (cur->next->next!=NULL)
	{
		cur = cur->next;
	}
	free(cur->next);
	cur->next = NULL;
}

//����
Node *SListFind(Node*first, DataType data)
{
	for (Node *cur = first; cur != NULL; cur = cur->next)
	{
		if (cur->data == data)
		{
			return cur;
		}
	}
	return NULL;

}
//��posǰ����
void SListInsert(Node **ppfirst,Node *pos, DataType data)
{
	assert(ppfirst != NULL);
	if (*ppfirst == pos)
	{
		SListPushFront(ppfirst, data);
		return;
	}
	Node *cur = *ppfirst;
	while (cur->next != pos)
	{
		cur = cur->next;
	}
	cur->next = BuyNode(data);
	cur->next->next = pos;
}

//ɾ��pos������
void SListeraser(Node **ppfirst,Node* pos)
{
	if (*ppfirst == pos)
	{
		SListPopFront(ppfirst);
		return;
	}
	Node *cur = *ppfirst;
	while (cur->next != pos)
	{
		
		cur = cur->next;
	}
	cur->next = pos->next;
	free(pos);

}

void Test()
{
	
	Node* first;
	SListInit(&first);
	SListPushBack(&first, 0);
	SListPushBack(&first, 1);
	SListPushBack(&first, 2);
	SListPushBack(&first, 3);
	SListPushBack(&first, 4);
}