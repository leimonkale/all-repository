#include <iostream>
using namespace std;
#include <cstring>
class Demo{
public:
    Demo(const char *p){
        len = strlen(p);
        arr = new char[len];
        strcpy(arr, p);
    }

    Demo(Demo& s){
#if 0
        // 浅拷贝
        len = s.len;
        arr = s.arr;
#else 
        //深拷贝
        len = s.len;
        arr = new char[len];
        strcpy(arr, s.arr);
#endif
        cout << __func__ << " " << __LINE__ << endl;
    }

    void setArr(const char *a){
        if( strlen(a) > len){
            delete [] arr;
            arr = new char[strlen(a)];
        }
        strcpy(arr, a);
        len = strlen(a);
    }
    char *getArr(){
        return arr;
    }
private:
    char *arr;
    int len;
};

int main()
{
    Demo obj("hello world");
    Demo obj1 = obj;
    cout << obj1.getArr() << endl;

    obj1.setArr("welcome");
    cout << "obj1: " << obj1.getArr() << endl;
    cout << "obj: " << obj.getArr() << endl;
}