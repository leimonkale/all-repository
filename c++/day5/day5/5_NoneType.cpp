#include <iostream>
using namespace std;
#include <cstring>

template<class T, int size>         //size： 非类型形参，代替常量值   T:类型形参，代替数据类型
bool getMemery(T **p)
{
    *p = new T[size];
    return *p != NULL;
}

int main()
{
    int *p = NULL;
    if(getMemery<int, 2>(&p)){
        for(int i = 0; i < 2; i++ ){
            p[i] = i;
        }
        for(int i = 0; i < 2; i++){
            cout << p[i] << " ";
        }
        cout << endl;
    }

    char *q = NULL;
    if(getMemery<char, 32>(&q)){
        strcpy(q, "hello world");
        cout << q << endl;
    }
}