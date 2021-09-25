#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>

#define WIDTH VGA_COLS
#define HEIGHT VGA_ROWS

#define COL(b, f) (uint8_t)((b << 4) | f)
#define put_c(c) put_char(c, row, col)
#define put_s(s) put_string(s, row, col)

extern const int VGA_COLS;
extern const int VGA_ROWS;

extern volatile uint16_t *vga_buffer;
// Entries in the VGA buffer take the binary form BBBBFFFFCCCCCCCC, where:
// - B is the background color
// - F is the foreground color
// - C is the ASCII character

enum vga_color
{
    BLACK = 0x00,
    BLUE = 0x01,
    GREEN = 0x02,
    CYAN = 0x03,
    RED = 0x04,
    MAGENTA = 0x05,
    BROWN = 0x06,
    WHITE = 0x07,
    GRAY = 0x08,
    LIGHT_BLUE = 0x09,
    LIGHT_GREEN = 0x0A,
    LIGHT_CYAN = 0x0B,
    LIGHT_RED = 0x0C,
    LIGHT_MAGENTA = 0x0D,
    YELLOW = 0x0E,
    BRIGHT_WHITE = 0x0F
};

void put_string(const char *str, int r, int c);
void put_char(char ch, int r, int c);
void clear_term();
void delay(int t);

#endif // TERMINAL_H
