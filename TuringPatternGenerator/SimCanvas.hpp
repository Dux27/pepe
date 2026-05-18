#pragma once

#include "config.hpp"
#include <array>
#include <QWidget>
#include <QImage>
#include <QPainter>


struct Direction
{
    int dx;
    int dy;
};


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
        int activator_cell_rgb = qRgb(0, 255, 255); // Cyan
        int inhibitor_cell_rgb = qRgb(120, 0, 0);

        static constexpr int h = Config::window_height;
        static constexpr int w = static_cast<int>(Config::window_width * Config::sim_window_ratio);
        std::array<std::array<float, w>, h> curr_grid;
        std::array<std::array<float, w>, h> next_grid;
        std::array<std::array<float, w>, h> *curr_grid_ptr = &curr_grid;
        std::array<std::array<float, w>, h> *next_grid_ptr = &next_grid;

        void renderSimulation();
        void updateSimulation();

        void generateCircle(std::array<std::array<float, w>, h> *grid, int x, int y, int size, bool is_random=false);
};