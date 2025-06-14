#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>

#define PI 3.14159

void rotateTriangle(int x[], int y[], int cx, int cy, float angle)
{
    float rad = angle * PI / 180;
    for (int i = 0; i < 3; i++)
    {
        int tx = x[i] - cx;
        int ty = y[i] - cy;
        x[i] = cx + tx * cos(rad) - ty * sin(rad);
        y[i] = cy + tx * sin(rad) + ty * cos(rad);
    }
}

void drawTriangle(int x[], int y[])
{
    line(x[0], y[0], x[1], y[1]);
    line(x[1], y[1], x[2], y[2]);
    line(x[2], y[2], x[0], y[0]);
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int x[3], y[3];
    int orig_x[3], orig_y[3];

    printf("Enter the coordinates of the triangle:\n");
    for (int i = 0; i < 3; i++)
    {
        printf("Point %d (x y): ", i + 1);
        scanf("%d %d", &x[i], &y[i]);
        orig_x[i] = x[i];
        orig_y[i] = y[i];
    }

    int dx;
    printf("Enter horizontal speed (e.g., 2): ");
    scanf("%d", &dx);

    float angle;
    printf("Enter rotation angle per frame (e.g., 5): ");
    scanf("%f", &angle);
    while (!kbhit())
    {
        cleardevice();
        drawTriangle(x, y);
        int cx = (x[0] + x[1] + x[2]) / 3;
        int cy = (y[0] + y[1] + y[2]) / 3;
        rotateTriangle(x, y, cx, cy, angle);
        for (int i = 0; i < 3; i++)
        {
            x[i] += dx;
            if (x[i] > getmaxx())
            {
                x[i] = orig_x[i];
                y[i] = orig_y[i];
            }
        }
        delay(100); // Delay for visible animation
    }
    getch();
    closegraph();
    return 0;
}

// Enter the coordinates of the triangle:
// Point 1 (x y): 100 200
// Point 2 (x y): 150 150
// Point 3 (x y): 200 200
// Enter horizontal speed (e.g., 2): 5
// Enter rotation angle per frame (e.g., 5): 10