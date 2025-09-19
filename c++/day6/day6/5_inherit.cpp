#include <iostream>
using namespace std;

class Base{
public:
    int x = 1;
protected:
    int b = 2;
private:
    int a = 3;
};

class Derived: public Base{
public:
    void print(){
        cout << "x = " << Base::x << endl;
        cout << "b = " << Base::b << endl;
    }
    int x = 12;
    int b = 13;
};

int main()
{
    Derived d;
    cout << "drived x: " << d.x << endl;
    cout << "Base b: " << d.Base::x << endl;
    d.print();
}
