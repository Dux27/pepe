#include <QApplication>
#include "TuringPatternGenerator.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    TuringPatternGenerator widget;
    widget.resize(1280, 720);
    widget.show();

    return app.exec();
}