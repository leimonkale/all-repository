#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QKeyEvent>

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

    //重写特定事件处理器:键盘按下事件处理器
    //      当键盘事件发生：系统自动调用，keypressevent函数处理该事件，并将当前按键的事件信息传递给形参e
    void keyPressEvent(QKeyEvent *e);
    //鼠标移动时间处理器
    void mouseMoveEvent(QMouseEvent *e);
    //重写基类event虚函数
    bool event(QEvent *e);
    //重写事件过滤器
    bool eventFilter(QObject *obj,QEvent *e);
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
