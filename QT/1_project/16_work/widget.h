#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void openfile();
    void buildnewfile();
    void savefile();
    void savefileat();
    void closefile();

private:
    Ui::Widget *ui;
    QMenu *stdMenu;
    QString files;
    int flage_open = 0;
    int flage_save = 0;
};
#endif // WIDGET_H
