#include "qcheck.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qcheck w;
    w.show();
    return a.exec();
}
