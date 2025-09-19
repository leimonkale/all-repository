#include <iostream>
using namespace std;

class B;
class A{
public:
    A(int x): x(x){}
    void Show(B &b);
private:
    int x;
};

class B{
public:
    B(int x): x(x){} 
private:
    int x;
    // friend void A::Show(B &b);      //声明友元成员函数
    friend class A;
};
void A::Show(B &b)
{
    cout << "A: " << x << endl;
    cout << "B: " << b.x << endl;
}


int main()
{
    A a(10);
    B b(20);
    a.Show(b);
}