#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 100

typedef int NodeType;
int length = 0;

typedef struct SLLISTNode
{
    NodeType data;
    struct SLLISTNode* next;
} Node, * pNode, ** ppNode;

pNode newNode(NodeType x);
pNode end(pNode head);
int num(pNode head);
void print(pNode head);
void printc(pNode head);
void add(ppNode head, NodeType x);
pNode delete(ppNode head, int index);
pNode deleteRange(ppNode head, NodeType mink, NodeType maxk);
pNode deleteRangeOrderly(ppNode head, NodeType mink, NodeType maxk);
void releaseList(ppNode head);
pNode reverse(ppNode head);
pNode addHead(ppNode head, NodeType x);

pNode newNode(NodeType x)
{
    pNode temp = (pNode)malloc(sizeof(Node));
    temp->data = x;
    temp->next = NULL;
    return temp;
}

pNode end(pNode head)
{
    if (!head)
        return NULL;
    while (head->next)
        head = head->next;
    return head;
}

int num(pNode head)
{
    length = 0;
    pNode temp = head;
    while (temp)
        temp = temp->next, length++;
    return length;
}

void print(pNode head)
{
    pNode temp = head;
    if (!head)
    {
        printf("NULL");
        return;
    }
    while (temp->next)
        printf("%d ", temp->data), temp = temp->next;
    printf("%d", temp->data);
}

void printc(pNode head)
{
    pNode temp = head;
    if (!head)
    {
        printf("NULL");
        return;
    }
    while (temp->next)
        printf("%c,", temp->data), temp = temp->next;
    printf("%c", temp->data);
}

void add(ppNode head, NodeType x)
{
    pNode tail = newNode(x);
    pNode last;
    last = end(*head);
    last->next = tail;
    length++;
}

pNode delete(ppNode head, int index)
{
    pNode temp = *head;
    pNode temp1 = *head;
    if (!index)
    {
        temp1 = temp1->next, free(temp);
        return temp1;
    }
    while (--index)
        temp = temp->next;
    pNode x = temp->next;
    if (!x)
        temp->next = NULL;
    else
        temp->next = x->next;
    free(x);
    length--;
    return *head;
}

pNode deleteRange(ppNode head, NodeType mink, NodeType maxk)
{
    pNode temp = NULL;
    pNode pointer = *head;
    while (pointer && (pointer->data > mink && pointer->data < maxk))
        pointer = pointer->next;
    if (!pointer)
        return NULL;
    temp = newNode(pointer->data);
    pointer = pointer->next;
    while (pointer)
    {
        if (pointer->data <= mink || pointer->data >= maxk)
            add(&temp, pointer->data);
        pointer = pointer->next;
    }
    releaseList(head);
    return temp;
}

pNode deleteRangeOrderly(ppNode head, NodeType mink, NodeType maxk)
{
    pNode temp = *head;
    pNode temp0 = NULL, temp1 = NULL;
    if (!temp)
        return NULL;
    while (temp->next && temp->next->data <= mink)
        temp = temp->next;
    if (temp)
        temp0 = temp;
    while (temp0->next && temp0->next->data < maxk)
        temp0 = temp0->next;
    temp->next = temp0->next;
    temp0->next = NULL;
    releaseList(&temp);
    return *head;
}

pNode reverse(ppNode head)
{
    pNode pointer = *head, temp = NULL;
    while (pointer)
        temp = addHead(&temp, pointer->data), pointer = pointer->next;
    pointer = *head;
    releaseList(&pointer);
    return temp;
}

pNode addHead(ppNode head, NodeType x)
{
    pNode newHead = newNode(x);
    newHead->next = *head;
    *head = newHead;
    return *head;
}

void releaseList(ppNode head)
{
    pNode temp = *head;
    pNode pointer = temp;
    while (!temp)
    {
        temp = temp->next;
        free(pointer);
        pointer = temp;
    }
}

void main()
{
    int temp = 0, c;
    c = getchar();
    pNode head = newNode(c);
    while ((c = getchar()) != EOF && c != '\n')
    {
        add(&head, getchar());
    }
    head = reverse(&head);
    printc(head);
}