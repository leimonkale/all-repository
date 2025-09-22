#ifndef QCHECK_H
#define QCHECK_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class qcheck;
}
QT_END_NAMESPACE

class qcheck : public QMainWindow
{
    Q_OBJECT

public:
    qcheck(QWidget *parent = nullptr);
    ~qcheck();

private slots:
    void on_checkBox_checkStateChanged(const Qt::CheckState &arg1);

    void auto_agin(const Qt::CheckState arg1);

private:
    Ui::qcheck *ui;
};
#endif // QCHECK_H
