/********************************************************************************
** Form generated from reading UI file 'combo.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMBO_H
#define UI_COMBO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_combo
{
public:
    QWidget *centralwidget;
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *combo)
    {
        if (combo->objectName().isEmpty())
            combo->setObjectName("combo");
        combo->resize(800, 600);
        centralwidget = new QWidget(combo);
        centralwidget->setObjectName("centralwidget");
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(20, 20, 361, 51));
        comboBox->setEditable(true);
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(390, 20, 371, 51));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(390, 80, 99, 28));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(500, 80, 99, 28));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(610, 80, 99, 28));
        combo->setCentralWidget(centralwidget);
        menubar = new QMenuBar(combo);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        combo->setMenuBar(menubar);
        statusbar = new QStatusBar(combo);
        statusbar->setObjectName("statusbar");
        combo->setStatusBar(statusbar);

        retranslateUi(combo);

        QMetaObject::connectSlotsByName(combo);
    } // setupUi

    void retranslateUi(QMainWindow *combo)
    {
        combo->setWindowTitle(QCoreApplication::translate("combo", "combo", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("combo", "1111111111111", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("combo", "\347\216\213\344\274\201\351\271\205", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("combo", "\345\207\204\345\207\204\345\210\207\345\210\207\345\207\204\345\207\204\345\210\207\345\210\207", nullptr));

        pushButton->setText(QCoreApplication::translate("combo", "\346\267\273\345\212\240", nullptr));
        pushButton_2->setText(QCoreApplication::translate("combo", "\345\210\240\351\231\244", nullptr));
        pushButton_3->setText(QCoreApplication::translate("combo", "\346\217\222\345\205\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class combo: public Ui_combo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMBO_H
