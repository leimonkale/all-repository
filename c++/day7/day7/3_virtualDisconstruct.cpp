#include <iostream>
using namespace std;

#define pri cout << __func__ << " : " << __LINE__ << endl;

class Base {
public:
    Base() {
        pri;
    }
    // virtual ~Base() {  //虚析构函数
    //     pri;
    // }

    virtual ~Base() = 0;       //纯虚析构函数
    virtual void print() = 0;  //纯虚函数
};
Base::~Base() {

}
class Derived : public Base {
public:
    Derived() {
        pri;
    }
    ~Derived() {
        pri;
    }
    void print(){
        
    }
};
int main() 
{
    Base *p = new Derived;
    delete p;
    return 0;
}