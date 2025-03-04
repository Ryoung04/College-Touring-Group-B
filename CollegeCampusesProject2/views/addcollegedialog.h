#ifndef ADDCOLLEGEDIALOG_H
#define ADDCOLLEGEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QVector>
#include <QPair>
#include "../models/campus.h"

namespace Ui {
class AddCollegeDialog;
}

class AddCollegeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCollegeDialog(const QVector<Campus>& existingCampuses, QWidget *parent = nullptr);
    ~AddCollegeDialog();

    QString getCollegeName() const;
    QMap<QString, double> getDistances() const;

private:
    Ui::AddCollegeDialog *ui;
    QLineEdit* nameEdit;
    QVector<QPair<QString, QLineEdit*>> distanceEdits;
    void setupForm(const QVector<Campus>& existingCampuses);
};

#endif // ADDCOLLEGEDIALOG_H 