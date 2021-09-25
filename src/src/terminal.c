#include "../header/terminal.h"

#include <stddef.h>

int col = 0;
int row = 0;

const int VGA_COLS = 80;
const int VGA_ROWS = 25;

volatile uint16_t *vga_buffer = (uint16_t *)0xB8000;

uint8_t color = COL(BLACK, BRIGHT_WHITE);

void clear_term()
{
    const uint16_t clear = ((uint16_t)color << 8) | ' ';
    for (int c = 0; c < VGA_COLS; c++)
    {
        for (int r = 0; r < VGA_ROWS; r++)
        {
            const size_t index = (VGA_COLS * r) + c;
            vga_buffer[index] = clear;
        }
    }
}

void put_char(char ch, int r, int c)
{
    switch (ch)
    {
    case '\n':
        row++;
        col = 0;
        break;
    default:;
        const size_t index = (VGA_COLS * r) + c;
        vga_buffer[index] = ((uint16_t)color << 8) | ch;
        col++;
        break;
    }
    if (col >= VGA_COLS)
    {
        col = 0;
        row++;
    }
    if (row >= VGA_ROWS)
    {
        col = 0;
        row = 0;
    }
}

void put_string(const char *str, int r, int c)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        put_c(str[i]);
    }
}

void delay(int t)
{

    while (t--)
    {
        __asm__("nop\n\t");
    }
}