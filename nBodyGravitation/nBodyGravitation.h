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
        const int TICK_MS = 5;
        bool running;

        QImage lowResImage;
        QImage scaledImage;
        const int lowResW = 1920*3;
        const int lowResH = 1080*3;

        int orbitColor = qRgb(255, 0, 0); 
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

        Body mercury = {"Mercury", 828.5f}; // 328.5f
        Body venus = {"Venus", 160028.5f};    // 4867.0f
        std::vector<std::reference_wrapper<Body>> bodies = {mercury, venus};
        std::vector<std::unique_ptr<Body>> generatedBodies;

        float earthGravity;
        const int radiusMassRatio = 355; 
};