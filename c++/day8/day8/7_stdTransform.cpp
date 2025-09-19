#include <iostream>
using namespace std;


class Base{
    int x;
public:
    Base(int x):x(x){}
    int getX(){ return x; }
};
class Derived:public Base{
    int y;
public:
    Derived(int x,int y):Base(x),y(y){}
    void print(){
        cout << getX() << " " << y << endl;
    }
};
int main()
{
    char *str = "ab123";

    // 1、reinterpret_cast 将 一个指针转换为另一个指针类型
    int *q = reinterpret_cast<int *>(str);
    cout << *q << endl;
    char *s = reinterpret_cast<char *>(q);
    cout << s << endl;

    // 2、const_cast 将一个const指针转换为非const指针
    const char *p = "abc";
    char *r = const_cast<char *>(p);
    cout << r << endl;

    // 3、static_cast： 在继承关系间类型转换
    Base *b = new Base(14);
    Derived *d = static_cast<Derived *>(b);
    d->print();
    delete b;
}