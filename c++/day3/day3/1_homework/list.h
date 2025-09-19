#ifndef _LIST_
#define _LIST_

class list
{
public:
    list();
    void list_insert(int offset, int data);
    void list_delete(int data);
    void list_update(int olddata, int newdata);
    int list_select(int data);
    int list_show();
private:
    int data;
    list *ptr;  //成员对象指针
};

#endif
