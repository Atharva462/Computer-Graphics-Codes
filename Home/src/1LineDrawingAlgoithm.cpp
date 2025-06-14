#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
void DDA_Line(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1, dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xIncrement = dx / (float)steps;
    float yIncrement = dy / (float)steps;
    float x = x1, y = y1;
    putpixel(round(x), round(y), WHITE);
    for (int i = 0; i < steps; i++)
    {
        x += xIncrement;
        y += yIncrement;
        putpixel(round(x), round(y), WHITE);
    }
}
void Bresenham_Line(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int p = 2 * dy - dx;
    int twoDy = 2 * dy, twoDyDx = 2 * (dy - dx);
    int x = x1, y = y1;
    putpixel(x, y, WHITE);
    while (x < x2)
    {
        x++;
        if (p < 0)
        {
            p += twoDy;
        }
        else
        {
            y++;
            p += twoDyDx;
        }
        putpixel(x, y, WHITE);
    }
}
int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    int choice, x1, y1, x2, y2;
    printf("Menu:\n");
    printf("1. DDA Line Drawing Algorithm\n");
    printf("2. Bresenham's Line Drawing Algorithm\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    printf("Enter the coordinates of the starting point (x1, y1): ");
    scanf("%d%d", &x1, &y1);
    printf("Enter the coordinates of the ending point (x2, y2): ");
    scanf("%d%d", &x2, &y2);
    switch (choice)
    {
    case 1:
        DDA_Line(x1, y1, x2, y2);
        break;
    case 2:
        Bresenham_Line(x1, y1, x2, y2);
        break;
    default:
        printf("Invalid choice\n");
        break;
    }
    getch();
    closegraph();
    return 0;
}
