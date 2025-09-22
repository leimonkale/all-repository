#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QLabel *lab;
    QLabel *lab2;
    QLabel *lab3;
    QLineEdit *edt;
    QPushButton *ton;

};
#endif // MAINWINDOW_H
