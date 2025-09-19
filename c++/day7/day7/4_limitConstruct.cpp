#include <iostream>
using namespace std;

class Demo{
protected:
    Demo(int a){
        cout << "Constructor called" << endl;
    }
    virtual ~Demo(){}

    friend Demo *create();
    friend void destroy(Demo *p){
        delete p;
    }
private:
    int a;
};

Demo *create()
{
    return new Demo(10);
}
class Subclass : public Demo{
public:
    Subclass(int a) : Demo(a){}
};
int main()
{
    // Demo d(10);  //错误，构造函数权限为 protected 权限，称为限制构造

    Demo *p = new Subclass(10);     // 正确,限制构造的使用方法1： 派生一个子类


    Demo *q= create();      //正确，限制构造的使用方法2：使用友元函数
    destroy(q);

    return 0;
}