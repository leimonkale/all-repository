#ifndef COMBO_H
#define COMBO_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class combo;
}
QT_END_NAMESPACE

class combo : public QMainWindow
{
    Q_OBJECT

public:
    combo(QWidget *parent = nullptr);
    ~combo();

private slots:
    void on_comboBox_activated(int index);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::combo *ui;
};
#endif // COMBO_H
