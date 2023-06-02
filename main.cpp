#include <graphics.h>
#include <iostream>
#include <vector>
#define d(x,y,e,c) drawPixel(x,y,e,c)

#define L 100
#define P 200
#define E 300
#define F 301
#define G 302
#define H 303
#define Z 400
#define b 500
#define c 501

int game[100][100] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    // {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    // {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    // {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,Z,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,E,0,F,0,G,0,H,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,b,0,c,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,P,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

int ih = 0;
int jh = 0;


int ii=0;
int jj=0;
int posi=0;

void drawPixel(int x, int y, int e, int color) {
    for (int i = 0; i < e; i++) {
        for (int j = 0; j < e; j++) {
            putpixel(x + i, y + j, color);
        }
    }
}
void drawMesh(int x, int y, int e, std::vector<std::string> mesh, int color) {
    for(int i=0; i < mesh.size(); i++) {
        for(int j=0; j < mesh[i].size(); j++) {
            if(mesh[i][j] == '#') {
                d(x+j*e,y+i*e,e,color);
            }
            else if(mesh[i][j] == '-') {
                d(x+j*e,y+i*e,e,RED);
            }
            else d(x+j*e,y+i*e,e,BLACK);

        }
    }
}

void drawEnemy(int x, int y, int e, int pos, int color) {
    std::vector<std::string> f1 = {
        "  #     #  ",
        "   #   #   ",
        "  #######  ",
        " ##-###-## ",
        "###########",
        "# ####### #",
        "# ####### #",
        "# #     # #",
        "   ## ##   ",
    };
    std::vector<std::string> f2 = {
        "  #     #  ",
        "   #   #   ",
        "# ####### #",
        "###-###-###",
        "###########",
        " ######### ",
        "  #######  ",
        "  #     #  ",
        " #       # ",
    };
    std::vector<std::string> f3 = {
        " #       # ",
        "  #  #  #  ",
        "   # # #  #",
        "           ",
        "# #     ## ",
        "           ",
        "   # #  # #",
        "  #  #  #  ",
        " #       # ",
    };
    
    if (pos == 0) drawMesh(x,y,e/2,f1,color);
    if (pos == 1) drawMesh(x,y,e/2,f2,color);
    if (pos == 2) drawMesh(x,y,e/2,f3,color);
}
void drawEnemy2(int x, int y, int e, int pos, int color)
{
    std::vector<std::string> f1 = {
        "    ###    ",
        "   #####   ",
        "  #######  ",
        " ##-###-## ",
        "###########",
        "###########",
        "   #   #   ",
        "  # ### #  ",
        " # #   # # ",
    };
    std::vector<std::string> f2 = {
        "   ## ##   ",
        "  #######  ",
        "  #######  ",
        " ##-###-## ",
        "###########",
        "###########",
        "  # ### #  ",
        "##       ##",
        "  #     #  ",
    };
    std::vector<std::string> f3 = {
        " #       # ",
        "  #  #  #  ",
        "   # # #  #",
        "           ",
        "# #     ## ",
        "           ",
        "   # #  # #",
        "  #  #  #  ",
        " #       # ",
    };
    if (pos == 0) drawMesh(x,y,e/2,f1,color);
    if (pos == 1) drawMesh(x,y,e/2,f2,color);
    if (pos == 2) drawMesh(x,y,e/2,f3,color);
}

void drawEnemy3(int x, int y, int e, int pos, int color)
{
    std::vector<std::string> f1 = {
        "    ######    ",
        " ############ ",
        "##############",
        "###---##---###",
        "##############",
        "   ###  ###   ",
        "  ##  ##  ##  ",
        "##          ##",
    };
    std::vector<std::string> f2 = {
        "    ######    ",
        " ############ ",
        "##############",
        "###---##---###",
        "##############",
        "  ####  ####  ",
        " ###  ##  ### ",
        "  ###    ###  ",
    };

    std::vector<std::string> f3 = {
        "  #         # ",
        "   #   #   #  ",
        "    #  #  #  #",
        "              ",
        " # #       ## ",
        "              ",
        "    #  #   # #",
        "   #   #   #  ",
    };
    if (pos == 0) drawMesh(x,y,e/2,f1,color);
    if (pos == 1) drawMesh(x,y,e/2,f2,color);
    if (pos == 2) drawMesh(x,y,e/2,f3,color);
}

void drawEnemy4(int x, int y, int e, int pos, int color)
{
    std::vector<std::string> f1 = {
        "          #########          ",
        "      #################      ",
        "    #####################    ",
        "  ####  ###  ###  ###  ####  ",
        "#############################",
        "    ######   ###     #####   ",
        " ###  ##        ###    ##    ",
        "#  #   ##        #   # ###   ",
    };

    std::vector<std::string> f2 = {
        "     ###  ####   ##     ##   ",
        "     ## ####   ###  ## ##    ",
        " ## ####  #####   # ##  #    ",
        "  ####  ###  ###  # #  ####  ",
        "## #  # ##   # #  #### # # ##",
        "    ######   ###     #####   ",
        " ###  ##        ###    ##    ",
        "#  #   ##        #   # ###   ",
    };
    std::vector<std::string> f3 = {
        "##    #  # ##    ##     ##   ",
        "  ## #   # #   ###  ## ##    ",
        "    ##   ######   # ##  #    ",
        "    ##  #      ##  #   ####  ",
        "  # ####        # #### # # ##",
        "   ##  ##   #  #    ##  ##   ",
        "  #   ##   ##   ##    ###    ",
        " #  ##    ##   ###     # ##  ",
    };
    std::vector<std::string> f4 = {
        "##    #    ##    ##     ##   ",
        "  #      # #    #      #     ",
        "    ##   # #  ##    # #      ",
        "     #  #     ##  ##         ",
        "    #  #            ## # # ##",
        "       ##           #        ",
        "  #   #    #    ##    ###    ",
        " #  ##    ##   # #     # ##  ",
    };
    if (pos == 0) drawMesh(x,y,e/2,f1,color);
    if (pos == 1) drawMesh(x,y,e/2,f2,color);
    if (pos == 2) drawMesh(x,y,e/2,f3,color);
    if (pos == 3) drawMesh(x,y,e/2,f4,color);
}
void drawPlayer(int x, int y, int e, int pos, int color)
{
    std::vector<std::string> f1 = {
        "              ",
        "       #      ",
        "      ###     ",
        "      ###     ",
        "  ########### ",
        "##############",
        "##############",
        "##############",
        "              ",
    };
    std::vector<std::string> f2 = {
        "     #   #    ",
        "  #   #  #    ",
        " # #    #   # ",
        "    #  ##  #  ",
        "  #         # ",
        "#        # #  ",
        "    # #   # # ",
        "   #   #     #",
        "  #    ##  #  ",
    };
    pos %=2;
    if (pos == 0) drawMesh(x,y,e/2,f1, color);
    if (pos == 1) drawMesh(x,y,e/2,f2, color);
}
void drawBullet1(int x, int y, int e, int pos, int color)
{
    std::vector<std::string> f1 = {
        "  # ",
        " #  ",
        " #  ",
        "  # ",
    };
    std::vector<std::string> f2 = {
        "    ",
        "#  #",
        " ## ",
        "    ",
    };
    std::vector<std::string> f3 = {
        " #  ",
        "  # ",
        "  # ",
        " #  ",
    };
    if (pos == 0) drawMesh(x,y,e/2,f1,color);
    if (pos == 1) drawMesh(x,y,e/2,f2,color);
    if (pos == 2) drawMesh(x,y,e/2,f3,color);
}

void drawBullet(int x, int y, int e, int color)
{
    std::vector<std::string> f1 = {
        "#",
    };
    drawMesh(x,y,e/2,f1,color);
}

void jugar(int x, int y, int e)
{
    int a = 0;
    int tecla = 0;
    while(true)
    {
        if (kbhit()){
            tecla = getch();
        }
        for (int i=0; i<15; i++) {
            for (int j=0; j<15; j++) {
                
                if (game[i][j] == E) {
                    drawEnemy(x+j*e*5, y+i*e*5, e, a%3, COLOR(2,243,255));
                }
                if (game[i][j] == F) {
                    drawEnemy2(x+j*e*5, y+i*e*5, e, a%3, COLOR(60, 255, 0));
                }
                if (game[i][j] == G) {
                    drawEnemy3(x+j*e*5, y+i*e*5, e, a%3, COLOR(230, 0, 255));
                }
                if (game[i][j] == Z) {
                    drawEnemy4(x+j*e*5, y+i*e*5, e, a%3, COLOR(255,25,1));
                }
                if (game[i][j] == P) {
                    drawPlayer(x+j*e*5, y+i*e*5, e, a, COLOR(35,204,1));
                }
                if (game[i][j] == b) {
                    drawBullet(x+j*e*5, y+i*e*5, e, YELLOW);
                }
                if (game[i][j] == c) {
                    drawBullet1(x+j*e*5, y+i*e*5, e, a%3, YELLOW);
                }
            }
        }
        a++;
        // drawEnemy(100,100,scale,a);
        delay(800);
    }
}

int main()
{
    initwindow(800,600);
    int scale = 10;
    jugar(10,10,scale);
    getch();
    closegraph();
}

/*
    
*/