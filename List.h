#pragma once

//无头节点单向链表
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
//头插
void SListPushFront(Node **ppfirst, DataType data)
{
	assert(ppfirst != NULL);
	Node* node = BuyNode(data);
	*ppfirst = node;

}
//尾插
void SListPushBack(Node** ppfirst, DataType data)
{
	assert(ppfirst != NULL);//ppfirst传来的地址不为空
	if (*ppfirst == NULL)//链表是一条空链表
	{
		*ppfirst = BuyNode(data);
		return;
	}
	Node* node = BuyNode(data);//为节点申请空间
	Node* pre = *ppfirst;
	while (pre->next!=NULL)
	{
		pre = pre->next;
	}
	pre->next = node;
	pre->next->data = data;
	node->next = NULL;
}
//头删
void SListPopFront(Node** ppfirst)
{
	assert(ppfirst!=NULL);
	assert(*ppfirst != NULL);
	Node *cur = *ppfirst;
	*ppfirst = (*ppfirst)->next;
	free(cur);
}

//尾删
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

//查找
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
//在pos前插入
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

//删除pos这个结点
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