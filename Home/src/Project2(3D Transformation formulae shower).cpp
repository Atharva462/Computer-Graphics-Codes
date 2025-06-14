#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void showMatrix(char *title, char *matrix[], int rows)
{
    cleardevice();
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    setcolor(WHITE);
    outtextxy(50, 20, title);

    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    setcolor(LIGHTGREEN);

    int y = 100;
    for (int i = 0; i < rows; i++)
    {
        outtextxy(100, y, matrix[i]);
        y += 40;
        delay(200);
    }

    delay(500);
    setcolor(LIGHTCYAN);
    outtextxy(100, y + 50, "Click anywhere to return to menu...");

    while (!ismouseclick(WM_LBUTTONDOWN))
        delay(100);
    clearmouseclick(WM_LBUTTONDOWN);
}

void showSubOptions(char *title, char *labels[], char *matrices[][6], int counts[])
{
    cleardevice();
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    outtextxy(50, 30, title);

    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    for (int i = 0; i < 3; i++)
    {
        outtextxy(100, 120 + i * 60, labels[i]);
    }

    int x, y;
    while (1)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            for (int i = 0; i < 3; i++)
            {
                if (y >= (120 + i * 60) && y <= (140 + i * 60))
                {
                    showMatrix(labels[i], matrices[i], counts[i]);
                    cleardevice();
                    outtextxy(50, 30, title);
                    for (int j = 0; j < 3; j++)
                        outtextxy(100, 120 + j * 60, labels[j]);
                }
            }

            if (y > 320)
                break;
        }
    }
}

void showRotationDirection(char *direction)
{
    char *labels[] = {
        "Rotation about X-axis",
        "Rotation about Y-axis",
        "Rotation about Z-axis"};

    char *cw[3][6] = {
        {"| 1            0                0             0 |       | x |",
         "| 0       cosTheta    sinTheta       0 |  *   | y |",
         "| 0      -sinTheta    cosTheta      0 |       | z |",
         "| 0            0                0             1 |       | 1 |",
         "",
         "P` = R.P (Clockwise X-axis)"},
        {"| cosTheta     0   -sinTheta     0 |      | x |",
         "|      0            1          0           0 |  *   | y |",
         "| sinTheta      0    cosTheta     0 |      | z |",
         "|      0            0          0             1 |      | 1 |",
         "",
         "P` = R.P (Clockwise Y-axis)"},
        {"| cosTheta   sinTheta     0     0 |      | x |",
         "|-sinTheta   cosTheta     0     0 |  *   | y |",
         "|      0               0            1     0 |      | z |",
         "|      0               0            0     1 |      | 1 |",
         "",
         "P` = R.P (Clockwise Z-axis)"}};

    char *acw[3][6] = {
        {"| 1        0                0             0 |       | x |",
         "| 0   cosTheta   -sinTheta      0 |  *   | y |",
         "| 0   sinTheta    cosTheta      0 |      | z |",
         "| 0        0                0             1 |       | 1 |",
         "",
         "P` = R.P (Anti-clockwise X-axis)"},
        {"| cosTheta     0   -sinTheta     0 |      | x |",
         "|      0            1        0             0 |  *   | y |",
         "| sinTheta     0    cosTheta     0 |      | z |",
         "|      0            0         0             1 |      | 1 |",
         "",
         "P` = R.P (Anti-clockwise Y-axis)"},
        {"| cosTheta  -sinTheta     0     0 |      | x |",
         "| sinTheta   cosTheta     0     0 |  *   | y |",
         "|      0              0             1     0 |      | z |",
         "|      0              0             0     1 |      | 1 |",
         "",
         "P` = R.P (Anti-clockwise Z-axis)"}};

    int counts[] = {6, 6, 6};

    if (strcmp(direction, "Clockwise") == 0)
        showSubOptions("Clockwise Rotation", labels, cw, counts);
    else
        showSubOptions("Anti-Clockwise Rotation", labels, acw, counts);
}

void showRotationMenu()
{
    cleardevice();
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    outtextxy(50, 30, "Rotation Menu");

    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(100, 120, "Clockwise");
    outtextxy(100, 180, "Anti-Clockwise");

    int x, y;
    while (1)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (y >= 120 && y <= 140)
                showRotationDirection("Clockwise");
            else if (y >= 180 && y <= 200)
                showRotationDirection("Anti-Clockwise");
            else if (y > 250)
                break;

            cleardevice();
            outtextxy(50, 30, "Rotation Menu");
            outtextxy(100, 120, "Clockwise");
            outtextxy(100, 180, "Anti-Clockwise");
        }
    }
}

void drawMenu()
{
    cleardevice();
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    setcolor(YELLOW);
    outtextxy(100, 30, "3D Transformation Matrix Calculator");

    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    setcolor(CYAN);
    outtextxy(100, 100, "1. Translation");
    outtextxy(100, 150, "2. Scaling");
    outtextxy(100, 200, "3. Rotation");
    outtextxy(100, 250, "4. Reflection");
    outtextxy(100, 300, "5. Shearing");

    outtextxy(100, 380, "Click on a transformation type...");
}

void handleClick(int x, int y)
{
    if (y >= 100 && y <= 130)
    {
        char *translation[] = {
            "| 1  0  0  Tx |      | x |",
            "| 0  1  0  Ty |  *   | y |",
            "| 0  0  1  Tz |      | z |",
            "| 0  0  0  1  |      | 1 |",
            "",
            "P` = T.P"};
        showMatrix("Translation Matrix", translation, 6);
    }
    else if (y >= 150 && y <= 180)
    {
        char *scaling[] = {
            "| Sx  0   0   0 |      | x |",
            "| 0   Sy  0   0 |  *   | y |",
            "| 0   0   Sz  0 |      | z |",
            "| 0   0   0   1 |      | 1 |",
            "",
            "P` = S.P"};
        showMatrix("Scaling Matrix", scaling, 6);
    }
    else if (y >= 200 && y <= 230)
    {
        showRotationMenu();
    }
    else if (y >= 250 && y <= 280)
    {
        char *labels[] = {
            "Reflection about X-Axis",
            "Reflection about Y-Axis",
            "Reflection about Z-Axis"};
        char *reflections[3][6] = {
            {"| 1  0   0   0 |      | x |",
             "| 0 -1   0   0 |  *   | y |",
             "| 0  0  -1   0 |      | z |",
             "| 0  0   0   1 |      | 1 |",
             "",
             "P` = R.P"},
            {"| -1  0   0   0 |      | x |",
             "|  0  1   0   0 |  *   | y |",
             "|  0  0  -1   0 |      | z |",
             "|  0  0   0   1 |      | 1 |",
             "",
             "P` = R.P"},
            {"|-1   0   0   0 |      | x |",
             "| 0  -1   0   0 |  *   | y |",
             "| 0   0   1   0 |      | z |",
             "| 0   0   0   1 |      | 1 |",
             "",
             "P` = R.P"}};
        int counts[] = {6, 6, 6};
        showSubOptions("Reflection Options", labels, reflections, counts);
    }
    else if (y >= 300 && y <= 330)
    {
        char *labels[] = {
            "Shear in X direction",
            "Shear in Y direction",
            "Shear in Z direction"};
        char *shears[3][6] = {
            {"| 1       0     0  0 |      | x |",
             "| Shy   1     0  0 |  *   | y |",
             "| Shz   0     1  0 |      | z |",
             "| 0       0     0  1 |      | 1 |",
             "",
             "P` = Sh.P"},
            {"| 1   Shx     0       0 |       | x |",
             "| 0     1       0       0 |  *   | y |",
             "| 0   Shz     1       0 |       | z |",
             "| 0     0       0       1 |       | 1 |",
             "",
             "P` = Sh.P"},
            {"| 1   0       Shx    0 |      | x |",
             "| 0   1       Shy    0 |  *   | y |",
             "| 0   0         1      0 |      | z |",
             "| 0   0         0      1 |      | 1 |",
             "",
             "P` = Sh.P"}};
        int counts[] = {6, 6, 6};
        showSubOptions("Shearing Options", labels, shears, counts);
    }
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    drawMenu();
    int done = 0;

    while (!done)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            handleClick(x, y);
            drawMenu();
        }

        if (kbhit() && getch() == 27)
            done = 1;
    }

    closegraph();
    return 0;
}
