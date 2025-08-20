#include <QApplication>
#include "GameOfLifeWidget.h"

int main(int argc, char* argv[]){
    QApplication app(argc, argv);

    GameOfLifeWidget widget;
    widget.resize(1280, 720);
    widget.show();

    return app.exec();
}