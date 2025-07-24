#include <QApplication>
#include "MandelbrotWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);   // Create Qt application object. Must exist before any UI widgets. It sets up the event loop.

    MandelbrotWidget widget;
    widget.resize(800, 600);
    widget.show();  

    return app.exec();  // Starts the event loop. This keeps the application running and responsive to user input.
}
