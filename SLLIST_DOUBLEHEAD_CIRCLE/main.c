#include <stdio.h>
#include <stdlib.h>
#define MAXSTEP 10000

typedef int NodeType;
int length = 0;
int step = 0;

typedef struct DLLISTNode
{
    NodeType data;
    struct DLLISTNode* pre;
    struct DLLISTNode* next;
    int freq;
    int step;
} Node, * pNode, ** ppNode;

pNode newNode(NodeType x);
pNode end(pNode head);
int num(pNode head);
void print(pNode head);
void printc(pNode head);
void add(ppNode head, NodeType x);
pNode delete(ppNode head, int index);
pNode bubble(ppNode head, ppNode node);
pNode locate(ppNode head, NodeType x);
pNode swap(pNode head, ppNode nodea, ppNode nodeb);

// make a new Node
pNode newNode(NodeType x)
{
    pNode temp = (pNode)malloc(sizeof(Node));
    temp->data = x;
    temp->next = temp;
    temp->pre = temp;
    temp->freq = 0;
    temp->step = MAXSTEP;
    return temp;
}

// return the end of head
pNode end(pNode head)
{
    return head->pre;
}

// return the length of the list and update the value length
int num(pNode head)
{
    length = 1;
    pNode temp = head->next;
    while (temp != head)
        temp = temp->next, length++;
    return length;
}

// print the whole list as integers with blank intervals
void print(pNode head)
{
    pNode temp = head;
    while (temp->next != head)
        printf("%d ", temp->data), temp = temp->next;
    printf("%d\n", temp->data);
}

// print the whole list as characters with comma intervals
void printc(pNode head)
{
    pNode temp = head;
    while (temp->next != head)
        printf("%c,", temp->data), temp = temp->next;
    printf("%c", temp->data);
}

// add a new Node in the end
void add(ppNode head, NodeType x)
{
    pNode newN = newNode(x);
    pNode temp = (*head)->pre;
    temp->next = (*head)->pre = newN;
    newN->pre = temp;
    newN->next = *head;
}

pNode swap(pNode head, ppNode nodea, ppNode nodeb)
{
    pNode a = *nodea, b = *nodeb;
    if (a->next == b)
    {
        pNode tempnext = b->next, temppre = a->pre;
        tempnext->pre = a, temppre->next = b;
        b->next = a, a->pre = b;
        a->next = tempnext;
        b->pre = temppre;
    }
    else if (a == b->next)
        return swap(head, nodeb, nodea);
    else
    {
        pNode apre = a->pre, anext = a->next, bpre = b->pre, bnext = b->next;
        apre->next = anext->pre = b, bpre->next = bnext->pre = a;
        a->pre = bpre, a->next = bnext, b->pre = apre, b->next = anext;
    }
    if (a == head)
        return b;
    if (b == head)
        return a;
    return head;
}

pNode bubble(ppNode head, ppNode node)
{
    if (*node == *head)
        return *head;
    while ((*node)->pre->data != (*head)->data && (*node)->freq > (*node)->pre->freq)
        *head = swap(*head, node, &((*node)->pre));
    while ((*node)->pre->data != (*head)->data && (*node)->freq == (*node)->pre->freq)
    {
        if ((*node)->step > (*node)->pre->step)
            break;
        *head = swap(*head, node, &((*node)->pre));
    }
    if ((*node)->pre->data == (*head)->data && (*node)->freq > (*head)->freq || ((*node)->freq == (*head)->freq && (*node)->step < (*head)->step))
    {
        *head = swap(*head, node, head);
        return *node;
    }
    return *head;
}

pNode locate(ppNode head, NodeType x)
{
    pNode temp = *head;
    while (temp->next != (*head) && temp->data != x)
        temp = temp->next;
    if (temp->data == x)
    {
        temp->freq++;
        if (temp->step == MAXSTEP)
        {
            temp->step = step;
        }
        step++;
        return bubble(head, &temp);
    }
    return *head;
}


void main()
{
    pNode head = newNode(1);
    add(&head, 2);
    add(&head, 3);
    add(&head, 4);
    add(&head, 5);
    print(head);
    head = locate(&head, 1);
    head = locate(&head, 3);
    head = locate(&head, 2);
    head = locate(&head, 2);
    print(head);
}