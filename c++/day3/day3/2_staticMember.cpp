#include <iostream>
using namespace std;

class Demo
{
public:
    Demo(){}
    Demo(int x, int y);

    int getValue(){
        // return this->x;
        return Demo::x;
    }
private:
    static int x; 
    int y;
};
int Demo::x = 12; 

// 1、构造函数参数初始化列表(初始化列表)  : 成员(形参), 成员(形参) ...
// 2、构造函数初始化列表只在构造函数定义时存在，声明不能使用。
Demo::Demo(int a, int b) : y(b)
{
    // this->x = a;   //变量赋值
    // this->y = b;
}
int main()
{
    Demo obj(1, 2);
    // cout << obj.x << endl;
    // cout << Demo::x << endl;
    // // cout << Demo::a << endl;     // 错误，a是非静态成员
    // Demo obj1;
    // cout << obj1.x << endl;
    // obj1.x += 13;
    // cout << obj.x << endl;

    cout << obj.getValue() << endl;

}