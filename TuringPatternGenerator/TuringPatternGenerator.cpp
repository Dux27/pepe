#include "TuringPatternGenerator.hpp"
#include <iostream>


TuringPatternGenerator::TuringPatternGenerator(QWidget *parent)
    : QWidget(parent), running(true)
{
    setWindowTitle("Turing Pattern Generator");
    setFocusPolicy(Qt::StrongFocus);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() -> void {
        if (running)
        {
            update();
            renderSimulation();
        }
        else
            timer->stop();
    });
    timer->start(frame_dur_ms);
}

void TuringPatternGenerator::renderSimulation()
{
    if (image.isNull())
    {
        image = QImage(width(), height(), QImage::Format_RGB32);
        image.fill(background_rgb);
        return;
    }
}

void TuringPatternGenerator::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}