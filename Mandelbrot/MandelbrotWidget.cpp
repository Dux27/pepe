#include <MandelbrotWidget.h>
#include <QPainter>
#include <QWheelEvent>
#include <QMouseEvent>
#include <complex>
#include <iostream>

// Constructor. Initializes the widget and renders the Mandelbrot set. Can pass a parent widget.
// renderMandelbrot() is associated with the constructor
MandelbrotWidget::MandelbrotWidget(QWidget *parent): QWidget(parent) {
    renderMandelbrot();
}

float MandelbrotWidget::mapping(float x, float in_max, float out_max, float in_min, float out_min) {
    float ratio = (x - in_min) / (in_max - in_min);
    float mapped = ratio * (out_max - out_min) + out_min;
    return mapped; 
}

void MandelbrotWidget::renderMandelbrot() {
    int w = width();
    int h = height();
    image = QImage(w, h, QImage::Format_RGB32);    

    const int maxIter = 100;

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            std::complex<double> c(
                (x - w / 2.0) / scale + centerX,
                (y - h / 2.0) / scale + centerY
            );

            std::complex<double> z = 0;
            int iter = 0;
            while (abs(z) <= 2.0 && iter < maxIter) {
                z = z * z + c;
                ++iter;
            }

            int color = iter * 255 / maxIter;
            image.setPixel(x, y, qRgb(color, color, color));
        }
    }
    update();  // Trigger repaint
}

void MandelbrotWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawImage(0, 0, image); // (x, y, image) draws the image at the top-left corner of the widget
}

void MandelbrotWidget::wheelEvent(QWheelEvent *event) {
    double zoomFactor = (event->angleDelta().y() > 0) ? 1.1 : 0.9;  // "event" is a pointer to the object so "->" is used
    // There is used ternary operator to determine the zoom direction. 'condition ? value_if_true : value_if_false'
    scale *= zoomFactor;
    renderMandelbrot();
}

void MandelbrotWidget::mousePressEvent(QMouseEvent *event){
    int xMouse = event->position().x();
    int yMouse = event->position().y();
    
    float stepSize = 0.5;   
    stepSize *= 2;
    float buffor;

    float mappedX = mapping(xMouse, width(), stepSize);
    if(xMouse > width()/2){
        buffor = mappedX - stepSize/2;
        centerX += buffor;
    }
    else{
        buffor = -(stepSize/2 - mappedX);
        centerX += buffor;
    }

    float mappedY = mapping(yMouse, height(), stepSize);
    if(yMouse > height()/2){
        buffor = mappedY - stepSize/2;
        centerY += buffor;
    }
    else{
        buffor = -(stepSize/2 - mappedY);
        centerY += buffor;
    }

    // DEBUG
    // std::cout<<std::endl<<xMouse<<"   "<<buffor<<std::endl;
    // std::cout<<yMouse<<"   "<<centerX<<std::endl;
    renderMandelbrot();
}
