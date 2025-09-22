#ifndef WIDGE_H
#define WIDGE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class widge;
}
QT_END_NAMESPACE

class widge : public QMainWindow
{
    Q_OBJECT

public:
    widge(QWidget *parent = nullptr);
    ~widge();

private slots:
    void on_pushButton_clicked();

private:
    Ui::widge *ui;
};
#endif // WIDGE_H
