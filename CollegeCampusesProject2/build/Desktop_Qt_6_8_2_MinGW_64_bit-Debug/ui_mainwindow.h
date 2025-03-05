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
#include <QtWidgets/QGroupBox>
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
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionAbout;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tripPlannerTab;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *tripPlannerLayout;
    QVBoxLayout *tripInputLayout;
    QLabel *allCollegesLabel;
    QListWidget *allCollegesList;
    QPushButton *addToTripButton;
    QPushButton *resetTripButton;
    QVBoxLayout *routeLayout;
    QLabel *tripLabel;
    QListWidget *tripCollegesList;
    QHBoxLayout *tripButtonsLayout;
    QPushButton *removeFromTripButton;
    QPushButton *moveUpButton;
    QPushButton *moveDownButton;
    QPushButton *optimizeRouteButton;
    QLabel *tripResultsLabel;
    QTextEdit *tripResultsText;
    QWidget *souvenirsTab;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *souvenirsGroup;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *collegeComboBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *refreshSouvenirsButton;
    QTableWidget *souvenirsTable;
    QWidget *distancesTab;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *distancesGroup;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *refreshDistancesButton;
    QTextEdit *distancesTextEdit;
    QLabel *statusLabel;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(950, 700);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow, QDialog, QWidget {\n"
"    background-color: #001F3F;\n"
"    color: #FFFFFF;\n"
"}\n"
"\n"
"QTabWidget::pane {\n"
"    border: 1px solid #0087FF;\n"
"    background: #001F3F;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QTabWidget::tab-bar {\n"
"    left: 5px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background: #153154;\n"
"    border: 1px solid #0087FF;\n"
"    border-bottom-color: #0087FF;\n"
"    border-top-left-radius: 4px;\n"
"    border-top-right-radius: 4px;\n"
"    min-width: 8ex;\n"
"    padding: 10px 15px;\n"
"    margin-right: 2px;\n"
"    font-weight: bold;\n"
"    color: #FFFFFF;\n"
"}\n"
"\n"
"QTabBar::tab:selected, QTabBar::tab:hover {\n"
"    background: #0087FF;\n"
"    color: #FFFFFF;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    border-color: #0087FF;\n"
"    border-bottom-color: #0087FF;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #0087FF;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}"
                        "\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #FF4500;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #AACC00;\n"
"}\n"
"\n"
"QComboBox {\n"
"    padding: 5px;\n"
"    border: 1px solid #0087FF;\n"
"    border-radius: 4px;\n"
"    background: #153154;\n"
"    color: #FFFFFF;\n"
"    min-height: 25px;\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"    background-color: #153154;\n"
"    color: #FFFFFF;\n"
"    selection-background-color: #0087FF;\n"
"    selection-color: #FFFFFF;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 15px;\n"
"    border-left-width: 1px;\n"
"    border-left-color: #0087FF;\n"
"    border-left-style: solid;\n"
"}\n"
"\n"
"QListWidget {\n"
"    border: 1px solid #0087FF;\n"
"    border-radius: 4px;\n"
"    background: #153154;\n"
"    color: #FFFFFF;\n"
"    alternate-background-color: #001F3F;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QListWidget::item:selected {\n"
"    background-co"
                        "lor: #0087FF;\n"
"    color: #FFFFFF;\n"
"}\n"
"\n"
"QTableWidget {\n"
"    border: 1px solid #0087FF;\n"
"    border-radius: 4px;\n"
"    background: #153154;\n"
"    color: #FFFFFF;\n"
"    gridline-color: #0087FF;\n"
"    selection-background-color: #0087FF;\n"
"    selection-color: #FFFFFF;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QTableWidget QHeaderView::section {\n"
"    background-color: #0087FF;\n"
"    color: #FFFFFF;\n"
"    border: 1px solid #001F3F;\n"
"    padding: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QTextEdit {\n"
"    border: 1px solid #0087FF;\n"
"    border-radius: 4px;\n"
"    background: #153154;\n"
"    color: #FFFFFF;\n"
"    padding: 5px;\n"
"    font-family: Consolas, monospace;\n"
"}\n"
"\n"
"QGroupBox {\n"
"    border: 1px solid #0087FF;\n"
"    border-radius: 4px;\n"
"    margin-top: 20px;\n"
"    font-weight: bold;\n"
"    background-color: #153154;\n"
"    color: #FFB700;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;"
                        "\n"
"    subcontrol-position: top left;\n"
"    left: 10px;\n"
"    padding: 0 5px;\n"
"    color: #FFB700;\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"QLabel {\n"
"    color: #FFFFFF;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QMenu {\n"
"    background-color: #153154;\n"
"    color: #FFFFFF;\n"
"    border: 1px solid #0087FF;\n"
"}\n"
"\n"
"QMenu::item {\n"
"    padding: 5px 30px 5px 20px;\n"
"}\n"
"\n"
"QMenu::item:selected {\n"
"    background-color: #0087FF;\n"
"    color: #FFFFFF;\n"
"}\n"
"\n"
"QMenuBar {\n"
"    background-color: #001F3F;\n"
"    color: #FFFFFF;\n"
"}\n"
"\n"
"QMenuBar::item {\n"
"    padding: 5px 10px;\n"
"    background: transparent;\n"
"}\n"
"\n"
"QMenuBar::item:selected, QMenuBar::item:pressed {\n"
"    background: #0087FF;\n"
"    color: #FFFFFF;\n"
"}\n"
"\n"
"QStatusBar {\n"
"    background-color: #001F3F;\n"
"    color: #FFFFFF;\n"
"}\n"
"\n"
"QScrollBar:vertical {\n"
"    border: none;\n"
"    background: #001F3F;\n"
"    width: 12px;\n"
"    margin: 0px;\n"
"}\n"
"\n"
""
                        "QScrollBar::handle:vertical {\n"
"    background: #0087FF;\n"
"    min-height: 20px;\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover {\n"
"    background: #FF4500;\n"
"}\n"
"\n"
"QScrollBar:horizontal {\n"
"    border: none;\n"
"    background: #001F3F;\n"
"    height: 12px;\n"
"    margin: 0px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal {\n"
"    background: #0087FF;\n"
"    min-width: 20px;\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal:hover {\n"
"    background: #FF4500;\n"
"}\n"
"\n"
"QScrollBar::add-line, QScrollBar::sub-line {\n"
"    border: none;\n"
"    background: none;\n"
"}\n"
"\n"
"QScrollBar::add-page, QScrollBar::sub-page {\n"
"    background: none;\n"
"}\n"
"\n"
"QCheckBox {\n"
"    color: #FFFFFF;\n"
"}\n"
"\n"
"QCheckBox::indicator {\n"
"    width: 16px;\n"
"    height: 16px;\n"
"}\n"
"\n"
"QCheckBox::indicator:unchecked {\n"
"    border: 1px solid #0087FF;\n"
"    background: #153154;\n"
"}\n"
"\n"
"QCheckBox::indicator:checked {\n"
""
                        "    border: 1px solid #AACC00;\n"
"    background: #AACC00;\n"
"}\n"
""));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tripPlannerTab = new QWidget();
        tripPlannerTab->setObjectName("tripPlannerTab");
        verticalLayout_3 = new QVBoxLayout(tripPlannerTab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        tripPlannerLayout = new QHBoxLayout();
        tripPlannerLayout->setObjectName("tripPlannerLayout");
        tripInputLayout = new QVBoxLayout();
        tripInputLayout->setObjectName("tripInputLayout");
        allCollegesLabel = new QLabel(tripPlannerTab);
        allCollegesLabel->setObjectName("allCollegesLabel");
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        allCollegesLabel->setFont(font);

        tripInputLayout->addWidget(allCollegesLabel);

        allCollegesList = new QListWidget(tripPlannerTab);
        allCollegesList->setObjectName("allCollegesList");

        tripInputLayout->addWidget(allCollegesList);

        addToTripButton = new QPushButton(tripPlannerTab);
        addToTripButton->setObjectName("addToTripButton");

        tripInputLayout->addWidget(addToTripButton);

        resetTripButton = new QPushButton(tripPlannerTab);
        resetTripButton->setObjectName("resetTripButton");

        tripInputLayout->addWidget(resetTripButton);


        tripPlannerLayout->addLayout(tripInputLayout);

        routeLayout = new QVBoxLayout();
        routeLayout->setObjectName("routeLayout");
        tripLabel = new QLabel(tripPlannerTab);
        tripLabel->setObjectName("tripLabel");
        tripLabel->setFont(font);

        routeLayout->addWidget(tripLabel);

        tripCollegesList = new QListWidget(tripPlannerTab);
        tripCollegesList->setObjectName("tripCollegesList");

        routeLayout->addWidget(tripCollegesList);

        tripButtonsLayout = new QHBoxLayout();
        tripButtonsLayout->setObjectName("tripButtonsLayout");
        removeFromTripButton = new QPushButton(tripPlannerTab);
        removeFromTripButton->setObjectName("removeFromTripButton");

        tripButtonsLayout->addWidget(removeFromTripButton);

        moveUpButton = new QPushButton(tripPlannerTab);
        moveUpButton->setObjectName("moveUpButton");

        tripButtonsLayout->addWidget(moveUpButton);

        moveDownButton = new QPushButton(tripPlannerTab);
        moveDownButton->setObjectName("moveDownButton");

        tripButtonsLayout->addWidget(moveDownButton);


        routeLayout->addLayout(tripButtonsLayout);

        optimizeRouteButton = new QPushButton(tripPlannerTab);
        optimizeRouteButton->setObjectName("optimizeRouteButton");

        routeLayout->addWidget(optimizeRouteButton);


        tripPlannerLayout->addLayout(routeLayout);


        verticalLayout_3->addLayout(tripPlannerLayout);

        tripResultsLabel = new QLabel(tripPlannerTab);
        tripResultsLabel->setObjectName("tripResultsLabel");
        tripResultsLabel->setFont(font);

        verticalLayout_3->addWidget(tripResultsLabel);

        tripResultsText = new QTextEdit(tripPlannerTab);
        tripResultsText->setObjectName("tripResultsText");
        tripResultsText->setReadOnly(true);

        verticalLayout_3->addWidget(tripResultsText);

        tabWidget->addTab(tripPlannerTab, QString());
        souvenirsTab = new QWidget();
        souvenirsTab->setObjectName("souvenirsTab");
        verticalLayout_6 = new QVBoxLayout(souvenirsTab);
        verticalLayout_6->setObjectName("verticalLayout_6");
        souvenirsGroup = new QGroupBox(souvenirsTab);
        souvenirsGroup->setObjectName("souvenirsGroup");
        verticalLayout_7 = new QVBoxLayout(souvenirsGroup);
        verticalLayout_7->setObjectName("verticalLayout_7");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(souvenirsGroup);
        label_2->setObjectName("label_2");

        horizontalLayout_3->addWidget(label_2);

        collegeComboBox = new QComboBox(souvenirsGroup);
        collegeComboBox->setObjectName("collegeComboBox");

        horizontalLayout_3->addWidget(collegeComboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        refreshSouvenirsButton = new QPushButton(souvenirsGroup);
        refreshSouvenirsButton->setObjectName("refreshSouvenirsButton");

        horizontalLayout_3->addWidget(refreshSouvenirsButton);


        verticalLayout_7->addLayout(horizontalLayout_3);

        souvenirsTable = new QTableWidget(souvenirsGroup);
        if (souvenirsTable->columnCount() < 2)
            souvenirsTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        souvenirsTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        souvenirsTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        souvenirsTable->setObjectName("souvenirsTable");
        souvenirsTable->setAlternatingRowColors(true);
        souvenirsTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        souvenirsTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        souvenirsTable->setSortingEnabled(true);
        souvenirsTable->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_7->addWidget(souvenirsTable);


        verticalLayout_6->addWidget(souvenirsGroup);

        tabWidget->addTab(souvenirsTab, QString());
        distancesTab = new QWidget();
        distancesTab->setObjectName("distancesTab");
        verticalLayout_8 = new QVBoxLayout(distancesTab);
        verticalLayout_8->setObjectName("verticalLayout_8");
        distancesGroup = new QGroupBox(distancesTab);
        distancesGroup->setObjectName("distancesGroup");
        verticalLayout_9 = new QVBoxLayout(distancesGroup);
        verticalLayout_9->setObjectName("verticalLayout_9");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        refreshDistancesButton = new QPushButton(distancesGroup);
        refreshDistancesButton->setObjectName("refreshDistancesButton");

        horizontalLayout_4->addWidget(refreshDistancesButton);


        verticalLayout_9->addLayout(horizontalLayout_4);

        distancesTextEdit = new QTextEdit(distancesGroup);
        distancesTextEdit->setObjectName("distancesTextEdit");
        distancesTextEdit->setReadOnly(true);

        verticalLayout_9->addWidget(distancesTextEdit);


        verticalLayout_8->addWidget(distancesGroup);

        tabWidget->addTab(distancesTab, QString());

        verticalLayout->addWidget(tabWidget);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");
        QFont font1;
        font1.setBold(true);
        font1.setItalic(true);
        statusLabel->setFont(font1);
        statusLabel->setStyleSheet(QString::fromUtf8("color: #007ACC;"));
        statusLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout->addWidget(statusLabel);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 950, 27));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionExit);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "College Campus Tour", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "E&xit", nullptr));
#if QT_CONFIG(shortcut)
        actionExit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAbout->setText(QCoreApplication::translate("MainWindow", "&About", nullptr));
        allCollegesLabel->setText(QCoreApplication::translate("MainWindow", "All Colleges:", nullptr));
        addToTripButton->setText(QCoreApplication::translate("MainWindow", "Add to Trip \342\206\222", nullptr));
        resetTripButton->setText(QCoreApplication::translate("MainWindow", "Reset Trip", nullptr));
        tripLabel->setText(QCoreApplication::translate("MainWindow", "Your Trip (First college is starting point):", nullptr));
        removeFromTripButton->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        moveUpButton->setText(QCoreApplication::translate("MainWindow", "\342\206\221 Move Up", nullptr));
        moveDownButton->setText(QCoreApplication::translate("MainWindow", "\342\206\223 Move Down", nullptr));
        optimizeRouteButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #1a5c8e;", nullptr));
        optimizeRouteButton->setText(QCoreApplication::translate("MainWindow", "\342\234\223 Optimize Route", nullptr));
        tripResultsLabel->setText(QCoreApplication::translate("MainWindow", "Route Details:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tripPlannerTab), QCoreApplication::translate("MainWindow", "Trip Planner", nullptr));
        souvenirsGroup->setTitle(QCoreApplication::translate("MainWindow", "Campus Souvenirs", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Select College:", nullptr));
        refreshSouvenirsButton->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
        QTableWidgetItem *___qtablewidgetitem = souvenirsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = souvenirsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Price", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(souvenirsTab), QCoreApplication::translate("MainWindow", "Souvenirs", nullptr));
        distancesGroup->setTitle(QCoreApplication::translate("MainWindow", "Campus Distances", nullptr));
        refreshDistancesButton->setText(QCoreApplication::translate("MainWindow", "Refresh Distances", nullptr));
        distancesTextEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Consolas','monospace'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:10pt; color:#cccccc;\">Click Refresh to display campus distances...</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(distancesTab), QCoreApplication::translate("MainWindow", "Distances", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Ready", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "&File", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "&Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
