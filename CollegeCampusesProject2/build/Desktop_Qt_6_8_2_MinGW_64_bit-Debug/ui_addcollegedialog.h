/********************************************************************************
** Form generated from reading UI file 'addcollegedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCOLLEGEDIALOG_H
#define UI_ADDCOLLEGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_AddCollegeDialog
{
public:

    void setupUi(QDialog *AddCollegeDialog)
    {
        if (AddCollegeDialog->objectName().isEmpty())
            AddCollegeDialog->setObjectName("AddCollegeDialog");
        AddCollegeDialog->resize(400, 300);

        retranslateUi(AddCollegeDialog);

        QMetaObject::connectSlotsByName(AddCollegeDialog);
    } // setupUi

    void retranslateUi(QDialog *AddCollegeDialog)
    {
        AddCollegeDialog->setWindowTitle(QCoreApplication::translate("AddCollegeDialog", "Add New College", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddCollegeDialog: public Ui_AddCollegeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCOLLEGEDIALOG_H
