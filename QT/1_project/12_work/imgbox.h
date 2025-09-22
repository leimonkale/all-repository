#ifndef IMGBOX_H
#define IMGBOX_H

#include <QMainWindow>

#include <QDebug>
#include <QFileDialog>
#include <qlistwidget.h>


QT_BEGIN_NAMESPACE
namespace Ui {
class imgbox;
}
QT_END_NAMESPACE

class imgbox : public QMainWindow
{
    Q_OBJECT

public:
    imgbox(QWidget *parent = nullptr);
    ~imgbox();

private slots:
    void on_pushButton_2_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::imgbox *ui;
};
#endif // IMGBOX_H
