#include <iostream>
using namespace std;

#include <cmath>

class Point
{
public:
    Point(int x, int y) : x(x), y(y){}
    friend float dis(Point &p1, Point &p2);
private:
    int x, y;
};
float dis(Point &p1, Point &p2)
{
    return sqrt(pow(p1.x-p2.x, 2) + pow(p1.y-p2.y, 2));
}
int main()
{
    Point p1(0, 3);
    Point p2(4, 0);
    cout << "distance:" << dis(p1, p2) << endl;
}