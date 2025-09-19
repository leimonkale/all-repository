#include <iostream>
using namespace std;

#define pri cout << "func: " << __func__ << endl;

class Man{
public:
    Man(){ pri; }
    ~Man(){ pri; }
    void print(){ pri; }
};

class Wolf{
public:
    Wolf(){ pri; }
    ~Wolf(){ pri; }
    void print(){ pri; }
};

class WolfMan: public Wolf, public Man{
public:
    WolfMan(){ pri; }
    ~WolfMan(){ pri; }
};

int main()
{
    WolfMan wm;
    // wm.print();          //错误，有歧义，名字二义性
    wm.Wolf::print();       //作用域访问符
}