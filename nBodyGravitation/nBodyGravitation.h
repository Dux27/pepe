#pragma once

#include <QWidget>
#include <QImage>

class NBodyGravitation : public QWidget 
{
    Q_OBJECT   

    public:
        explicit NBodyGravitation(QWidget *parent=nullptr);

    protected:
        void paintEvent(QPaintEvent *event) override;
        void resizeEvent(QResizeEvent *event) override;

    private:
        QImage lowResImage;
        QImage scaledImage;
        int lowResW = 320;
        int lowResH = 180;

        void renderSimulation();
        void printCircle(int x, int y, int r, QRgb color);
};