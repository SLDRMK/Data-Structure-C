#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 100

typedef int NodeType, Power;
int length = 0;

typedef struct SLLISTNode
{
    NodeType data;
    Power power;
    struct SLLISTNode* next;
} Node, * pNode, ** ppNode;

pNode newNode(NodeType x, Power power);
pNode end(pNode head);
void print(pNode head);
void printNode(pNode head, pNode node);
pNode add(ppNode head, NodeType x, Power power);
pNode differentiate(ppNode head);

// make a new Node
pNode newNode(NodeType x, Power power)
{
    pNode temp = (pNode)malloc(sizeof(Node));
    temp->data = x;
    temp->power = power;
    temp->next = temp;
    return temp;
}

// return the end of head
pNode end(pNode head)
{
    if (!head)
        return NULL;
    pNode temp = head;
    while (temp->next != head)
        temp = temp->next;
    return temp;
}

void printNode(pNode head, pNode node)
{
    NodeType data = node->data;
    NodeType power = node->power;
    if (node == head && data > 0 && power == 0)
    {
        printf("%d ", data);
        return;
    }
    if (node != head && data > 0 && power == 0)
    {
        printf("+ %d ", data);
        return;
    }
    if (data < 0 && power == 0)
    {
        printf("- %d ", -data);
        return;
    }
    if (node != head && data > 0 && power)
    {
        if (data != 1)
            printf("+ %d", data);
        else
            printf("+ ");
    }
    if (node == head && node->data > 0 && data != 1 && power)
        printf("%d", node->data);
    if (node->data < 0 && power)
    {
        if (data != 1)
            printf("- %d", -data);
        else
            printf("- ");
    }
    if (node->power > 0)
    {
        printf("x");
        if (node->power != 1)
            printf("^%d", node->power);
    }
    printf(" ");
}

// print the whole list as integers with blank intervals
void print(pNode head)
{
    pNode temp = head;
    if (!head)
    {
        printf("0");
        return;
    }
    while (temp->next != head)
        printNode(head, temp), temp = temp->next;
    printNode(head, temp);
}

// add a new Node in the end
pNode add(ppNode head, NodeType x, Power power)
{
    pNode node, last, temp = *head;
    last = end(*head);
    if (!(*head))
        return *head = newNode(x, power);
    if (temp->power == power)
    {
        temp->data += x;
        return temp;
    }
    if (temp->power < power)
    {
        node = newNode(x, power);
        node->next = temp;
        last->next = node;
        return node;
    }
    if (temp == last)
    {
        if (temp->power == power)
            temp->data += x;
        else
        {
            node = newNode(x, power), temp->next = node, node->next = temp;
            if (temp->power < power)
                return node;
        }
        return *head;
    }
    while (temp->next != last && temp->next->power > power)
    {
        if (temp->power == power)
        {
            temp->data += x;
            return *head;
        }
        temp = temp->next;
    }
    if (temp->next == last)
    {
        if (last->power > power)
            node = newNode(x, power), last->next = node, node->next = *head;
        else if (last->power < power)
            node = newNode(x, power), temp->next = node, node->next = last;
        else
            last->data += x;
        return *head;
    }
    if (temp->next->power == power)
    {
        temp->next->data += x;
        return *head;
    }
    node = newNode(x, power);
    node->next = temp->next;
    temp->next = node;
    return *head;
}

pNode differentiate(ppNode head)
{
    pNode h = *head, nodenext = h->next;
    if (h->power == 0)
        return *head = NULL;
    while (h->next != *head)
        h->data *= h->power, h->power--, h = h->next;
    h->data *= h->power, h->power--;
    h = *head;
    while (nodenext != *head)
    {
        if (nodenext->data == 0)
            h->next = nodenext->next;
        h = h->next, nodenext = h->next;
    }
    if (h->data == 0)
        return *head = NULL;
    return *head;
}

void main()
{
    NodeType x = 0, c, sign;
    Power p = 0;
    pNode list = NULL;
    c = getchar();
    if (c == 'x')
    {
        c = getchar();
        p = 0;
        if (c == ' ')
            p = 1, c = getchar();
        if (c == '^')
        {
            while ((c = getchar()) >= '0' && c <= '9')
                p = p * 10 + c - '0';
        }
        list = add(&list, 1, p);
    }
    while (c != '\n')
    {
        if (list)
            c = getchar();
        sign = 1, x = p = 0;
        if (c == '+')
            c = getchar();
        if (c == '-')
            sign = -1, c = getchar();
        if (c >= '0' && c <= '9')
            x = c - '0';
        while ((c = getchar()) >= '0' && c <= '9')
            x = x * 10 + c - '0';
        if (x == 0)
            x = 1;
        if (c == ' ')
        {
            list = add(&list, x * sign, 0);
            continue;
        }
        if (c == '\n')
        {
            list = add(&list, x * sign, 0);
            break;
        }
        if (c == 'x')
        {
            if ((c = getchar()) == ' ')
            {
                list = add(&list, x * sign, 1);
                continue;
            }
            if (c == '\n')
            {
                list = add(&list, x * sign, 1);
                break;
            }
            if (c == '^')
            {
                while ((c = getchar()) >= '0' && c <= '9')
                    p = p * 10 + c - '0';
            }
            list = add(&list, x * sign, p);
        }
    }
    list = differentiate(&list);
    print(list);
}