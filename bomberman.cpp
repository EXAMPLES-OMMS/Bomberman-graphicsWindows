#include <iostream>
#include <vector>
#include <winbgim.h>

#define M 100
#define H 200
#define E 300

using namespace std;

int background[10][15] = {
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, 0, 0, 0, 0, W, 0, 0, 0, 0, 0, 0, 0, 0, W},
    {W, 0, W, 0, W, W, 0, 0, 0, W, 0, W, 0, 0, W},
    {W, 0, W, 0, 0, W, W, W, W, W, 0, W, W, 0, W},
    {W, 0, W, 0, W, W, 0, 0, 0, 0, 0, W, 0, 0, W},
    {W, 0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    {W, 0, W, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    {W, 0, 0, W, 0, W, W, W, W, W, W, W, 0, 0, W},
    {W, 0, 0, 0, 0, 0, 0, 0, W, 0, 0, 0, 0, 0, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},
};

int ih = 3;
int jh = 3;
int posh = 0;

int ie_1 = 5;
int je_1 = 5;
int die_1 = 0;
int dje_1 = 1;
int pose_1 = 0;

int vidas = 5;

void muro(int x, int y, int e, int color)
{
    setcolor(color);
    rectangle(x, y, x + 5 * e, y + 5 * e);
    rectangle(x + 1.5 * e, y + 1.5 * e, x + 3.5 * e, y + 3.5 * e);
    line(x, y, x + 1.5 * e, y + 1.5 * e);
}

void heroe(int x, int y, int e, int color, int pos)
{
    setcolor(color);
    circle(x + 2.5 * e, y + e, e);
    line(x + 2.5 * e, y + 2 * e, x + 2.5 * e, y + 3 * e);
    line(x + 2.5 * e, y + 3 * e, x + e, y + 5 * e);
    line(x + 2.5 * e, y + 3 * e, x + 4 * e, y + 5 * e);
    if (pos == 0)
    {
        line(x + 2.5 * e, y + 2.5 * e, x + e, y + 2 * e);
        line(x + 2.5 * e, y + 2.5 * e, x + 4 * e, y + 2 * e);
    }
    else if (pos == 1 || pos == 3)
    {
        line(x + 2.5 * e, y + 2.5 * e, x + e, y + 2.5 * e);
        line(x + 2.5 * e, y + 2.5 * e, x + 4 * e, y + 2.5 * e);
    }
    if (pos == 2)
    {
        line(x + 2.5 * e, y + 2.5 * e, x + e, y + 3 * e);
        line(x + 2.5 * e, y + 2.5 * e, x + 4 * e, y + 3 * e);
    }
}

void enemigo(int x, int y, int e, int color, int pos)
{
    setcolor(color);
    ellipse(x + 2.5 * e, y + 2 * e, 0, 180, 2.5 * e, 2 * e);
    circle(x + 2.5 * e, y + 1.5 * e, e);
    circle(x + 2.5 * e, y + 1.5 * e, 0.5 * e);
    if (pos == 0)
    {
        moveto(x, y + 2 * e);
        lineto(x, y + 5 * e);
        lineto(x + 1.5 * e, y + 3 * e);
        lineto(x + 2.5 * e, y + 5 * e);
        lineto(x + 3.5 * e, y + 3 * e);
        lineto(x + 5 * e, y + 5 * e);
        lineto(x + 5 * e, y + 2 * e);
    }
    else if (pos == 1)
    {
        moveto(x, y + 2 * e);
        lineto(x + 1.5 * e, y + 5 * e);
        lineto(x + 1.5 * e, y + 3 * e);
        lineto(x + 3 * e, y + 5 * e);
        lineto(x + 3 * e, y + 3 * e);
        lineto(x + 4.5 * e, y + 5 * e);
        lineto(x + 5 * e, y + 2 * e);
    }
}

void dibujarJuego(int x, int y, int e)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (background[i][j] == W)
            {
                muro(x + j * e * 5, y + i * e * 5, e, 10);
            }
            else if (background[i][j] == H)
            {
                heroe(x + j * e * 5, y + i * e * 5, e, 15, posh);
            }
            else if (background[i][j] == E)
            {
                enemigo(x + j * e * 5, y + i * e * 5, e, 4, pose_1);
            }
        }
    }
}

void se_choco()
{
    if (background[ih][jh] == E)
    {
        cout << "Se murio" << endl;
        ih = 1;
        jh = 1;
        background[ih][jh] = H;
        vidas--;
    }
    if (background[ie_1][je_1] == H)
    {
        cout << "Se murio" << endl;
        ih = 1;
        jh = 1;
        background[ih][jh] = H;
        vidas--;
    }
}

void jugar(int x, int y, int e)
{
    background[ih][jh] = H;
    background[ie_1][je_1] = E;
    int tecla = 0;
    while (true)
    {
        dibujarJuego(x, y, e);
        if (kbhit())
        {
            tecla = getch();
            heroe(x + jh * e * 5, y + ih * e * 5, e, 0, posh);
            if (tecla == 72)
            {
                if (background[ih - 1][jh] != W)
                {
                    background[ih][jh] = 0;
                    ih--;
                    se_choco();
                    background[ih][jh] = H;
                }
            }
            if (tecla == 80)
            {
                if (background[ih + 1][jh] != W)
                {
                    background[ih][jh] = 0;
                    ih++;
                    se_choco();
                    background[ih][jh] = H;
                }
            }
            if (tecla == 75)
            {
                if (background[ih][jh - 1] != W)
                {
                    background[ih][jh] = 0;
                    jh--;
                    se_choco();
                    background[ih][jh] = H;
                }
            }
            if (tecla == 77)
            {
                if (background[ih][jh + 1] != W)
                {
                    background[ih][jh] = 0;
                    jh++;
                    se_choco();
                    background[ih][jh] = H;
                }
            }
        }
        else
        {
            delay(250);
            enemigo(x + je_1 * e * 5, y + ie_1 * e * 5, e, 0, pose_1);
            heroe(x + jh * e * 5, y + ih * e * 5, e, 0, posh);
            if (background[ie_1][je_1 + dje_1] == W)
            {
                dje_1 = -dje_1;
            }
            else
            {
                background[ie_1][je_1] = 0;
                je_1 = je_1 + dje_1;
                se_choco();
                background[ie_1][je_1] = E;
            }
            pose_1 = (++pose_1) % 2;
            posh = (++posh) % 4;
        }
    }
}

int main()
{
    initwindow(800, 600);
    jugar(10, 10, 10);
    getch();
    closegraph();
    return 0;
}

// This receives for points(rect) and a point
bool pointInRect(std::vector<std::vector<int>> rect, int x, int y)
{
    return (
        rect[0][0] < x && rect[0][1] < y &&
        rect[1][0] > x && rect[1][1] < y &&
        rect[2][0] > x && rect[2][1] > y &&
        rect[3][0] < x && rect[3][1] > y);
}

class GameObject
{
public:
    int x, y;
    int width, height;
    GameObject(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    // Compute each corner of an object respect the actual object
    // If you dont know wich are the width or height do this ->> obj1.collision(obj2) || obj2.collision(obj1)
    bool Collision(GameObject o)
    {
        std::vector<std::vector<int>> vec = {
            {x, y},
            {x + width, y},
            {x + width, y + height},
            {x, y + height}
        };
        std::vector<std::vector<int>> ovec = {
            {o.x, o.y},
            {o.x + o.width, o.y},
            {o.x + o.width, o.y + o.height},
            {o.x, o.y + o.height}
        };
        return (
            pointInRect(vec, o.x, o.y) ||
            pointInRect(vec, o.x + o.width, o.y) ||
            pointInRect(vec, o.x + o.width, o.y + o.height) ||
            pointInRect(vec, o.x, o.y + o.height) ||
            pointInRect(ovec, x, y)||
            pointInRect(ovec, x + width, y)||
            pointInRect(ovec, x + width, y + height)||
            pointInRect(ovec, x, y + height) ||
            (x == o.x && y == o.x && width == o.width && height == o.height)
            );
    }
};

