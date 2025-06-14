#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#define PI 3.14159

void drawShape(int x[], int y[], int z[], int n)
{
    for (int i = 0; i < n; i++)
    {
        line(x[i], y[i], x[(i + 1) % n], y[(i + 1) % n]);
    }
}

void scaleShape(int x[], int y[], int z[], int n, float sx, float sy, float sz)
{
    for (int i = 0; i < n; i++)
    {
        x[i] = x[i] * sx;
        y[i] = y[i] * sy;
        z[i] = z[i] * sz;
    }
}

void translateShape(int x[], int y[], int z[], int n, int tx, int ty, int tz)
{
    for (int i = 0; i < n; i++)
    {
        x[i] = x[i] + tx;
        y[i] = y[i] + ty;
        z[i] = z[i] + tz;
    }
}

void rotateShapeX(int x[], int y[], int z[], int n, float angle)
{
    float rad = angle * (PI / 180);
    float cosTheta = cos(rad);
    float sinTheta = sin(rad);
    for (int i = 0; i < n; i++)
    {
        int tempY = y[i];
        int tempZ = z[i];
        y[i] = tempY * cosTheta - tempZ * sinTheta;
        z[i] = tempY * sinTheta + tempZ * cosTheta;
    }
}

void rotateShapeY(int x[], int y[], int z[], int n, float angle)
{
    float rad = angle * (PI / 180);
    float cosTheta = cos(rad);
    float sinTheta = sin(rad);
    for (int i = 0; i < n; i++)
    {
        int tempX = x[i];
        int tempZ = z[i];
        x[i] = tempX * cosTheta + tempZ * sinTheta;
        z[i] = -tempX * sinTheta + tempZ * cosTheta;
    }
}

void rotateShapeZ(int x[], int y[], int z[], int n, float angle)
{
    float rad = angle * (PI / 180);
    float cosTheta = cos(rad);
    float sinTheta = sin(rad);
    for (int i = 0; i < n; i++)
    {
        int tempX = x[i];
        int tempY = y[i];
        x[i] = tempX * cosTheta - tempY * sinTheta;
        y[i] = tempX * sinTheta + tempY * cosTheta;
    }
}

void shearShape(int x[], int y[], int z[], int n, float shxy, float shxz, float shyz)
{
    for (int i = 0; i < n; i++)
    {
        x[i] = x[i] + shxy * y[i] + shxz * z[i];
        y[i] = y[i] + shyz * z[i];
        z[i] = z[i];
    }
}

void reflectShape(int x[], int y[], int z[], int n, int plane)
{
    for (int i = 0; i < n; i++)
    {
        if (plane == 1)
            z[i] = -z[i];
        else if (plane == 2)
            x[i] = -x[i];
        else if (plane == 3)
            y[i] = -y[i];
    }
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\MinGW\\include\\graphics.h");
    int n, i, choice;
    int x[10], y[10], z[10];
    float sx, sy, sz, angle, shxy, shxz, shyz;
    int tx, ty, tz, plane;

    printf("Enter the number of vertices of the 3D shape: ");
    scanf("%d", &n);
    printf("Enter the coordinates of the 3D shape (x y z):\n");
    for (i = 0; i < n; i++)
    {
        printf("Vertex %d (x y z): ", i + 1);
        scanf("%d %d %d", &x[i], &y[i], &z[i]);
    }

    setcolor(WHITE);
    drawShape(x, y, z, n);

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Scaling\n");
        printf("2. Translation\n");
        printf("3. Rotation around X-axis\n");
        printf("4. Rotation around Y-axis\n");
        printf("5. Rotation around Z-axis\n");
        printf("6. Shearing\n");
        printf("7. Reflection\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\nEnter scaling factors (sx sy sz): ");
            scanf("%f %f %f", &sx, &sy, &sz);
            scaleShape(x, y, z, n, sx, sy, sz);
            setcolor(RED);
            drawShape(x, y, z, n);
            break;
        case 2:
            printf("\nEnter translation values (tx ty tz): ");
            scanf("%d %d %d", &tx, &ty, &tz);
            translateShape(x, y, z, n, tx, ty, tz);
            setcolor(MAGENTA);
            drawShape(x, y, z, n);
            break;
        case 3:
            printf("\nEnter rotation angle around X-axis (in degrees): ");
            scanf("%f", &angle);
            rotateShapeX(x, y, z, n, angle);
            setcolor(YELLOW);
            drawShape(x, y, z, n);
            break;
        case 4:
            printf("\nEnter rotation angle around Y-axis (in degrees): ");
            scanf("%f", &angle);
            rotateShapeY(x, y, z, n, angle);
            setcolor(CYAN);
            drawShape(x, y, z, n);
            break;
        case 5:
            printf("\nEnter rotation angle around Z-axis (in degrees): ");
            scanf("%f", &angle);
            rotateShapeZ(x, y, z, n, angle);
            setcolor(GREEN);
            drawShape(x, y, z, n);
            break;
        case 6:
            printf("\nEnter shearing factors (shxy shxz shyz): ");
            scanf("%f %f %f", &shxy, &shxz, &shyz);
            shearShape(x, y, z, n, shxy, shxz, shyz);
            setcolor(BLUE);
            drawShape(x, y, z, n);
            break;
        case 7:
            printf("\nReflection about:\n1. XY plane\n2. YZ plane\n3. XZ plane\nEnter choice: ");
            scanf("%d", &plane);
            reflectShape(x, y, z, n, plane);
            setcolor(WHITE);
            drawShape(x, y, z, n);
            break;
        case 8:
            closegraph();
            return 0;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
}
