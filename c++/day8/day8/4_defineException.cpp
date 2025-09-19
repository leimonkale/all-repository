#include <iostream>
#include <stdexcept>
using namespace std;

class FileException : public exception
{
public:
    FileException(const char *message) noexcept : m_message(message)
    {
    }
    virtual const char *what() const noexcept
    {
        return m_message;
    }
    const char *printMsg() noexcept{
        return m_message;
    }
private:
    const char *m_message;
};

int fileOperation(const char *fileName)
{
    if(fileName == NULL)
    {
        throw invalid_argument("File name is null");
    }
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        // 抛出自定义的异常类对象
        throw FileException("File not found");

        // FileException e("File not found");
        // throw e;
    }
    // ....
    fclose(fp);
    return 0;
}

int main()
{
    char buf[32];
    cin >> buf;
    try
    {
        fileOperation(buf);
    } catch(const exception &e){
        cout << "Exception: " << e.what() << endl;
    }
}