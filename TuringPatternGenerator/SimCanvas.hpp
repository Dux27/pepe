#pragma once

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

        int background_1_rgb = qRgb(255, 0, 255);
        int background_2_rgb = qRgb(255, 255, 0);
        bool odd_frame = true;

        void renderSimulation();
};