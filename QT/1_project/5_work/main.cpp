#include "tv.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TV w;
    w.show();
    return a.exec();
}
