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
    int getY() const;       //声明const成员函数
private:
    const int x;
    int y;
};
int Demo::getY() const      //const成员函数的定义
{
    // y += 13;             //错误，const成员函数只能访问成员变量，不能修改
    // getX();              //错误，c++默认的成员函数都可以修改成员变量，const成员函数只能调用 const成员函数
    return y;
}
int main()
{
    Demo obj(1, 2);
}
