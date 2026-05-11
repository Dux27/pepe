#pragma once

#include <QWidget>
#include <QImage>
#include <QTime>

class TuringPatternGenerator : public QWidget
{
    Q_OBJECT

    public:
        explicit TuringPatternGenerator(QWidget *parent=nullptr);

    protected:
        void paintEvent(QPaintEvent *event) override;

    private:
        QTimer *timer;
        QImage image;
};