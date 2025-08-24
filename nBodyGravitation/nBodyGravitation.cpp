#include "nBodyGravitation.h"
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <iostream>
#include <math.h>
#include <functional>
#include <cstdlib>
#include <algorithm> // added for std::clamp
#include <random>   

NBodyGravitation::NBodyGravitation(QWidget *parent): QWidget(parent) , running(true)
{
    earthGravity = 9.81 / (1000 / TICK_MS); // Considering that one pixel is 1 m

    QVector2D mercuryRelativeToCenter{100.0f, 400.0f};
    mercury.pos = posRelativeToCenter(mercuryRelativeToCenter);
    mercury.vel = QVector2D(-22.00f, 0.0f);
    mercury.acc = QVector2D(0.0f, 0.0f);

    QVector2D venusRelativeToCenter{0.0f, 0.0f};
    venus.pos = posRelativeToCenter(venusRelativeToCenter);
    venus.vel = QVector2D(0.0f, 0.0f);
    venus.acc = QVector2D(0.0f, 0.0f);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() 
    {
        if(running)
        {
            for(Body& b : bodies)
            {
                QVector2D force = gravitationalForce(b) * 1e13;
                QVector2D acc = force / b.mass;

                acc.setX(std::clamp(acc.x(), -accCap, accCap));
                acc.setY(std::clamp(acc.y(), -accCap, accCap));
                b.acc = acc;

                b.pos += b.vel;
                b.vel += b.acc;

                std::cout << b.name << " velocity: (" << b.vel.x() << ", " << b.vel.y() << ")" << std::endl;
                std::cout << b.name << " acceleration: (" << b.acc.x() << ", " << b.acc.y() << ")" << std::endl;
            }
            std::cout << std::endl;

            renderSimulation();
        }
        else
        {
            timer->stop();
        }
    });

    renderSimulation();
    timer->start(TICK_MS);
}

void NBodyGravitation::renderSimulation()
{
    // Create once only at initialization
    if (lowResImage.isNull()) {
        lowResImage = QImage(lowResW, lowResH, QImage::Format_RGB32);
        lowResImage.fill(Qt::black);
    }
   
    // Fill the image with black, but keep the orbit visualization
    for(int x = 0; x < lowResImage.width(); x++)
    {
        for (int y = 0; y < lowResImage.height(); y++)
        {
            if(lowResImage.pixel(x, y) != orbitColor)
                lowResImage.setPixel(x, y, qRgb(0, 0, 0));
        }
        
    }

    for(const Body& b : bodies)
    {   
        float radius = std::pow(b.mass, 1.0/3.0) * radiusMassRatio;
        radius /= radiusScaling; // Scaling for simulation purposes
        // std::cout << b.name << " radius: " << radius << std::endl;
        renderCircle(b.pos, radius, qRgb(255, 255, 255));

        // Render orbit visualiztion
        renderCircle(b.pos, 1, orbitColor); 
    }

    renderCircle(centerOfMass(), 4, qRgb(0, 0, 255));
    //std::cout << "Center of mass: (" << centerOfMass().x() << ", " << centerOfMass().y() << ")" << std::endl;

    scaledImage = lowResImage.scaled(width(), height(), Qt::KeepAspectRatio, Qt::FastTransformation);
    update();
}

void NBodyGravitation::renderCircle(QVector2D pos, const int r, const QRgb color)
{
    int x = pos.x();
    int y = pos.y();

    int x_min = std::max(0, x - r);
    int x_max = std::min(lowResImage.width() - 1, x + r);
    int y_min = std::max(0, y - r);
    int y_max = std::min(lowResImage.height() - 1, y + r);

    for(int i = x_min; i <= x_max; i++)     
    {
        for (int j = y_min; j <= y_max; j++)
        {
            int dx = (i - x);
            int dy = (j - y);
            if(dx * dx + dy * dy <= r * r - 0.01)   // 0.01 is to get rid of the one pixel at the edge
            {
                lowResImage.setPixel(i, j, color);
            }
        }
        
    }
}

QVector2D NBodyGravitation::posRelativeToCenter(QVector2D vector)
{   
    QVector2D center{static_cast<float>(lowResW)/2, static_cast<float>(lowResH)/2};
    QVector2D pos = center + vector;

    return pos;
}

QVector2D NBodyGravitation::centerOfMass()
{
    QVector2D massCenter;
    QVector2D posXMassSum{0.0f, 0.0f};
    int massSum = 0;

    for(const Body& b : bodies)
    {
        posXMassSum += b.pos * b.mass;
        massSum += b.mass;
    }

    return massCenter = posXMassSum / massSum;
}

QVector2D NBodyGravitation::gravitationalForce(Body body)
{
    // Net gravitational force on `body`: F = G * (m1 * m2 / |r|^3) * r

    const double G = 6.67430e-11;   // m^3 / (kg * s^2)
    QVector2D totalForce{0.0f, 0.0f};

    for (const Body& b : bodies)
    {
        if(&body != &b)
        {
            QVector2D r = b.pos - body.pos;
            float distance = r.length();

            if (distance > 0.0f) {
                // Force vector: G * m1 * m2 / r^3 * r
                QVector2D force = (G * body.mass * b.mass / pow(distance, 3)) * r;
                totalForce += force;
            }
        }
    }

    return totalForce;
}

void NBodyGravitation::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (!scaledImage.isNull()) {
        painter.drawImage(0, 0, scaledImage);
    }
}

void NBodyGravitation::resizeEvent(QResizeEvent *event) 
{
    if (!lowResImage.isNull()) {
        scaledImage = lowResImage.scaled(width(), height(), Qt::KeepAspectRatio, Qt::FastTransformation);
        update();
    }
    QWidget::resizeEvent(event);
}

void NBodyGravitation::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        running = !running;
        if (running && !timer->isActive()) {
            timer->start(TICK_MS);
        }
        std::string msg = running ? "START" : "STOP"; 
        std::cout<<msg<<std::endl;
    }
}

void NBodyGravitation::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {   
        QVector2D position{static_cast<float>(event->pos().x()), static_cast<float>(event->pos().y())};
        std::string name = "Generated Body " + std::to_string(bodyIndex);

        float x = static_cast<float>(event->pos().x()) * lowResW / std::max(1, width());
        float y = static_cast<float>(event->pos().y()) * lowResH / std::max(1, height());

        // allocate a new Body dynamically on the heap using unique_ptr 
        // (so it has a lifetime beyond this function call)
        std::unique_ptr<Body> genBody = std::make_unique<Body>();    // alternative to "std::unique_ptr<Body>" is "auto"

        genBody->name = name;
        genBody->mass = genBodyMass;
        genBody->pos  = QVector2D(x, y);
        genBody->vel  = genBodyVel;
        genBody->acc  = QVector2D(0.0f, 0.0f);

        // push a *copy* of the Body into the simple vector
        bodies.push_back(*genBody);                      
        // transfer ownership of the dynamically allocated Body into the unique_ptr vector 
        generatedBodies.push_back(std::move(genBody));  

        bodyIndex ++;
    }
}