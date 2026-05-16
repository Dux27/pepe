#include "SimCanvas.hpp"

SimCanvas::SimCanvas(QWidget *parent)
    : QWidget(parent) {}

void SimCanvas::renderSimulation()
{
    if (image.isNull())
    {
        image = QImage(width(), height(), QImage::Format_RGB32);
        image.fill(background_rgb);
        return;
    }

    image = QImage(width(), height(), QImage::Format_RGB32);
    image.fill(background_rgb);
}

void SimCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}