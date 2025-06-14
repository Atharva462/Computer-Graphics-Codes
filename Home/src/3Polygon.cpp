#include <graphics.h>
#include <stdio.h>
#include <conio.h>
void boundaryFill(int x, int y, int fillColor, int boundaryColor)
{
    int currentColor = getpixel(x, y);
    if (currentColor != boundaryColor && currentColor != fillColor)
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
    int currentColor = getpixel(x, y);
    if (currentColor == oldColor)
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
    initgraph(&gd, &gm, "C:\\MinGW\\include\\graphics.h");
    int choice;
    int poly[10] = {100, 100, 200, 100, 150, 200};
    int numPoints = 5;
    printf("Menu:\n");
    printf("1. Boundary Fill Algorithm\n");
    printf("2. Flood Fill Algorithm\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    setcolor(WHITE);
    drawpoly(numPoints, poly);
    int x = 300, y = 100;
    switch (choice)
    {
    case 1:
        boundaryFill(x, y, YELLOW, WHITE);
        break;
    case 2:
        floodFill(x, y, GREEN, BLACK);
        break;
    default:
        printf("Invalid choice!\n");
        break;
    }
    getch();
    closegraph();
    return 0;
}

// Enter the number of vertices of the polygon: 4
// Enter the coordinates of the polygon:
// Vertex 1 (x y): 150     150
// Vertex 2 (x y): 250     150
// Vertex 3 (x y): 250     250
// Vertex 4 (x y): 150     250
// Enter the seed point (x y): 200 200
// Enter the fill color (0-15): 2
// Enter the boundary color (0-15): 15
// Choose the filling algorithm:
// 1. Boundary Fill Algorithm
// 2. Flood Fill Algorithm
// Enter your choice: 2