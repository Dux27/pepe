#include "UIPanel.hpp"


UIPanel::UIPanel(QWidget *parent)
    : QWidget(parent) 
{
    panel_layout = new QVBoxLayout(this);
    on_off_checkbox = new QCheckBox("Run simulation", this);
    panel_layout->addWidget(on_off_checkbox);
    panel_layout->addStretch();

    connect(on_off_checkbox, &QCheckBox::toggled, this, &UIPanel::run_simulation_toggled);
}

