/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "views/hometabwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad_Trip;
    QAction *actionSave_Trip;
    QAction *actionExit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *homeTab;
    QVBoxLayout *homeVerticalLayout;
    QLabel *welcomeLabel;
    QSpacerItem *homeVerticalSpacer;
    QVBoxLayout *buttonLayout;
    QPushButton *goToTripPlannerButton;
    QPushButton *goToSouvenirsButton;
    QPushButton *goToDistancesButton;
    QSpacerItem *verticalSpacer_2;
    QWidget *tripPlannerTab;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QListWidget *campusList;
    QVBoxLayout *verticalLayout_3;
    QPushButton *addToTripButton;
    QPushButton *removeFromTripButton;
    QSpacerItem *verticalSpacer;
    QListWidget *selectedCampusList;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *optimizeRouteButton;
    QPushButton *calculateDistanceButton;
    QLabel *totalDistanceLabel;
    QWidget *souvenirTab;
    QVBoxLayout *souvenirLayout;
    QComboBox *souvenirCampusCombo;
    QTableWidget *souvenirTable;
    QWidget *distancesTab;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QComboBox *startingCampusCombo;
    QTableWidget *distancesTable;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionLoad_Trip = new QAction(MainWindow);
        actionLoad_Trip->setObjectName("actionLoad_Trip");
        actionSave_Trip = new QAction(MainWindow);
        actionSave_Trip->setObjectName("actionSave_Trip");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setStyleSheet(QString::fromUtf8("\n"
"        /* Modern Tab Widget Style */\n"
"        QTabWidget::pane {\n"
"          border: none;\n"
"          background: transparent;\n"
"        }\n"
"        \n"
"        QTabBar::tab {\n"
"          padding: 10px 25px;\n"
"          margin: 0px 3px;\n"
"          border-top-left-radius: 8px;\n"
"          border-top-right-radius: 8px;\n"
"          background: rgba(0, 0, 0, 0.7);\n"
"          color: white;\n"
"          font-weight: bold;\n"
"          font-size: 13px;\n"
"        }\n"
"        \n"
"        QTabBar::tab:hover {\n"
"          background: #E91E63;  /* Pink */\n"
"        }\n"
"        \n"
"        QTabBar::tab:selected {\n"
"          background: #FF5722;  /* Coral */\n"
"          color: white;\n"
"        }\n"
"\n"
"        /* Modern Button Style */\n"
"        QPushButton {\n"
"          background-color: #E91E63;  /* Pink */\n"
"          color: white;\n"
"          border: none;\n"
"          border-radius: 10px;\n"
"          padding: 15px 25px;\n"
"          font-weight: bold;\n"
""
                        "          font-size: 14px;\n"
"          margin: 8px 50px;\n"
"        }\n"
"\n"
"        QPushButton:hover {\n"
"          background-color: #FF5722;  /* Coral */\n"
"          transform: translateY(-2px);\n"
"          box-shadow: 0 5px 15px rgba(0, 0, 0, 0.3);\n"
"        }\n"
"\n"
"        QPushButton:pressed {\n"
"          background-color: #FFC107;  /* Yellow */\n"
"          color: #000000;\n"
"          transform: translateY(1px);\n"
"        }\n"
"\n"
"        /* Modern ComboBox Style */\n"
"        QComboBox {\n"
"          padding: 10px 15px;\n"
"          border: 2px solid #E91E63;  /* Pink */\n"
"          border-radius: 8px;\n"
"          background: rgba(0, 0, 0, 0.8);\n"
"          color: white;\n"
"          min-width: 200px;\n"
"        }\n"
"\n"
"        QComboBox::placeholder {\n"
"          color: rgba(255, 255, 255, 0.6);\n"
"          font-style: italic;\n"
"        }\n"
"\n"
"        QComboBox:hover {\n"
"          border-color: #FF5722;  /* Coral */\n"
"          background: rgba(0, 0"
                        ", 0, 0.9);\n"
"        }\n"
"\n"
"        QComboBox::drop-down {\n"
"          border: none;\n"
"          width: 30px;\n"
"        }\n"
"\n"
"        /* Dark Table Style */\n"
"        QTableWidget {\n"
"          background: rgba(0, 0, 0, 0.8);\n"
"          border-radius: 10px;\n"
"          gridline-color: #E91E63;  /* Pink */\n"
"          color: white;\n"
"          border: 1px solid #FF5722;  /* Coral */\n"
"        }\n"
"\n"
"        QTableWidget::item {\n"
"          padding: 10px;\n"
"          border-radius: 4px;\n"
"          color: white;\n"
"        }\n"
"\n"
"        QTableWidget::item:selected {\n"
"          background: #E91E63;  /* Pink */\n"
"          color: white;\n"
"        }\n"
"\n"
"        QTableWidget::item:hover {\n"
"          background: rgba(255, 87, 34, 0.3);  /* Coral with transparency */\n"
"        }\n"
"\n"
"        QHeaderView::section {\n"
"          background: #000000;\n"
"          color: #FFC107;  /* Yellow */\n"
"          padding: 12px 8px;\n"
"          border: none"
                        ";\n"
"          border-right: 1px solid #E91E63;  /* Pink */\n"
"          border-bottom: 1px solid #E91E63;\n"
"          font-weight: bold;\n"
"        }\n"
"\n"
"        QHeaderView::section:hover {\n"
"          background: rgba(233, 30, 99, 0.3);  /* Pink with transparency */\n"
"        }\n"
"\n"
"        /* Modern Scrollbar Style */\n"
"        QScrollBar:vertical {\n"
"          border: none;\n"
"          background: rgba(0, 0, 0, 0.8);\n"
"          width: 10px;\n"
"          border-radius: 5px;\n"
"        }\n"
"\n"
"        QScrollBar::handle:vertical {\n"
"          background: #E91E63;  /* Pink */\n"
"          border-radius: 5px;\n"
"          min-height: 20px;\n"
"        }\n"
"\n"
"        QScrollBar::handle:vertical:hover {\n"
"          background: #FF5722;  /* Coral */\n"
"        }\n"
"\n"
"        /* Modern Label Style */\n"
"        QLabel {\n"
"          color: white;\n"
"          background-color: rgba(0, 0, 0, 0.7);\n"
"          padding: 15px;\n"
"          border-radius: 10px;\n"
""
                        "          border: 1px solid #E91E63;  /* Pink */\n"
"        }\n"
"\n"
"        /* Tab-specific backgrounds */\n"
"        #homeTab {\n"
"          background: qlineargradient(\n"
"            x1: 0, y1: 0, x2: 1, y2: 1,\n"
"            stop: 0 #000000,\n"
"            stop: 0.3 #E91E63,  /* Pink */\n"
"            stop: 0.6 #FF5722,  /* Coral */\n"
"            stop: 0.9 #FFC107,  /* Yellow */\n"
"            stop: 1 #4DD0E1    /* Blue */\n"
"          );\n"
"        }\n"
"\n"
"        #tripPlannerTab {\n"
"          background: qlineargradient(\n"
"            x1: 0, y1: 0, x2: 1, y2: 1,\n"
"            stop: 0 #000000,\n"
"            stop: 0.4 #E91E63,  /* Pink */\n"
"            stop: 0.8 #FF5722   /* Coral */\n"
"          );\n"
"        }\n"
"\n"
"        #souvenirTab {\n"
"          background: qlineargradient(\n"
"            x1: 0, y1: 0, x2: 1, y2: 1,\n"
"            stop: 0 #000000,\n"
"            stop: 0.4 #FF5722,  /* Coral */\n"
"            stop: 0.8 #FFC107   /* Yellow */\n"
"          );\n"
""
                        "        }\n"
"\n"
"        #distancesTab {\n"
"          background: qlineargradient(\n"
"            x1: 0, y1: 0, x2: 1, y2: 1,\n"
"            stop: 0 #000000,\n"
"            stop: 0.4 #FFC107,  /* Yellow */\n"
"            stop: 0.8 #4DD0E1   /* Blue */\n"
"          );\n"
"        }\n"
"       "));
        homeTab = new QWidget();
        homeTab->setObjectName("homeTab");
        homeVerticalLayout = new QVBoxLayout(homeTab);
        homeVerticalLayout->setObjectName("homeVerticalLayout");
        welcomeLabel = new QLabel(homeTab);
        welcomeLabel->setObjectName("welcomeLabel");
        QFont font;
        font.setPointSize(24);
        font.setBold(true);
        welcomeLabel->setFont(font);
        welcomeLabel->setAlignment(Qt::AlignCenter);

        homeVerticalLayout->addWidget(welcomeLabel);

        homeVerticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        homeVerticalLayout->addItem(homeVerticalSpacer);

        buttonLayout = new QVBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        goToTripPlannerButton = new QPushButton(homeTab);
        goToTripPlannerButton->setObjectName("goToTripPlannerButton");
        goToTripPlannerButton->setMinimumSize(QSize(200, 50));

        buttonLayout->addWidget(goToTripPlannerButton);

        goToSouvenirsButton = new QPushButton(homeTab);
        goToSouvenirsButton->setObjectName("goToSouvenirsButton");
        goToSouvenirsButton->setMinimumSize(QSize(200, 50));

        buttonLayout->addWidget(goToSouvenirsButton);

        goToDistancesButton = new QPushButton(homeTab);
        goToDistancesButton->setObjectName("goToDistancesButton");
        goToDistancesButton->setMinimumSize(QSize(200, 50));

        buttonLayout->addWidget(goToDistancesButton);


        homeVerticalLayout->addLayout(buttonLayout);

        verticalSpacer_2 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        homeVerticalLayout->addItem(verticalSpacer_2);

        tabWidget->addTab(homeTab, QString());
        tripPlannerTab = new QWidget();
        tripPlannerTab->setObjectName("tripPlannerTab");
        verticalLayout_2 = new QVBoxLayout(tripPlannerTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        campusList = new QListWidget(tripPlannerTab);
        campusList->setObjectName("campusList");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(campusList->sizePolicy().hasHeightForWidth());
        campusList->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(campusList);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        addToTripButton = new QPushButton(tripPlannerTab);
        addToTripButton->setObjectName("addToTripButton");

        verticalLayout_3->addWidget(addToTripButton);

        removeFromTripButton = new QPushButton(tripPlannerTab);
        removeFromTripButton->setObjectName("removeFromTripButton");

        verticalLayout_3->addWidget(removeFromTripButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout_3);

        selectedCampusList = new QListWidget(tripPlannerTab);
        selectedCampusList->setObjectName("selectedCampusList");
        sizePolicy.setHeightForWidth(selectedCampusList->sizePolicy().hasHeightForWidth());
        selectedCampusList->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(selectedCampusList);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        optimizeRouteButton = new QPushButton(tripPlannerTab);
        optimizeRouteButton->setObjectName("optimizeRouteButton");

        horizontalLayout_2->addWidget(optimizeRouteButton);

        calculateDistanceButton = new QPushButton(tripPlannerTab);
        calculateDistanceButton->setObjectName("calculateDistanceButton");

        horizontalLayout_2->addWidget(calculateDistanceButton);

        totalDistanceLabel = new QLabel(tripPlannerTab);
        totalDistanceLabel->setObjectName("totalDistanceLabel");

        horizontalLayout_2->addWidget(totalDistanceLabel);


        verticalLayout_2->addLayout(horizontalLayout_2);

        tabWidget->addTab(tripPlannerTab, QString());
        souvenirTab = new QWidget();
        souvenirTab->setObjectName("souvenirTab");
        souvenirLayout = new QVBoxLayout(souvenirTab);
        souvenirLayout->setObjectName("souvenirLayout");
        souvenirCampusCombo = new QComboBox(souvenirTab);
        souvenirCampusCombo->setObjectName("souvenirCampusCombo");

        souvenirLayout->addWidget(souvenirCampusCombo);

        souvenirTable = new QTableWidget(souvenirTab);
        souvenirTable->setObjectName("souvenirTable");

        souvenirLayout->addWidget(souvenirTable);

        tabWidget->addTab(souvenirTab, QString());
        distancesTab = new QWidget();
        distancesTab->setObjectName("distancesTab");
        verticalLayout_6 = new QVBoxLayout(distancesTab);
        verticalLayout_6->setObjectName("verticalLayout_6");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label = new QLabel(distancesTab);
        label->setObjectName("label");

        horizontalLayout_5->addWidget(label);

        startingCampusCombo = new QComboBox(distancesTab);
        startingCampusCombo->setObjectName("startingCampusCombo");

        horizontalLayout_5->addWidget(startingCampusCombo);


        verticalLayout_6->addLayout(horizontalLayout_5);

        distancesTable = new QTableWidget(distancesTab);
        if (distancesTable->columnCount() < 2)
            distancesTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        distancesTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        distancesTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        distancesTable->setObjectName("distancesTable");
        distancesTable->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        distancesTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        distancesTable->setSortingEnabled(true);

        verticalLayout_6->addWidget(distancesTable);

        tabWidget->addTab(distancesTab, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionLoad_Trip);
        menuFile->addAction(actionSave_Trip);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "College Campus Tour", nullptr));
        actionLoad_Trip->setText(QCoreApplication::translate("MainWindow", "Load Trip", nullptr));
        actionSave_Trip->setText(QCoreApplication::translate("MainWindow", "Save Trip", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        welcomeLabel->setText(QCoreApplication::translate("MainWindow", "Plan Your College Campus Tour", nullptr));
        goToTripPlannerButton->setText(QCoreApplication::translate("MainWindow", "Plan a Trip", nullptr));
        goToSouvenirsButton->setText(QCoreApplication::translate("MainWindow", "Browse Souvenirs", nullptr));
        goToDistancesButton->setText(QCoreApplication::translate("MainWindow", "View Distances", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(homeTab), QCoreApplication::translate("MainWindow", "Home", nullptr));
        addToTripButton->setText(QCoreApplication::translate("MainWindow", "Add to Trip \342\206\222", nullptr));
        removeFromTripButton->setText(QCoreApplication::translate("MainWindow", "\342\206\220 Remove", nullptr));
        optimizeRouteButton->setText(QCoreApplication::translate("MainWindow", "Optimize Route", nullptr));
        calculateDistanceButton->setText(QCoreApplication::translate("MainWindow", "Calculate Distance", nullptr));
        totalDistanceLabel->setText(QCoreApplication::translate("MainWindow", "Total Distance: 0.0 miles", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tripPlannerTab), QCoreApplication::translate("MainWindow", "Trip Planner", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(souvenirTab), QCoreApplication::translate("MainWindow", "Souvenirs", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Select Starting Campus:", nullptr));
        QTableWidgetItem *___qtablewidgetitem = distancesTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Campus", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = distancesTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Distance (miles)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(distancesTab), QCoreApplication::translate("MainWindow", "Distances", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
