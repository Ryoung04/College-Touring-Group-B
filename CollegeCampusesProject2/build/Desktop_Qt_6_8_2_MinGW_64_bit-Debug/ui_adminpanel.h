/********************************************************************************
** Form generated from reading UI file 'adminpanel.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINPANEL_H
#define UI_ADMINPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminPanel
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *collegesTab;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *collegesTable;
    QHBoxLayout *horizontalLayout;
    QPushButton *addCollegeButton;
    QPushButton *editCollegeButton;
    QPushButton *deleteCollegeButton;
    QPushButton *saveCollegesButton;
    QWidget *distancesTab;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *distancesTable;
    QHBoxLayout *distancesButtonLayout;
    QSpacerItem *distancesHorizontalSpacer;
    QPushButton *distancesApplyButton;
    QPushButton *distancesSaveExitButton;
    QPushButton *distancesCancelButton;
    QWidget *souvenirsTab;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *souvenirCollegeCombo;
    QTableWidget *souvenirsTable;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *addSouvenirButton;
    QPushButton *deleteSouvenirButton;
    QPushButton *applySouvenirsButton;
    QPushButton *saveSouvenirsButton;
    QPushButton *cancelSouvenirsButton;
    QWidget *usersTab;
    QVBoxLayout *verticalLayout_5;
    QTableWidget *usersTable;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *addCollegeButton_4;
    QPushButton *editCollegeButton_4;
    QPushButton *deleteCollegeButton_4;
    QPushButton *addUserButton;
    QPushButton *editUserButton;
    QPushButton *deleteUserButton;

    void setupUi(QDialog *AdminPanel)
    {
        if (AdminPanel->objectName().isEmpty())
            AdminPanel->setObjectName("AdminPanel");
        AdminPanel->resize(800, 600);
        verticalLayout = new QVBoxLayout(AdminPanel);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(AdminPanel);
        tabWidget->setObjectName("tabWidget");
        collegesTab = new QWidget();
        collegesTab->setObjectName("collegesTab");
        verticalLayout_2 = new QVBoxLayout(collegesTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        collegesTable = new QTableWidget(collegesTab);
        collegesTable->setObjectName("collegesTable");

        verticalLayout_2->addWidget(collegesTable);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        addCollegeButton = new QPushButton(collegesTab);
        addCollegeButton->setObjectName("addCollegeButton");

        horizontalLayout->addWidget(addCollegeButton);

        editCollegeButton = new QPushButton(collegesTab);
        editCollegeButton->setObjectName("editCollegeButton");

        horizontalLayout->addWidget(editCollegeButton);

        deleteCollegeButton = new QPushButton(collegesTab);
        deleteCollegeButton->setObjectName("deleteCollegeButton");

        horizontalLayout->addWidget(deleteCollegeButton);

        saveCollegesButton = new QPushButton(collegesTab);
        saveCollegesButton->setObjectName("saveCollegesButton");

        horizontalLayout->addWidget(saveCollegesButton);


        verticalLayout_2->addLayout(horizontalLayout);

        tabWidget->addTab(collegesTab, QString());
        distancesTab = new QWidget();
        distancesTab->setObjectName("distancesTab");
        verticalLayout_3 = new QVBoxLayout(distancesTab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        distancesTable = new QTableWidget(distancesTab);
        distancesTable->setObjectName("distancesTable");

        verticalLayout_3->addWidget(distancesTable);

        distancesButtonLayout = new QHBoxLayout();
        distancesButtonLayout->setObjectName("distancesButtonLayout");
        distancesHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        distancesButtonLayout->addItem(distancesHorizontalSpacer);

        distancesApplyButton = new QPushButton(distancesTab);
        distancesApplyButton->setObjectName("distancesApplyButton");

        distancesButtonLayout->addWidget(distancesApplyButton);

        distancesSaveExitButton = new QPushButton(distancesTab);
        distancesSaveExitButton->setObjectName("distancesSaveExitButton");

        distancesButtonLayout->addWidget(distancesSaveExitButton);

        distancesCancelButton = new QPushButton(distancesTab);
        distancesCancelButton->setObjectName("distancesCancelButton");

        distancesButtonLayout->addWidget(distancesCancelButton);


        verticalLayout_3->addLayout(distancesButtonLayout);

        tabWidget->addTab(distancesTab, QString());
        souvenirsTab = new QWidget();
        souvenirsTab->setObjectName("souvenirsTab");
        verticalLayout_4 = new QVBoxLayout(souvenirsTab);
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(souvenirsTab);
        label->setObjectName("label");

        horizontalLayout_3->addWidget(label);

        souvenirCollegeCombo = new QComboBox(souvenirsTab);
        souvenirCollegeCombo->setObjectName("souvenirCollegeCombo");

        horizontalLayout_3->addWidget(souvenirCollegeCombo);


        verticalLayout_4->addLayout(horizontalLayout_3);

        souvenirsTable = new QTableWidget(souvenirsTab);
        souvenirsTable->setObjectName("souvenirsTable");

        verticalLayout_4->addWidget(souvenirsTable);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        addSouvenirButton = new QPushButton(souvenirsTab);
        addSouvenirButton->setObjectName("addSouvenirButton");

        horizontalLayout_4->addWidget(addSouvenirButton);

        deleteSouvenirButton = new QPushButton(souvenirsTab);
        deleteSouvenirButton->setObjectName("deleteSouvenirButton");

        horizontalLayout_4->addWidget(deleteSouvenirButton);

        applySouvenirsButton = new QPushButton(souvenirsTab);
        applySouvenirsButton->setObjectName("applySouvenirsButton");

        horizontalLayout_4->addWidget(applySouvenirsButton);

        saveSouvenirsButton = new QPushButton(souvenirsTab);
        saveSouvenirsButton->setObjectName("saveSouvenirsButton");

        horizontalLayout_4->addWidget(saveSouvenirsButton);

        cancelSouvenirsButton = new QPushButton(souvenirsTab);
        cancelSouvenirsButton->setObjectName("cancelSouvenirsButton");

        horizontalLayout_4->addWidget(cancelSouvenirsButton);


        verticalLayout_4->addLayout(horizontalLayout_4);

        tabWidget->addTab(souvenirsTab, QString());
        usersTab = new QWidget();
        usersTab->setObjectName("usersTab");
        verticalLayout_5 = new QVBoxLayout(usersTab);
        verticalLayout_5->setObjectName("verticalLayout_5");
        usersTable = new QTableWidget(usersTab);
        usersTable->setObjectName("usersTable");

        verticalLayout_5->addWidget(usersTable);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        addCollegeButton_4 = new QPushButton(usersTab);
        addCollegeButton_4->setObjectName("addCollegeButton_4");

        horizontalLayout_5->addWidget(addCollegeButton_4);

        editCollegeButton_4 = new QPushButton(usersTab);
        editCollegeButton_4->setObjectName("editCollegeButton_4");

        horizontalLayout_5->addWidget(editCollegeButton_4);

        deleteCollegeButton_4 = new QPushButton(usersTab);
        deleteCollegeButton_4->setObjectName("deleteCollegeButton_4");

        horizontalLayout_5->addWidget(deleteCollegeButton_4);

        addUserButton = new QPushButton(usersTab);
        addUserButton->setObjectName("addUserButton");

        horizontalLayout_5->addWidget(addUserButton);

        editUserButton = new QPushButton(usersTab);
        editUserButton->setObjectName("editUserButton");

        horizontalLayout_5->addWidget(editUserButton);

        deleteUserButton = new QPushButton(usersTab);
        deleteUserButton->setObjectName("deleteUserButton");

        horizontalLayout_5->addWidget(deleteUserButton);


        verticalLayout_5->addLayout(horizontalLayout_5);

        tabWidget->addTab(usersTab, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(AdminPanel);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AdminPanel);
    } // setupUi

    void retranslateUi(QDialog *AdminPanel)
    {
        AdminPanel->setWindowTitle(QCoreApplication::translate("AdminPanel", "Admin Panel", nullptr));
        addCollegeButton->setText(QCoreApplication::translate("AdminPanel", "Add College", nullptr));
        editCollegeButton->setText(QCoreApplication::translate("AdminPanel", "Edit College", nullptr));
        deleteCollegeButton->setText(QCoreApplication::translate("AdminPanel", "Delete College", nullptr));
        saveCollegesButton->setText(QCoreApplication::translate("AdminPanel", "Save and Exit", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(collegesTab), QCoreApplication::translate("AdminPanel", "Colleges", nullptr));
        distancesApplyButton->setText(QCoreApplication::translate("AdminPanel", "Apply", nullptr));
        distancesSaveExitButton->setText(QCoreApplication::translate("AdminPanel", "Save and Exit", nullptr));
        distancesCancelButton->setText(QCoreApplication::translate("AdminPanel", "Cancel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(distancesTab), QCoreApplication::translate("AdminPanel", "Distances", nullptr));
        label->setText(QCoreApplication::translate("AdminPanel", "College:", nullptr));
        addSouvenirButton->setText(QCoreApplication::translate("AdminPanel", "Add Souvenir", nullptr));
        deleteSouvenirButton->setText(QCoreApplication::translate("AdminPanel", "Delete Selected Souvenir(s)", nullptr));
        applySouvenirsButton->setText(QCoreApplication::translate("AdminPanel", "Apply Changes", nullptr));
        saveSouvenirsButton->setText(QCoreApplication::translate("AdminPanel", "Save and Exit", nullptr));
        cancelSouvenirsButton->setText(QCoreApplication::translate("AdminPanel", "Cancel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(souvenirsTab), QCoreApplication::translate("AdminPanel", "Souvenirs", nullptr));
        addCollegeButton_4->setText(QCoreApplication::translate("AdminPanel", "Add College", nullptr));
        editCollegeButton_4->setText(QCoreApplication::translate("AdminPanel", "Edit College", nullptr));
        deleteCollegeButton_4->setText(QCoreApplication::translate("AdminPanel", "Delete College", nullptr));
        addUserButton->setText(QCoreApplication::translate("AdminPanel", "Add User", nullptr));
        editUserButton->setText(QCoreApplication::translate("AdminPanel", "Edit User", nullptr));
        deleteUserButton->setText(QCoreApplication::translate("AdminPanel", "Delete User", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(usersTab), QCoreApplication::translate("AdminPanel", "Users", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminPanel: public Ui_AdminPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINPANEL_H
