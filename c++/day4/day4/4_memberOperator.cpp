#include <iostream>
using namespace std;

class Demo{
public:
    Demo(int x): x(x){}

    //成员运算符重载函数有 this指针，作为第一形参，指向运算符第一操作数这个自定义类型的对象
    int operator+(int x){
        return this->x + x;
    }
    int operator+(Demo & obj){
        return this->x + obj.x;
    }
    int operator++(){
        return ++this->x;
    }
    int operator++(int){
        return this->x++;
    }
private:
    int x;
};
 // 1、cout << obj << endl;    
 // 2、cout << 1 + obj << endl;    
 // 3、obj(23);  cout << obj << endl;
int main()
{
    int a = 10;
    cout << a << endl;
    cout << a + 1 << endl;

    Demo obj(10);
    cout << obj + 1 << endl;  
    cout << obj.operator+(1) << endl;
    
    Demo obj2(20);
    cout << obj + obj2 << endl;     // --> 30

    cout << obj2++ << endl;         // --> 20
    cout << obj2.operator++(1) << endl;
    cout << ++obj2 << endl;         // --> 22
}