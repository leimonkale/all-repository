#include <iostream>
using namespace std;

class Base{
public:
    Base(int x): x(x) {}
    int getValue(){
        return x;
    }
private:
    int x;
};

class Demo{
public:
    Demo(int x): x(x) {}

    operator int(){
        cout << "Demo::operator int()" << endl;
        return x;
    }
    operator Base(){
        return Base(x);
    }
    friend int operator+(int a, Demo &obj){
        cout << "Demo::operator+(int a) 1" << endl;
        return a + obj.x;
    }
    friend int operator+(Demo &obj1, Demo &obj2){
        cout << "Demo::operator+(int a) 2" << endl;
        return obj1.x + obj2.x;
    }
private:
    int x;
};
int main()
{
    int a = 13;
    Demo obj(12);
    
    a = obj;
    cout << a << endl;

    Base b(30);
    b = obj;
    cout << b.getValue() << endl;

    cout << 1 + obj << endl;

    int i = obj + 1;
    cout << i << endl;
}

/*
    转换函数：将自定义 类型转换为 其他任意类型
    语法结构：
        operator 转换类型(){
            return ;
        }
    注意：
        1、转换函数没有数据类型，但有 return
        2、转换函数的返回值类型必须与转换的类型一致
        3、转换函数的参数列表为空
        4、不能定义到 数组 或者 函数、void类型的转换
*/