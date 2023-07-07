#include <graphics.h>
#include <vector>
#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <queue>
#include <vector>
#include <chrono>
#include <algorithm>
using std::string;
using std::vector;

#define SPACE 32

#define W 400
#define D 401
#define B 501

// Grid graphics for block
#define cellgrid 12

class Collides;
class Square;
class Player;
class Bomb;


void drawMap(int x, int y, int e);
void selectWinningCell(int&, int&);


const int mapHeight = 11;
const int mapWidth = 15;

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

int winCellX = -1, winCellY = -1;

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

void generateRandomMap(int map[mapHeight][mapWidth]) {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(0,9);

    for (int i = 1; i < mapHeight - 1; i++) {
        for (int j = 1; j < mapWidth - 1; ++j) {
            map[i][j] = W;
        }
    }
    for(int i = 1; i < mapHeight - 1; i++) {
        for (int j = 1; j < mapWidth - 1; j++) {
            if(distribution(rng) < 7) {
                map[i][j] = 0;
            }
        }
    }
    for (int i = 1; i < mapHeight - 1; i++) {
        for (int j = 1; j < mapWidth - 1; j++) {
            if (map[i][j] == 0 && distribution(rng) < 3) {
                map[i][j] = D;
            }
        }
    }

    map[1][1] = 0;
    map[2][1] = 0;
    map[1][2] = 0;
}

void selectWinningCell(int& winningCellX, int& winningCellY) {
    std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> xDistribution(4, mapWidth - 2);
    std::uniform_int_distribution<int> yDistribution(4, mapHeight - 2);

    do  {
        winningCellX = xDistribution(gen);
        winningCellY = yDistribution(gen);
    } while ( map[winningCellX][winningCellX] == W );
}

bool canReachExit(int startX, int startY, int exitX, int exitY) {
    std::queue<std::pair<int, int>> queue;
    std::vector<std::pair<int, int>> visited;

    if (exitX <= 0 || exitX >= mapHeight - 1 || exitY <= 0 || exitY >= mapWidth - 1) { return false; }

    if (map[exitX][exitY] == W) { return false; }

    queue.push(std::make_pair(startX, startY));
    visited.push_back(std::make_pair(startX, startY));

    while (!queue.empty()) {
        std::pair<int, int> current = queue.front();
        queue.pop();

        int x = current.first;
        int y = current.second;
        if (x == exitX && y == exitY) {
            return true;
        }

        std::pair<int, int> neighbors[] = {std::make_pair(x - 1, y), std::make_pair(x + 1, y), std::make_pair(x, y - 1), std::make_pair(x, y + 1)};
        for (const std::pair<int, int>& neighbor : neighbors) {
            if (neighbor.first >= 0 && neighbor.first < mapHeight && neighbor.second >= 0 && neighbor.second < mapWidth &&
                std::find(visited.begin(), visited.end(), neighbor) == visited.end() &&
                map[neighbor.first][neighbor.second] != W) {
                queue.push(neighbor);
                visited.push_back(neighbor);
            }
        }
    }

    return false;
}

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
    void Render2(int color[4])
    {
        setfillstyle(SOLID_FILL, color[3]);
        setcolor(color[0]);
        rectangle(x, y, x + e, y + e);
        setcolor(color[1]);
        rectanglem(x, y, e, 3);
        setcolor(color[2]);
        rectanglem(x, y, e, 4);
    }
};
void rectanglem(int x, int y, int e, int m)
{
    if (m <= cellgrid / 2)
        // rectangle(x + (cellgrid - m)*(e/cellgrid), y + (cellgrid - m) * (e/cellgrid), x + m * (e/cellgrid), y + m*(e/cellgrid));
        rectangle(x + m * (e / cellgrid), y + m * (e / cellgrid), x + e - m * (e / cellgrid), y + e - m * (e / cellgrid));
    // rectangle(x + (m) * (e / cellgrid), y + (m) * (e / cellgrid), x + (cellgrid - m) * (e / cellgrid), y + (cellgrid - m) * (e / cellgrid));
    // rectangle(x + e * ((cellgrid - m) / cellgrid), y + e * ((cellgrid - m) / cellgrid), x + e * (m / cellgrid), y + e * (m / cellgrid));
    // rectangle(x + e * ((cellgrid - m) / cellgrid), y + e * ((cellgrid - m) / cellgrid), x + e * (m / cellgrid), y + e * (m / cellgrid));
    else
        rectangle(x, y, x + e, y + e);
}
void circlem(int x, int y, int e, int m)
{
    circle(x + e / 2, y + e / 2, e / 2 - m * (e / cellgrid));
}
void wall(int x, int y, int e, int color)
{
    Square *w = new Square(x, y, e);
    w->Render1(color);
}
void squ1(int x, int y, int e, int color[4])
{
    Square *w = new Square(x, y, e);
    w->Render2(color);
}
void squ2()
{
}

void clearSquare(int x, int y, int e)
{
    setcolor(BLACK);
    int points[] = {x,y, x+e,y, x+e,y+e, x,y+e, x,y};
    setfillstyle(SOLID_FILL,BLACK);
    fillpoly(5,points);
}
void drawBomb(int x, int y, int e)
{
    setcolor(9);
    circlem(x, y, e, 1);
}

class Bomb
{
    // public:
    int xj, yi, e;
    float duration;
    int size;
    clock_t beginTime;
    // int beginTime;
    friend class Player;

public:
    Bomb(int i, int j, int e, BombStats b) : xj(i), yi(j), e(e)
    {
        map[yi][xj] = B;
        duration = b.duration;
        size = b.size;
        beginTime = std::clock();
    }
    ~Bomb() {}
    void draw()
    {
        setcolor(9);
        circlem(xj, yi, e, 1);
    }
    void clear()
    {
        clearSquare(xj*e, yi*e, e);
        // setcolor(0);
        // circlem(xj, yi, e, 1);
    }
    void exploid()
    {
        // undraw(); // bomb position to bomb in map board
        int w = 1;
        int i = yi, j = xj, k, ww;

        map[i][j] = 0;
        clearSquare(xj*e,yi*e,e);
        for (k = 1, ww = w; map[i][j+k] != W && k <= this->size && ww > 0; k++) {
            if(map[i][j+k] == D) ww--;
            map[i][j+k] = 0;
            clearSquare((j+k)*e, i*e, e);
        }
        for (k = 1, ww = w; map[i][j-k] != W && k <= this->size && ww > 0; k++) {
            if (map[i][j-k] == D) ww--;
            map[i][j-k] = 0;
            clearSquare((j-k)*e,i*e,e);
        }
        for (k = 1, ww = w; map[i-k][j] != W && k <= this->size && ww > 0; k++) {
            if (map[i-k][j] == D) ww--;
            map[i-k][j] = 0;
            clearSquare(j*e, (i-k)*e, e);
        }
        for (k = 1, ww = w; map[i+k][j] != W && k <= this->size && ww > 0; k++) {
            if (map[i+k][j] == D) ww--;
            map[i+k][j] = 0;
            clearSquare(j*e,(i+k)*e,e);
        }
        drawMap(0,0,e);
    }
    bool isExplode()
    {
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
        lifes = 2;
        numBombs = 1;
        bombsActive = 0;
        b.duration = 3;
        b.size = 2;
    }
    void draw()
    {
        setcolor(8);
        // rectangle(x + e * (1 / cellgrid), y + e * (1 / cellgrid), x + e * (12 / cellgrid), y + e * (12 / cellgrid));
        // rectangle(x+1*(e/cellgrid),y,x+e,y+e/2);
        // rectanglem(x, y, e, 1);
        rectangle(x,y,x+width,y+height);
    }
    void updateLeft()
    {
        if (map [y/e][(x-vx)/e] == 0 && map[(y+height)/e][(x-vx)/e] == 0)       {
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
        int points[] = {x,y, x+width,y, x+width,y+height, x,y+height, x,y};
        setfillstyle(SOLID_FILL, 0);
        fillpoly(5,points);
        // rectangle(x,y,x+width,y+height);
    }
    int getSpeed() { return vx; }
    void updateSpeed(float va = 2) { vx = vy += va; }
    Bomb *putBomb()
    {
        if (numBombs <= 0)
            return nullptr;
        numBombs--;
        bombsActive++;
        return new Bomb(int((x+width/2)/e), int((y+height/2)/e), e, b);
    }
    void deleteBomb(Bomb *bb)
    {
        numBombs++;
        bombsActive--;
        bb->exploid();
        
        delete bb;
    }
    bool playerCollisionBomb(Bomb *bb)
    {
        int i = bb->yi, j = bb->xj, ss = bb->size;

        if (i == int(y/e) && j == int(x/e)) return 1;
        for (int s = 1; map[i+s][j] == 0 && s <= ss; s++) if (i+s == int(y/e) && j == int(x/e)) return 1;
        for (int s = 1; map[i-s][j] == 0 && s <= ss; s++) if (i-s == int(y/e) && j == int(x/e)) return 1;
        for (int s = 1; map[i][j+s] == 0 && s <= ss; s++) if (i == int(y/e) && j+s == int(x/e)) return 1;
        for (int s = 1; map[i][j-s] == 0 && s <= ss; s++) if (i == int(y/e) && j-s == int(x/e)) return 1;

        return 0;
    }
    int dead() {
        return --lifes;
    }
    void setPos(int x, int y) {
        clearSquare(this->x,this->y,e);
        this->x = (x+e/cellgrid);
        this->y = (y+e/cellgrid);
    }
};
void drawWinningCell(int e) {
    if (map[winCellX][winCellY] == 0) {
        Square *w = new Square(winCellX*e, winCellY*e, e);
        w->Render1(12);
    }
}
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
    drawWinningCell(e);
}
void drawBlocks(int x, int y, int e)
{
    drawWinningCell(e);
    for (int i = 0; i < mapHeight; i++)
    {
        for (int j = 0; j < mapWidth; j++)
        {
            int xx = x + j * e;
            int yy = y + i * e;
            if (map[i][j] == D)
            {
                int color[] = {YELLOW, RED, BLUE, BLACK};
                squ1(xx, yy, e, color);
            }
            if (map[i][j] == B)
            {
                drawBomb(xx,yy,e);
            }
        }
    }
}

int main()
{
    int key = -1;
    initwindow(1280, 720);
    const int scale = 50;

    Player *pl = new Player(scale*1, scale*1, scale);
    Bomb *a = nullptr;

    selectWinningCell(winCellX, winCellY);
    int itomms = 0;
    do {
        generateRandomMap(map);
        if (itomms++ > 1000)
        {
            selectWinningCell(winCellX, winCellY);
            itomms = 0;
        }
    } while (!canReachExit(1,1,winCellX,winCellY));
    std::cout << winCellX << " " << winCellY << "\n";
    drawMap(0, 0, scale);
    while (1)
    {
        drawBlocks(0, 0, scale);
        pl->draw();
        if (kbhit())
        {
            key = getch();
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
                // a = pl->putBomb();
                Bomb *aa = pl->putBomb();
                if (aa != nullptr) a = aa;
            }
        }
        if (a != nullptr && a->isExplode())
        {
            if (pl->playerCollisionBomb(a))
            {
                if (pl->dead() < 1) break;
                pl->setPos(scale*1,scale*1);
            }
            pl->deleteBomb(a);
            a = nullptr;
        }

        pl->draw();

        // delay(1000);
        // fflush(stdin);
    }
    // getch();
    closegraph();
    return 0;
}