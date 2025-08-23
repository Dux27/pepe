#include <QApplication>
#include "nBodyGravitation.h"

int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);

    NBodyGravitation widget;
    widget.resize(1920, 1080);
    widget.setFixedSize(widget.size());
    widget.show();

    return app.exec();
}