#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
#if 1
    //获得默认菜单栏
   /* QMenuBar *mBar = menuBar();
    QMenu *fMenu = mBar->addMenu("文件");*/       //添加  文件菜单

    QMenu *fMenu = menuBar()->addMenu("文件");
#else
    QMenuBar &mBar = new QMenuBar();
    QMenu *fMenu = mBar.addMenu("文件");
    this->setMenuBar(mBar);
#endif
    QMenu *edtMenu = new QMenu("编辑");
    menuBar()->addMenu(edtMenu);

    newAct = fMenu->addAction("新建文件");
    newAct->setShortcut(QKeySequence("ctrl+n"));
    newAct->setIcon(QIcon(":/1.jpg"));

    openAct = fMenu->addAction(QIcon(":/1.jpg"),"打开文件",QKeySequence("ctrl+o"));
    openAct->setStatusTip("打开...");

    saveAct = fMenu->addAction(QIcon(":/1.jpg"),"保存文件",QKeySequence("ctrl+s"));
    saveAct->setStatusTip("保存...");

    asAct = fMenu->addAction(QIcon(":/1.jpg"),"另存文件",QKeySequence("ctrl+l"));
    asAct->setStatusTip("另存...");

    closeAct = fMenu->addAction(QIcon(":/1.jpg"),"关闭文件",QKeySequence("ctrl+c"));
    closeAct->setStatusTip("关闭...");

    edtMenu->addAction("字体");
    edtMenu->addAction("颜色");
    fMenu->addMenu(edtMenu);



    QToolBar *tool1 = addToolBar("工具1");
    tool1->addAction(newAct);
    tool1->addAction(openAct);
    tool1->addAction(saveAct);
    tool1->addAction(asAct);
    tool1->addAction(closeAct);

    QToolBar *tool2 = new QToolBar("工具2");
    QLabel *lab = new QLabel("页码：");
    QLineEdit *edt = new QLineEdit;
    QPushButton *btn = new QPushButton("跳转");

    tool2->addWidget(lab);          //添加控件
    tool2->addWidget(edt);
    tool2->addWidget(btn);
    tool2->setMovable(false);    //设置不可移动
    //addToolBar(tool2);         //添加工具栏
    addToolBar(Qt::RightToolBarArea,tool2);    //添加工具栏并设置初始位置




    // statusBar() 获取状态栏 showMessage("xxx", 5000): 显示临时消息，5秒
    QLabel *lab1 = new QLabel;
    lab1->setMinimumWidth(200);
    statusBar()->addWidget(lab1);
    statusBar()->addWidget(new QLabel("行数："));
    statusBar()->addWidget(new QLineEdit());
    statusBar()->addWidget(new QLabel("length: "));
    statusBar()->showMessage("hello world", 2000);




    QDockWidget *dock1 = new QDockWidget("工作1");
    dock1->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock1->setWidget(new QTextEdit);
    addDockWidget(Qt::LeftDockWidgetArea,dock1);

    QDockWidget *dock2 = new QDockWidget("工作2");
    dock2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);       //限制停靠边
    dock2->setWidget(new QTextEdit);
    addDockWidget(Qt::LeftDockWidgetArea,dock2);

    QDockWidget *dock3 = new QDockWidget("工作3");
    dock3->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock3->setWidget(new QTextEdit);
    addDockWidget(Qt::LeftDockWidgetArea,dock3);

    tabifyDockWidget(dock1, dock2);
    tabifyDockWidget(dock2, dock3);   //工作区堆叠关系  split切割，分割   --------------------------split line--------------------------
}

MainWindow::~MainWindow()
{
    delete ui;
}
