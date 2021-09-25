#include <stddef.h>
#include <stdint.h>
#include "header/terminal.h"
#include "header/gol.h"

#if defined(__linux__)
#error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
#error "This code must be compiled with an x86-elf compiler"
#endif

void kernal_main_func()
{
    clear_term();
    init_map();
    for (;;)
    {
        update_map();
        draw_map();
        delay(25000000);
    }
}