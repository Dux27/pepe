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
            renderSimulation();
            update();
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
        image = QImage(sim_width, sim_height, QImage::Format_RGB32);
        image.fill(background_rgb);
        return;
    }

    image = QImage(width() * 0.8, height(), QImage::Format_RGB32);
    image.fill(background_rgb);
}

void TuringPatternGenerator::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}