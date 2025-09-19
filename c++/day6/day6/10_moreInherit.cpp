#include <iostream>
using namespace std;

#define pri cout << "func: " << __func__ << endl;
class Worker{
public:
    Worker(){ pri; }
    ~Worker(){ pri; }

    void show(){
        cout << "show()" << endl;
    }
};
class Singger: public virtual Worker{
public:
    Singger(){ pri; }
    ~Singger(){ pri; }
};

class Writer: public virtual Worker{
public:
    Writer(){ pri; }
    ~Writer(){ pri; }
};
class SingingWriter: public Singger, public Writer{
public:
    SingingWriter(){ pri; }
    ~SingingWriter(){ pri; }
};
int main()
{
    SingingWriter sw;
    // sw.show();  //错误，因为Singger和Writer都继承了show()，路径二义性
    
    // sw.Singger::show();   //正确，指定Singger的show()

    sw.show();
    return 0;
}