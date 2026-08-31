#include <stdio.h>
#include <ctype.h>

#define MAX 100

typedef struct { int data[MAX], top; } Stack;

void push(Stack *s, int x) { s->data[++s->top] = x; }
int pop(Stack *s) { return s->data[s->top--]; }

int priority(char c)
{
    return c=='*'||c=='/' ? 2 : c=='+'||c=='-' ? 1 : 0;
}

int calculate(int a, int b, char op)
{
    if(op=='+') return a+b;
    if(op=='-') return a-b;
    if(op=='*') return a*b;
    return a/b;
}

int solve(char exp[])
{
    Stack numStack, opStack;
    numStack.top = opStack.top = -1;
    int i=0;

    while(exp[i])
    {
        if(isdigit(exp[i]))
        {
            int num=0;
            while(isdigit(exp[i]))
                num=num*10+exp[i++]-'0';
            push(&numStack,num);
        }
        else if(exp[i]=='(')
            push(&opStack,exp[i++]);
        else if(exp[i]==')')
        {
            while(opStack.data[opStack.top]!='(')
            {
                char op=pop(&opStack);
                int b=pop(&numStack),a=pop(&numStack);
                push(&numStack,calculate(a,b,op));
            }
            pop(&opStack); i++;
        }
        else
        {
            while(opStack.top>=0 && opStack.data[opStack.top]!='(' &&
                  priority(opStack.data[opStack.top])>=priority(exp[i]))
            {
                char op=pop(&opStack);
                int b=pop(&numStack),a=pop(&numStack);
                push(&numStack,calculate(a,b,op));
            }
            push(&opStack,exp[i++]);
        }
    }

    while(opStack.top>=0)
    {
        char op=pop(&opStack);
        int b=pop(&numStack),a=pop(&numStack);
        push(&numStack,calculate(a,b,op));
    }

    return pop(&numStack);
}

int main(int argc,char *argv[])
{
    if(argc!=2) return 1;
    printf("Value = %d\n",solve(argv[1]));
    return 0;
}