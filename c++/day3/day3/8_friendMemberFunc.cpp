#include <iostream>
using namespace std;

class A;    //声明不完整类型 A

class B{
public:
    void printMsg(A &);
};

class A{
public:
    A(int x):a(x){}
private:
    friend void B::printMsg(A &obj);        //声明 B的成员函数 printMsg为友元
    int a;
};

void B::printMsg(A &obj)
{
    cout << obj.a << endl;      //访问a，打破了A类的封装 
}
int main()
{
    A a(10);
    B b;
    b.printMsg(a);
    return 0;
}