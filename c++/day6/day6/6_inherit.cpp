#include <iostream>
using namespace std;

#define pri cout << "func: " << __func__ << endl;

class Base{
public:
    Base(){ pri;}
    ~Base(){ pri;}
};

class Derived: public Base{
public:
    Derived(){ pri; }
    ~Derived(){ pri; }
};

int main()
{
    Derived d;

}
