#include <stdio.h>
#include <stdlib.h>

typedef int T;

typedef struct node
{
	T data;
	struct node* pre;
	struct node* next;
} Node, * pNode, ** ppNode;

typedef struct queue
{
	pNode head;
	pNode trailer;
} Queue, * pQueue, ** ppQueue;

pNode newNode(T x);
pQueue newQueue();
void addNext(ppNode node, T x);
T getLast(pNode node) { return node->pre->data; }
T removeLast(ppNode node);
int isempty(pQueue queue) { return queue->head->next == queue->trailer; }
void push(ppQueue queue, T x) { addNext(&((*queue)->head), x); }
T pop(ppQueue queue) { if (isempty(*queue)) return NULL; return removeLast(&((*queue)->trailer)); }
T read(pQueue queue) { return getLast(queue->trailer); }

pNode newNode(T x)
{
	pNode p = (pNode)malloc(sizeof(Node));
	p->data = x;
	p->pre = NULL;
	p->next = NULL;
	return p;
}

pQueue newQueue()
{
	pQueue queue = (pQueue)malloc(sizeof(Queue));
	queue->head = newNode(NULL);
	queue->trailer = newNode(NULL);
	queue->head->next = queue->trailer;
	queue->trailer->pre = queue->head;
	return queue;
}

void addNext(ppNode node, T x)
{
	pNode p = *node;
	pNode n = newNode(x);
	n->next = p->next;
	p->next = n;
	n->next->pre = n;
	n->pre = p;
}

T removeLast(ppNode node)
{
	pNode n = *node;
	pNode pre = n->pre;
	n->pre = pre->pre;
	pre->pre->next = n;
	T x = pre->data;
	free(pre);
	return x;
}

void print(pQueue queue)
{
	pNode n = queue->trailer->pre;
	while (n != queue->head->next)
		printf("%d,", n->data), n = n->pre;
	printf("%d", n->data);
}

int main()
{
	int length = 0;
	pQueue queue = newQueue();
	scanf_s("%d", &length);
	length--;
	T c = getchar();
	while ((c = getchar()) != '\n' && c != EOF && length)
	{
		if (c == ',')
			length--;
		else
			push(&queue, c - '0');
	}
	push(&queue, c - '0');
	print(queue);
}