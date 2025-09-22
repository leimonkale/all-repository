#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_lineEdit_5_textEdited(const QString &arg1);

    void edt_text(QString arg);

    void on_lineEdit_4_selectionChanged();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
