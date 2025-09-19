#include <iostream>
using namespace std;


class Demo{
public:
    Demo(int x):x(x){}

    friend int operator+(int a, Demo &obj){
        return a + obj.x;
    }
    friend ostream& operator<<(ostream &out, Demo &obj){
        out << obj.x;
        return out;
    }
    int operator()(int a, int b){
        x = a + b;
        return x;
    }
private:
    int x;
};
int main()
{
    Demo obj(10);
    cout << 1 + obj << endl;
    cout << obj << endl;        // operator<<(cout, obj) << endl;
    int a = obj(23, 12);        // 仿函数
    cout << obj << endl;
}

/*
    Array buf(5);
    for(int i = 0; i < 5; i++)
        buf[i] = i;
    
    for(int i = 0; i < 5; i++)
        cout << buf[i] << " ";
    cout << endl;
*/