#include "tripsouvenirswidget.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QIcon>
#include <QPixmap>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>

TripSouvenirsWidget::TripSouvenirsWidget(QWidget* parent)
    : QWidget(parent)
{
    setupUI();
    
    // Connect signals
    connect(m_viewDetailsButton, &QPushButton::clicked, this, &TripSouvenirsWidget::onViewDetailsClicked);
    connect(m_clearAllButton, &QPushButton::clicked, this, &TripSouvenirsWidget::onClearAllClicked);
    
    refreshSouvenirs();
}

void TripSouvenirsWidget::setupUI()
{
    // Create layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    // Add a title label
    QLabel* titleLabel = new QLabel("Souvenirs for Trip");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(12);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);
    
    // Create table for souvenirs
    m_souvenirsTable = new QTableWidget(this);
    m_souvenirsTable->setColumnCount(6); // Add one more column for the remove button
    m_souvenirsTable->setHorizontalHeaderLabels({"College", "Souvenir", "Price", "Quantity", "Total", "Remove"});
    m_souvenirsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_souvenirsTable->horizontalHeader()->setSectionResizeMode(5, QHeaderView::ResizeToContents); // Make remove column smaller
    m_souvenirsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_souvenirsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_souvenirsTable->setMinimumHeight(150);  // Make sure it has enough height
    mainLayout->addWidget(m_souvenirsTable);
    
    // Add total cost label
    m_totalCostLabel = new QLabel("Total Cost: $0.00");
    QFont costFont = m_totalCostLabel->font();
    costFont.setBold(true);
    m_totalCostLabel->setFont(costFont);
    m_totalCostLabel->setAlignment(Qt::AlignRight);
    mainLayout->addWidget(m_totalCostLabel);
    
    // Add buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    m_viewDetailsButton = new QPushButton("View Details");
    m_clearAllButton = new QPushButton("Clear All");
    buttonLayout->addWidget(m_viewDetailsButton);
    buttonLayout->addWidget(m_clearAllButton);
    mainLayout->addLayout(buttonLayout);
    
    setLayout(mainLayout);
    setMinimumWidth(650);  // Make the widget wide enough
}

void TripSouvenirsWidget::refreshSouvenirs()
{
    populateSouvenirsTable();
    updateTotalCostLabel();
    emit souvenirsChanged();
}

void TripSouvenirsWidget::populateSouvenirsTable()
{
    // Clear the table
    m_souvenirsTable->clearContents();
    
    // Set the number of rows
    m_souvenirsTable->setRowCount(m_selectedSouvenirs.size());
    
    // Fill the table
    for (int i = 0; i < m_selectedSouvenirs.size(); ++i) {
        const TripSouvenir& souvenir = m_selectedSouvenirs[i];
        
        // Add the college name
        m_souvenirsTable->setItem(i, 0, new QTableWidgetItem(souvenir.collegeName));
        
        // Add the souvenir name
        m_souvenirsTable->setItem(i, 1, new QTableWidgetItem(souvenir.name));
        
        // Add the price
        m_souvenirsTable->setItem(i, 2, new QTableWidgetItem(QString("$%1").arg(souvenir.price, 0, 'f', 2)));
        
        // Add the quantity
        m_souvenirsTable->setItem(i, 3, new QTableWidgetItem(QString::number(souvenir.quantity)));
        
        // Add the total price
        m_souvenirsTable->setItem(i, 4, new QTableWidgetItem(QString("$%1").arg(souvenir.totalPrice(), 0, 'f', 2)));
        
        // Add the remove button
        QPushButton* removeButton = new QPushButton("X");
        removeButton->setMaximumWidth(30);
        
        // Store the souvenir info in the button's properties
        removeButton->setProperty("row", i);
        removeButton->setProperty("collegeName", souvenir.collegeName);
        removeButton->setProperty("souvenirName", souvenir.name);
        
        // Connect the button to the removal slot
        connect(removeButton, &QPushButton::clicked, this, &TripSouvenirsWidget::onRemoveSouvenirClicked);
        
        // Add the button to the table
        m_souvenirsTable->setCellWidget(i, 5, removeButton);
    }
}

double TripSouvenirsWidget::getTotalCost() const
{
    double total = 0.0;
    for (const TripSouvenir& souvenir : m_selectedSouvenirs) {
        total += souvenir.totalPrice();
    }
    return total;
}

void TripSouvenirsWidget::updateTotalCostLabel()
{
    double totalCost = getTotalCost();
    m_totalCostLabel->setText(QString("Total Cost: $%1").arg(totalCost, 0, 'f', 2));
}

void TripSouvenirsWidget::onViewDetailsClicked()
{
    if (m_selectedSouvenirs.isEmpty()) {
        QMessageBox::information(this, "Selected Souvenirs", "No souvenirs have been selected for your trip.");
        return;
    }
    
    // Create a dialog to show selected souvenirs
    QDialog dialog(this);
    dialog.setWindowTitle("Selected Souvenirs");
    dialog.setMinimumWidth(500);
    
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    
    // Create a table to display selected souvenirs
    QTableWidget* table = new QTableWidget(&dialog);
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({"College", "Souvenir", "Price", "Quantity", "Total"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    table->setRowCount(m_selectedSouvenirs.size());
    for (int i = 0; i < m_selectedSouvenirs.size(); ++i) {
        const TripSouvenir& souvenir = m_selectedSouvenirs[i];
        
        table->setItem(i, 0, new QTableWidgetItem(souvenir.collegeName));
        table->setItem(i, 1, new QTableWidgetItem(souvenir.name));
        table->setItem(i, 2, new QTableWidgetItem(QString("$%1").arg(souvenir.price, 0, 'f', 2)));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(souvenir.quantity)));
        table->setItem(i, 4, new QTableWidgetItem(QString("$%1").arg(souvenir.totalPrice(), 0, 'f', 2)));
    }
    
    layout->addWidget(table);
    
    // Add a label for the total cost
    QLabel* totalLabel = new QLabel(QString("Total Cost: $%1").arg(getTotalCost(), 0, 'f', 2));
    totalLabel->setAlignment(Qt::AlignRight);
    totalLabel->setFont(QFont("", 12, QFont::Bold));
    layout->addWidget(totalLabel);
    
    // Add buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* clearButton = new QPushButton("Clear All");
    QPushButton* closeButton = new QPushButton("Close");
    
    buttonLayout->addWidget(clearButton);
    buttonLayout->addWidget(closeButton);
    
    layout->addLayout(buttonLayout);
    
    // Connect buttons
    connect(clearButton, &QPushButton::clicked, this, [this, &dialog]() {
        if (QMessageBox::question(this, "Clear Souvenirs", 
                                "Are you sure you want to clear all selected souvenirs?",
                                QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            clearSouvenirs();
            dialog.accept();
        }
    });
    
    connect(closeButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    
    dialog.exec();
}

void TripSouvenirsWidget::onClearAllClicked()
{
    if (m_selectedSouvenirs.isEmpty()) {
        return;
    }
    
    if (QMessageBox::question(this, "Clear Souvenirs", 
                             "Are you sure you want to clear all selected souvenirs?",
                             QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        clearSouvenirs();
    }
}

void TripSouvenirsWidget::onRemoveSouvenirClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    
    // Get the souvenir info from the button's properties
    QString collegeName = button->property("collegeName").toString();
    QString souvenirName = button->property("souvenirName").toString();
    
    // Find and remove the souvenir (or decrease quantity)
    for (int i = 0; i < m_selectedSouvenirs.size(); ++i) {
        if (m_selectedSouvenirs[i].collegeName == collegeName && m_selectedSouvenirs[i].name == souvenirName) {
            if (m_selectedSouvenirs[i].quantity > 1) {
                // Decrease quantity by 1
                m_selectedSouvenirs[i].quantity--;
            } else {
                // Remove completely
                m_selectedSouvenirs.removeAt(i);
            }
            break;
        }
    }
    
    // Refresh the table
    refreshSouvenirs();
}

void TripSouvenirsWidget::addSouvenir(const QString& collegeName, const QString& souvenirName, double price)
{
    // Check if this souvenir is already in the list
    bool found = false;
    for (int i = 0; i < m_selectedSouvenirs.size(); ++i) {
        if (m_selectedSouvenirs[i].collegeName == collegeName && 
            m_selectedSouvenirs[i].name == souvenirName) {
            // Increment quantity
            m_selectedSouvenirs[i].quantity++;
            found = true;
            break;
        }
    }
    
    if (!found) {
        // Add new souvenir to the list
        m_selectedSouvenirs.append(TripSouvenir(collegeName, souvenirName, price));
    }
    
    // Refresh the UI
    refreshSouvenirs();
}

void TripSouvenirsWidget::clearSouvenirs()
{
    m_selectedSouvenirs.clear();
    refreshSouvenirs();
}

QString TripSouvenirsWidget::getSelectedSouvenirsSummary() const
{
    if (m_selectedSouvenirs.isEmpty()) {
        return "No souvenirs selected";
    }
    
    QString summary = "Selected Souvenirs:\n";
    
    // Group souvenirs by college
    QMap<QString, QVector<TripSouvenir>> souvenirsByCollege;
    for (const TripSouvenir& souvenir : m_selectedSouvenirs) {
        souvenirsByCollege[souvenir.collegeName].append(souvenir);
    }
    
    // Generate summary
    for (auto it = souvenirsByCollege.begin(); it != souvenirsByCollege.end(); ++it) {
        QString collegeName = it.key();
        const QVector<TripSouvenir>& collegeSouvenirs = it.value();
        
        summary += "\n" + collegeName + ":\n";
        
        double collegeTotal = 0.0;
        for (const TripSouvenir& souvenir : collegeSouvenirs) {
            summary += QString("  - %1 x %2: $%3\n")
                      .arg(souvenir.quantity)
                      .arg(souvenir.name)
                      .arg(souvenir.totalPrice(), 0, 'f', 2);
            collegeTotal += souvenir.totalPrice();
        }
        
        summary += QString("  Subtotal: $%1\n").arg(collegeTotal, 0, 'f', 2);
    }
    
    summary += QString("\nTotal Cost: $%1").arg(getTotalCost(), 0, 'f', 2);
    
    return summary;
} 