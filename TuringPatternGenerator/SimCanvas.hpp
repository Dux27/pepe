#pragma once

#include "config.hpp"
#include <vector>
#include <QWidget>
#include <QImage>
#include <QPainter>


class SimCanvas : public QWidget
{
    Q_OBJECT

    public:
        explicit SimCanvas(QWidget *parent=nullptr);

    protected:
        void paintEvent(QPaintEvent *event) override;

    public:
        QImage image;

        int background_rgb = qRgb(40, 40, 40);
        int activator_cell_rgb = qRgb(0, 255, 255);
        int inhibitor_cell_rgb = qRgb(120, 0, 0);

        int h = Config::window_height;
        int w = Config::window_width * Config::sim_window_ratio;
        std::vector<std::vector<float>> curr_grid;

        void renderSimulation();
};