#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
/*
 * Qt工作原理，时间驱动，信号与槽机制
 *
 *     事件：事件本身或者ui界面上发生的任何事（鼠标移动，点击，键盘按压，定时器等，都称为事件
 *
 *     信号：信号，是一个不完整函数（只声明没有定义），有系统类库提供或者程序员在类体的signal区声明
 *          信号由事件驱动触发，也可以是程序员手动_emit触发
 *
 *     槽函数：是一个完整的成员函数（既有声明又有定义）。
 *          由系统类库提供或者程序员在类体的   xxx slots区域声明。
 *          槽函数可以像普通成员函数一样调用，也可以绑定信号被系统调用。
 *
 *     事件驱动：
 *          当事件发生时界面的元件触发一个或多个信号，
 *     信号与槽机制：
 *          将信号与槽函数进行绑定（关联），当信号被触发，系统自动调用关联的槽函数实现功能。
 *
 *
 *     信号与槽函数绑定方式：
 *          1.如果有ui界面的情况
 *              1.在设计器中选中 控件 ，鼠标右键转到槽，选择绑定的信号
 *                  固定语法：
 *                      void on_objectname_signal();
 *
 *          2.无ui界面文件情况
 *              1手动关联绑定 connect
 *                  Qobject::connect(sender,signal,receiver,slot,connectType=默认值）；
 *                  参数：
 *                      sender:信号触发者，首地址
 *                      signal：触发的信号，首地址
 *                      receiver：信号接收者，首地址
 *                      slot：绑定的槽函数，首地址
 *                  注意：
 *                      receiver 一定是slot声明所在的类对象首地址
 *
 *
 *
 *
 *
 *
 */
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

private slots: //私有槽函数声明区
    void on_pushButton_clicked();  //声明了一个绑定了信号的槽函数

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void dateRead();

private:
    Ui::Widget *ui;


};
#endif // WIDGET_H
