/********************************************************************************
** Form generated from reading UI file 'imgbox.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMGBOX_H
#define UI_IMGBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_imgbox
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QListWidget *listWidget;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *imgbox)
    {
        if (imgbox->objectName().isEmpty())
            imgbox->setObjectName("imgbox");
        imgbox->resize(911, 663);
        centralwidget = new QWidget(imgbox);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 871, 601));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(30, 20, 256, 581));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(300, 30, 571, 501));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(430, 560, 99, 28));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(550, 560, 99, 28));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(670, 560, 99, 28));
        imgbox->setCentralWidget(centralwidget);
        menubar = new QMenuBar(imgbox);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 911, 24));
        imgbox->setMenuBar(menubar);
        statusbar = new QStatusBar(imgbox);
        statusbar->setObjectName("statusbar");
        imgbox->setStatusBar(statusbar);

        retranslateUi(imgbox);

        QMetaObject::connectSlotsByName(imgbox);
    } // setupUi

    void retranslateUi(QMainWindow *imgbox)
    {
        imgbox->setWindowTitle(QCoreApplication::translate("imgbox", "imgbox", nullptr));
        label->setText(QString());
        label_2->setText(QString());
        pushButton->setText(QCoreApplication::translate("imgbox", "PushButton", nullptr));
        pushButton_2->setText(QCoreApplication::translate("imgbox", "PushButton", nullptr));
        pushButton_3->setText(QCoreApplication::translate("imgbox", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class imgbox: public Ui_imgbox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMGBOX_H
