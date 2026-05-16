#include "TuringPatternGenerator.hpp"
#include "config.hpp"
#include <iostream>


TuringPatternGenerator::TuringPatternGenerator(QWidget *parent)
    : QWidget(parent), running(false)
{
    setWindowTitle("Turing Pattern Generator");
    setFocusPolicy(Qt::StrongFocus);

    main_layout = new QHBoxLayout(this);
    sim_canvas = new SimCanvas(this);
    ui_panel = new UIPanel(this);
    main_layout->addWidget(sim_canvas, (10 * Config::sim_window_ratio));
    main_layout->addWidget(ui_panel, 10 - (10 * Config::sim_window_ratio));
    this->setLayout(main_layout);

    sim_canvas->renderSimulation();
    
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() -> void {
        if (running)
        {
            sim_canvas->renderSimulation();
            sim_canvas->updateSimulation();
            update();
        }
    });
    timer->start(frame_dur_ms);

    connect(ui_panel, &UIPanel::run_simulation_toggled, this, [this](bool is_running){ 
        this->running = is_running; 
    });
}
