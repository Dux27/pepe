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

        int width = 1280;
        int height = 720;
        
        bool running = true;
        int frame_dur_ms = 100;;

        bool first_frame = true;
        int red = qRgb(255, 0, 0);

        void renderSimulation();

};