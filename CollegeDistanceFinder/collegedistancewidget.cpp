#include "collegedistancewidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>

CollegeDistanceWidget::CollegeDistanceWidget(QWidget *parent)
    : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);

    // Header
    auto headerLayout = new QHBoxLayout();
    auto titleLabel = new QLabel("College Distance Finder", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);

    logoutButton = new QPushButton("Logout", this);
    logoutButton->setStyleSheet("background-color: #dc2626; color: white; padding: 8px 16px;");

    headerLayout->addWidget(titleLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(logoutButton);

    // Main content
    auto contentLayout = new QHBoxLayout();

    // Available colleges
    auto collegesGroup = new QGroupBox("Available Colleges", this);
    auto collegesLayout = new QVBoxLayout(collegesGroup);
    collegeList = new QListWidget(this);
    collegesLayout->addWidget(collegeList);

    // Selected colleges
    auto selectedGroup = new QGroupBox("Your Trip", this);
    auto selectedLayout = new QVBoxLayout(selectedGroup);
    selectedColleges = new QListWidget(this);
    totalDistanceLabel = new QLabel(this);
    selectedLayout->addWidget(selectedColleges);
    selectedLayout->addWidget(totalDistanceLabel);

    contentLayout->addWidget(collegesGroup);
    contentLayout->addWidget(selectedGroup);

    layout->addLayout(headerLayout);
    layout->addLayout(contentLayout);

    // Load data
    CSVParser parser;
    auto data = parser.parseCollegeData();
    distanceMap = data.first;

    // Populate college list
    for (const QString& college : data.second) {
        collegeList->addItem(college);
    }

    // Connect signals
    connect(collegeList, &QListWidget::itemClicked, this, &CollegeDistanceWidget::onCollegeClicked);
    connect(logoutButton, &QPushButton::clicked, this, &CollegeDistanceWidget::onLogoutClicked);
}

void CollegeDistanceWidget::onCollegeClicked(QListWidgetItem* item)
{
    QString college = item->text();
    bool alreadySelected = false;

    // Check if college is already in selected list
    for (int i = 0; i < selectedColleges->count(); ++i) {
        if (selectedColleges->item(i)->text() == college) {
            delete selectedColleges->takeItem(i);
            alreadySelected = true;
            break;
        }
    }

    if (!alreadySelected) {
        auto newItem = new QListWidgetItem(QString("%1. %2")
                                               .arg(selectedColleges->count() + 1)
                                               .arg(college));
        selectedColleges->addItem(newItem);
    }

    updateTotalDistance();
}

void CollegeDistanceWidget::onLogoutClicked()
{
    emit logout();
}

void CollegeDistanceWidget::updateTotalDistance()
{
    double total = calculateTotalDistance();
    if (total > 0) {
        totalDistanceLabel->setText(QString("Total Distance: %1 miles")
                                        .arg(QString::number(total, 'f', 1)));
    } else {
        totalDistanceLabel->clear();
    }
}

double CollegeDistanceWidget::calculateTotalDistance()
{
    if (selectedColleges->count() < 2) return 0;

    double total = 0;
    for (int i = 0; i < selectedColleges->count() - 1; ++i) {
        QString start = selectedColleges->item(i)->text().section('.', 1).trimmed();
        QString end = selectedColleges->item(i + 1)->text().section('.', 1).trimmed();
        total += distanceMap[start][end];
    }

    return total;
}
