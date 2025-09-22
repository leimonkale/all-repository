#include "qcheck.h"
#include "ui_qcheck.h"

qcheck::qcheck(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::qcheck)
{
    ui->setupUi(this);

    connect(ui->checkBox_2,&QCheckBox::checkStateChanged,this,&qcheck::auto_agin);

    //判断复选框的勾选状态
    if(!ui->checkBox->isChecked())
        //设置复选框勾选
        ui->checkBox->setChecked(true);
}

qcheck::~qcheck()
{
    delete ui;
}

//checkstatechanged(const qt::checkstate &):该信号 在复选框状态被改变时触发
void qcheck::on_checkBox_checkStateChanged(const Qt::CheckState &arg1)
{
    if(arg1 == Qt::Unchecked){
        ui->lineEdit->setText("忘记密码");
    }
    if(arg1 == Qt::Checked){
        ui->lineEdit->setText("记住密码");
    }
}

void qcheck::auto_agin(const Qt::CheckState arg1){
    if(arg1 == Qt::Unchecked){
        ui->lineEdit->setText("手动登录");
    }
    if(arg1 == Qt::Checked){
        ui->lineEdit->setText("自动登录");
    }
}

