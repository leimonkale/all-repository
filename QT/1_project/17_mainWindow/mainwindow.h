#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMenuBar>   //菜单栏
#include <QMenu>      //菜单
#include <QAction>    //菜单项
#include <QToolBar>   //工具栏
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDockWidget>
#include <QTextEdit>

#include <QTabWidget>

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

private:
    Ui::MainWindow *ui;

    QAction *newAct,*openAct,*saveAct,*asAct,*closeAct;
};
#endif // MAINWINDOW_H
