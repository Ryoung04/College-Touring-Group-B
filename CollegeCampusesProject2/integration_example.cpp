// Example code for integrating TripSouvenirsWidget into your main program

// In your MainWindow header file:
#include "tripsouvenirswidget.h"

// In your class declaration:
private:
    TripSouvenirsWidget* m_souvenirsWidget;

// In your MainWindow constructor:
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Create the souvenirs widget
    m_souvenirsWidget = new TripSouvenirsWidget(this);
    
    // Add it to your UI - for example in a dock widget or specific area
    // Example: add it to a QVBoxLayout called 'souvenirsContainerLayout'
    ui->souvenirsContainerLayout->addWidget(m_souvenirsWidget);
    
    // Connect to the souvenirs changed signal to update total trip cost
    connect(m_souvenirsWidget, &TripSouvenirsWidget::souvenirsChanged, this, &MainWindow::updateTotalCost);
    
    // ... rest of your initialization code
}

// When a user clicks "Add to Trip" button in your souvenirs display:
void MainWindow::onAddSouvenirToTripClicked()
{
    // Get the souvenir details from the button or selection
    QString collegeName = /* get college name */;
    QString souvenirName = /* get souvenir name */;
    double price = /* get souvenir price */;
    
    // Add it to the widget
    m_souvenirsWidget->addSouvenir(collegeName, souvenirName, price);
    
    // Show confirmation message if desired
    QMessageBox::information(this, "Added to Trip", 
                           QString("Added %1 from %2 to your trip.")
                           .arg(souvenirName)
                           .arg(collegeName));
}

// Add a method to update the total trip cost:
void MainWindow::updateTotalCost()
{
    // Calculate total distance cost
    double distanceCost = calculateDistanceCost(); // your existing method
    
    // Get the souvenir cost
    double souvenirCost = m_souvenirsWidget->getTotalCost();
    
    // Calculate total cost
    double totalCost = distanceCost + souvenirCost;
    
    // Update the UI
    ui->totalCostLabel->setText(QString("Total Trip Cost: $%1").arg(totalCost, 0, 'f', 2));
}

// When you need a summary of selected souvenirs (e.g., for a trip report):
void MainWindow::generateTripReport()
{
    QString report = "Trip Summary:\n\n";
    
    // Add distance information
    report += "Distance: " + QString::number(totalDistance) + " miles\n";
    report += "Distance Cost: $" + QString::number(distanceCost, 'f', 2) + "\n\n";
    
    // Add souvenirs information
    report += m_souvenirsWidget->getSelectedSouvenirsSummary();
    
    // Display or save the report
    QMessageBox::information(this, "Trip Report", report);
} 