#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265

// Koch Curve function
void koch(float x1, float y1, float x2, float y2, int level)
{
    if (level == 0)
    {
        line(x1, y1, x2, y2);
        return;
    }

    float dx = (x2 - x1) / 3;
    float dy = (y2 - y1) / 3;

    float x3 = x1 + dx;
    float y3 = y1 + dy;

    float x5 = x2 - dx;
    float y5 = y2 - dy;

    float x4 = x3 + (dx * cos(PI / 3) - dy * sin(PI / 3));
    float y4 = y3 + (dx * sin(PI / 3) + dy * cos(PI / 3));

    koch(x1, y1, x3, y3, level - 1);
    koch(x3, y3, x4, y4, level - 1);
    koch(x4, y4, x5, y5, level - 1);
    koch(x5, y5, x2, y2, level - 1);
}

// Hilbert Curve recursive function
void hilbert(int x, int y, int xi, int xj, int yi, int yj, int level)
{
    if (level <= 0)
    {
        int x1 = x + (xi + yi) / 2;
        int y1 = y + (xj + yj) / 2;
        lineto(x1, y1);
    }
    else
    {
        hilbert(x, y, yi / 2, yj / 2, xi / 2, xj / 2, level - 1);
        hilbert(x + xi / 2, y + xj / 2, xi / 2, xj / 2, yi / 2, yj / 2, level - 1);
        hilbert(x + xi / 2 + yi / 2, y + xj / 2 + yj / 2, xi / 2, xj / 2, yi / 2, yj / 2, level - 1);
        hilbert(x + xi / 2 + yi, y + xj / 2 + yj, -yi / 2, -yj / 2, -xi / 2, -xj / 2, level - 1);
    }
}

int main()
{
    int gd = DETECT, gm;
    int choice, level;
    float x1, y1, x2, y2;

    initgraph(&gd, &gm, "");

    while (1)
    {
        cleardevice();
        printf("\nCurves and Fractals Menu\n");
        printf("1. Koch Curve\n");
        printf("2. Hilbert Curve\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 3)
            break;

        printf("Enter recursion level (1-5 recommended): ");
        scanf("%d", &level);

        if (choice == 1)
        {
            printf("Enter coordinates for Koch Curve:\n");
            printf("x1 y1: ");
            scanf("%f %f", &x1, &y1);
            printf("x2 y2: ");
            scanf("%f %f", &x2, &y2);

            cleardevice();
            koch(x1, y1, x2, y2, level);
        }
        else if (choice == 2)
        {
            int hil_x, hil_y, size;
            printf("Enter starting point (x y): ");
            scanf("%d %d", &hil_x, &hil_y);
            printf("Enter size of square: ");
            scanf("%d", &size);

            cleardevice();
            moveto(hil_x, hil_y);
            hilbert(hil_x, hil_y, size, 0, 0, size, level);
        }
        else
        {
            printf("Invalid choice!\n");
        }

        printf("\nPress any key to continue...");
        getch();
    }

    closegraph();
    return 0;
}

// Curves and Fractals Menu
// 1. Koch Curve
// 2. Hilbert Curve
// 3. Exit
// Enter your choice: 1
// Enter recursion level (1-5 recommended): 5
// Enter coordinates for Koch Curve:
// x1 y1: 100 300
// x2 y2: 500 300

// Curves and Fractals Menu
// 1. Koch Curve
// 2. Hilbert Curve
// 3. Exit
// Enter your choice: 2
// Enter recursion level (1-5 recommended): 2
// Enter starting point (x y): 100 100
// Enter size of square: 200
