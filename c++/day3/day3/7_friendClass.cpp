#include <iostream>
using namespace std;

class A{
public:
    A(int x):a(x){}
private:
    friend class B;   //声明友元类
    int a;
};
class B{
public:
    void printMsg(A &obj){
        cout << obj.a << endl;      //访问a，打破了A类的封装 
    }
    void setAobj(A &obj){
        obj.a = 20;                 //修改a的值，打破了A类的封装
    }
};
int main()
{
    A a(10);
    B b;
    b.printMsg(a);
    return 0;
}