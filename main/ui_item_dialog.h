/********************************************************************************
** Form generated from reading UI file 'item_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEM_DIALOG_H
#define UI_ITEM_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_item_dialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QLabel *label_6;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;

    void setupUi(QDialog *item_dialog)
    {
        if (item_dialog->objectName().isEmpty())
            item_dialog->setObjectName(QStringLiteral("item_dialog"));
        item_dialog->resize(419, 290);
        label = new QLabel(item_dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(140, 0, 161, 31));
        QFont font;
        font.setFamily(QStringLiteral("Fira Code iScript"));
        font.setPointSize(16);
        font.setItalic(true);
        label->setFont(font);
        label_2 = new QLabel(item_dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 40, 51, 21));
        QFont font1;
        font1.setFamily(QStringLiteral("Fira Code iScript"));
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);
        lineEdit = new QLineEdit(item_dialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(100, 40, 301, 24));
        label_3 = new QLabel(item_dialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 80, 51, 21));
        label_3->setFont(font1);
        lineEdit_2 = new QLineEdit(item_dialog);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(100, 80, 301, 24));
        lineEdit_3 = new QLineEdit(item_dialog);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(100, 120, 301, 24));
        label_4 = new QLabel(item_dialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(40, 120, 51, 21));
        label_4->setFont(font1);
        label_5 = new QLabel(item_dialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(40, 160, 51, 21));
        label_5->setFont(font1);
        lineEdit_4 = new QLineEdit(item_dialog);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(100, 160, 301, 24));
        label_6 = new QLabel(item_dialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(40, 200, 211, 21));
        QFont font2;
        font2.setFamily(QStringLiteral("Fira Code iScript"));
        font2.setPointSize(13);
        font2.setBold(true);
        font2.setWeight(75);
        label_6->setFont(font2);
        pushButton = new QPushButton(item_dialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(230, 200, 61, 31));
        pushButton_2 = new QPushButton(item_dialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(340, 200, 61, 31));
        pushButton_3 = new QPushButton(item_dialog);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(220, 250, 80, 24));
        pushButton_4 = new QPushButton(item_dialog);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(330, 250, 80, 24));

        retranslateUi(item_dialog);

        QMetaObject::connectSlotsByName(item_dialog);
    } // setupUi

    void retranslateUi(QDialog *item_dialog)
    {
        item_dialog->setWindowTitle(QApplication::translate("item_dialog", "Dialog", nullptr));
        label->setText(QApplication::translate("item_dialog", "New Item Information", nullptr));
        label_2->setText(QApplication::translate("item_dialog", "Name:", nullptr));
        label_3->setText(QApplication::translate("item_dialog", "Time:", nullptr));
        label_4->setText(QApplication::translate("item_dialog", "Place:", nullptr));
        label_5->setText(QApplication::translate("item_dialog", "Other:", nullptr));
        label_6->setText(QApplication::translate("item_dialog", "Whether to be reminded: ", nullptr));
        pushButton->setText(QApplication::translate("item_dialog", "Yes", nullptr));
        pushButton_2->setText(QApplication::translate("item_dialog", "No", nullptr));
        pushButton_3->setText(QApplication::translate("item_dialog", "Cancel", nullptr));
        pushButton_4->setText(QApplication::translate("item_dialog", "Yes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class item_dialog: public Ui_item_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITEM_DIALOG_H
