#include "TuringPatternGenerator.hpp"
#include <iostream>

TuringPatternGenerator::TuringPatternGenerator(QWidget *parent)
    : QWidget(parent), running(true)
{
    setWindowTitle("Turing Pattern Generator");
    setFocusPolicy(Qt::StrongFocus);

    main_layout = new QHBoxLayout(this);
    sim_canvas = new SimCanvas(this);
    ui_panel = new UIPanel(this);
    main_layout->addWidget(sim_canvas, 4);
    main_layout->addWidget(ui_panel, 1);
    this->setLayout(main_layout);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() -> void {
        if (running)
        {
            sim_canvas->renderSimulation();
            update();
        }
        else
            timer->stop();
    });
    timer->start(frame_dur_ms);
}
