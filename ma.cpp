#include <graphics.h>
#include <vector>
#include <iostream>
#include <string>
#include <deque>
#include <stack>
#include <ctime>
#include <math.h>
using std::string;
using std::vector;

#define SPACE 32

#define W 400
#define D 401

#define cellgrid 12

class Collides;
class Square;
class Player;
class Bomb;

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
class Collides;
class Square;
class Bomb;
class Player;

class Collides //This collision is only for movement
{
    public:
    bool RectCollision(std::vector<std::vector<int>> r1, std::vector<std::vector<int>> r2)//r[4,2]
    {
        return (
            pointInRect(r2, r1[0][0], r1[0][1]) ||
            pointInRect(r2, r1[1][0], r1[1][1]) ||
            pointInRect(r2, r1[2][0], r1[2][1]) ||
            pointInRect(r2, r1[3][0], r1[3][1]) ||

            pointInRect(r1, r2[0][0], r2[0][1]) ||
            pointInRect(r1, r2[1][0], r2[1][1]) ||
            pointInRect(r1, r2[2][0], r2[2][1]) ||
            pointInRect(r1, r2[3][0], r2[3][1])
            ); 
    }
    bool RectCollisionEquals(int x1, int y1, int x2, int y2, int e)
    {
        return RectCollision({
            {x1, y1},
            {x1 + e, y1},
            {x1 + e, y1 + e},
            {x1, y1 + e},
        },
        {
            {x2, y2},
            {x2 + e, y2},
            {x2 + e, y2 + e},
            {x2, y2 + e}
        });
    }
    bool RectCollision(std::vector<int> r1, int w, std::vector<int> r2, int w2)
    {
        std::vector<std::vector<int>> c1 = {
            {r1[0],r1[1]},
            {r1[0]+w,r1[1]},
            {r1[0]+w,r1[1]+w},
            {r1[0],r1[1]+w}
        };
        std::vector<std::vector<int>> c2 = {
            {r2[0],r2[1]},
            {r2[0]+w2,r2[1]},
            {r2[0]+w2,r2[1]+w2},
            {r2[0],r2[1]+w2}
        };
        return RectCollision(c1,c2);
    }
    bool pointInRect(std::vector<std::vector<int>> r, int x, int y)
    {
        return (
            r[0][0] <= x && r[0][1] <= y &&
            r[1][0] >= x && r[1][1] <= y &&
            r[2][0] >= x && r[2][1] >= y &&
            r[3][0] <= x && r[3][1] >= y
        );
    }
};
Collides c;
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
        rectangle(x + m * (e / gridBlock), y + m * (e / gridBlock), x + e - m * (e / gridBlock), y + e - m * (e / gridBlock));
    // rectangle(x + (m) * (e / gridBlock), y + (m) * (e / gridBlock), x + (gridBlock - m) * (e / gridBlock), y + (gridBlock - m) * (e / gridBlock));
    // rectangle(x + e * ((gridBlock - m) / gridBlock), y + e * ((gridBlock - m) / gridBlock), x + e * (m / gridBlock), y + e * (m / gridBlock));
    // rectangle(x + e * ((gridBlock - m) / gridBlock), y + e * ((gridBlock - m) / gridBlock), x + e * (m / gridBlock), y + e * (m / gridBlock));
    else
        rectangle(x, y, x + e, y + e);
}
void circlem(int x, int y, int e, int m)
{
    circle(x + e / 2, y + e / 2, e / 2 - m * (e / gridBlock));
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
    // public:
    float x, y, e;
    float duration;
    int size;
    clock_t beginTime;
    // int beginTime;

public:
    Bomb(int x, int y, int e, BombStats b) : x(x), y(y), e(e)
    {
        duration = b.duration;
        size = b.size;
        // beginTime = std::time(NULL);
        beginTime = std::clock();
    }
    ~Bomb() {}
    void draw()
    {
        setcolor(9);
        circlem(x, y, e, 1);
    }
    void exploid()
    {
        setcolor(0);
        circlem(x, y, e, 1);
    }
    bool isExplode()
    {
        // return true;
        // return duration < (std::time(NULL) - beginTime);
        return duration < (float(std::clock() - beginTime) / CLOCKS_PER_SEC);
    }
};

std::vector<int> getSquare(int x, int y, int e) // return i and j
{
    return {int(x/e), int(y/e)};
}

class Player
{
    // public:
    int x, y, e;
    int width, height;
    int vx, vy;
    int lifes, numBombs, bombsActive;
    BombStats b;

public:
    Player(float x, float y, float e) : x(x+e/cellgrid), y(y+e/cellgrid), e(e)
    {
        height = width = 10*(e/cellgrid);
        vx = vy = 10;
        lifes = 1;
        numBombs = 1;
        bombsActive = 0;
        b.duration = 3;
        b.size = 1;
    }
    void draw()
    {
        setcolor(8);
        // rectangle(x + e * (1 / gridBlock), y + e * (1 / gridBlock), x + e * (12 / gridBlock), y + e * (12 / gridBlock));
        // rectangle(x+1*(e/gridBlock),y,x+e,y+e/2);
        // rectanglem(x, y, e, 1);
        rectangle(x,y,x+width,y+width);
    }
    void updateLeft()
    {
        if (map [y/e][(x-vx)/e] == 0 && map[(y+height)/e][(x-vx)/e] == 0)
        {
            x -= vx;
        }
    }
    void updateRight()
    {
        if (map [y/e][(x+vx+width)/e] == 0 && map[(y+height)/e][(x+vx+width)/e] == 0)
        {
            x += vx;
        }
    }
    void updateTop()
    {
        if (map[(y-vy)/e][x/e] == 0 && map[(y-vy)/e][(x+width)/e] == 0)
        {
            y -= vy;
        }
    }
    void updateBottom()
    {
        if (map[(y+vy+height)/e][x/e] == 0 && map[(y+vy+height)/e][(x+width)/e] == 0)
        {
            y += vy;
        }
    }
    void clear()
    {
        setcolor(0);
        // rectanglem(x, y, e, 1);
        rectangle(x,y,x+width,y+height);
    }
    int getSpeed() { return vx; }
    void updateSpeed(float va = 2) { vx = vy += va; }
    Bomb *putBomb()
    {
        if (numBombs <= 0)
            return nullptr;
        numBombs--;
        bombsActive++;
        // std::cout << x <<  "," << y << " || " << int(x/e) << "," << int(y/e) << '\n';
        return new Bomb(int(x/e)*e, int(y/e)*e, e, b);
    }
    void deleteBomb(Bomb *bb)
    {
        numBombs++;
        bombsActive--;
        bb->exploid();
        delete bb;
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
                if (i==0) wall(xx,yy,e,4);
                else wall(xx, yy, e, GREEN);
                
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
    Player *pl = new Player(50*2, 50*1, scale);
    Bomb *a = nullptr;

    drawMap(0, 0, scale);
    while (1)
    {
        drawBlocks(0, 0, scale);
        pl->draw();
        if (kbhit())
        {
            key = getch();
            // std::cout << key << " || ";
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
                Bomb *aa = pl->putBomb();
                if (aa != nullptr) a = aa;
            }
        }
        if (a != nullptr && a->isExplode())
        {
            pl->deleteBomb(a);
            a = nullptr;
        }

        if (a != nullptr)
        {
            a->draw();
        }
        pl->draw();

        // delay(1000);
        // fflush(stdin);
    }
    // getch();
    closegraph();
    return 0;
}