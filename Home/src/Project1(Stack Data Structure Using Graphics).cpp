#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>

#define MAX 100 // Maximum size of stack

// Stack structure
char stack[MAX];
int top = -1;

// Function to push character onto stack
void push(char ch)
{
    if (top < MAX - 1)
    {
        stack[++top] = ch;
    }
}

// Function to pop character from stack
char pop()
{
    if (top >= 0)
    {
        return stack[top--];
    }
    return '\0'; // Return NULL character if stack is empty
}

// Function to display stack visually
void displayStack(int x, int y)
{
    int i;
    setcolor(YELLOW);
    settextstyle(3, 0, 3);

    for (i = 0; i <= top; i++)
    {
        char temp[2] = {stack[i], '\0'};
        rectangle(x, y - (i * 40), x + 40, y - (i * 40) - 40);
        outtextxy(x + 10, y - (i * 40) - 30, temp);
        delay(300);
    }
}

// Function to animate popping from stack
void popAnimation(int x, int y, char reversed[], int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        cleardevice();

        // Display remaining stack
        int j;
        setcolor(YELLOW);
        for (j = i; j < len; j++)
        {
            char temp[2] = {stack[j], '\0'};
            rectangle(x, y - (j * 40), x + 40, y - (j * 40) - 40);
            outtextxy(x + 10, y - (j * 40) - 30, temp);
        }

        // Display reversed string dynamically
        setcolor(GREEN);
        reversed[i] = pop();
        reversed[i + 1] = '\0';
        outtextxy(300, 200, "Reversed: ");
        outtextxy(450, 200, reversed);

        delay(500);
    }
}

int main()
{
    char str[MAX], reversed[MAX] = "";
    int gd = DETECT, gm;
    int i, len, x = 200, y = 400;

    printf("Enter a string: ");
    gets(str);

    len = strlen(str);

    initgraph(&gd, &gm, "C:\\MinGW\\include\\graphics.h");

    // Push characters onto stack
    for (i = 0; i < len; i++)
    {
        push(str[i]);
    }

    // Display stack visually
    cleardevice();
    outtextxy(50, 50, "Pushing onto Stack...");
    displayStack(x, y);
    delay(3000);

    // Pop characters and show animation
    cleardevice();
    outtextxy(50, 50, "Popping from Stack...");
    popAnimation(x, y, reversed, len);

    // Final reversed string
    delay(1000);
    cleardevice();
    outtextxy(200, 200, "Final Reversed String: ");
    setcolor(CYAN);
    outtextxy(450, 200, reversed);

    getch();
    closegraph();
    return 0;
}