#include "list.h"
#include <iostream>
using namespace std;


list::list()
{
    data = -1;
    ptr = NULL;
}

void list::list_insert(int offset, int data)
{
    list *tmp = this->ptr;
    //pack;
    list *node = new list[sizeof(list)];
    node->data = data;
    node->ptr = NULL;

    while(offset-- && tmp)
        tmp = tmp->ptr;

    node->ptr = tmp->ptr;
    tmp->ptr = node;
}

void list::list_delete(int data)
{
    list *tmp = this->ptr;
    while(tmp)
    {
        if(tmp->ptr->data == data)
        {
            list *t = tmp->ptr;
            tmp->ptr = tmp->ptr->ptr;
            free(t);
        }
        tmp = tmp->ptr;
    }
}

void list::list_update(int olddata, int newdata)
{
    list *tmp = this->ptr;
    while(tmp)
    {
        if(tmp->data == olddata)
        {
            tmp->data = newdata;
            break;
        }

        tmp = tmp->ptr;
    }
}

int list::list_select(int data)
{
    list *tmp = this->ptr;
    while(tmp)
    {
        if(tmp->data == data)
        {
            return 1;
        }
        tmp = tmp->ptr;
    }

    return 0;
}

int list::list_show()
{
    list *tmp = this->ptr;
    while(tmp)
    {
        cout << tmp->data << ", ";
        tmp = tmp->ptr;//list++
    }
    cout << endl;
    return 0;
}

