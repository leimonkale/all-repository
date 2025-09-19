#include <iostream>
using namespace std;
class Demo
{
public:
    Demo(int x, int y) : x(x)
    {
        this->y = y;
    }

    int getX(){
        return x;
    }
    int getY(){
        return y;
    }
private:
    const int x;        //const修饰成员变量，该变量只可读
    int y;
};
int main()
{
    Demo obj(1, 2);
}
