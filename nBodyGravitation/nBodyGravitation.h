#pragma once

#include <QWidget>
#include <QImage>
#include <QVector2D>

class NBodyGravitation : public QWidget 
{
    Q_OBJECT   

    public:
        explicit NBodyGravitation(QWidget *parent=nullptr);

    protected:
        void paintEvent(QPaintEvent *event) override;
        void resizeEvent(QResizeEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;

    private:
        QTimer *timer;
        const int TICK_MS = 50;
        bool running;

        QImage lowResImage;
        QImage scaledImage;
        const int lowResW = 1920;
        const int lowResH = 1080;

        float accCap = 2.0f;
        int orbitColor = qRgb(0, 255, 0); 
        int bodyIndex = 1;

        void renderSimulation();
        void renderCircle(QVector2D pos, int r, QRgb color);
        QVector2D posRelativeToCenter(QVector2D vector);

        struct Body 
        {
            std::string name;
            float mass;
            QVector2D pos;
            QVector2D vel;
            QVector2D acc;
        };

        QVector2D centerOfMass();
        QVector2D gravitationalForce(Body body);

        // *1e23
        Body mercury = {"Mercury", 3.285f}; // 328.5f
        Body venus = {"Venus", 3500.67f};    // 4867.0f
        std::vector<std::reference_wrapper<Body>> bodies = {venus};
        std::vector<std::unique_ptr<Body>> generatedBodies;

        float earthGravity;
        const int radiusMassRatio = 355; 
};