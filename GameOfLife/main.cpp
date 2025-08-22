#include <QApplication>
#include <QIcon>
#include "GameOfLifeWidget.h"

int main(int argc, char* argv[]){
    QApplication app(argc, argv);

    app.setWindowIcon(QIcon("/home/dux/inf/pepe/GameOfLife/res/glider.png")); 

    GameOfLifeWidget widget;
    widget.resize(1280, 720);
    widget.show();

    return app.exec();
}