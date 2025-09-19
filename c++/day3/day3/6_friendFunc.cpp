#include <iostream>
using namespace std;

class Demo
{
public:
    friend void setValue(Demo &s, int x)  //声明定义一个友元函数
    {
        // this->x = x;          //友元函数不是类的成员函数，因此没有 this指针
        // y = x;                //错误，该函数不是类域中，不能直接访问类的任何成员
        s.x = x;
    }
    friend int getValue(Demo &);        //声明友元函数
private:
    int x;
    int y;
};

int getValue(Demo &o)          //友元函数类外部的定义，就是一个普通函数的定义
{
    return o.x;                //正确，该友元函数打破了Demo类的封装，对象可访问类的任何成员
}

int main()
{
    Demo obj;
    setValue(obj, 12);          //友元函数的调用
    cout << getValue(obj) << endl;
}