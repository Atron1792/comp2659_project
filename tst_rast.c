#include <osbind.h>

#include "TYPES.H"
#include "raster.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
static void wait_for_key(void)
{
    Cconin();
}

static void clear_after_case(UINT32 *base)
{
    clear_screen(base);
}

static void clear_and_wait(UINT32 *base)
{
    clear_after_case(base);
}

static void tst_clear_region(UINT32 *base)
{
    plot_rectangle(base, 0, 0, 10, 10);
    wait_for_key();
    clear_region(base, 0, 0, 10, 10);
    wait_for_key();
}

static void tst_clear_screen(UINT32 *base)
{
    clear_screen(base);
    wait_for_key();
}

static void tst_plot_pixel(UINT8 *base)
{
    plot_pixel(base, 0, 0);
    wait_for_key();
    clear_after_case((UINT32 *)base);

    plot_pixel(base, 0, SCREEN_WIDTH - 1);
    wait_for_key();
    clear_after_case((UINT32 *)base);

    plot_pixel(base, SCREEN_HEIGHT - 1, SCREEN_WIDTH - 1);
    wait_for_key();
    clear_after_case((UINT32 *)base);

    plot_pixel(base, SCREEN_HEIGHT - 1, 0);
    wait_for_key();
    clear_after_case((UINT32 *)base);
}

static void tst_plot_horizontal_line(UINT32 *base)
{
    plot_horizontal_line(base, 0, 0, 80);
    wait_for_key();
    clear_after_case(base);

    plot_horizontal_line(base, 0, SCREEN_WIDTH - 80, 80);
    wait_for_key();
    clear_after_case(base);

    plot_horizontal_line(base, SCREEN_HEIGHT - 1, SCREEN_WIDTH - 80, 80);
    wait_for_key();
    clear_after_case(base);

    plot_horizontal_line(base, SCREEN_HEIGHT - 1, 0, 80);
    wait_for_key();
    clear_after_case(base);
}

static void tst_plot_vertical_line(UINT32 *base)
{
    plot_vertical_line(base, 0, 0, 80);
    wait_for_key();
    clear_after_case(base);

    plot_vertical_line(base, 0, SCREEN_WIDTH - 1, 80);
    wait_for_key();
    clear_after_case(base);

    plot_vertical_line(base, SCREEN_HEIGHT - 80, SCREEN_WIDTH - 1, 80);
    wait_for_key();
    clear_after_case(base);

    plot_vertical_line(base, SCREEN_HEIGHT - 80, 0, 80);
    wait_for_key();
    clear_after_case(base);
}

static void tst_plot_line(UINT32 *base)
{
    plot_line(base, 0, 0, 80, 80);
    wait_for_key();
    clear_after_case(base);

    plot_line(base, 0, SCREEN_WIDTH - 1, 80, SCREEN_WIDTH - 81);
    wait_for_key();
    clear_after_case(base);

    plot_line(base, SCREEN_HEIGHT - 81, SCREEN_WIDTH - 81, SCREEN_HEIGHT - 1, SCREEN_WIDTH - 1);
    wait_for_key();
    clear_after_case(base);

    plot_line(base, SCREEN_HEIGHT - 81, 0, SCREEN_HEIGHT - 1, 80);
    wait_for_key();
    clear_after_case(base);
}

static void tst_plot_rectangle(UINT32 *base)
{
    plot_rectangle(base, 0, 0, 40, 80);
    wait_for_key();
    clear_and_wait(base);

    plot_rectangle(base, 0, SCREEN_WIDTH - 80, 40, 80);
    wait_for_key();
    clear_and_wait(base);

    plot_rectangle(base, SCREEN_HEIGHT - 40, SCREEN_WIDTH - 80, 40, 80);
    wait_for_key();
    clear_and_wait(base);

    plot_rectangle(base, SCREEN_HEIGHT - 40, 0, 40, 80);
    wait_for_key();
    clear_and_wait(base);
}

static void tst_plot_square(UINT32 *base)
{
    plot_square(base, 0, 0, 40);
    wait_for_key();
    clear_and_wait(base);

    plot_square(base, 0, SCREEN_WIDTH - 40, 40);
    wait_for_key();
    clear_and_wait(base);

    plot_square(base, SCREEN_HEIGHT - 40, SCREEN_WIDTH - 40, 40);
    wait_for_key();
    clear_and_wait(base);

    plot_square(base, SCREEN_HEIGHT - 40, 0, 40);
    wait_for_key();
    clear_and_wait(base);
}

static void tst_plot_triangle(UINT32 *base)
{
    plot_triangle(base, 0, 0, 40, 40, 0);
    wait_for_key();
    clear_and_wait(base);

    plot_triangle(base, 0, SCREEN_WIDTH - 1, 40, 40, 1);
    wait_for_key();
    clear_and_wait(base);

    plot_triangle(base, SCREEN_HEIGHT - 1, SCREEN_WIDTH - 1, 40, 40, 3);
    wait_for_key();
    clear_and_wait(base);

    plot_triangle(base, SCREEN_HEIGHT - 1, 0, 40, 40, 2);
    wait_for_key();
    clear_and_wait(base);
}

static void tst_plot_8bit_bitmap(UINT8 *base)
{
    static const UINT8 bitmap[] = {
        0x00, 0x0E, 0x0E, 0x1C, 0x78, 0x38, 0x20, 0x00
    };

    plot_8bit_bitmap(base, 0, 0, bitmap, 8);
    wait_for_key();
    clear_after_case((UINT32 *)base);

    plot_8bit_bitmap(base, 0, SCREEN_WIDTH - 8, bitmap, 8);
    wait_for_key();
    clear_after_case((UINT32 *)base);

    plot_8bit_bitmap(base, SCREEN_HEIGHT - 8, SCREEN_WIDTH - 8, bitmap, 8);
    wait_for_key();
    clear_after_case((UINT32 *)base);
    
    plot_8bit_bitmap(base, SCREEN_HEIGHT - 8, 0, bitmap, 8);
    wait_for_key();
    clear_after_case((UINT32 *)base);
}

static void tst_plot_16bit_bitmap(UINT16 *base)
{
    static const UINT16 bitmap[] = {
        0x0000, 0x0078, 0x00FC, 0x00FC,
        0x00FC, 0x00F8, 0x01E0, 0x27F0,
        0x3FE0, 0x3FC0, 0x1FC0, 0x0F80,
        0x0780, 0x0480, 0x0480, 0x0000
    };

    plot_16bit_bitmap(base, 0, 0, bitmap, 16);
    wait_for_key();
    clear_after_case((UINT32 *)base);

    plot_16bit_bitmap(base, 0, SCREEN_WIDTH - 16, bitmap, 16);
    wait_for_key();
    clear_after_case((UINT32 *)base);

    plot_16bit_bitmap(base, SCREEN_HEIGHT - 16, SCREEN_WIDTH - 16, bitmap, 16);
    wait_for_key();
    clear_after_case((UINT32 *)base);

    plot_16bit_bitmap(base, SCREEN_HEIGHT - 16, 0, bitmap, 16);
    wait_for_key();
    clear_after_case((UINT32 *)base);
}

static void tst_plot_32bit_bitmap(UINT32 *base)
{
    static const UINT32 bitmap[] = {
        0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00007FE0UL,
        0x0000FFF0UL, 0x0000CFF0UL, 0x0000FFF0UL, 0x0000FFF0UL,
        0x0000FFF0UL, 0x0000FFF0UL, 0x0000FC00UL, 0x0000FFC0UL,
        0x0803F800UL, 0x0807F800UL, 0x0C1FFE00UL, 0x0C3FFE00UL,
        0x0E7FFA00UL, 0x0FFFF800UL, 0x0FFFF800UL, 0x07FFF800UL,
        0x03FFF000UL, 0x03FFF000UL, 0x01FFC000UL, 0x00FF8000UL,
        0x007F8000UL, 0x00398000UL, 0x00308000UL, 0x00208000UL,
        0x0030C000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL
    };

    plot_32bit_bitmap(base, 0, 0, bitmap, 32);
    wait_for_key();
    clear_and_wait(base);

    plot_32bit_bitmap(base, 0, SCREEN_WIDTH - 32, bitmap, 32);
    wait_for_key();
    clear_and_wait(base);

    plot_32bit_bitmap(base, SCREEN_HEIGHT - 32, SCREEN_WIDTH - 32, bitmap, 32);
    wait_for_key();
    clear_and_wait(base);

    plot_32bit_bitmap(base, SCREEN_HEIGHT - 32, 0, bitmap, 32);
    wait_for_key();
    clear_and_wait(base);
}

static void tst_plot_character(UINT8 *base)
{
    plot_character(base, 0, 0, 'A');
    wait_for_key();
    clear_and_wait((UINT32 *)base);

    plot_character(base, 0, SCREEN_WIDTH - 8, 'A');
    wait_for_key();
    clear_and_wait((UINT32 *)base);

    plot_character(base, SCREEN_HEIGHT - 8, SCREEN_WIDTH - 8, 'A');
    wait_for_key();
    clear_and_wait((UINT32 *)base);

    plot_character(base, SCREEN_HEIGHT - 8, 0, 'A');
    wait_for_key();
    clear_and_wait((UINT32 *)base);
}

static void tst_plot_string(UINT8 *base)
{
    plot_string(base, 0, 0, "TEST");
    wait_for_key();
    clear_and_wait((UINT32 *)base);

    plot_string(base, 0, SCREEN_WIDTH - 32, "TEST");
    wait_for_key();
    clear_and_wait((UINT32 *)base);

    plot_string(base, SCREEN_HEIGHT - 8, SCREEN_WIDTH - 32, "TEST");
    wait_for_key();
    clear_and_wait((UINT32 *)base);

    plot_string(base, SCREEN_HEIGHT - 8, 0, "TEST");
    wait_for_key();
    clear_and_wait((UINT32 *)base);
}


int main(void){
    UINT32 *base;

    base = Physbase();

    tst_clear_region(base);
    tst_clear_screen(base);
    tst_plot_pixel((UINT8 *)base);
    tst_plot_horizontal_line(base);
    tst_plot_vertical_line(base);
    tst_plot_line(base);
    tst_plot_rectangle(base);
    tst_plot_square(base);
    tst_plot_triangle(base);
    tst_plot_8bit_bitmap((UINT8 *)base);
    tst_plot_16bit_bitmap((UINT16 *)base);
    tst_plot_32bit_bitmap(base);
    tst_plot_character((UINT8 *)base);
    tst_plot_string((UINT8 *)base);

    clear_screen(base);
    return 0;
}