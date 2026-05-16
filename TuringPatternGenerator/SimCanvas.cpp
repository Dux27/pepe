#include "SimCanvas.hpp"


SimCanvas::SimCanvas(QWidget *parent)
    : QWidget(parent) {}

void SimCanvas::renderSimulation()
{
    if (image.isNull())
    {
        image = QImage(width(), height(), QImage::Format_RGB32);
        image.fill(background_1_rgb);
        return;
    }
    odd_frame = !odd_frame;
    if (odd_frame)
    {
        image = QImage(width(), height(), QImage::Format_RGB32);
        image.fill(background_1_rgb);
    }
    else
    {
        image = QImage(width(), height(), QImage::Format_RGB32);
        image.fill(background_2_rgb);
    }

}

void SimCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}