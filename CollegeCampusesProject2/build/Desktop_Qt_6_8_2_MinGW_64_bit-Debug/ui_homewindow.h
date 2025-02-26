/********************************************************************************
** Form generated from reading UI file 'homewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMEWINDOW_H
#define UI_HOMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomeWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *welcomeLabel;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *buttonLayout;
    QPushButton *distancesButton;
    QPushButton *souvenirsButton;
    QPushButton *tripPlannerButton;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QMainWindow *HomeWindow)
    {
        if (HomeWindow->objectName().isEmpty())
            HomeWindow->setObjectName("HomeWindow");
        HomeWindow->resize(800, 600);
        centralwidget = new QWidget(HomeWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        welcomeLabel = new QLabel(centralwidget);
        welcomeLabel->setObjectName("welcomeLabel");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        welcomeLabel->setFont(font);
        welcomeLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(welcomeLabel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonLayout = new QVBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        distancesButton = new QPushButton(centralwidget);
        distancesButton->setObjectName("distancesButton");
        distancesButton->setMinimumSize(QSize(200, 50));

        buttonLayout->addWidget(distancesButton);

        souvenirsButton = new QPushButton(centralwidget);
        souvenirsButton->setObjectName("souvenirsButton");
        souvenirsButton->setMinimumSize(QSize(200, 50));

        buttonLayout->addWidget(souvenirsButton);

        tripPlannerButton = new QPushButton(centralwidget);
        tripPlannerButton->setObjectName("tripPlannerButton");
        tripPlannerButton->setMinimumSize(QSize(200, 50));

        buttonLayout->addWidget(tripPlannerButton);


        verticalLayout->addLayout(buttonLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        HomeWindow->setCentralWidget(centralwidget);

        retranslateUi(HomeWindow);

        QMetaObject::connectSlotsByName(HomeWindow);
    } // setupUi

    void retranslateUi(QMainWindow *HomeWindow)
    {
        HomeWindow->setWindowTitle(QCoreApplication::translate("HomeWindow", "College Campus Tour - Home", nullptr));
        welcomeLabel->setText(QCoreApplication::translate("HomeWindow", "Welcome to College Campus Tour", nullptr));
        distancesButton->setText(QCoreApplication::translate("HomeWindow", "View Distances", nullptr));
        souvenirsButton->setText(QCoreApplication::translate("HomeWindow", "Browse Souvenirs", nullptr));
        tripPlannerButton->setText(QCoreApplication::translate("HomeWindow", "Plan a Trip", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HomeWindow: public Ui_HomeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEWINDOW_H
