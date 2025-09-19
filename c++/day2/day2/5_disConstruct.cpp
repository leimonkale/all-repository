#include <iostream>
using namespace std;

#define pri() cout << "line: " << __LINE__ << " func: " << __func__ << endl;

class Demo
{
public:
    Demo();
    ~Demo() { pri() }

    int getValue();
private:
    int a = 12;
};

Demo::Demo()
{
    pri()
    cout << this << endl;
    cout << this->a << endl;
    cout << (*this).a << endl;
}
int Demo::getValue()
{
    return a;
}

int main()
{
    Demo obj;
    cout << &obj << endl;
    cout << "---------1---------" << endl;
    Demo *p = new Demo;
    cout << p << endl;
    cout << "---------2---------" << endl;
    delete p;
    cout << "---------3---------" << endl;
}