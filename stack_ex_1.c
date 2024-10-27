#include <stdio.h>
#include <stdlib.h>
#define MAXSTACK 100

int stack[MAXSTACK];
int top = -1;

int isEmpty()
{
    if (top == -1)
        return 1;
    else
        return 0;
}

int push(int data)
{
    if (top >= MAXSTACK)
    {
        printf("STACK is full, Cannot add data\n");
        return 0;
    }
    else
    {
        stack[++top] = data;
        return 1;
    }
}

int pop()
{
    if (isEmpty())
    {
        return -1;
    }
    else
    {
        return stack[top--];
    }
}

int main()
{
    int value;
    int i;
    do
    {
        printf("PUSH : enter 1, POP : enter 0, STOP : eneter -1 : ");
        scanf("%d", &i);
        if (i == -1)
        {
            break;
        }
        else if (i == 1)
        {
            printf("please enter the element : ");
            scanf("%d", &value);
            push(value);
        }
        else if (i == 0)
        {
            printf("The element poped is : %d\n", pop());
        }
    } while (i != -1);
    printf("============================\n");
    while (!isEmpty())
    {
        printf("Pop from Stack is : %d\n", pop());
    }
    printf("============================\n");
    system("pause");
    return 0;
}
