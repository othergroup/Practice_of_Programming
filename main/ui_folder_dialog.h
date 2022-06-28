/********************************************************************************
** Form generated from reading UI file 'folder_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FOLDER_DIALOG_H
#define UI_FOLDER_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Folder_Dialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;
    QPushButton *pushButton_1;

    void setupUi(QDialog *Folder_Dialog)
    {
        if (Folder_Dialog->objectName().isEmpty())
            Folder_Dialog->setObjectName(QStringLiteral("Folder_Dialog"));
        Folder_Dialog->resize(427, 167);
        label = new QLabel(Folder_Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 60, 16));
        QFont font;
        font.setFamily(QStringLiteral("Hiragino Sans GB"));
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(Folder_Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 50, 41, 16));
        QFont font1;
        font1.setFamily(QStringLiteral("Hiragino Sans GB"));
        label_2->setFont(font1);
        lineEdit = new QLineEdit(Folder_Dialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(60, 50, 331, 16));
        pushButton_2 = new QPushButton(Folder_Dialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(330, 110, 51, 21));
        pushButton_1 = new QPushButton(Folder_Dialog);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));
        pushButton_1->setGeometry(QRect(270, 110, 51, 21));

        retranslateUi(Folder_Dialog);

        QMetaObject::connectSlotsByName(Folder_Dialog);
    } // setupUi

    void retranslateUi(QDialog *Folder_Dialog)
    {
        Folder_Dialog->setWindowTitle(QApplication::translate("Folder_Dialog", "Dialog", nullptr));
        label->setText(QApplication::translate("Folder_Dialog", "\346\226\260\345\273\272\345\210\227\350\241\250", nullptr));
        label_2->setText(QApplication::translate("Folder_Dialog", "\345\220\215\347\247\260:", nullptr));
        pushButton_2->setText(QApplication::translate("Folder_Dialog", "\345\245\275", nullptr));
        pushButton_1->setText(QApplication::translate("Folder_Dialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Folder_Dialog: public Ui_Folder_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FOLDER_DIALOG_H
