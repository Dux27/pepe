#include <QApplication>
#include "TuringPatternGenerator.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    TuringPatternGenerator widget;
    widget.show();
    widget.resize(1280, 720);

    return app.exec();
}