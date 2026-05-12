#include "GameOfLifeWidget.h"
#include <QCoreApplication>
#include <iostream>
#include <QApplication>
#include <QIcon>
#include <QFile>
#include <QDir>

int main(int argc, char* argv[]){
    QApplication app(argc, argv);

    QString exe_dir = QCoreApplication::applicationDirPath();
    QDir dir(exe_dir);
    dir.cdUp();
    dir.cdUp();
    QString path = dir.filePath("img/glider.png"); // adjust depending on distribution
    std::cout << path.toStdString() << std::endl;
    if (QFile::exists(path))
    {
        QIcon icon = QIcon(path);
        app.setWindowIcon(icon); 
    }

    GameOfLifeWidget widget;
    widget.resize(1280, 720);
    widget.show();

    return app.exec();
}