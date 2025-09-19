#include <iostream>
using namespace std;

class Demo{
public:
    Demo(int x): x(x){}

    friend int operator+(Demo &, int);      //声明友元运算符重载函数
    friend int operator+(int, Demo &);
    friend int operator+(Demo &, Demo &);
    friend int operator++(Demo &);          //前++运算符重载函数
    friend int operator++(Demo &, int);          //后++运算符重载函数
private:
    int x;
};
int operator+(Demo &obj, int a) 
{
    return obj.x + a;
}
int operator+(int a, Demo &obj) 
{
    return obj.x + a;
}
int operator+(Demo &obj1, Demo &obj2) 
{
    return obj1.x + obj2.x;
}

int operator++(Demo &obj)
{
    return ++obj.x;
}
int operator++(Demo &obj, int)
{
    return obj.x++;
}
int main()
{
    int a = 10;
    cout << a << endl;
    cout << a + 1 << endl;

    Demo obj(10);
    cout << obj + 1 << endl;  
    cout << operator+(obj, 1) << endl;
    cout << 1 + obj << endl;            // operator+(1, obj);

    Demo obj2(20);
    cout << obj + obj2 << endl;     // --> 30

    cout << obj2++ << endl;         // --> 20
    cout << operator++(obj2, 1) << endl;
    cout << ++obj2 << endl;         // --> 22
}