#include "animatedbackground.h"
#include <QPainter>
#include <QPainterPath>
#include <QResizeEvent>
#include <QDebug>
#include <QtMath>

// Define constants
const int ANIMATION_DURATION = 10000; // 10 seconds per cycle
const int WAVE_COUNT = 4;

AnimatedBackground::AnimatedBackground(QWidget *parent)
    : QWidget(parent)
    , m_currentColor(Qt::white)
    , m_animation(new QPropertyAnimation(this, "currentColor", this))
    , m_currentIndex(0)
    , m_timer(new QTimer(this))
{
    // Set default colors if none provided
    if (m_colors.isEmpty()) {
        m_colors = {
            QColor(41, 128, 185),   // Blue
            QColor(52, 152, 219),   // Light Blue
            QColor(46, 204, 113),   // Green
            QColor(26, 188, 156)    // Teal
        };
    }

    // Make this widget fill the parent
    if (parent) {
        resize(parent->size());
    }

    setupAnimation();
    
    // Connect timer to change colors
    connect(m_timer, &QTimer::timeout, this, &AnimatedBackground::nextColor);
    m_timer->setInterval(ANIMATION_DURATION);
}

AnimatedBackground::~AnimatedBackground()
{
    stopAnimation();
}

void AnimatedBackground::setColors(const QList<QColor>& colors)
{
    if (!colors.isEmpty()) {
        m_colors = colors;
        m_currentIndex = 0;
        m_currentColor = m_colors.first();
        setupAnimation();
        update();
    }
}

void AnimatedBackground::setupAnimation()
{
    if (m_colors.size() < 2) return;
    
    m_animation->setDuration(ANIMATION_DURATION);
    m_animation->setEasingCurve(QEasingCurve::InOutQuad);
    
    // Set the next color as the end value
    int nextIndex = (m_currentIndex + 1) % m_colors.size();
    m_animation->setStartValue(m_currentColor);
    m_animation->setEndValue(m_colors[nextIndex]);
}

void AnimatedBackground::startAnimation()
{
    if (m_colors.size() < 2) return;
    
    m_animation->start();
    m_timer->start();
}

void AnimatedBackground::stopAnimation()
{
    m_animation->stop();
    m_timer->stop();
}

QColor AnimatedBackground::currentColor() const
{
    return m_currentColor;
}

void AnimatedBackground::setCurrentColor(const QColor& color)
{
    m_currentColor = color;
    update();
}

void AnimatedBackground::nextColor()
{
    // Move to next color in the list
    m_currentIndex = (m_currentIndex + 1) % m_colors.size();
    
    // Update animation to transition to the next color
    setupAnimation();
    m_animation->start();
}

void AnimatedBackground::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Paint background with current color
    painter.fillRect(rect(), m_currentColor);
    
    // Add a gradient effect
    QLinearGradient gradient(rect().topLeft(), rect().bottomRight());
    gradient.setColorAt(0, m_currentColor);
    QColor endColor = m_currentColor;
    endColor.setAlpha(150); // More transparent
    gradient.setColorAt(1, endColor);
    
    painter.fillRect(rect(), gradient);
}

void AnimatedBackground::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    update();
} 