#include <iostream>
using namespace std;

#include <memory>

class Demo{
public:
    Demo(){
        cout << "Constructor called" << endl;
    }
    ~Demo(){
        cout << "Destructor called" << endl;
    }
    void show(){
        cout << "Inside show" << endl;
    }
};

void test()
{
    //定义一个shared_ptr资源共享智能指针
    // shared_ptr<Demo> p(new Demo);

    // make_shared<>(): 用来在堆区安全开辟 某个类型的空间
    shared_ptr<Demo> p = make_shared<Demo>();
    // 定义第二个资源共享智能指针，指向同一片堆区
    shared_ptr<Demo> p2 = p;
    shared_ptr<Demo> p3(p);

    p->show();          //智能指针访问 成员函数， -> 
    p2->show();
    p3->show();
}
int main()
{
    test();
}