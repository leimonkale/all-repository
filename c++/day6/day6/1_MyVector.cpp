#include <iostream>
using namespace std;


template <typename T>
class MyVector
{
public:
    MyVector();
    MyVector(int size);
    MyVector(T *start, T *stop);
    ~MyVector();
    void push_back(T value);
    int size() const;
    T operator[](int index) const;

    void pop_back();

    MyVector<T> operator+(MyVector<T> &other);

    template<class B>
    friend ostream &operator<<(ostream &out, const MyVector<B> &vec);
private:
    T *data;
    T top;
    T maxSize;
};
template<class T> MyVector<T>::MyVector(){
    maxSize = 10;
    data = new int[maxSize];
    top = 0;
}
template<class T> MyVector<T>::~MyVector(){
    delete [] data;
}
template<class T> void MyVector<T>::push_back(T value){
    if(top == maxSize){             //判断数组空间是否足够
        maxSize *= 2;                
        T *temp = new T[maxSize];   //申请新的空间
        for(int i = 0; i < maxSize; i++)//拷贝数据
            temp[i] = data[i];
        delete [] data;                 //释放旧空间
        data = temp;                    //更新指针
    }
    data[top++] = value;
}
template<class T> int MyVector<T>::size() const{
    return top;
}
template<class T> T MyVector<T>::operator[](int index) const{
    return data[index];
}
template<class T> void MyVector<T>::pop_back(){
    top--;
}
template<class T> MyVector<T> MyVector<T>::operator+(MyVector<T> &other){
    MyVector<T> temp;
    for(int i = 0; i < size(); i++)
        temp.push_back(data[i]);
    for(int i = 0; i < other.size(); i++)
        temp.push_back(other[i]);
    return temp;
}

template<class B> ostream &operator<<(ostream &out, const MyVector<B> &vec){
    for(int i = 0; i < vec.size(); i++)
        // out << vec[i] << " ";  //out << vec.operator[](i) << " ";
        out << vec.data[i] << " ";
    return out;
}

template<class T> MyVector<T>::MyVector(int size)
{ 
    maxSize = size;
    data = new T[size];
    top = 0;
}
template<class T> MyVector<T>::MyVector(T *start, T *stop)
{
    maxSize = stop - start;
    data = new T[maxSize];
    top = 0;
    for(int i = 0; i < maxSize; i++)
        data[top++] = *(start + i);
}
int main()
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    for(int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;  
    
    v.pop_back();
    cout << v.size() << endl;

    MyVector<int> v2;
    for(int i = 0; i < 20; i++)
        v2.push_back(i);
    cout << v2.size() << endl;
    for(int i = 0; i < v2.size(); i++)
        cout << v2[i] << " ";
    cout << endl;  

    cout << v + v2 << endl;

    MyVector <int> v3(20);

    int buf[] = {1, 2, 3, 4, 5};
    MyVector<int> v4(buf, buf + sizeof(buf)/sizeof(int));
    cout << v4 << endl;
}