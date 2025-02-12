/********************************************************************************
** Form generated from reading UI file 'collegedistancewidget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLLEGEDISTANCEWIDGET_H
#define UI_COLLEGEDISTANCEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CollegeDistanceWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *headerLayout;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *logoutButton;
    QHBoxLayout *contentLayout;
    QGroupBox *collegesGroup;
    QVBoxLayout *collegesLayout;
    QListWidget *collegeList;
    QGroupBox *selectedGroup;
    QVBoxLayout *selectedLayout;
    QListWidget *selectedColleges;
    QLabel *totalDistanceLabel;

    void setupUi(QWidget *CollegeDistanceWidget)
    {
        if (CollegeDistanceWidget->objectName().isEmpty())
            CollegeDistanceWidget->setObjectName("CollegeDistanceWidget");
        CollegeDistanceWidget->resize(800, 600);
        verticalLayout = new QVBoxLayout(CollegeDistanceWidget);
        verticalLayout->setObjectName("verticalLayout");
        headerLayout = new QHBoxLayout();
        headerLayout->setObjectName("headerLayout");
        titleLabel = new QLabel(CollegeDistanceWidget);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        titleLabel->setFont(font);

        headerLayout->addWidget(titleLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(horizontalSpacer);

        logoutButton = new QPushButton(CollegeDistanceWidget);
        logoutButton->setObjectName("logoutButton");
        logoutButton->setStyleSheet(QString::fromUtf8("background-color: #dc2626; color: white; padding: 8px 16px;"));

        headerLayout->addWidget(logoutButton);


        verticalLayout->addLayout(headerLayout);

        contentLayout = new QHBoxLayout();
        contentLayout->setObjectName("contentLayout");
        collegesGroup = new QGroupBox(CollegeDistanceWidget);
        collegesGroup->setObjectName("collegesGroup");
        collegesLayout = new QVBoxLayout(collegesGroup);
        collegesLayout->setObjectName("collegesLayout");
        collegeList = new QListWidget(collegesGroup);
        collegeList->setObjectName("collegeList");

        collegesLayout->addWidget(collegeList);


        contentLayout->addWidget(collegesGroup);

        selectedGroup = new QGroupBox(CollegeDistanceWidget);
        selectedGroup->setObjectName("selectedGroup");
        selectedLayout = new QVBoxLayout(selectedGroup);
        selectedLayout->setObjectName("selectedLayout");
        selectedColleges = new QListWidget(selectedGroup);
        selectedColleges->setObjectName("selectedColleges");

        selectedLayout->addWidget(selectedColleges);

        totalDistanceLabel = new QLabel(selectedGroup);
        totalDistanceLabel->setObjectName("totalDistanceLabel");

        selectedLayout->addWidget(totalDistanceLabel);


        contentLayout->addWidget(selectedGroup);


        verticalLayout->addLayout(contentLayout);


        retranslateUi(CollegeDistanceWidget);

        QMetaObject::connectSlotsByName(CollegeDistanceWidget);
    } // setupUi

    void retranslateUi(QWidget *CollegeDistanceWidget)
    {
        CollegeDistanceWidget->setWindowTitle(QCoreApplication::translate("CollegeDistanceWidget", "College Distance Finder", nullptr));
        titleLabel->setText(QCoreApplication::translate("CollegeDistanceWidget", "College Distance Finder", nullptr));
        logoutButton->setText(QCoreApplication::translate("CollegeDistanceWidget", "Logout", nullptr));
        collegesGroup->setTitle(QCoreApplication::translate("CollegeDistanceWidget", "Available Colleges", nullptr));
        selectedGroup->setTitle(QCoreApplication::translate("CollegeDistanceWidget", "Your Trip", nullptr));
        totalDistanceLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CollegeDistanceWidget: public Ui_CollegeDistanceWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLLEGEDISTANCEWIDGET_H
