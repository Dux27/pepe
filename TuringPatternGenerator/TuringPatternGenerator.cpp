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
        }
        else
            timer->stop();
    });
}