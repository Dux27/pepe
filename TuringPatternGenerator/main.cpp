#include <QApplication>
#include "TuringPatternGenerator.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    TuringPatternGenerator widget;
    widget.showMaximized();

    return app.exec();
}