#pragma once

#include <QWidget>
#include <QImage>

class GameOfLifeWidget : public QWidget {
    Q_OBJECT

    public:
        explicit GameOfLifeWidget(QWidget *parent=nullptr);

    protected:
        void paintEvent(QPaintEvent *event) override;
        void resizeEvent(QResizeEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;

    private:
        QTimer *timer;
        QImage image;
        QImage scaledImage;

        bool rendered = false;
        bool running;
        bool firstFrame = true;

        double resolution;
        double frame_dur_ms = 100;
        int alive = qRgb(255, 255, 0);
        int dead = qRgb(0, 0, 0);

        void renderSimulation();
        int countLiveNeighbors(int x, int y, int width, int height, const QImage& pixelGrid); 
};