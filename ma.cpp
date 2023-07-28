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

const float scaleSprites = .5;
const int scale = 50;

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

int winCellX = 0, winCellY = 0;

//colores Bomberman
const int rosadoClaro = COLOR(240, 160, 216);
const int rosado= COLOR(248, 56, 104);
const int rosadoOscuro = COLOR(176, 24, 32);
const int casiBlanco = COLOR(248, 248, 248);
const int gris = COLOR(216, 216, 224);
const int grisOscuro = COLOR(168, 160, 168);
const int medioAmarilla = COLOR(248, 184, 0);
const int casiNegro = COLOR(40, 16, 16);
const int azul = COLOR(0, 104, 224);
const int celesteOscuro = COLOR(48, 160, 248);
const int celeste = COLOR(88, 192, 248);
const int negroClaro = COLOR(40, 40, 40);
//bomba
const int casiCeleste = COLOR(72, 208, 240);
const int casiAzul = COLOR(24, 128, 248);
const int azulOscuro = COLOR(24, 48, 64);
const int parecidoAzul = COLOR(32, 80, 136);
const int amarillo = COLOR(248, 248, 0);
const int rojo = COLOR(232, 32, 16);
const int casiGris = COLOR(160, 152, 152);
//sprites
void bombermanArriba(int x,int y, float e,int color);
void bomba(int x, int y, float e, int color);


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

    // for (int i = 1; i < mapHeight - 1; i++) {
        // for (int j = 1; j < mapWidth - 1; ++j) {
            // map[i][j] = W;
        // }
    // }
    // for(int i = 1; i < mapHeight - 1; i++) {
        // for (int j = 1; j < mapWidth - 1; j++) {
            // if(distribution(rng) < 7) {
                // map[i][j] = 0;
            // }
        // }
    // }
    for (int i = 1; i < mapHeight - 1; i++) {
        for (int j = 1; j < mapWidth - 1; j++) {
            if (map[i][j] == 0 && distribution(rng) < 7) {
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

    while ( map[winningCellX][winningCellX] == W )
    {
        winningCellX = xDistribution(gen);
        winningCellY = yDistribution(gen);
    } 
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
        rectangle(x+1, y+1, x + e - 1, y + e - 1);
        line(x,y, x+e/3, y+e/3);
        line(x+e,y, x+e-e/3, y+e/3);
        line(x+e,y+e, x+e-e/3, y+e-e/3);
        line(x,y+e, x+e/3, y+e-e/3);
        rectangle(x+e/3,y+e/3, x+e-e/3, y+e-e/3);
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
    int xj, yi, e;
    float duration;
    int size;
    clock_t beginTime;
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
        int w = 1;
        int i = yi, j = xj, k, ww;

        map[i][j] = 0;
        clearSquare(xj*e,yi*e,e);
        for (k = 1, ww = w; map[i][j+k] != W && k <= this->size && ww > 0; k++) {
            if(map[i][j+k] == D) ww--;
            map[i][j+k] = 0;
            if(map[i][j+k] != B) clearSquare((j+k)*e, i*e, e);
        }
        for (k = 1, ww = w; map[i][j-k] != W && k <= this->size && ww > 0; k++) {
            if (map[i][j-k] == D) ww--;
            map[i][j-k] = 0;
            if(map[i][j+k] != B) clearSquare((j-k)*e,i*e,e);
        }
        for (k = 1, ww = w; map[i-k][j] != W && k <= this->size && ww > 0; k++) {
            if (map[i-k][j] == D) ww--;
            map[i-k][j] = 0;
            if(map[i][j+k] != B) clearSquare(j*e, (i-k)*e, e);
        }
        for (k = 1, ww = w; map[i+k][j] != W && k <= this->size && ww > 0; k++) {
            if (map[i+k][j] == D) ww--;
            map[i+k][j] = 0;
            if(map[i][j+k] != B) clearSquare(j*e,(i+k)*e,e);
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
    float rh, rw;
    BombStats b;

public:
    Player(float x, float y, float e) : e(e)
    {
        // x = x+e/cellgrid;
        this->x = x;
        // y = y+e/cellgrid;
        this->y = y;
        height = width = 10*(e/cellgrid);
        // width = height = e;
        vx = vy = 10;
        lifes = 2;
        numBombs = 1;
        bombsActive = 0;
        b.duration = 3;
        b.size = 2;
        //sprite
        rh = e/(84);
        rw = e/(53);
        // width = rh*height;
    }
    void draw()
    {
        setcolor(8);
        // rectangle(x + e * (1 / cellgrid), y + e * (1 / cellgrid), x + e * (12 / cellgrid), y + e * (12 / cellgrid));
        // rectangle(x+1*(e/cellgrid),y,x+e,y+e/2);
        // rectanglem(x, y, e, 1);
        bombermanFrente(x,y,1);
        // rectangle(x,y,x+width,y+height);
    }
    void updateLeft()
    {
        if (map [y/e][(x-vx)/e] == 0 && map[(y+height)/e][(x-vx)/e] == 0) {
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
        // int points[] = {x,y, x+width,y, x+width,y+height, x,y+height, x,y};
        int points[] = {x,y, x+e,y, x+e,y+e, x,y+e, x,y};
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
        int cx = (x+width/2)/e;
        int cy = (y+height/2)/e;
        if (map[cx][cy] == B) return nullptr;
        return new Bomb(cx, cy, e, b);
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
    void bombermanFrente(int x, int y, int color);
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
                bomba(xx,yy,floor(e/53.0),5);
                // drawBomb(xx,yy,e);
            }
        }
    }
}

int main()
{
    int key = -1;
    initwindow(1280, 720);

    Player *pl = new Player(scale*1, scale*1, scale);
    std::queue<Bomb*> vbombs;

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
                Bomb *aa = pl->putBomb();
                if (aa != nullptr) vbombs.push(aa);
            }
        }
        if (!vbombs.empty() && (vbombs.front())->isExplode())
        {
            if (pl->playerCollisionBomb(vbombs.front()))
            {
                if (pl->dead() == 0) break;
                pl->setPos(scale*1, scale*1);
            }
            pl->deleteBomb(vbombs.front());
            vbombs.pop();
        }

        pl->draw();

        // delay(1000);
    }
    closegraph();
    return 0;
}

void Player::bombermanFrente(int x,int y, int color){
    //53*84
    x += 1;
    float pp = rh;
    // rw = rh;
    {//gorrito
        setcolor(rosadoClaro);
        setfillstyle(1, rosadoClaro);
        bar(x+23*rw,y+4*pp, x+26*rw,y+8*pp);

        setcolor(rosado);
        setfillstyle(1, rosado);
        bar(x+26*rw,y+4*pp, x+30*rw,y+8*pp);

        setcolor(rosadoOscuro);
        setfillstyle(1,rosadoOscuro);
        bar(x+30*rw,y+4*pp, x+33*rw,y+8*pp);
    }

    //cabeza
    {
        setcolor(casiBlanco);
        setfillstyle(1, casiBlanco);
        //de arriba - abajo, izquierda - derecha
        int cabeza[]={x+14*rw,y+11*pp, x+14*rw,y+15*pp, x+7*rw,y+15*pp, x+7*rw,y+18*pp, x+4*rw,y+18*pp, x+4*rw,y+39*pp, x+7*rw,y+39*pp,
                        x+7*rw,y+42*pp, x+14*rw,y+42*pp, x+14*rw,y+46*pp, x+39*rw,y+46*pp, x+39*rw,y+42*pp, x+46*rw,y+42*pp, x+46*rw,y+39*pp,
                        x+49*rw,y+39*pp, x+49*rw,y+18*pp, x+46*rw,y+18*pp, x+46*rw,y+15*pp, x+39*rw,y+15*pp, x+39*rw,y+11*pp, x+14*rw,y+11*pp};
        fillpoly(21, cabeza);
    }

    //cabeza detalles claro
    {
        setcolor(gris);
        setfillstyle(1, gris);
        bar(x+17*rw,y+11*pp, x+36*rw,y+15*pp); bar(x+7*rw,y+15*pp, x+10*rw,y+18*pp); bar(x+33*rw,y+15*pp, x+42*rw,y+18*pp);
        bar(x+4*rw,y+18*pp, x+7*rw,y+22*pp); bar(x+36*rw,y+18*pp, x+46*rw,y+22*pp); bar(x+42*rw,y+22*pp, x+46*rw,y+39*pp);
        bar(x+4*rw,y+35*pp, x+7*rw,y+39*pp); bar(x+7*rw,y+39*pp, x+10*rw,y+42*pp); bar(x+39*rw,y+39*pp, x+42*rw,y+42*pp);
        bar(x+17*rw,y+42*pp, x+20*rw,y+46*pp); bar(x+33*rw,y+42*pp, x+36*rw,y+46*pp);
    }

    //cabeza detalles oscuro
    {
        setcolor(grisOscuro);
        setfillstyle(1, grisOscuro);
        bar(x+14*rw,y+11*pp, x+17*rw,y+15*pp); bar(x+36*rw,y+11*pp, x+39*rw,y+15*pp); bar(x+42*rw,y+15*pp, x+46*rw,y+18*pp);
        bar(x+46*rw,y+18*pp, x+49*rw,y+39*pp); bar(x+42*rw,y+39*pp, x+46*rw,y+42*pp); bar(x+14*rw,y+42*pp, x+17*rw,y+46*pp);
        bar(x+36*rw,y+42*pp, x+39*rw,y+46*pp);
    }

    //cara interior
    {
        setcolor(medioAmarilla);
        setfillstyle(1, medioAmarilla);
        bar(x+14*rw,y+25*pp, x+39*rw,y+39*pp);
    }

    //ojos
    {
        setcolor(casiNegro);
        setfillstyle(1, casiNegro);
        bar(x+17*rw,y+25*pp, x+20*rw,y+39*pp); bar(x+33*rw,y+25*pp, x+36*rw,y+39*pp);
    }

    //cara exterior
    setcolor(rosado);
    setfillstyle(1, rosado);
    bar(x+11*rw,y+22*pp, x+42*rw,y+25*pp); bar(x+11*rw,y+25*pp, x+14*rw,y+39*pp); bar(x+39*rw,y+25*pp, x+42*rw,y+39*pp);
    bar(x+14*rw,y+39*pp, x+39*rw,y+42*pp);

    //cuerpo exterior
    setcolor(azul);
    setfillstyle(1, azul);
    int cuerpo[]={x+14*rw,y+49*pp, x+14*rw,y+66*pp, x+23*rw,y+66*pp, x+23*rw,y+70*pp, x+30*rw,y+70*pp, x+30*rw,y+66*pp, x+39*rw,y+66*pp,
                    x+39*rw,y+49*pp, x+14*rw,y+49*pp};
    fillpoly(9, cuerpo);

    //cuerpo interior oscuro
    setcolor(celesteOscuro);
    setfillstyle(1, celesteOscuro);
    bar(x+17*rw,y+49*pp, x+20*rw,y+52*pp); bar(x+23*rw,y+49*pp, x+30*rw,y+52*pp); bar(x+26*rw,y+52*pp, x+33*rw,y+56*pp);
    bar(x+26*rw,y+59*pp, x+33*rw,y+63*pp); bar(x+20*rw,y+63*pp, x+30*rw,y+66*pp);

    //cuerpo interior claro
    setcolor(celeste);
    setfillstyle(1, celeste);
    bar(x+20*rw,y+49*pp, x+23*rw,y+52*pp); bar(x+20*rw,y+52*pp, x+26*rw,y+56*pp); bar(x+17*rw,y+59*pp, x+26*rw,y+63*pp);

    //brillo interior
    setcolor(casiBlanco);
    setfillstyle(1, casiBlanco);
    bar(x+17*rw,y+52*pp, x+20*rw,y+56*pp);

    //correa
    setcolor(negroClaro);
    setfillstyle(1, negroClaro);
    bar(x+14*rw,y+56*pp, x+39*rw,y+59*pp);

    //hebilla
    setcolor(medioAmarilla);
    setfillstyle(1, medioAmarilla);
    bar(x+23*rw,y+56*pp, x+30*rw,y+59*pp);

    //brazo derecho
    setcolor(casiBlanco);
    setfillstyle(1, casiBlanco);
    bar(x+10*rw,y+49*pp, x+14*rw,y+52*pp); bar(x+7*rw,y+52*pp, x+10*rw,y+56*pp);

    //mano derecha
    setcolor(rosado);
    setfillstyle(1, rosado);
    bar(x+4*rw,y+56*pp, x+10*rw,y+63*pp);

    //brazo izquierdo
    setcolor(gris);
    setfillstyle(1, gris);
    bar(x+39*rw,y+49*pp, x+42*rw,y+52*pp); bar(x+42*rw,y+52*pp, x+46*rw,y+56*pp);

    //mano izquierda
    setcolor(rosado);
    setfillstyle(1, rosado);
    bar(x+42*rw,y+56*pp, x+49*rw,y+63*pp);

    //sombra manos
    setcolor(rosadoOscuro);
    setfillstyle(1, rosadoOscuro);
    bar(x+7*rw,y+59*pp, x+10*rw,y+63*pp); bar(x+46*rw,y+59*pp, x+49*rw,y+63*pp);

    //pierna derecha
    setcolor(gris);
    setfillstyle(1, gris);
    bar(x+14*rw,y+66*pp, x+23*rw,y+73*pp);

    setcolor(grisOscuro);
    setfillstyle(1, grisOscuro);
    bar(x+20*rw,y+66*pp, x+23*rw,y+73*pp);

    setcolor(casiBlanco);
    setfillstyle(1, casiBlanco);
    bar(x+14*rw,y+70*pp, x+17*rw,y+73*pp);

    //pierna izquierda
    setcolor(gris);
    setfillstyle(1, gris);
    bar(x+30*rw,y+66*pp, x+39*rw,y+73*pp);

    setcolor(grisOscuro);
    setfillstyle(1, grisOscuro);
    bar(x+30*rw,y+66*pp, x+33*rw,y+73*pp); bar(x+36*rw,y+66*pp, x+39*rw,y+70*pp);

    setcolor(casiBlanco);
    setfillstyle(1, casiBlanco);
    bar(x+33*rw,y+70*pp, x+36*rw,y+73*pp);

    //pie derecho
    setcolor(rosado);
    setfillstyle(1, rosado);
    bar(x+10*rw,y+73*pp, x+23*rw,y+80*pp);

    setcolor(rosadoOscuro);
    setfillstyle(1, rosadoOscuro);
    bar(x+10*rw,y+73*pp, x+14*rw,y+76*pp); bar(x+20*rw,y+73*pp, x+23*rw,y+80*pp); bar(x+7*rw,y+76*pp, x+10*rw,y+80*pp);

    setcolor(rosadoClaro);
    setfillstyle(1, rosadoClaro);
    bar(x+14*rw,y+73*pp, x+17*rw,y+76*pp); bar(x+10*rw,y+76*pp, x+14*rw,y+80*pp);

    //pie izquierdo
    setcolor(rosado);
    setfillstyle(1, rosado);
    bar(x+30*rw,y+73*pp, x+42*rw,y+80*pp);

    setcolor(rosadoOscuro);
    setfillstyle(1, rosadoOscuro);
    bar(x+30*rw,y+73*pp, x+33*rw,y+80*pp); bar(x+39*rw,y+73*pp, x+42*rw,y+80*pp); bar(x+42*rw,y+76*pp, x+46*rw,y+80*pp);

    setcolor(rosadoClaro);
    setfillstyle(1, rosadoClaro);
    bar(x+33*rw,y+73*pp, x+36*rw,y+76*pp);

    //bordes
    setcolor(casiNegro);
    setfillstyle(1, casiNegro);
    bar(x+23*rw,y+1*pp, x+33*rw,y+4*pp); bar(x+20*rw,y+4*pp, x+23*rw,y+8*pp); bar(x+33*rw,y+4*pp, x+36*rw,y+8*pp);
    bar(x+14*rw,y+8*pp, x+39*rw,y+11*pp); bar(x+7*rw,y+11*pp, x+14*rw,y+15*pp); bar(x+39*rw,y+11*pp, x+46*rw,y+15*pp);
    bar(x+4*rw,y+15*pp, x+7*rw,y+18*pp); bar(x+46*rw,y+15*pp, x+49*rw,y+18*pp); bar(x+1*rw,y+18*pp, x+4*rw,y+39*pp);
    bar(x+49*rw,y+18*pp, x+52*rw,y+39*pp); bar(x+4*rw,y+39*pp, x+7*rw,y+42*pp); bar(x+46*rw,y+39*pp, x+49*rw,y+42*pp);
    bar(x+7*rw,y+42*pp, x+14*rw,y+46*pp); bar(x+39*rw,y+42*pp, x+46*rw,y+46*pp); bar(x+10*rw,y+46*pp, x+42*rw,y+49*pp);

    bar(x+7*rw,y+49*pp, x+10*rw,y+52*pp); bar(x+42*rw,y+49*pp, x+46*rw,y+52*pp); bar(x+4*rw,y+52*pp, x+7*rw,y+56*pp);
    bar(x+10*rw,y+52*pp, x+14*rw,y+73*pp); bar(x+39*rw,y+52*pp, x+42*rw,y+73*pp); bar(x+46*rw,y+52*pp, x+49*rw,y+56*pp);
    bar(x+1*rw,y+56*pp, x+4*rw,y+63*pp); bar(x+49*rw,y+56*pp, x+52*rw,y+63*pp); bar(x+4*rw,y+63*pp, x+10*rw,y+66*pp);
    bar(x+42*rw,y+63*pp, x+49*rw,y+66*pp); bar(x+7*rw,y+70*pp, x+10*rw,y+76*pp); bar(x+42*rw,y+70*pp, x+46*rw,y+76*pp);
    bar(x+4*rw,y+73*pp, x+7*rw,y+80*pp); bar(x+46*rw,y+73*pp, x+49*rw,y+80*pp); bar(x+23*rw,y+70*pp, x+30*rw,y+80*pp);
    bar(x+7*rw,y+80*pp, x+46*rw,y+83*pp);
}

void bombermanArriba(int x,int y, float e,int color){
    e = std::max(53,84)/scale;
    //53x84
    //gorrito

    setcolor(rosadoOscuro);
    setfillstyle(1,rosadoOscuro);
    bar(x+23*e,y+4*e, x+33*e,y+14*e);

    setcolor(rosado);
    setfillstyle(1, rosado);
    bar(x+23*e,y+4*e, x+30*e,y+11*e);

    setcolor(rosadoClaro);
    setfillstyle(1, rosadoClaro);
    bar(x+23*e,y+4*e, x+27*e,y+8*e);

    //cabeza
    setcolor(casiBlanco);
    setfillstyle(1, casiBlanco);
    //de arriba - abajo, izquierda - derecha
    int cabeza[]={x+14*e,y+11*e, x+14*e,y+14*e, x+7*e,y+14*e, x+7*e,y+18*e, x+4*e,y+18*e, x+4*e,y+38*e, x+7*e,y+38*e,
                    x+7*e,y+42*e, x+14*e,y+42*e, x+14*e,y+45*e, x+39*e,y+45*e, x+39*e,y+42*e, x+46*e,y+42*e, x+46*e,y+38*e,
                    x+49*e,y+38*e, x+49*e,y+18*e, x+20*e,y+18*e, x+20*e,y+11*e, x+14*e,y+11*e};
    fillpoly(19, cabeza);

    //cabeza detalles claro
    setcolor(gris);
    setfillstyle(1, gris);
    bar(x+17*e,y+11*e, x+20*e,y+14*e); bar(x+7*e,y+14*e, x+11*e,y+18*e); bar(x+20*e,y+14*e, x+23*e,y+18*e);
    bar(x+30*e,y+14*e, x+46*e,y+21*e); bar(x+4*e,y+18*e, x+7*e,y+21*e); bar(x+36*e,y+21*e, x+46*e,y+25*e);
    bar(x+39*e,y+25*e, x+46*e,y+42*e); bar(x+4*e,y+35*e, x+7*e,y+38*e); bar(x+7*e,y+38*e, x+11*e,y+42*e); 
    bar(x+36*e,y+38*e, x+39*e,y+42*e); bar(x+17*e,y+42*e, x+20*e,y+45*e); bar(x+33*e,y+42*e, x+36*e,y+45*e);

    //cabeza detalles oscuro
    setcolor(grisOscuro);
    setfillstyle(1, grisOscuro);
    bar(x+14*e,y+11*e, x+17*e,y+14*e); bar(x+36*e,y+11*e, x+39*e,y+14*e); bar(x+33*e,y+14*e, x+36*e,y+18*e);
    bar(x+43*e,y+14*e, x+46*e,y+18*e); bar(x+46*e,y+18*e, x+49*e,y+38*e); bar(x+43*e,y+38*e, x+46*e,y+42*e);
    bar(x+14*e,y+42*e, x+17*e,y+45*e); bar(x+36*e,y+42*e, x+39*e,y+45*e);

    //cuerpo exterior
    setcolor(azul);
    setfillstyle(1, azul);
    int cuerpo[]={x+14*e,y+49*e, x+14*e,y+66*e, x+23*e,y+66*e, x+23*e,y+69*e, x+30*e,y+69*e, x+30*e,y+66*e, x+39*e,y+66*e,
                    x+39*e,y+49*e, x+14*e,y+49*e};
    fillpoly(9, cuerpo);

    //cuerpo interior claro
    setcolor(celeste);
    setfillstyle(1, celeste);
    bar(x+17*e,y+49*e, x+30*e,y+62*e);

    //cuerpo interior oscuro
    setcolor(celesteOscuro);
    setfillstyle(1, celesteOscuro);
    bar(x+17*e,y+49*e, x+20*e,y+52*e); bar(x+23*e,y+49*e, x+30*e,y+52*e); bar(x+27*e,y+52*e, x+33*e,y+56*e);
    bar(x+30*e,y+59*e, x+33*e,y+62*e); bar(x+20*e,y+62*e, x+30*e,y+66*e);    

    //brillo interior
    setcolor(casiBlanco);
    setfillstyle(1, casiBlanco);
    bar(x+17*e,y+52*e, x+20*e,y+56*e);

    //correa
    setcolor(negroClaro);
    setfillstyle(1, negroClaro);
    bar(x+14*e,y+56*e, x+39*e,y+59*e);

    //brazo derecho
    setcolor(gris);
    setfillstyle(1, gris);
    bar(x+39*e,y+49*e, x+43*e,y+52*e); bar(x+43*e,y+52*e, x+46*e,y+56*e);

    //mano derecha
    setcolor(rosado);
    setfillstyle(1, rosado);
    bar(x+43*e,y+56*e, x+49*e,y+62*e);

    //brazo izquierdo
    setcolor(casiBlanco);
    setfillstyle(1, casiBlanco);
    bar(x+11*e,y+49*e, x+14*e,y+52*e); bar(x+7*e,y+52*e, x+11*e,y+56*e);

    //mano izquierda
    setcolor(rosado);
    setfillstyle(1, rosado);
    bar(x+4*e,y+56*e, x+11*e,y+62*e);

    //sombra manos
    setcolor(rosadoOscuro);
    setfillstyle(1, rosadoOscuro);
    bar(x+7*e,y+59*e, x+11*e,y+62*e); bar(x+46*e,y+59*e, x+49*e,y+62*e);

    //pierna derecha
    setcolor(gris);
    setfillstyle(1, gris);
    bar(x+30*e,y+66*e, x+39*e,y+73*e);

    setcolor(grisOscuro);
    setfillstyle(1, grisOscuro);
    bar(x+30*e,y+66*e, x+33*e,y+73*e); bar(x+36*e,y+66*e, x+39*e,y+69*e);

    setcolor(casiBlanco);
    setfillstyle(1, casiBlanco);
    bar(x+33*e,y+69*e, x+36*e,y+73*e);

    //pierna izquierda
    setcolor(gris);
    setfillstyle(1, gris);
    bar(x+14*e,y+66*e, x+20*e,y+73*e);

    setcolor(grisOscuro);
    setfillstyle(1, grisOscuro);
    bar(x+20*e,y+66*e, x+23*e,y+73*e);

    setcolor(casiBlanco);
    setfillstyle(1, casiBlanco);
    bar(x+14*e,y+69*e, x+17*e,y+73*e);

    //pie derecho
    setcolor(rosado);
    setfillstyle(1, rosado);
    bar(x+33*e,y+73*e, x+39*e,y+80*e);

    setcolor(rosadoOscuro);
    setfillstyle(1, rosadoOscuro);
    bar(x+30*e,y+73*e, x+33*e,y+80*e); bar(x+39*e,y+73*e, x+43*e,y+76*e); bar(x+36*e,y+76*e, x+39*e,y+80*e);

    //pie izquierdo
    setcolor(rosado);
    setfillstyle(1, rosado);
    bar(x+14*e,y+73*e, x+20*e,y+80*e);

    setcolor(rosadoOscuro);
    setfillstyle(1, rosadoOscuro);
    bar(x+11*e,y+73*e, x+14*e,y+76*e); bar(x+20*e,y+73*e, x+23*e,y+80*e); bar(x+14*e,y+76*e, x+17*e,y+80*e);

    //bordes
    setcolor(casiNegro);
    setfillstyle(1, casiNegro);
    bar(x+23*e,y+1*e, x+33*e,y+4*e); bar(x+20*e,y+4*e, x+23*e,y+14*e); bar(x+33*e,y+4*e, x+36*e,y+14*e);
    bar(x+14*e,y+8*e, x+20*e,y+11*e); bar(x+36*e,y+8*e, x+39*e,y+11*e); bar(x+7*e,y+11*e, x+14*e,y+14*e);
    bar(x+39*e,y+11*e, x+46*e,y+14*e); bar(x+4*e,y+14*e, x+7*e,y+18*e); bar(x+23*e,y+14*e, x+33*e,y+18*e);
    bar(x+46*e,y+14*e, x+49*e,y+18*e); bar(x+1*e,y+18*e, x+4*e,y+38*e); bar(x+49*e,y+18*e, x+52*e,y+38*e);
    bar(x+4*e,y+38*e, x+7*e,y+42*e); bar(x+46*e,y+38*e, x+49*e,y+42*e); bar(x+7*e,y+42*e, x+14*e,y+45*e);
    bar(x+39*e,y+42*e, x+46*e,y+45*e); bar(x+11*e,y+45*e, x+43*e,y+49*e); 
    
    bar(x+7*e,y+49*e, x+11*e,y+52*e); bar(x+43*e,y+49*e, x+46*e,y+52*e); bar(x+4*e,y+52*e, x+7*e,y+56*e); 
    bar(x+11*e,y+52*e, x+14*e,y+73*e); bar(x+39*e,y+52*e, x+43*e,y+73*e); bar(x+46*e,y+52*e, x+49*e,y+56*e);
    bar(x+1*e,y+56*e, x+4*e,y+62*e); bar(x+49*e,y+56*e, x+52*e,y+62*e); bar(x+4*e,y+62*e, x+11*e,y+66*e);
    bar(x+43*e,y+62*e, x+49*e,y+66*e); bar(x+7*e,y+69*e, x+11*e,y+83*e); bar(x+43*e,y+69*e, x+46*e,y+83*e);
    bar(x+4*e,y+73*e, x+7*e,y+80*e); bar(x+46*e,y+73*e, x+49*e,y+80*e); bar(x+11*e,y+76*e, x+14*e,y+80*e);
    bar(x+39*e,y+76*e, x+43*e,y+80*e); bar(x+7*e,y+80*e, x+46*e,y+83*e); bar(x+23*e,y+69*e, x+30*e,y+80*e);

    //punto negro en gorro
    setcolor(negroClaro);
    setfillstyle(1, negroClaro);
    bar(x+27*e,y+18*e, x+30*e,y+21*e); 
}

void bomba(int x, int y, float e, int color){
    e = std::max(55,53)/scale;
    //55x53
    //de fuera para dentro arriba - abajo, izquierda- derecha
    //bomba exterior
    setcolor(azulOscuro);
    setfillstyle(1, azulOscuro);
    //de arriba - abajo, izquierda - derecha
    int bombaExterior[]={x+30*e,y+7*e, x+4*e,y+31*e, x+4*e,y+37*e, x+6*e,y+37*e, x+6*e,y+43*e, x+11*e,y+43*e, x+11*e,y+48*e,
                    x+16*e,y+48*e, x+16*e,y+50*e, x+35*e,y+50*e, x+40*e,y+45*e, x+49*e,y+45*e, x+49*e,y+21*e, x+43*e,y+21*e,
                    x+43*e,y+7*e, x+30*e,y+7*e};
    fillpoly(16, bombaExterior);
    
    //bomba medio
    setcolor(parecidoAzul);
    setfillstyle(1, parecidoAzul);
    int bombaMedio[]={x+17*e,y+7*e, x+17*e,y+11*e, x+11*e,y+11*e, x+11*e,y+14*e, x+7*e,y+14*e, x+7*e,y+18*e, x+4*e,y+18*e,
                    x+4*e,y+31*e, x+7*e,y+31*e, x+7*e,y+35*e, x+11*e,y+35*e, x+11*e,y+38*e, x+17*e,y+38*e, x+17*e,y+42*e,
                    x+30*e,y+42*e, x+30*e,y+38*e, x+36*e,y+38*e, x+36*e,y+35*e, x+39*e,y+35*e, x+39*e,y+28*e, x+33*e,y+28*e,                    
                    x+33*e,y+25*e, x+30*e,y+25*e, x+30*e,y+21*e, x+27*e,y+21*e, x+27*e,y+11*e, x+30*e,y+11*e, x+30*e,y+7*e,
                    x+17*e,y+7*e};
    fillpoly(29, bombaMedio);

    //brillo
    setcolor(casiBlanco);
    setfillstyle(1,casiBlanco);
    bar(x+20*e,y+11*e, x+23*e,y+14*e); bar(x+11*e,y+18*e, x+17*e,y+25*e);
    
    setcolor(casiCeleste);
    setfillstyle(1, casiCeleste);
    bar(x+17*e,y+11*e, x+20*e,y+14*e); bar(x+7*e,y+18*e, x+11*e,y+25*e); bar(x+17*e,y+18*e, x+20*e,y+25*e);
    bar(x+11*e,y+25*e, x+17*e,y+28*e);

    setcolor(casiAzul);
    setfillstyle(1, casiAzul);
    bar(x+20*e,y+7*e, x+23*e,y+11*e); bar(x+23*e,y+11*e, x+27*e,y+14*e); bar(x+11*e,y+14*e, x+17*e,y+18*e);
    bar(x+20*e,y+14*e, x+23*e,y+18*e); bar(x+7*e,y+25*e, x+11*e,y+28*e); bar(x+17*e,y+25*e, x+20*e,y+28*e);
    bar(x+11*e,y+28*e, x+17*e,y+31*e);

    //mecha
    setcolor(rojo);
    setfillstyle(1, rojo);
    bar(x+46*e,y+1*e, x+49*e,y+4*e); bar(x+43*e,y+4*e, x+46*e,y+11*e); bar(x+49*e,y+4*e, x+52*e,y+11*e);

    setcolor(amarillo);
    setfillstyle(1, amarillo);
    bar(x+46*e,y+4*e, x+49*e,y+11*e);

    setcolor(casiGris);
    setfillstyle(1, casiGris);
    bar(x+30*e,y+11*e, x+33*e,y+14*e); bar(x+43*e,y+11*e, x+46*e,y+14*e); bar(x+36*e,y+14*e, x+43*e,y+18*e);
    bar(x+43*e,y+18*e, x+46*e,y+21*e); bar(x+33*e,y+21*e, x+36*e,y+25*e); bar(x+39*e,y+21*e, x+43*e,y+25*e);

    setcolor(gris);
    setfillstyle(1, gris);
    bar(x+33*e,y+11*e, x+36*e,y+14*e); bar(x+39*e,y+11*e, x+43*e,y+14*e); bar(x+30*e,y+18*e, x+36*e,y+21*e);
    bar(x+36*e,y+21*e, x+39*e,y+25*e);

    setcolor(casiNegro);
    setfillstyle(1, casiNegro);
    bar(x+36*e,y+11*e, x+39*e,y+14*e); bar(x+33*e,y+14*e, x+36*e,y+18*e); bar(x+43*e,y+14*e, x+46*e,y+18*e);
    bar(x+36*e,y+18*e, x+43*e,y+21*e);

    setcolor(casiBlanco);
    setfillstyle(1, casiBlanco);
    bar(x+30*e,y+14*e, x+33*e,y+18*e);

    //bombaExterior
    setcolor(casiNegro);
    setfillstyle(1,casiNegro);
    bar(x+17*e,y+4*e, x+36*e,y+7*e); bar(x+11*e,y+7*e, x+17*e,y+11*e); bar(x+36*e,y+7*e, x+43*e,y+11*e);
    bar(x+7*e,y+11*e, x+11*e,y+14*e); bar(x+46*e,y+11*e, x+49*e,y+21*e); bar(x+4*e,y+14*e, x+7*e,y+18*e);
    bar(x+1*e,y+18*e, x+4*e,y+38*e); bar(x+49*e,y+21*e, x+52*e,y+38*e); bar(x+4*e,y+35*e, x+7*e,y+45*e);
    bar(x+46*e,y+35*e, x+49*e,y+45*e); bar(x+7*e,y+42*e, x+11*e,y+49*e); bar(x+43*e,y+42*e, x+46*e,y+49*e);
    bar(x+11*e,y+45*e, x+17*e,y+49*e); bar(x+36*e,y+45*e, x+46*e,y+49*e); bar(x+14*e,y+49*e, x+39*e,y+52*e);
}