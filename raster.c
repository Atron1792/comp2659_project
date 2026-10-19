#include "TYPES.H"
#include "raster.h"

#define FRAMEBUFFER_WORD_COUNT 8000
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

void clear_screen(UINT32 *base)
{
    int i;

    for (i = 0; i < FRAMEBUFFER_WORD_COUNT; i++)
    {
        base[i] = 0;
    }
}

void clear_region(UINT32 *base, int row, int col, UINT16 length, UINT16 width)
{
}

void plot_pixel(UINT8 *base, int row, int col)
{
    if (col >= 0 && col < SCREEN_WIDTH && row >= 0 && row < SCREEN_HEIGHT)
    {
        *(base + row * 80 + (col >> 3)) |= 1 << (7 - (col & 7));
    }
}

void plot_horizontal_line(UINT32 *base, int row, int col, UINT16 length)
{
}

void plot_vertical_line(UINT32 *base, int row, int col, UINT16 length)
{
}

void plot_line(UINT32 *base, int start_row, int start_col, int end_row, int end_col)
{
}

void plot_rectangle(UINT32 *base, int row, int col, UINT16 length, UINT16 width)
{
}

void plot_square(UINT32 *base, int row, int col, UINT16 side)
{
}

void plot_triangle(UINT32 *base, int row, int col, UINT16 triangle_base, UINT16 height, UINT8 direction)
{
}

void plot_8bit_bitmap(UINT8 *base, int row, int col, const UINT8 *bitmap, UINT16 height)
{
}

void plot_16bit_bitmap(UINT16 *base, int row, int col, const UINT16 *bitmap, UINT16 height)
{
}

void plot_32bit_bitmap(UINT32 *base, int row, int col, const UINT32 *bitmap, UINT16 height)
{
}

void plot_character(UINT8 *base, int row, int col, char ch)
{
    char *font;
    int i;

    if (col >= 0 && col < SCREEN_WIDTH && row >= 0 && row < SCREEN_HEIGHT)
    {
        for (i = 0; i < 8; i++)
        {
            base[i * 80] = font[ch + i * 256];
        }
    }
}

void plot_string(UINT8 *base, int row, int col, char *ch)
{
}