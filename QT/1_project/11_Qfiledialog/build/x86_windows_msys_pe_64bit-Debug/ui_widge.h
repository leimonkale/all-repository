/********************************************************************************
** Form generated from reading UI file 'widge.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGE_H
#define UI_WIDGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widge
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *widge)
    {
        if (widge->objectName().isEmpty())
            widge->setObjectName("widge");
        widge->resize(800, 600);
        centralwidget = new QWidget(widge);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(60, 40, 99, 28));
        widge->setCentralWidget(centralwidget);
        menubar = new QMenuBar(widge);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        widge->setMenuBar(menubar);
        statusbar = new QStatusBar(widge);
        statusbar->setObjectName("statusbar");
        widge->setStatusBar(statusbar);

        retranslateUi(widge);

        QMetaObject::connectSlotsByName(widge);
    } // setupUi

    void retranslateUi(QMainWindow *widge)
    {
        widge->setWindowTitle(QCoreApplication::translate("widge", "widge", nullptr));
        pushButton->setText(QCoreApplication::translate("widge", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widge: public Ui_widge {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGE_H
