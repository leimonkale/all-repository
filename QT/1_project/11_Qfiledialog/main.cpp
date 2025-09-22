#include "widge.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    widge w;
    w.show();
    return a.exec();
}
