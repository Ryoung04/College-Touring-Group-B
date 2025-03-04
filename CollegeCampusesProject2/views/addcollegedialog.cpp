#include "addcollegedialog.h"
#include "ui_addcollegedialog.h"
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QMessageBox>

AddCollegeDialog::AddCollegeDialog(const QVector<Campus>& existingCampuses, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddCollegeDialog)
{
    ui->setupUi(this);
    setWindowTitle("Add New College");
    setupForm(existingCampuses);
}

AddCollegeDialog::~AddCollegeDialog()
{
    delete ui;
}

void AddCollegeDialog::setupForm(const QVector<Campus>& existingCampuses)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // College name input
    QFormLayout* formLayout = new QFormLayout();
    nameEdit = new QLineEdit(this);
    formLayout->addRow("Enter college name:", nameEdit);

    // Add a separator
    QFrame* line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(line);

    // Distance inputs
    if (!existingCampuses.isEmpty()) {
        QLabel* distanceLabel = new QLabel("Enter distances (in miles):", this);
        mainLayout->addWidget(distanceLabel);

        QFormLayout* distanceForm = new QFormLayout();
        for (const Campus& campus : existingCampuses) {
            QLineEdit* distanceEdit = new QLineEdit(this);
            distanceEdit->setPlaceholderText("Enter distance");
            distanceForm->addRow("Distance from " + campus.getName() + ":", distanceEdit);
            distanceEdits.append({campus.getName(), distanceEdit});
        }
        mainLayout->addLayout(distanceForm);
    }

    // Dialog buttons
    QDialogButtonBox* buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
}

QString AddCollegeDialog::getCollegeName() const
{
    return nameEdit->text().trimmed();
}

QMap<QString, double> AddCollegeDialog::getDistances() const
{
    QMap<QString, double> distances;
    for (const auto& pair : distanceEdits) {
        bool ok;
        double distance = pair.second->text().toDouble(&ok);
        if (ok && distance >= 0) {
            distances[pair.first] = distance;
        }
    }
    return distances;
} 