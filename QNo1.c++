
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct
{
    char data[MAX];
    int top;
} Stack;

void push(Stack *s, char c)
{
    s->data[++s->top] = c;
}

char pop(Stack *s)
{
    return s->data[s->top--];
}

char peek(Stack *s)
{
    return s->data[s->top];
}

int empty(Stack *s)
{
    return s->top == -1;
}

int priority(char c)
{
    if(c == '*' || c == '/')
        return 2;
    else if(c == '+' || c == '-')
        return 1;
    return 0;
}

void convert(char infix[], char postfix[])
{
    Stack s;
    s.top = -1;

    int i, j = 0;
    char ch;

    for(i = 0; infix[i] != '\0'; i++)
    {
        ch = infix[i];

        if(isdigit(ch))
        {
            postfix[j] = ch;
            j++;
        }
        else if(ch == '(')
        {
            push(&s, ch);
        }
        else if(ch == ')')
        {
            while(!empty(&s) && peek(&s) != '(')
            {
                postfix[j++] = pop(&s);
            }

            if(!empty(&s))
                pop(&s);
        }
        else
        {
            while(!empty(&s) && peek(&s) != '(' &&
                  priority(peek(&s)) >= priority(ch))
            {
                postfix[j++] = pop(&s);
            }

            push(&s, ch);
        }
    }

    while(!empty(&s))
    {
        postfix[j++] = pop(&s);
    }

    postfix[j] = '\0';
}

int main()
{
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    convert(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}

