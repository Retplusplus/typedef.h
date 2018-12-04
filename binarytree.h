#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
typedef int TDataType;

typedef struct Bnode {
	TDataType data;
	struct Bnode *left;
	struct Bnode *right;
}Bnode;

static Bnode *CreateNode(TDataType data)
{
	Bnode *node = (Bnode *)malloc(sizeof(Bnode));
	node->data = data;
	node->left = node->right = NULL;
	return node;
}

typedef struct {
	Bnode *root;
	int used;
}RESULT;


//利用含空结点的前序创建二叉树
//返回结果是二叉树的根节点
//preorder：带空节点的前序
//size：preorder的长度
RESULT CreateTree(TDataType preorder[], int size)
{
	if (size == 0)
	{
		RESULT result = { NULL,0};
		return result;
	}

	//根，左子树，右子树
	TDataType rootValue = preorder[0];
	if (rootValue == -1)
	{
		RESULT result = { NULL,1 };
		return result;
	}


	Bnode *root = CreateNode(rootValue);

	RESULT lr = CreateTree(&preorder[1], size - 1);
	root->left = lr.root;
	RESULT rr = CreateTree(&preorder[1 + lr.used], size - 1 - lr.used);
	root->right = rr.root;

	RESULT result = { root,1 + lr.used+rr.used };
	return result;
}

//递归前序
void Preorder(Bnode *root)
{
	if (root == NULL)//终止条件
	{
		return;
	}
	printf("%d ", root->data);
	Preorder(root->left);
	Preorder(root->right);
}

//递归中序
void Inorder(Bnode *root)
{
	if (root == NULL)
	{
		return;
	}
	Inorder(root->left);
	printf("%d ", root->data);
	Inorder(root->right);

}

//递归后序
void postorder(Bnode *root)
{
	if (root == NULL)
	{
		return;
	}
	postorder(root->left);
	postorder(root->right);
	printf("%d ", root->data);
	
}

//求结点个数
int GetSize(Bnode *root)
{
	if (root == NULL)
	{
		return 0;
	}
	return GetSize(root->left) + GetSize(root->right)+1;
}

//叶子结点个数
int GetLeafSize(Bnode *root)
{
	if (root == NULL)
	{
		return 0;
	}
	else if ((root->left == NULL) && (root->right == NULL))
	{
		return 1;
	}
	else
	{
		return GetLeafSize(root->left) + GetLeafSize(root->right);
	}
}

//求第k层结点个数
int GetKsize(Bnode *root, int key)
{
	assert(key > 0);
	if (root == NULL)
	{
		return 0;
	}
	if (key == 1)
	{
		return 1;
	}
	return GetKsize(root->left, key - 1) + GetKsize(root->right, key - 1);
}

//求二叉树高度
#define MAX(a,b) ((a)>(b)?(a):(b))
int GetHeight(Bnode *root)
{
	if (root == NULL)
	{
		return 0;
	}
	int leftherght = GetHeight(root->left);
	int rightheight = GetHeight(root->right);
	return MAX(leftherght, rightheight) + 1;
}


Bnode *Search(Bnode *root, TDataType key)
{
	if (root == NULL) {
		return NULL;
	}
	if (root->data == key)
	{
		return root;
	}
	Bnode *node = Search(root->left, key);
	if (node != NULL)
	{
		return node;
	}
	node=Search(root->right, key);
	if (node != NULL)
	{
		return node;
	}
	else {
		return NULL;
	}
}


//void test()
//{
//	TDataType preorder[] = { 1,2,4,-1,-1,5,-1,-1,3,-1,6,7 };
//	int size = sizeof(preorder) / sizeof(TDataType);
//	RESULT r = CreateTree(preorder, size);
//	Preorder(r.root);
//	printf("\n");
//	printf("%d %d\n", size, r.used);
//}



//QueueInit 初始化
//QueueDestroy 销毁
//QueuePush 放队列尾
//QueueFront 查看队首结点
//QueuePop 弹出队首结点
//QueuEmpty判断队列是否为空
#include"Queue.h"
void LevelOrder(Bnode *root)//层序遍历
{
	Queue queue;
	QueueInit(&queue);
	if (root == NULL)
	{
		return;
	}
	QueuePush(&queue,root);
	while (!QueueEmpty(&queue))
	{
		Bnode *front = QueueFront(&queue);
		QueuePop(&queue);
		printf("%d ", front->data);
		if (front->left != NULL)
		{
			QueuePush(&queue, front->left);
		}
		if (front->right != NULL)
		{
			QueuePush(&queue, front->right);
		}

	}
}

//判断二叉树是否是完全二叉树
int IsComplete(Bnode *root)
{
	Queue queue;
	QueueInit(&queue);
	if (root == NULL)
	{
		return 1;
	}
	QueuePush(&queue, root);
	while (!QueueEmpty(&queue))
	{
		Bnode *front = QueueFront(&queue);
		QueuePop(&queue);
		
		if (front == NULL)
		{
			while (!QueueEmpty(&queue))
			{
				Bnode *node = QueueFront(&queue);
				QueuePop(&queue);
				if (node!= NULL)
				{
					return 0;
				}
			}
			return 1;
		}	
			QueuePush(&queue, front->left);		
			QueuePush(&queue, front->right);
	}
	QueueDestroy(&queue);
	return 1;
}

#include"stack.h"

void PreorderLoop(Bnode *root)//前序遍历  入栈时打印
{
	Stack stack;
	StackInit(&stack);
	Bnode *node = root;
	Bnode *top;
	while (!StackEmpty(&stack) || node != NULL)
	{
		while (node != NULL)
		{
			printf("%d ", node->data);
			StackPush(&stack, node);
			node = node->left;
		}
		top = StackTop(&stack);
		StackPop(&stack);
		node = top->right;
	}
}

void InorderLoop(Bnode *root)//中序遍历 出栈时打印
{
	Stack stack;
	StackInit(&stack);
	Bnode *node = root;
	Bnode *top;
	while (!StackEmpty(&stack) || node != NULL)
	{
		while (node != NULL)
		{
			
			StackPush(&stack, node);
			node = node->left;
		}
		top = StackTop(&stack);
		StackPop(&stack);
		printf("%d ", top->data);
		node = top->right;
	}
}

void PostorderLoop(Bnode *root)//后序遍历
{
	Stack stack;
	StackInit(&stack);
	Bnode *node = root;
	Bnode *top;
	Bnode *last = NULL;

	while (!StackEmpty(&stack) || node != NULL)
	{
		while (node != NULL)
		{

			StackPush(&stack, node);
			node = node->left;
		}
		top = StackTop(&stack);

		if (top->right == NULL || top->right == last)
		{
			printf("%d ", top->data);
			last = top;
			StackPop(&stack);

		}
		else
		{
			node = top->right;
		}
		
	}
}


//镜像
void Mirror(Bnode *root)
{
	if (root == NULL)
	{
		return;
	}
	Bnode *t = root->left;
	root->left = root->right;
	root->left = t;
	Mirror(root->left);
	Mirror(root->right);
}

Bnode *GetNearestAncestor(Bnode *root, Bnode *n1, Bnode *n2)//找最近的公共祖先结点
{
	Bnode *n1InLeft = Search(root->left, n1->data);
	Bnode *n2InLeft = Search(root->left, n2->data);

	if (n1InLeft && !n1InLeft)
	{
		return root;
	}
	if (!n1InLeft&& n2InLeft)
	{
		return root;
	}
	if (n1InLeft)
	{
		return GetNearestAncestor(root->left, n1, n2);
	}
	else
	{
		return GetNearestAncestor(root->right, n1,n2);
	}
}

//平衡二叉树
int IsBalance(Bnode *root)
{
	if (root == NULL)
	{
		
		return 1;
	}
	int isBalance = IsBalance(root->left);
	if (isBalance == 0)
	{
		return 0;
	}
	isBalance = IsBalance(root->right);
	if (isBalance == 0)
	{
		return 0;
	}
	int leftHeight = GetHeight(root->left);
	int rightHeight = GetHeight(root->right);
	int diff = leftHeight - rightHeight;
	if (diff < -1 || diff>1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int IsBalance2(Bnode *root,int *pHeight)
{
	if (root == NULL)
	{
		*pHeight = 0;
		return 1;
	}
	int leftheight;
	int rightheight;
	int leftBalance = IsBalance2(root->left, &leftheight);
	int rightBalance = IsBalance2(root->right, &rightheight);

	*pHeight = MAX(leftheight, rightheight) + 1;
	int diff = leftheight - rightheight;
	if (diff < -1 || diff>1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void test()
{
	TDataType preorder[] = { 1,2,4,-1,-1,5,-1,-1,3,-1,6,7 };
	int size = sizeof(preorder) / sizeof(TDataType);
	RESULT r = CreateTree(preorder, size);
	Preorder(r.root);printf("\n");
	PreorderLoop(r.root); printf("\n");

	Bnode *root = r.root;
	//LevelOrder(root); printf("\n");
}


