#include "animatedbackground.h"
#include <QPainter>
#include <QPainterPath>
#include <QResizeEvent>
#include <QDebug>
#include <QtMath>

AnimatedBackground::AnimatedBackground(QWidget *parent)
    : QWidget(parent)
    , m_phase(0.0)
    , m_animationGroup(new QParallelAnimationGroup(this))
    , m_phaseAnimation(new QPropertyAnimation(this, "phase", this))
    , m_waveCount(WAVE_COUNT)
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

    // Initialize animations
    initializeAnimations();
    
    // Create initial wave paths
    createWavePaths();
    
    // This widget should be in the background
    lower();
    
    // Start animation immediately
    startAnimation();
}

AnimatedBackground::~AnimatedBackground()
{
    stopAnimation();
}

void AnimatedBackground::setColors(const QVector<QColor>& colors)
{
    if (!colors.isEmpty()) {
        m_colors = colors;
        update();
    }
}

void AnimatedBackground::initializeAnimations()
{
    // Phase animation (0.0 to 1.0)
    m_phaseAnimation->setStartValue(0.0);
    m_phaseAnimation->setEndValue(1.0);
    m_phaseAnimation->setDuration(ANIMATION_DURATION);
    m_phaseAnimation->setLoopCount(-1); // Infinite loop
    
    // Add to animation group
    m_animationGroup->addAnimation(m_phaseAnimation);
}

void AnimatedBackground::startAnimation()
{
    m_animationGroup->start();
}

void AnimatedBackground::stopAnimation()
{
    m_animationGroup->stop();
}

void AnimatedBackground::setPhase(qreal phase)
{
    m_phase = phase;
    update(); // Trigger repaint when phase changes
}

void AnimatedBackground::createWavePaths()
{
    m_wavePaths.clear();
    
    QSize size = this->size();
    qreal width = size.width();
    qreal height = size.height();
    
    // Create waves with different amplitudes and frequencies
    for (int i = 0; i < m_waveCount; i++) {
        QPainterPath path;
        
        // Different parameters for each wave
        qreal amplitude = height * 0.05 * (i + 1);
        qreal frequency = 1.0 + i * 0.2;
        qreal yBase = height * (0.2 + i * 0.15);
        
        path.moveTo(0, yBase);
        
        for (qreal x = 0; x <= width; x += 2) {
            qreal y = yBase + amplitude * qSin(frequency * (x / width) * 2 * M_PI);
            path.lineTo(x, y);
        }
        
        // Close the path by drawing to the bottom corners
        path.lineTo(width, height);
        path.lineTo(0, height);
        path.closeSubpath();
        
        m_wavePaths.append(path);
    }
}

void AnimatedBackground::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Fill background with first color
    if (!m_colors.isEmpty()) {
        painter.fillRect(rect(), m_colors.first());
    }
    
    // Draw each wave
    for (int i = 0; i < m_wavePaths.size(); i++) {
        QPainterPath path = m_wavePaths.at(i);
        
        // Transform the path based on animation phase
        QTransform transform;
        qreal phaseOffset = m_phase * (i % 2 == 0 ? 1.0 : -0.7); // Alternate directions
        transform.translate(width() * phaseOffset, 0);
        QPainterPath transformedPath = transform.map(path);
        
        // Use appropriate color from the palette
        int colorIndex = qMin(i + 1, m_colors.size() - 1);
        QColor waveColor = m_colors.at(colorIndex);
        
        // Increase opacity for dark mode visibility
        waveColor.setAlpha(220); // More visible in dark mode
        
        painter.fillPath(transformedPath, waveColor);
    }
}

void AnimatedBackground::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    createWavePaths(); // Recreate paths when resized
} 