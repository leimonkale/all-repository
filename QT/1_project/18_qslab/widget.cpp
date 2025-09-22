#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->label_2->installEventFilter(this);      //装载事件处理器
    ui->label_3->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

#include <QDebug>

void Widget::keyPressEvent(QKeyEvent *e)
{
    qDebug() << "key" << e->key();
    //key():获取当前按键的ascll编码值
    switch(e->key()){
        case Qt::Key_A:
        case Qt::Key_Left:
            ui->label->move(ui->label->x() - 1,ui->label->y());
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            ui->label->move(ui->label->x() + 1,ui->label->y());
            break;
        case Qt::Key_W:
        case Qt::Key_Up:
            ui->label->move(ui->label->x(),ui->label->y() - 1);
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            ui->label->move(ui->label->x(),ui->label->y() + 1);
            break;
        default:
            break;
    }

}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    //ui->label->move(e->pos());
    ui->label->move(e->pos().x() - ui->label->width()/2,e->pos().y() - ui->label->height()/2);
}

bool Widget::event(QEvent *e)
{
    qDebug() << "event........";
    //判断事件类型
    //判断事件类型
    if(e->type() == QEvent::KeyPress){
        qDebug() << "key press event..........";
        return true;  //时间完成一定要return，目的是在派生类中截取该事件，不让基类event做处理
    }
    if(e->type() == QEvent::MouseMove){
        qDebug() << "mouse move event..........";
        return true;
    }
    // 其他不处理的事件 交给基类的 event虚函数做默认处理
    return QWidget::event(e);
}

bool Widget::eventFilter(QObject *obj, QEvent *e)
{
    qDebug() << "envenFilter.............";
    if(obj == ui->label_2){                              //判断事件产生者
        if(e->type() == QEvent::MouseButtonPress){       //判断事件类型
            QMouseEvent *event = (QMouseEvent *)e;      //将当前事件转换为鼠标事件
            if(event->button() == Qt::LeftButton){
                ui->label->resize(ui->label->width()+5,ui->label->height() +5);
                //ui->label->move();
                ui->label->setStyleSheet(QString("background-color: red; border-radius:%lpx;").arg(ui->label->width()/2));
                return true;
            }
        }
    }
    if(obj == ui->label_3){                              //判断事件产生者
        if(e->type() == QEvent::MouseButtonPress){       //判断事件类型
            QMouseEvent *event = (QMouseEvent *)e;      //将当前事件转换为鼠标事件
            if(event->button() == Qt::RightButton){
                ui->label->resize(ui->label->width()-5,ui->label->height() -5);
                ui->label->setStyleSheet(QString("background-color: red; border-radius:%lpx;").arg(ui->label->width()/2));
                return true;
            }
        }
    }
    return QObject::eventFilter(obj, e);
}
