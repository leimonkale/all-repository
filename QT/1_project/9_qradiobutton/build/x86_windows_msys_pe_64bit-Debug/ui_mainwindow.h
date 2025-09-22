/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEdit;
    QGroupBox *groupBox;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_3;
    QGroupBox *groupBox_2;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_7;
    QRadioButton *radioButton_8;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(859, 678);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(180, 40, 231, 31));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(180, 80, 291, 121));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(0, 90, 161, 24));
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setGeometry(QRect(0, 30, 151, 24));
        radioButton_4 = new QRadioButton(groupBox);
        radioButton_4->setObjectName("radioButton_4");
        radioButton_4->setGeometry(QRect(0, 70, 161, 24));
        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName("radioButton_3");
        radioButton_3->setGeometry(QRect(0, 50, 151, 24));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(180, 220, 291, 121));
        radioButton_5 = new QRadioButton(groupBox_2);
        radioButton_5->setObjectName("radioButton_5");
        radioButton_5->setGeometry(QRect(0, 90, 161, 24));
        radioButton_6 = new QRadioButton(groupBox_2);
        radioButton_6->setObjectName("radioButton_6");
        radioButton_6->setGeometry(QRect(0, 30, 151, 24));
        radioButton_7 = new QRadioButton(groupBox_2);
        radioButton_7->setObjectName("radioButton_7");
        radioButton_7->setGeometry(QRect(0, 70, 161, 24));
        radioButton_8 = new QRadioButton(groupBox_2);
        radioButton_8->setObjectName("radioButton_8");
        radioButton_8->setGeometry(QRect(0, 50, 151, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 859, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "1\343\200\201\344\273\245\344\270\213\346\230\257\351\200\211\351\241\271\344\270\255\346\230\257\345\215\225\351\200\211\346\214\211\351\222\256\347\232\204\346\230\257", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "A\343\200\201qradiobutton", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "B\343\200\201qcheckbox", nullptr));
        radioButton_4->setText(QCoreApplication::translate("MainWindow", "D\343\200\201qtpplbutton", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MainWindow", "C\343\200\201qpushbutton", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "1\343\200\201\344\273\245\344\270\213\346\230\257\351\200\211\351\241\271\344\270\255\346\230\257\345\215\225\351\200\211\346\214\211\351\222\256\347\232\204\346\230\257", nullptr));
        radioButton_5->setText(QCoreApplication::translate("MainWindow", "A\343\200\201qradiobutton", nullptr));
        radioButton_6->setText(QCoreApplication::translate("MainWindow", "B\343\200\201qcheckbox", nullptr));
        radioButton_7->setText(QCoreApplication::translate("MainWindow", "D\343\200\201qtpplbutton", nullptr));
        radioButton_8->setText(QCoreApplication::translate("MainWindow", "C\343\200\201qpushbutton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
