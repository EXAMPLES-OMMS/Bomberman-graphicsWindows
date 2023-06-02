#include <graphics.h>
#include <vector>
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
class Player : public GameObject{
    public:
    void Draw()
    {

    }
};
int main(){
    initwindow(800,600);
    getch();
    closegraph();
    return 0;
}