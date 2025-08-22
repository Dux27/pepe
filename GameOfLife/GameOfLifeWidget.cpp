#include "GameOfLifeWidget.h"
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <iostream>
#include <random>   

GameOfLifeWidget::GameOfLifeWidget(QWidget *parent)
    : QWidget(parent), running(false) 
{
    setWindowTitle("Conway's Game of Life");

    std::cout << "+==================== CONWAY'S GAME OF LIFE - CONTROLS =====================+" << std::endl;
    std::cout << "| SPACEBAR       - Start/Stop simulation                                    |" << std::endl;
    std::cout << "| LEFT CLICK     - Place single alive cell                                  |" << std::endl;
    std::cout << "| RIGHT CLICK    - Place glider                                             |" << std::endl;           
    std::cout << "| MIDDLE CLICK   - Hold to create random field (longer hold = bigger field) |" << std::endl;
    std::cout << "| Ctrl + R       - Restart Simulation                                       |" << std::endl;
    std::cout << "+===========================================================================+" << std::endl;

    setFocusPolicy(Qt::StrongFocus);
    
    timer = new QTimer(this);   // 'this' is passed as the parent, so the timer will be destroyed automatically when the widget is destroyed
    connect(timer, &QTimer::timeout, this, [this]() {
        if (running) {
            renderSimulation();
            update();
        } else {
            timer->stop(); 
        }
    });

    flickerTimer = new QTimer(this);
    connect(flickerTimer, &QTimer::timeout, this, [this]() {
        int holdDuration = pressTime.msecsTo(QTime::currentTime());
        flickerSquareSize = (holdDuration / 100) * (width() / lowResW); // Scale to widget size
        showIndicator = !showIndicator;
        update();
    });
    timer->start(frame_dur_ms); 
}

int GameOfLifeWidget::countLiveNeighbors(int x, int y, int width, int height, const QImage& pixelGrid) {
    int count = 0;

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0)
                continue;

            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                if(pixelGrid.pixelColor(nx, ny) == alive)
                    count++;
            }
        }
    }

    return count;
}

void GameOfLifeWidget::renderSimulation() {
    int w = width();
    int h = height();

    // Only create image on first frame
    if (firstFrame || image.isNull()) {
        image = QImage(lowResW, lowResH, QImage::Format_RGB32);
        image.fill(dead);
        
        // Set initial pattern ONLY on first frame
        for (int y = 0; y < lowResH; y++) {
            for (int x = 0; x < lowResW; x++) {
                if ((x == 80 && y == 45) ||
                    (x == 80 && y == 46) ||
                    (x == 81 && y == 45) ||
                    (x == 81 && y == 46) ||
                    (x == 90 && y == 45) ||
                    (x == 90 && y == 46) ||
                    (x == 90 && y == 47) ||
                    (x == 91 && y == 44) ||
                    (x == 91 && y == 48) ||
                    (x == 92 && y == 43) ||
                    (x == 92 && y == 49) ||
                    (x == 93 && y == 43) ||
                    (x == 93 && y == 49) ||
                    (x == 94 && y == 46) ||
                    (x == 95 && y == 44) ||
                    (x == 95 && y == 48) ||
                    (x == 96 && y == 45) ||
                    (x == 96 && y == 46) ||
                    (x == 96 && y == 47) ||
                    (x == 97 && y == 46) ||
                    (x == 100 && y == 43) ||
                    (x == 100 && y == 44) ||
                    (x == 100 && y == 45) ||
                    (x == 101 && y == 43) ||
                    (x == 101 && y == 44) ||
                    (x == 101 && y == 45) ||
                    (x == 102 && y == 42) ||
                    (x == 102 && y == 46) ||
                    (x == 104 && y == 41) ||
                    (x == 104 && y == 42) ||
                    (x == 104 && y == 46) ||
                    (x == 104 && y == 47) ||
                    (x == 114 && y == 43) ||
                    (x == 114 && y == 44) ||
                    (x == 115 && y == 43) ||
                    (x == 115 && y == 44)) {
                    image.setPixel(x, y, alive);
                }
            }
        }
        firstFrame = false;
        scaledImage = image.scaled(w, h, Qt::KeepAspectRatio, Qt::FastTransformation);
        return; // Exit early on first frame
    }

    // Create a copy to read the previous state
    QImage previousImage = image.copy();

    for (int y = 0; y < lowResH; y++) {
        for (int x = 0; x < lowResW; x++) {   
            int neighbours = countLiveNeighbors(x, y, lowResW, lowResH, previousImage);
            bool selfState = (previousImage.pixelColor(x, y) == alive);

            // Conway's Game of Life RULES
            if (selfState && neighbours < 2) {
                // 1. Underpopulation
                image.setPixel(x, y, dead);
            }
            else if (selfState && (neighbours == 2 || neighbours == 3)) {
                // 2. Survival
                image.setPixel(x, y, alive);
            }
            else if (selfState && neighbours > 3) {
                // 3. Overpopulation
                image.setPixel(x, y, dead);
            }
            else if (!selfState && neighbours == 3) {
                // 4. Birth
                image.setPixel(x, y, alive);
            }
            else {
                // 5. Stay dead
                image.setPixel(x, y, dead);
            }
        }
    }
    
    scaledImage = image.scaled(w, h, Qt::KeepAspectRatio, Qt::FastTransformation);
}

void GameOfLifeWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawImage(0, 0, scaledImage);
    
    if (middleButtonPressed && showIndicator) {
        int leftCornerX = gridX * width() / lowResW - flickerSquareSize/2;
        int leftCornerY = gridY * height() / lowResH - flickerSquareSize/2;
        painter.fillRect(leftCornerX, leftCornerY, flickerSquareSize, flickerSquareSize, Qt::darkGray);
    }
}

void GameOfLifeWidget::resizeEvent(QResizeEvent *event) {
    if (!rendered) {
        renderSimulation();   // First render 
        rendered = true;
    }
    QWidget::resizeEvent(event);
}

void GameOfLifeWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        running = !running;
        if (running && !timer->isActive()) {
            timer->start(frame_dur_ms);
        }
        std::string msg = running ? "START" : "STOP"; 
        std::cout<<msg<<std::endl;
    }
    else if (event->key() == Qt::Key_R && event->modifiers() & Qt::ControlModifier) {
        firstFrame = true;
        std::cout << "Restarting simulation" << std::endl;
    }
}

void GameOfLifeWidget::mousePressEvent(QMouseEvent *event) {
    int clickX = event->pos().x();
    int clickY = event->pos().y();
        
    // Convert to low-res coordinates
    gridX = (clickX * lowResW) / width();
    gridY = (clickY * lowResH) / height();

    if (event->button() == Qt::LeftButton){
        image.setPixel(gridX, gridY, alive);
    }
    else if (event->button() == Qt::RightButton){
        image.setPixel(gridX, gridY, alive);
        if(gridX + 1 >= 0 && gridX + 1 < lowResW && gridY + 1 >= 0 && gridY + 1 < lowResH)
            image.setPixel(gridX + 1, gridY + 1, alive);
        if(gridX - 1 >= 0 && gridX - 1 < lowResW && gridY + 2 >= 0 && gridY + 2 < lowResH)
            image.setPixel(gridX - 1, gridY + 2, alive);
        if(gridY + 2 >= 0 && gridY + 2 < lowResH)
            image.setPixel(gridX, gridY + 2, alive);
        if(gridX + 1 >= 0 && gridX + 1 < lowResW && gridY + 2 >= 0 && gridY + 2 < lowResH)
            image.setPixel(gridX + 1, gridY + 2, alive);
    }
    else if (event->button() == Qt::MiddleButton){
        pressTime = QTime::currentTime();
        middleButtonPressed = true;
        showIndicator = true;
        flickerTimer->start(100);
    }

    scaledImage = image.scaled(width(), height(), Qt::KeepAspectRatio, Qt::FastTransformation);
    update(); 
}

void GameOfLifeWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::MiddleButton && middleButtonPressed){
        int holdDuration = pressTime.msecsTo(QTime::currentTime());
        std::cout << "Middle button held for: " << holdDuration << " ms" << std::endl;
        
        int fieldSize = holdDuration / 100;

        for(int dx = -fieldSize/2; dx < fieldSize/2; dx++){
            for(int dy = -fieldSize/2; dy < fieldSize/2; dy++){
                int rx = gridX + dx;
                int ry = gridY + dy;
                
                // Some new school shit
                std::random_device rd;                      // seed for randomness
                std::mt19937 gen(rd());                     // random number engine
                std::uniform_int_distribution<> dist(0, 1); // 0 or 1

                if(rx >= 0 && rx < lowResW && ry >= 0 && ry < lowResH) {
                    bool randVal = dist(gen);
                    image.setPixel(rx, ry, randVal ? alive : dead);
                }
            }
        }

        scaledImage = image.scaled(width(), height(), Qt::KeepAspectRatio, Qt::FastTransformation);
        update(); 

        middleButtonPressed = false;
        flickerTimer->stop();
        flickerSquareSize = 0;
        showIndicator = false;
    }
}