#pragma once

#include <QWidget>
#include <QImage>
#include <QTimer>
#include <QPainter>


class TuringPatternGenerator : public QWidget
{
    Q_OBJECT

    public:
        explicit TuringPatternGenerator(QWidget *parent=nullptr);

    protected:
        void paintEvent(QPaintEvent *event) override;

    private:
        QTimer *timer;
        QImage image;

        bool running;
        int frame_dur_ms = 100;

        int window_width = 1920;
        int window_height = 1080;
        int sim_width_ratio = 0.8;

        int sim_width = 1920 * 0.8;
        int sim_height = window_height;

        int background_rgb = qRgb(255, 0, 255);

        void renderSimulation();
};