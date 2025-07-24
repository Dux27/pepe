#pragma once    // File is included only once in compilation

#include <QWidget>    // The base class for UI elements
#include <QImage>     // Used to draw pixel-by-pixel images

// Defines a new class that inherits from QWidget. Interface class for the widget.
class MandelbrotWidget : public QWidget {
    Q_OBJECT    // Macro required for all Qt classes that use signals/slots

    public:
        // Constructor. Called when widget is created. Explicit means it cannot be implicitly converted.
        explicit MandelbrotWidget(QWidget *parent = nullptr);   // Initializes the widget with a parent widget. If no parent is given, it defaults to nullptr.
        // Parent is optional, allowing nesting of widgets.

    protected:
        // These two functions are overridden from QWidget.
        // paintEvent() is called when the window needs to be drawn.
        // wheelEvent() handles scroll wheel input for zoom.

        void paintEvent(QPaintEvent *event) override;
        void wheelEvent(QWheelEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;

    private:
        QImage image;   // Image to hold the Mandelbrot set pixels
        double centerX = -0.5;  // Center of the Mandelbrot set in the complex plane
        double centerY = 0.0;   // Center of the Mandelbrot set in the complex plane
        double scale = 250.0;   // Scale factor for zooming in/out

        float mapping(float x, float in_max, float out_max, float in_min = 0.0, float out_min = 0.0);
        void renderMandelbrot();    // Function to compute and draw the Mandelbrot set
};
