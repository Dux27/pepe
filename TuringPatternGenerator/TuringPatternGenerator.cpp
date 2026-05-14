#include "TuringPatternGenerator.hpp"

TuringPatternGenerator::TuringPatternGenerator(QWidget *parent)
    : QWidget(parent)
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
    int w = width();
    int h = height();
    
    if (first_frame)
    {
        image = QImage();
        image.fill(red);
        first_frame = false;
    }
}

void TuringPatternGenerator::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}