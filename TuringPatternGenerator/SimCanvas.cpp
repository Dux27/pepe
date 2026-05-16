#include "SimCanvas.hpp"


SimCanvas::SimCanvas(QWidget *parent)
    : QWidget(parent) 
{
    image = QImage(w, h, QImage::Format_ARGB32);
    image.fill(background_rgb);

    curr_grid.assign(h, std::vector<float>(w, 0.0f));
    curr_grid[h / 2][w / 2] = 1.0f;
}

void SimCanvas::renderSimulation()
{
    if (image.isNull() || image.bits() == nullptr)
    {
        // Wait for image to allocate memory.
        return;
    }

    image.fill(background_rgb);

    // Get the raw pointer to the first memory cell of the image data.
    // Interpret the pointer as 32-bit in type (QRgb*) rather than a 1-byte type (uchar*)
    // This means whenever we increment the index by 1, the compiler automatically jumps forward by 4 bytes (one full pixel) in memory.
    QRgb *pixel_data = reinterpret_cast<QRgb *>(image.bits());

    for (int y = 0; y < h; y++)
    {
        int row_offset = y * w;
        
        for (int x = 0; x < w; x++)
        {
            if(curr_grid[y][x] > 0.0f)
            {
                int alpha = static_cast<int>(curr_grid[y][x] * 255.0f);
                pixel_data[row_offset + x] = (alpha << 24) | (activator_cell_rgb & 0x00FFFFFF);
            }
        }
    }
}

void SimCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}