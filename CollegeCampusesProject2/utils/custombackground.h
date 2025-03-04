#ifndef CUSTOMBACKGROUND_H
#define CUSTOMBACKGROUND_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QRandomGenerator>

class CustomBackground : public QWidget
{
    Q_OBJECT

public:
    explicit CustomBackground(QWidget *parent = nullptr) : QWidget(parent) {
        // Set up animation timer for subtle movement
        animationTimer = new QTimer(this);
        connect(animationTimer, &QTimer::timeout, this, &CustomBackground::updateAnimation);
        animationTimer->start(50);
        
        // Make widget transparent to let painting show through
        setAttribute(Qt::WA_StyledBackground, true);
        
        // Colors from the palette
        navyBlue = QColor("#001F3F");
        orange = QColor("#FF4500");
        lightBlue = QColor("#0087FF");
        green = QColor("#AACC00");
        gold = QColor("#FFB700");
    }

protected:
    void paintEvent(QPaintEvent * /* event */) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        
        // Fill background with navy blue
        painter.fillRect(rect(), navyBlue);
        
        // Draw animated circles and shapes with the palette colors
        drawFloatingShapes(painter);
        
        // Add subtle grid pattern
        drawGrid(painter);
        
        // Draw college campus silhouette at the bottom
        drawCampusSilhouette(painter);
    }

private slots:
    void updateAnimation() {
        animationOffset += 0.5;
        if (animationOffset > 360) animationOffset = 0;
        update(); // Trigger repaint
    }

private:
    void drawFloatingShapes(QPainter &painter) {
        // Draw large, semi-transparent circles with various colors
        int numShapes = 15;
        for (int i = 0; i < numShapes; i++) {
            qreal x = width() * (0.1 + 0.8 * sin(i * 2.0 + animationOffset * 0.01));
            qreal y = height() * (0.1 + 0.8 * cos(i * 3.0 + animationOffset * 0.01));
            qreal size = width() * 0.1 + (i % 3) * width() * 0.05;
            
            QColor color;
            switch (i % 5) {
                case 0: color = lightBlue; break;
                case 1: color = orange; break;
                case 2: color = green; break;
                case 3: color = gold; break;
                case 4: color = QColor("#3A7BD5"); break; // Additional blue shade
            }
            
            color.setAlpha(40); // Make shapes semi-transparent
            painter.setPen(Qt::NoPen);
            painter.setBrush(color);
            
            if (i % 3 == 0) {
                // Draw circle
                painter.drawEllipse(QPointF(x, y), size, size);
            } else if (i % 3 == 1) {
                // Draw rounded rectangle
                painter.drawRoundedRect(x-size/2, y-size/2, size, size, 15, 15);
            } else {
                // Draw polygon (hexagon)
                QPolygonF hexagon;
                for (int j = 0; j < 6; j++) {
                    qreal angle = j * 2 * M_PI / 6;
                    hexagon << QPointF(x + size*cos(angle), y + size*sin(angle));
                }
                painter.drawPolygon(hexagon);
            }
        }
    }
    
    void drawGrid(QPainter &painter) {
        // Draw a subtle grid pattern
        painter.setPen(QPen(QColor(255, 255, 255, 15), 1, Qt::SolidLine));
        
        int gridSize = 30;
        for (int x = 0; x < width(); x += gridSize) {
            painter.drawLine(x, 0, x, height());
        }
        
        for (int y = 0; y < height(); y += gridSize) {
            painter.drawLine(0, y, width(), y);
        }
    }
    
    void drawCampusSilhouette(QPainter &painter) {
        // Draw a stylized campus silhouette at the bottom
        int baseY = height() - height() * 0.15;
        
        // Create silhouette path
        QPainterPath path;
        path.moveTo(0, baseY);
        
        // Draw buildings
        int numBuildings = width() / 80;
        for (int i = 0; i < numBuildings; i++) {
            int x = i * 80;
            int buildingHeight = 20 + (QRandomGenerator::global()->bounded(80));
            int buildingWidth = 30 + (QRandomGenerator::global()->bounded(30));
            
            // Main building
            path.lineTo(x, baseY - buildingHeight);
            
            // Building details like windows or towers
            if (i % 3 == 0) { // Tower
                path.lineTo(x + 10, baseY - buildingHeight - 20);
                path.lineTo(x + 20, baseY - buildingHeight);
            }
            
            path.lineTo(x + buildingWidth, baseY - buildingHeight);
            path.lineTo(x + buildingWidth, baseY);
        }
        
        path.lineTo(width(), baseY);
        path.lineTo(width(), height());
        path.lineTo(0, height());
        path.closeSubpath();
        
        // Fill silhouette with gradient
        QLinearGradient gradient(0, baseY - 100, 0, height());
        gradient.setColorAt(0, QColor(0, 0, 30, 180));
        gradient.setColorAt(1, QColor(0, 0, 50, 220));
        painter.fillPath(path, gradient);
    }

    QTimer* animationTimer;
    qreal animationOffset = 0;
    
    // Color palette
    QColor navyBlue;
    QColor orange;
    QColor lightBlue;
    QColor green;
    QColor gold;
};

#endif // CUSTOMBACKGROUND_H 