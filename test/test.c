#include <stdio.h>
#include <stdlib.h>

const int MAXLEN = 100;

typedef char T;

typedef struct stack
{
	T* s;
	T* end;
	int len;
} Stack, * pStack, ** ppStack;

pStack init();
void push(ppStack pp, T x);
T top(pStack p) { if (!isempty(p)) return *(p->end - 1); printf("ERROR: Stack is empty"); return NULL; }
T pop(ppStack pp);
void printc(pStack p);
int isempty(pStack p);

pStack init()
{
	pStack p = (pStack)malloc(sizeof(pStack));
	if (p)
	{
		p->end = p->s = (T*)malloc(sizeof(T) * MAXLEN);
		p->len = 0;
	}
	return p;
}

void push(ppStack pp, T x)
{
	pStack p = *pp;
	if (p->len < MAXLEN - 1)
	{
		*(p->end++) = x;
		return;
	}
	printf("ERROR: Stack is full\n");
}

T pop(ppStack pp)
{
	pStack p = *pp;
	if (p->s == p->end)
	{
		printf("ERROR: Stack is empty");
		return NULL;
	}
	T x = *(--p->end);
	return x;
}

void printc(pStack p)
{
	T* temp = p->s;
	while (temp != p->end)
		printf("%c", *temp), temp++;
	printf("\n");
}

int isempty(pStack p)
{
	if (p->s == p->end)
		return 1;
	return 0;
}

int higher(char op1, char op2)
{
	if ((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-'))
		return 1;
	return 0;
}

int isCharacter(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int isOp(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

int main()
{
	pStack opr = init();
	char c = 0, op = 0;
	while ((c = getchar()) !=  '\n' && c != EOF)
	{
		if (isCharacter(c))
		{
			printf("%c", c);
			continue;
		}
		if (c == '(')
			push(&opr, c);
		if (isOp(c))
		{
			if (isempty(opr) || higher(c, op = top(opr)) || op == '(')
				push(&opr, c);
			else
			{
				printf("%c", pop(&opr));
				while (isOp(c))
				{
					if (c == '\n' || c == EOF)
						return 0;
					else if (isempty(opr) || higher(c, op = top(opr)) || op == '(')
					{
						push(&opr, c);
						break;
					}
					else
						printf("%c", pop(&opr));
				}
			}
		}
		if (c == ')')
			while ((op = pop(&opr)) != '(')
				printf("%c", op);
	}
	while (!isempty(opr))
		printf("%c", pop(&opr));
	return 0;
}