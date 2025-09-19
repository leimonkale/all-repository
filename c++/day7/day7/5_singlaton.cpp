#include <iostream>
using namespace std;

class Singleton1{
public:
    static Singleton1* getInstance();
private:
    Singleton1(){}
    static Singleton1* instance;     //定义静态的当前类对象指针作为成员
};
Singleton1* Singleton1 :: instance = NULL;        //懒汉式
Singleton1* Singleton1 :: getInstance(){
    if(instance == NULL){           // 判断是否有实例
        instance = new Singleton1(); // 没有就 创建实例
    }
    return instance;                // 返回实例
}


class Singleton2{
public:
    static Singleton2* getInstance();
    static void delInstance(Singleton2*);
private:
    Singleton2(){}
    static Singleton2* instance;     //定义静态的当前类对象指针作为成员
};
Singleton2* Singleton2 :: instance = new Singleton2();        //饿汉式
Singleton2* Singleton2 :: getInstance()
{
    return instance;                // 返回实例
}
void Singleton2 ::delInstance(Singleton2*instance)
{
    delete instance;
}

int main()
{
    Singleton1* s1 = Singleton1 :: getInstance();
    Singleton1* s2 = Singleton1 :: getInstance();
    cout << s1 << endl;
    cout << s2 << endl;


    Singleton2* s3 = Singleton2 :: getInstance();
    Singleton2* s4 = Singleton2 :: getInstance();
    cout << s3 << endl;
    cout << s4 << endl;

    return 0;
}