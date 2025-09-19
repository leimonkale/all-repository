
#include <iostream>
using namespace std;
class Demo
{
public:
    Demo(){}
    Demo(int x, int y) : y(y){}

    int getX(){
        return Demo::x;
    }
    static int getY();          //声明静态成员函数
private:
    static int x; 
    int y;
};
int Demo::x = 12; 

int Demo::getY()
{
    // return y;            //错误，静态成员函数只能访问类的静态成员
    // return this->x;      //错误，静态成员函数没有 this指针
    return x;    
}
int main()
{
    cout << Demo::getY() << endl;
}