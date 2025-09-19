#include <iostream>
using namespace std;

class Base{
public:
    virtual void func(){
        cout << "Base " << __func__ << endl;
    }
};
class Derived: public Base{
public:
    void func(){
        cout << "Derived " << __func__ << endl;
    }
};
void test(Base *ptr)
{
    ptr->func();
}
int main()
{
    Base b;
    Derived d;

    test(&b);
    test(&d);
}