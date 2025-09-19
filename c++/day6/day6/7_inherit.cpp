#include <iostream>
using namespace std;

#define pri cout << "func: " << __func__ << endl;

class Base{
public:
    Base(int x): x(x){ pri; }
    int getX(){
        return x;
    }
private:
    int x;
};

class Derived: public Base{
public:
    Derived(int y): y(y), Base(12)
    {}
    int getY(){
        return y;
    }
private:
    int y;
};

int main()
{
    Derived d(1);
    cout << d.getX() << " " << d.getY() << endl;

    Base obj(25);

    obj = d;                    //向上隐式转换，将派生类对象中基类部分的数据拷贝 给基类对象
    cout << obj.getX() << endl;

    // d = obj;                 //错误，不允许向下隐式转化，基类对象中没有 派生类类型的数据

    Base *p = &d;
    p = new Derived(2);
    Base &q = d;
}
