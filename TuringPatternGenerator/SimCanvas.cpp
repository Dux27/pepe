#include "SimCanvas.hpp"
#include <cstdlib>
#include <ctime>
#include <random>


SimCanvas::SimCanvas(QWidget *parent)
    : QWidget(parent) 
{
    image = QImage(w, h, QImage::Format_ARGB32);
    image.fill(background_rgb);

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    generateCircle(curr_grid_ptr, w / 2, h / 2, 200, true);
    generateCircle(curr_grid_ptr, w / 2 + 300, h / 2 + 300, 200, true);
}

void SimCanvas::renderSimulation()
{
    if (image.isNull() || image.bits() == nullptr)
    {
        // Wait for image to allocate memory.
        return;
    }

    // Get the raw pointer to the first memory cell of the image data.
    // Interpret the pointer as 33-bit in type (QRgb*) rather than a 1-byte type (uchar*)
    // This means whenever we increment the index by 1, the compiler automatically jumps forward by 4 bytes (one full pixel) in memory.
    QRgb *pixel_data = reinterpret_cast<QRgb *>(image.bits());

    for (int y = 0; y < h; y++)
    {
        int row_offset = y * w;
        
        for (int x = 0; x < w; x++)
        {
            if((*curr_grid_ptr)[y][x] > 0.0f)
            {
                int alpha = static_cast<int>((*curr_grid_ptr)[y][x] * 255.0f);
                pixel_data[row_offset + x] = (alpha << 24) | (activator_cell_rgb & 0x00FFFFFF);
            }
        }
    }
}

void SimCanvas::updateSimulation()
{
    const std::vector<Direction> directions = {
        {0, -1}, {0, 1}, {-1, 0}, {1, 0},   // sides
        {-1, -1}, {1, -1}, {-1, 1}, {1, 1}  // corners
    };

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            float sum = 0.0f;
            for (const auto& dir : directions)
            {
                int neigbor_x = (x + dir.dx + w) % w;
                int neigbor_y = (y + dir.dy + h) % h;
                sum += (*curr_grid_ptr)[neigbor_y][neigbor_x];
            }

            float sim_factor = 0.5f;
            float new_val = ((1.0f - sim_factor) * (*curr_grid_ptr)[y][x]) + (sim_factor * sum/8.0f);
            (*next_grid_ptr)[y][x] = new_val;
        }
    }

    curr_grid = next_grid;
}

void SimCanvas::generateCircle(std::array<std::array<float, w>, h> *grid, int cX, int cY, int radius, bool is_random)
{
    int rSqr = radius * radius;

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            int dx = x - cX;
            int dy = y - cY;

            if ((dx * dx) + (dy * dy) <= rSqr)
            {
                if (is_random)
                    (*grid)[y][x] = static_cast<float>(rand()) / RAND_MAX;
                else
                    (*grid)[y][x] = 1.0f;
            }
        }
    }
}

void SimCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}