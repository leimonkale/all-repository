#include "widget.h"
#include "ui_widget.h"

#include <QHBoxLayout>    //水平布局管理器
#include <QVBoxLayout>     //垂直布局管理器
#include <QGridLayout>     //网格布局管理器

widget::widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::widget)
{
    ui->setupUi(this);
#if 0
    ui->pushButton->setMinimumHeight(61);
    ui->pushButton_2->setMinimumHeight(61);
    ui->pushButton_3->setMinimumHeight(61);
    ui->pushButton_4->setMinimumHeight(61);
    ui->pushButton_5->setMinimumHeight(61);

    QHBoxLayout *hb = new QHBoxLayout;
    QVBoxLayout *vb = new QVBoxLayout;
    hb->setSpacing(1);    //设置布局管理器的间隙
    hb->addStretch();     //添加弹簧
    vb->setSpacing(1);
    //QVBoxLayout *vb = new QVBoxLayout(this);  //制定父对象为窗口
    vb->addLayout(hb);                  //添加布局
    vb->addWidget(ui->textEdit);        //添加控件
    hb->addWidget(ui->pushButton);
    hb->addWidget(ui->pushButton_2);
    hb->addWidget(ui->pushButton_3);
    hb->addWidget(ui->pushButton_4);
    hb->addWidget(ui->pushButton_5);
    this->setLayout(vb);                //设置界面的最终布局
#else
    QGridLayout *gd = new QGridLayout(this);
    // 参数2：所在行号 参数3：所在列号 参数4：占用几行 参数5：占用几列
    gd->addWidget(ui->pushButton, 0, 0, 1, 1);
    gd->addWidget(ui->pushButton_2, 0, 1, 1, 1);
    gd->addWidget(ui->pushButton_3, 0, 2, 1, 1);
    gd->addWidget(ui->pushButton_4, 0, 3, 1, 1);
    gd->addWidget(ui->pushButton_5, 0, 4, 1, 1);
    gd->addWidget(ui->textEdit, 1, 0, 1, 1);
#endif
}

widget::~widget()
{
    delete ui;
}
