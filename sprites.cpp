#include <winbgim.h>
#include <math.h>

void back1(int x, int y, float e) {
    setfillstyle(SOLID_FILL, GREEN);
    setcolor(WHITE);
    rectangle(x, y, x+e, y+e);
    floodfill(x+e*.5, y+e*.5, WHITE);
}

int deg() {
    int x1=100, y1=100, x2=600, y2=600;
    int numSteps=5;
    int r1=0, g1=0, b1=0;
    int r2=0, g2=0, b2=255;

    for (int i = 0; i < numSteps; ++i) {
        int r = r1+(i*(r2-r1) /numSteps);
        int g = g1+(i*(g2-g1) /numSteps);
        int b = b1+(i*(b2-b1) /numSteps);

        setfillstyle(SOLID_FILL, COLOR(r,g,b));
        bar(x1, y1+i*((y2-y1) /numSteps), x2, y1 + (i+1) * ((y2-y1)/numSteps));
    }
}
int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "lmao");
    // initwindow(800, 800, "xd");
    int scale = 50;
    // back1(10,10,scale);
    // deg();
    while (!kbhit()) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            printf("Mouse clicked at X: %d, Y: %d\n", x, y);
        }
    }
    // getch();
    closegraph();
    return 0;
}