#include <graphics.h>
#include <stdio.h>
#include <conio.h>

void drawCirclePoints(int xc, int yc, int x, int y)
{
    putpixel(xc + x, yc + y, WHITE);
    putpixel(xc - x, yc + y, WHITE);
    putpixel(xc + x, yc - y, WHITE);
    putpixel(xc - x, yc - y, WHITE);
    putpixel(xc + y, yc + x, WHITE);
    putpixel(xc - y, yc + x, WHITE);
    putpixel(xc + y, yc - x, WHITE);
    putpixel(xc - y, yc - x, WHITE);
}
void BresenhamCircle(int xc, int yc, int r)
{
    int x = 0, y = r;
    int d = 3 - (2 * r);

    while (x <= y)
    {
        drawCirclePoints(xc, yc, x, y);
        x++;

        if (d < 0)
        {
            d += 4 * x + 6;
        }
        else
        {
            y--;
            d += 4 * (x - y) + 10;
        }
    }
}
void MidpointCircle(int xc, int yc, int r)
{
    int x = 0, y = r;
    int p = 1 - r;
    while (x <= y)
    {
        drawCirclePoints(xc, yc, x, y);
        x++;
        if (p < 0)
        {
            p += 2 * x + 1;
        }
        else
        {
            y--;
            p += 2 * (x - y) + 1;
        }
    }
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    int choice, xc, yc, r;
    printf("Menu:\n");
    printf("1. Bresenham's Circle Drawing Algorithm\n");
    printf("2. Midpoint Circle Drawing Algorithm\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter the center coordinates (xc, yc): ");
    scanf("%d%d", &xc, &yc);
    printf("Enter the radius of the circle: ");
    scanf("%d", &r);
    switch (choice)
    {
    case 1:
        BresenhamCircle(xc, yc, r);
        break;
    case 2:
        MidpointCircle(xc, yc, r);
        break;
    default:
        printf("Invalid choice!\n");
        break;
    }
    getch();
    closegraph();
    return 0;
}

// (xc,yc): 300 250  radius: 200
