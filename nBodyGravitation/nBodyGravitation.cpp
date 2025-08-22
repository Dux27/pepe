#include "nBodyGravitation.h"
#include <QPainter>
#include <iostream>
#include <math.h>

NBodyGravitation::NBodyGravitation(QWidget *parent): QWidget(parent) 
{
    renderSimulation();
}

void NBodyGravitation::renderSimulation()
{
    lowResImage = QImage(lowResW, lowResH, QImage::Format_RGB32);
    lowResImage.fill(Qt::black);
    
    printCircle(50, 50, 23, qRgb(255, 255, 255));

    scaledImage = lowResImage.scaled(width(), height(), Qt::KeepAspectRatio, Qt::FastTransformation);
    update();
}

void NBodyGravitation::printCircle(const int x, const int y, const int r, const QRgb color)
{
    int x_min = std::max(0, x - r);
    int x_max = std::min(lowResImage.width() - 1, x + r);
    int y_min = std::max(0, y - r);
    int y_max = std::min(lowResImage.height() - 1, y + r);

    for(int i = x_min; i <= x_max; i++)
    {
        for (int j = y_min; j <= y_max; j++)
        {
            int dx = (i - x);
            int dy = (j - y);
            if(dx * dx + dy * dy <= r * r)
            {
                lowResImage.setPixel(i, j, color);
            }
        }
        
    }
}

void NBodyGravitation::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (!scaledImage.isNull()) {
        painter.drawImage(0, 0, scaledImage);
    }
}

void NBodyGravitation::resizeEvent(QResizeEvent *event) 
{
    if (!lowResImage.isNull()) {
        scaledImage = lowResImage.scaled(width(), height(), Qt::KeepAspectRatio, Qt::FastTransformation);
        update();
    }
    QWidget::resizeEvent(event);
}