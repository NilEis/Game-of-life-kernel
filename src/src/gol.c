#include "../header/terminal.h"
#include "../header/gol.h"

#define XY_TO_I(x, y) (x + y * VGA_COLS)

#define buffer_a (map_flag ? map_a : map_b)
#define buffer_b (map_flag ? map_b : map_a)

static uint8_t map_a[80][25] = {0};

static uint8_t map_b[80][25] = {0};

static int map_flag = 0;

void draw_map()
{
    int x, y;
    for (y = 1; y < VGA_ROWS - 1; y++)
    {
        for (x = 1; x < VGA_COLS - 1; x++)
        {
            vga_buffer[XY_TO_I(x, y)] = ((buffer_a[x][y]) * (COL(BRIGHT_WHITE, BRIGHT_WHITE) << 8)) | ' ';
        }
    }
    map_flag = (map_flag + 1) % 2;
}

void update_map()
{
    int x, y, neighbors;
    for (y = 1; y < VGA_ROWS - 1; y++)
    {
        for (x = 1; x < VGA_COLS - 1; x++)
        {
            neighbors =
                buffer_b[x - 1][y - 1] +
                buffer_b[x - 1][y + 0] +
                buffer_b[x - 1][y + 1] +
                buffer_b[x - 0][y - 1] +
                buffer_b[x - 0][y + 1] +
                buffer_b[x + 1][y - 1] +
                buffer_b[x + 1][y + 0] +
                buffer_b[x + 1][y + 1];
            switch (neighbors)
            {
            case 2:
                buffer_a[x][y] = buffer_b[x][y] * 1;
                break;
            case 3:
                buffer_a[x][y] = 1;
                break;

            default:
                buffer_a[x][y] = 0;
                break;
            }
        }
    }
}

void init_map()
{
    int x = WIDTH / 2, y;
    for (y = 0; y < HEIGHT; y++)
    {
        buffer_b[x][y] = 1;
    }
    y = HEIGHT / 2;
    for (x = 0; x < WIDTH; x++)
    {
        buffer_b[x][y] = 1;
    }
}