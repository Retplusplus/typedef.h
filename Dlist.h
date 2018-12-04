#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
//双向链表

typedef struct DNode {
	struct DNode *prev;
	struct DNode *next;
	int data;
}DNode;

DNode *CreateDNode(int data)
{
	DNode *node = (DNode*)malloc(sizeof(DNode));
	node->data = data;
	node->prev = node->next = NULL;
	return node;
}


void DListInit(DNode **ppHead)
{
	assert(ppHead != NULL);
	DNode *node = CreateDNode(0);

	node->prev = node;
	node->next = node;
	*ppHead = node;
}

//清空
void DListclear(DNode *head)
{
	DNode *next;
	for (DNode *cur = head->next; cur != head; cur = next)
	{
		next = cur->next;
		free(cur);
	}

	head->prev = head->next = head;
}

//销毁
void DListDestroy(DNode *head)
{
	DListclear(head);
	free(head);
}

//头插，不需要二级指针
void DListPushFrount(DNode *head, int data)
{
	DNode *node = CreateDNode(data);
	node->prev = head->prev;
	node->next = head;
	head->prev->next = node;
	head->prev = node;
}

void DListPushBack(DNode *head, int data)
{
	DNode *node = CreateDNode(data);
	node->prev = head->prev;
	node->next = head;
	head->prev->next = node;
	head->prev = node;
}

//插入到pos前
void DListInsert(DNode *head, DNode *pos,int data)
{

	DNode *node = CreateDNode(data);
	node->prev = pos->prev;
	node->next = pos;
	pos->prev->next = node;
	pos->prev = node;
}

void DListPopFront(DNode *head)
{
	assert(head->next != head);
	DNode *first = head->next;
	DNode* second = head->next->next;
	head->next = second;
	second->prev = head;
	free(first);
}

void DListPopBack(DNode *head)
{
	assert(head->next != head);
	DNode*node = head->prev;
	head->prev->next = head;
	head->prev = node->prev;
	free(node);
}

void DListerser(DNode *head, DNode *pos)
{
	assert(head->next != head);
	
	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	free(pos);
}


