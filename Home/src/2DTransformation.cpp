#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#define PI 3.14159

void drawShape(int x[], int y[], int n)
{
    for (int i = 0; i < n; i++)
    {
        line(x[i], y[i], x[(i + 1) % n], y[(i + 1) % n]);
    }
}

void scaleShape(int x[], int y[], int n, float sx, float sy)
{
    for (int i = 0; i < n; i++)
    {
        x[i] = x[i] * sx;
        y[i] = y[i] * sy;
    }
}

void translateShape(int x[], int y[], int n, int tx, int ty)
{
    for (int i = 0; i < n; i++)
    {
        x[i] = x[i] + tx;
        y[i] = y[i] + ty;
    }
}

void rotateShape(int x[], int y[], int n, float angle, int px, int py)
{
    float rad = angle * (PI / 180);
    float cosTheta = cos(rad);
    float sinTheta = sin(rad);
    for (int i = 0; i < n; i++)
    {
        int tempX = x[i] - px;
        int tempY = y[i] - py;
        x[i] = px + (tempX * cosTheta - tempY * sinTheta);
        y[i] = py + (tempX * sinTheta + tempY * cosTheta);
    }
}
void shearShape(int x[], int y[], int n, float shx, float shy)
{
    for (int i = 0; i < n; i++)
    {
        x[i] = x[i] + shx * y[i];
        y[i] = y[i] + shy * x[i];
    }
}
void reflectShape(int x[], int y[], int n, int axis)
{
    for (int i = 0; i < n; i++)
    {
        if (axis == 1)
            y[i] = -y[i];
        else if (axis == 2)
            x[i] = -x[i];
        else if (axis == 3)
        {
            x[i] = -x[i];
            y[i] = -y[i];
        }
    }
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\MinGW\\include\\graphics.h");
    int n, i, choice;
    int x[10], y[10];
    float sx, sy, angle, shx, shy;
    int tx, ty, px, py, axis;

    printf("Enter the number of vertices of the polygon: ");
    scanf("%d", &n);
    printf("Enter the coordinates of the polygon:\n");
    for (i = 0; i < n; i++)
    {
        printf("Vertex %d (x y): ", i + 1);
        scanf("%d %d", &x[i], &y[i]);
    }

    setcolor(WHITE);
    drawShape(x, y, n);

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Scaling\n");
        printf("2. Translation\n");
        printf("3. Rotation\n");
        printf("4. Shearing\n");
        printf("5. Reflection\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\nEnter scaling factors (sx sy): ");
            scanf("%f %f", &sx, &sy);
            scaleShape(x, y, n, sx, sy);
            setcolor(RED);
            drawShape(x, y, n);
            break;
        case 2:
            printf("\nEnter translation values (tx ty): ");
            scanf("%d %d", &tx, &ty);
            translateShape(x, y, n, tx, ty);
            setcolor(MAGENTA);
            drawShape(x, y, n);
            break;
        case 3:
            printf("\nEnter rotation angle (in degrees): ");
            scanf("%f", &angle);
            printf("Enter pivot point (px py): ");
            scanf("%d %d", &px, &py);
            rotateShape(x, y, n, angle, px, py);
            setcolor(YELLOW);
            drawShape(x, y, n);
            break;
        case 4:
            printf("\nEnter shearing factors (shx shy): ");
            scanf("%f %f", &shx, &shy);
            shearShape(x, y, n, shx, shy);
            setcolor(CYAN);
            drawShape(x, y, n);
            break;
        case 5:
            printf("\nReflection about:\n1. X-axis\n2. Y-axis\n3. Origin\nEnter choice: ");
            scanf("%d", &axis);
            reflectShape(x, y, n, axis);
            setcolor(GREEN);
            drawShape(x, y, n);
            break;
        case 6:
            closegraph();
            return 0;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
}
