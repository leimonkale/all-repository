#include <iostream>
using namespace std;



/*
     构造函数：
         1、没有返回值，没有数据类型
         2、函数名与类名相同，可以有参数
     构造函数的意义：
         定义类对象时，系统自动调用，用来初始化 对象。
     
    当类体中没有显示定义 默认构造、默认析构、拷贝构造、移动构造、赋值运算、地址运算等，编译器都将自动生成。

    注意：
        1、当类体中定义了有参构造，默认构造就不会自动生成。
        2、构造函数也可以重载
*/
#define pri() cout << __func__ << " " << __LINE__ << endl;

class Demo{
public:
    Demo(){      //定义无参构造函数，也就是显示定义默认构造
        pri() 
    }
    Demo(Demo& o){      //拷贝构造函数(浅拷贝)
        pri()
        val = o.val;    
    }
    Demo(Demo&& o){     //移动构造
        pri()
        val = o.val;    //转移资源
        o.val = -1;     //移交原对象对数据的操作权
    }
    Demo(int x){   //定义有参构造，编译器不会自动生成
        pri()
        val = x;
    }
    void setValue(int x){
        val = x;
    }
    int getValue(){
        return val;
    }
private:
    int val;
};

int main()
{               
    Demo obj;    //定义类对象，系统自动调用构造函数，完成初始化成员变量
    obj.setValue(13);
    cout << obj.getValue() << endl;
    cout << "-----------------------------------" << endl;

    Demo obj1(23);          //调用有参构造
    cout << obj1.getValue() << endl;
    cout << "-----------------------------------" << endl;

    Demo obj2 = obj1;       //调用默认的拷贝构造       
    cout << obj2.getValue() << endl;
    cout << "-----------------------------------" << endl;

    Demo obj3(obj2);        //调用拷贝构造
    cout << obj3.getValue() << endl;
    cout << "-----------------------------------" << endl;

    Demo obj4 = move(obj2);  //调用移动构造
    cout << obj4.getValue() << endl;
    cout << "-----------------------------------" << endl;

    // //需求 构造形参为 const & 或 &&，会调用有参构造
    Demo obj5 = 36; 
    cout << obj5.getValue() << endl;
    cout << "-----------------------------------" << endl;

    Demo *p;
    p = new Demo;
    delete p;

    p = new Demo(12);
}