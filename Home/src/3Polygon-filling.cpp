#include <stdio.h>
#include <graphics.h>
void boundaryFill(int x, int y, int fillColor, int boundaryColor)
{
    if (getpixel(x, y) != boundaryColor && getpixel(x, y) != fillColor)
    {
        putpixel(x, y, fillColor);
        boundaryFill(x + 1, y, fillColor, boundaryColor);
        boundaryFill(x - 1, y, fillColor, boundaryColor);
        boundaryFill(x, y + 1, fillColor, boundaryColor);
        boundaryFill(x, y - 1, fillColor, boundaryColor);
    }
}
void floodFill(int x, int y, int fillColor, int oldColor)
{
    if (getpixel(x, y) == oldColor)
    {
        putpixel(x, y, fillColor);
        floodFill(x + 1, y, fillColor, oldColor);
        floodFill(x - 1, y, fillColor, oldColor);
        floodFill(x, y + 1, fillColor, oldColor);
        floodFill(x, y - 1, fillColor, oldColor);
    }
}
int main()
{
    int gd = DETECT, gm;
    int choice, n, i, x[10], y[10], seedX, seedY, fillColor, boundaryColor;
    initgraph(&gd, &gm, "C:\\MinGW\\include\\graphics.h");
    printf("Enter the number of vertices of the polygon: ");
    scanf("%d", &n);
    printf("Enter the coordinates of the polygon:\n");
    for (i = 0; i < n; i++)
    {
        printf("Vertex %d (x y): ", i + 1);
        scanf("%d %d", &x[i], &y[i]);
    }
    printf("Enter the seed point (x y): ");
    scanf("%d %d", &seedX, &seedY);
    printf("Enter the fill color (0-15): ");
    scanf("%d", &fillColor);
    printf("Enter the boundary color (0-15): ");
    scanf("%d", &boundaryColor);
    x[n] = x[0];
    y[n] = y[0];
    for (i = 0; i < n; i++)
    {
        line(x[i], y[i], x[i + 1], y[i + 1]);
    }
    printf("Choose the filling algorithm:\n");
    printf("1. Boundary Fill Algorithm\n");
    printf("2. Flood Fill Algorithm\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        boundaryFill(seedX, seedY, fillColor, boundaryColor);
        break;
    case 2:
        floodFill(seedX, seedY, fillColor, getpixel(seedX, seedY));
        break;
    default:
        printf("Invalid choice\n");
    }
    getch();
    closegraph();
    return 0;
}
