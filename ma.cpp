#include <graphics.h>
#include <vector>
#include <iostream>
#include <string>
#include <deque>
#include <stack>
using std::string;
using std::vector;

#define SPACE 32

#define W 400
#define D 401

const int mapHeight = 11;
const int mapWidth = 15;

// Grid graphics for block
const int gridBlock = 12;

int map[mapHeight][mapWidth] = {
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, 0, 0, D, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    {W, 0, W, D, W, 0, W, 0, W, 0, W, 0, W, 0, W},
    {W, D, 0, D, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    {W, 0, W, 0, W, 0, W, 0, W, 0, W, 0, W, 0, W},
    {W, D, D, D, D, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    {W, 0, W, 0, W, 0, W, 0, W, 0, W, 0, W, 0, W},
    {W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    {W, 0, W, 0, W, 0, W, 0, W, 0, W, 0, W, 0, W},
    {W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W}};

struct Position
{
    float x, y;
};
struct Velocity
{
    float vy, vx;
};
struct Sprite
{
    float width, height;
    int color;
};
struct BombStats
{
    int duration, size;
};
struct PlayerStats
{
    int lifes, numBombs, bombsActive;
};
void rectanglem(int x, int y, int e, int m);
void circlem(int x, int y, int e, int m);

class Square
{
    int x, y, e, width, color;

public:
    Square(int x, int y, int e) : x(x), y(y), e(e)
    {
        width = x + e;
    }
    void Render1(int color)
    {
        setcolor(color);
        setfillstyle(SOLID_FILL, color);
        rectangle(x, y, x + e, y + e);
    }
    void Render2(int color)
    {
        setfillstyle(SOLID_FILL, color);
        setcolor(YELLOW);
        rectangle(x, y, x + e, y + e);
        setcolor(RED);
        rectanglem(x, y, e, 3);
        setcolor(BLUE);
        rectanglem(x, y, e, 4);
    }
};
void rectanglem(int x, int y, int e, int m)
{
    if (m <= gridBlock / 2)
        // rectangle(x + (gridBlock - m)*(e/gridBlock), y + (gridBlock - m) * (e/gridBlock), x + m * (e/gridBlock), y + m*(e/gridBlock));
        rectangle(x + m*(e/gridBlock), y + m*(e/gridBlock), x+e - m*(e/gridBlock), y+e - m*(e/gridBlock));
        // rectangle(x + (m) * (e / gridBlock), y + (m) * (e / gridBlock), x + (gridBlock - m) * (e / gridBlock), y + (gridBlock - m) * (e / gridBlock));
    // rectangle(x + e * ((gridBlock - m) / gridBlock), y + e * ((gridBlock - m) / gridBlock), x + e * (m / gridBlock), y + e * (m / gridBlock));
    // rectangle(x + e * ((gridBlock - m) / gridBlock), y + e * ((gridBlock - m) / gridBlock), x + e * (m / gridBlock), y + e * (m / gridBlock));
    else
        rectangle(x, y, x + e, y + e);
}
void circlem(int x, int y, int e, int m)
{
    circle(x+e/2, y+e/2, e/2-m*(e/gridBlock));
}
void wall(int x, int y, int e, int color)
{
    Square *w = new Square(x, y, e);
    w->Render1(color);
}
void squ1(int x, int y, int e, int color)
{
    Square *w = new Square(x, y, e);
    w->Render2(color);
}
void squ2()
{
}

class Bomb
{
public:
    float x, y, e;
    float explTime;
    float size;

public:
    Bomb(int x, int y, int e, BombStats b) : x(x), y(y), e(e)
    {
        explTime = b.duration;
        size = b.size;
    }
    void draw()
    {
        setcolor(9);
        circlem(x, y, e, 1);
    }
};

class Player
{
public:
    float x, y, e;
    float vx, vy;
    int lifes, numBombs, bombsActive;
    BombStats b;

public:
    Player(float x, float y, float e) : x(x), y(y), e(e)
    {
        vx = vy = 10;
        lifes = 1;
        numBombs = 1;
        bombsActive = 0;
        b.duration = 2;
        b.size = 1;
    }
    void draw()
    {
        setcolor(8);
        // rectangle(x + e * (1 / gridBlock), y + e * (1 / gridBlock), x + e * (12 / gridBlock), y + e * (12 / gridBlock));
        // rectangle(x+1*(e/gridBlock),y,x+e,y+e/2);
        rectanglem(x, y, e, 1);
    }
    void updateLeft() { x -= vx; }
    void updateRight() { x += vx; }
    void updateTop() { y -= vy; }
    void updateBottom() { y += vy; }
    void clear()
    {
        setcolor(0);
        rectanglem(x, y, e, 1);
    }
    void setSpeed(float v) { vx = vy; }
    int getSpeed() { return vx; }
    void updateSpeed(float va = 2) { vx = vy += va; }
    Bomb *putBomb()
    {
        if (numBombs <= 0)
            return nullptr;
        numBombs--;
        bombsActive++;
        return new Bomb(x, y, e, b);
    }
};

void drawMap(int x, int y, int e)
{
    for (int i = 0; i < mapHeight; i++)
    {
        for (int j = 0; j < mapWidth; j++)
        {
            int xx = x + j * e;
            int yy = y + i * e;
            if (map[i][j] == W)
            {
                wall(xx, yy, e, GREEN);
            }
        }
    }
}
void drawBlocks(int x, int y, int e)
{
    for (int i = 0; i < mapHeight; i++)
    {
        for (int j = 0; j < mapWidth; j++)
        {
            int xx = x + j * e;
            int yy = y + i * e;
            if (map[i][j] == D)
            {
                squ1(xx, yy, e, GREEN);
            }
        }
    }
}

int main()
{
    int key = -1;
    initwindow(1280, 720);
    const int scale = 50;
    Player *pl = new Player(scale, scale, scale);

    drawMap(0, 0, scale);
    while (1)
    {
        drawBlocks(0, 0, scale);
        pl->draw();
        if (kbhit())
        {
            key = getch();
            std::cout << key << " || ";
            if (key == 'q' || key == 'Q')
            {
                break;
            }
            if (key == 75 || key == 'a' || key == 'A') // left
            {
                pl->clear();
                pl->updateLeft();
            }
            if (key == 77 || key == 'd' || key == 'D') // right
            {
                pl->clear();
                pl->updateRight();
            }
            if (key == 72 || key == 'w' || key == 'W') // top
            {
                pl->clear();
                pl->updateTop();
            }
            if (key == 80 || key == 's' || key == 'S') // bottom
            {
                pl->clear();
                pl->updateBottom();
            }
            if (key == SPACE)
            {
                Bomb *a = pl->putBomb();
                if (a != nullptr)
                {
                    a->draw();
                }
            }
        }

        // drawMap(0, 0, scale);
        // drawBlocks(0, 0, scale);
        pl->draw();

        // delay(100);
        fflush(stdin);
    }
    // getch();
    closegraph();
    return 0;
}