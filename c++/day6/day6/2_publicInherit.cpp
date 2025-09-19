#include <iostream>
using namespace std;

class Base{
public:
    int x = 1;
    int getA(){
        return a;
    }
protected:
    int b = 2;
private:
    int a = 3;
};

// 派生一个 子类
class Derived: public Base{
public:
    void print(){
        cout << "x = " << x << endl;
        cout << "b = " << b << endl;
        cout << "a = " << getA() << endl;

        // cout << "a = " << a << endl;  //错误，a是基类私有的成员，不能直接访问
    }
};

int main()
{
    Derived d;
    d.x = 10;
    cout << "d.a = " << d.getA() << endl;
    // d.b = 20;        //错误，b是基类被保护的成员
    // d.a = 30;        //错误，a是基类私有的成员

    d.print();
}
