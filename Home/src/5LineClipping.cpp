#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

int x_min, y_min, x_max, y_max;

// Function to compute region code
int computeCode(int x, int y)
{
    int code = 0;
    if (x < x_min)
        code |= LEFT;
    if (x > x_max)
        code |= RIGHT;
    if (y < y_min)
        code |= BOTTOM;
    if (y > y_max)
        code |= TOP;
    return code;
}

void drawClippingWindow()
{
    rectangle(x_min, y_min, x_max, y_max);
}

// Cohen-Sutherland Line Clipping
void cohenSutherlandClip(int x1, int y1, int x2, int y2)
{
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    int accept = 0;

    while (1)
    {
        if ((code1 == 0) && (code2 == 0))
        {
            accept = 1;
            break;
        }
        else if (code1 & code2)
        {
            break;
        }
        else
        {
            int code_out;
            int x, y;

            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            if (code_out & TOP)
            {
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            }
            else if (code_out & BOTTOM)
            {
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            }
            else if (code_out & RIGHT)
            {
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            }
            else if (code_out & LEFT)
            {
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            if (code_out == code1)
            {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept)
        line(x1, y1, x2, y2);
}

// Midpoint Subdivision Line Clipping
void midpointSubdivision(int x1, int y1, int x2, int y2)
{
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);

    if ((code1 | code2) == 0)
    {
        line(x1, y1, x2, y2);
    }
    else if (code1 & code2)
    {
        return;
    }
    else
    {
        int xm = (x1 + x2) / 2;
        int ym = (y1 + y2) / 2;

        if (abs(x1 - x2) < 1 && abs(y1 - y2) < 1)
            return;

        midpointSubdivision(x1, y1, xm, ym);
        midpointSubdivision(xm, ym, x2, y2);
    }
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    printf("Enter Clipping Window Coordinates:\n");
    printf("x_min y_min: ");
    scanf("%d %d", &x_min, &y_min);
    printf("x_max y_max: ");
    scanf("%d %d", &x_max, &y_max);

    int x1, y1, x2, y2, choice;

    printf("Enter Line Coordinates:\n");
    printf("x1 y1: ");
    scanf("%d %d", &x1, &y1);
    printf("x2 y2: ");
    scanf("%d %d", &x2, &y2);

    do
    {
        cleardevice();
        drawClippingWindow();
        setcolor(YELLOW);
        line(x1, y1, x2, y2);
        setcolor(WHITE);

        printf("\nMenu:\n");
        printf("1. Cohen-Sutherland Line Clipping\n");
        printf("2. Midpoint Subdivision Line Clipping\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        cleardevice();
        drawClippingWindow();

        switch (choice)
        {
        case 1:
            setcolor(RED);
            cohenSutherlandClip(x1, y1, x2, y2);
            break;
        case 2:
            setcolor(GREEN);
            midpointSubdivision(x1, y1, x2, y2);
            break;
        case 3:
            break;
        default:
            printf("Invalid choice!\n");
        }

        getch();
    } while (choice != 3);

    closegraph();
    return 0;
}

// Enter Clipping Window Coordinates:
// x_min y_min: 100 100
// x_max y_max: 300 300
// Enter Line Coordinates:
// x1 y1: 50 50
// x2 y2: 250 250