#pragma once

#include <QWidget>
#include <QImage>
#include <QTimer>
#include <QPainter>
#include <QBoxLayout>
#include "SimCanvas.hpp"
#include "UIPanel.hpp"


class TuringPatternGenerator : public QWidget
{
    Q_OBJECT

    public:
        explicit TuringPatternGenerator(QWidget *parent=nullptr);

    // protected:

    private:
        QTimer *timer;
        QImage image;

        QHBoxLayout *main_layout;
        SimCanvas *sim_canvas;
        UIPanel *ui_panel;

        bool running;
        int frame_dur_ms = 100;

        int init_window_width = 1920;
        int init_window_height = 1080;
};