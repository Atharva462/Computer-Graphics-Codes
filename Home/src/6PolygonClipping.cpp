#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int x_min, y_min, x_max, y_max;

#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

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

void drawPolygon(int *x, int *y, int n)
{
    for (int i = 0; i < n - 1; i++)
        line(x[i], y[i], x[i + 1], y[i + 1]);
    line(x[n - 1], y[n - 1], x[0], y[0]);
}

void clipWithCohenSutherland(int *x, int *y, int n)
{
    for (int i = 0; i < n - 1; i++)
        cohenSutherlandClip(x[i], y[i], x[i + 1], y[i + 1]);
    cohenSutherlandClip(x[n - 1], y[n - 1], x[0], y[0]);
}

void clipWithMidpoint(int *x, int *y, int n)
{
    for (int i = 0; i < n - 1; i++)
        midpointSubdivision(x[i], y[i], x[i + 1], y[i + 1]);
    midpointSubdivision(x[n - 1], y[n - 1], x[0], y[0]);
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    printf("Enter clipping window coordinates:\n");
    printf("Enter x_min and y_min: ");
    scanf("%d %d", &x_min, &y_min);
    printf("Enter x_max and y_max: ");
    scanf("%d %d", &x_max, &y_max);

    int n, choice;
    printf("Enter number of vertices in polygon: ");
    scanf("%d", &n);

    int *x = (int *)malloc(n * sizeof(int));
    int *y = (int *)malloc(n * sizeof(int));

    printf("Enter coordinates (x y) of each vertex:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Vertex %d: ", i + 1);
        scanf("%d %d", &x[i], &y[i]);
    }

    do
    {
        cleardevice();
        drawClippingWindow();
        drawPolygon(x, y, n);

        printf("\nMenu:\n");
        printf("1. Clip using Cohen-Sutherland\n");
        printf("2. Clip using Midpoint Subdivision\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        cleardevice();
        drawClippingWindow();

        switch (choice)
        {
        case 1:
            clipWithCohenSutherland(x, y, n);
            break;
        case 2:
            clipWithMidpoint(x, y, n);
            break;
        case 3:
            break;
        default:
            printf("Invalid choice.\n");
        }

        getch();
    } while (choice != 3);

    closegraph();
    free(x);
    free(y);
    return 0;
}

// Enter clipping window coordinates:
// Enter x_min and y_min: 150 150
// Enter x_max and y_max: 300 300
// Enter number of vertices in polygon: 3
// Enter coordinates (x y) of each vertex:
// Vertex 1: 100 100
// Vertex 2: 200 200
// Vertex 3: 250 100