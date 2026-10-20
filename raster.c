#include "TYPES.H"
#include "font.h"
#include "raster.h"

#define FRAMEBUFFER_WORD_COUNT 8000
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define BYTES_PER_SCANLINE 80
#define BITS_PER_BYTE 8

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
    int curr_row, curr_col;
    UINT8 *byte_base;
    UINT8 mask;

    byte_base = (UINT8 *)base;

    for (curr_row = row; curr_row < row + length; curr_row++)
    {
        for (curr_col = col; curr_col < col + width; curr_col++)
        {
            if (curr_row >= 0 && curr_row < SCREEN_HEIGHT && curr_col >= 0 && curr_col < SCREEN_WIDTH)
            {
                mask = 1 << (BITS_PER_BYTE - 1 - (curr_col & (BITS_PER_BYTE - 1)));
                byte_base[curr_row * BYTES_PER_SCANLINE + (curr_col >> 3)] &= ~mask;
            }
        }
    }
}

void plot_pixel(UINT8 *base, int row, int col)
{
    if (col >= 0 && col < SCREEN_WIDTH && row >= 0 && row < SCREEN_HEIGHT)
    {
        *(base + row * BYTES_PER_SCANLINE + (col >> 3)) |= 1 << (BITS_PER_BYTE - 1 - (col & (BITS_PER_BYTE - 1)));
    }
}

void plot_horizontal_line(UINT32 *base, int row, int col, UINT16 length)
{
    UINT8 *byte_base;
    UINT8 mask;
    int i;
    int curr_col;

    byte_base = (UINT8 *)base;

    for (i = 0; i < length; i++)
    {
        curr_col = col + i;

        if (row >= 0 && row < SCREEN_HEIGHT && curr_col >= 0 && curr_col < SCREEN_WIDTH)
        {
            mask = 1 << (BITS_PER_BYTE - 1 - (curr_col & (BITS_PER_BYTE - 1)));

            byte_base[row * BYTES_PER_SCANLINE + (curr_col >> 3)] |= mask;
        }
    }
}

void plot_vertical_line(UINT32 *base, int row, int col, UINT16 length)
{
    UINT8 *byte_base;
    UINT8 mask;
    int i;
    int curr_row;

    byte_base = (UINT8 *)base;

    for (i = 0; i < length; i++)
    {
        curr_row = row + i;

        if (curr_row >= 0 && curr_row < SCREEN_HEIGHT && col >= 0 && col < SCREEN_WIDTH)
        {
            mask = 1 << (BITS_PER_BYTE - 1 - (col & (BITS_PER_BYTE - 1)));

            byte_base[curr_row * BYTES_PER_SCANLINE + (col >> 3)] |= mask;
        }
    }
}

void plot_line(UINT32 *base, int start_row, int start_col, int end_row, int end_col)
{
    UINT8 *byte_base;
    UINT8 mask;
    int delta_row;
    int delta_col;
    int step_row;
    int step_col;
    int error;
    int doubled_error;
    int curr_row;
    int curr_col;

    byte_base = (UINT8 *)base;

    delta_row = end_row - start_row;
    delta_col = end_col - start_col;

    if (delta_row < 0)
    {
        delta_row = -delta_row;
        step_row = -1;
    }
    else
    {
        step_row = 1;
    }

    if (delta_col < 0)
    {
        delta_col = -delta_col;
        step_col = -1;
    }
    else
    {
        step_col = 1;
    }

    error = delta_col - delta_row;
    curr_row = start_row;
    curr_col = start_col;

    while (1)
    {
        if (curr_row >= 0 && curr_row < SCREEN_HEIGHT && curr_col >= 0 && curr_col < SCREEN_WIDTH)
        {
            mask = 1 << (BITS_PER_BYTE - 1 - (curr_col & (BITS_PER_BYTE - 1)));

            byte_base[curr_row * BYTES_PER_SCANLINE + (curr_col >> 3)] |= mask;
        }

        if (curr_row == end_row && curr_col == end_col)
        {
            break;
        }

        doubled_error = 2 * error;

        if (doubled_error > -delta_row)
        {
            error -= delta_row;
            curr_col += step_col;
        }

        if (doubled_error < delta_col)
        {
            error += delta_col;
            curr_row += step_row;
        }
    }
}

void plot_rectangle(UINT32 *base, int row, int col, UINT16 length, UINT16 width)
{
    UINT8 *byte_base;
    UINT8 mask;
    int curr_row;
    int curr_col;

    byte_base = (UINT8 *)base;

    for (curr_row = row; curr_row < row + (int)length; curr_row++)
    {
        for (curr_col = col; curr_col < col + (int)width; curr_col++)
        {
            if (curr_row >= 0 && curr_row < SCREEN_HEIGHT && curr_col >= 0 && curr_col < SCREEN_WIDTH)
            {
                mask = 1 << (BITS_PER_BYTE - 1 - (curr_col & (BITS_PER_BYTE - 1)));

                byte_base[curr_row * BYTES_PER_SCANLINE + (curr_col >> 3)] |= mask;
            }
        }
    }
}

void plot_square(UINT32 *base, int row, int col, UINT16 side)
{
    UINT8 *byte_base;
    UINT8 mask;
    int curr_row;
    int curr_col;

    byte_base = (UINT8 *)base;

    for (curr_row = row; curr_row < row + (int)side; curr_row++)
    {
        for (curr_col = col; curr_col < col + (int)side; curr_col++)
        {
            if (curr_row >= 0 && curr_row < SCREEN_HEIGHT && curr_col >= 0 && curr_col < SCREEN_WIDTH)
            {
                mask = 1 << (BITS_PER_BYTE - 1 - (curr_col & (BITS_PER_BYTE - 1)));

                byte_base[curr_row * BYTES_PER_SCANLINE + (curr_col >> 3)] |= mask;
            }
        }
    }
}

void plot_triangle(UINT32 *base, int row, int col, UINT16 triangle_base, UINT16 height, UINT8 direction)
{
    UINT8 *byte_base;
    UINT8 mask;
    int curr_row;
    int curr_col;
    int screen_row;
    int screen_col;
    int span;
    int start_col;

    byte_base = (UINT8 *)base;

    if (height == 0 || triangle_base == 0)
    {
        return;
    }

    for (curr_row = 0; curr_row < height; curr_row++)
    {
        if (direction == 0 || direction == 1)
        {
            span = ((curr_row + 1) * triangle_base + height - 1) / height;
        }
        else
        {
            span = ((height - curr_row) * triangle_base + height - 1) / height;
        }

        if (direction == 0 || direction == 2)
        {
            start_col = col;
        }
        else
        {
            start_col = col - span + 1;
        }

        if (direction == 0 || direction == 1)
        {
            screen_row = row + curr_row;
        }
        else
        {
            screen_row = row - curr_row;
        }

        for (curr_col = 0; curr_col < span; curr_col++)
        {
            screen_col = start_col + curr_col;

            if (screen_row >= 0 && screen_row < SCREEN_HEIGHT && screen_col >= 0 && screen_col < SCREEN_WIDTH)
            {
                mask = 1 << (BITS_PER_BYTE - 1 - (screen_col & (BITS_PER_BYTE - 1)));

                byte_base[screen_row * BYTES_PER_SCANLINE + (screen_col >> 3)] |= mask;
            }
        }
    }
}

void plot_8bit_bitmap(UINT8 *base, int row, int col, const UINT8 *bitmap, UINT16 height)
{
    UINT8 mask;
    int curr_row;
    int curr_col;
    int screen_row;
    int screen_col;

    for (curr_row = 0; curr_row < height; curr_row++)
    {
        screen_row = row + curr_row;

        for (curr_col = 0; curr_col < BITS_PER_BYTE; curr_col++)
        {
            screen_col = col + curr_col;
            mask = 1 << (BITS_PER_BYTE - 1 - curr_col);

            if (screen_row >= 0 && screen_row < SCREEN_HEIGHT && screen_col >= 0 && screen_col < SCREEN_WIDTH)
            {
                if (bitmap[curr_row] & mask)
                {
                    base[screen_row * BYTES_PER_SCANLINE + (screen_col >> 3)] |= 1 << (BITS_PER_BYTE - 1 - (screen_col & (BITS_PER_BYTE - 1)));
                }
            }
        }
    }
}

void plot_16bit_bitmap(UINT16 *base, int row, int col, const UINT16 *bitmap, UINT16 height)
{
    UINT16 mask;
    UINT8 *byte_base;
    int curr_row;
    int curr_col;
    int screen_row;
    int screen_col;

    byte_base = (UINT8 *)base;

    for (curr_row = 0; curr_row < height; curr_row++)
    {
        screen_row = row + curr_row;

        for (curr_col = 0; curr_col < 16; curr_col++)
        {
            screen_col = col + curr_col;
            mask = 1 << (15 - curr_col);

            if (screen_row >= 0 && screen_row < SCREEN_HEIGHT && screen_col >= 0 && screen_col < SCREEN_WIDTH)
            {
                if (bitmap[curr_row] & mask)
                {
                    byte_base[screen_row * BYTES_PER_SCANLINE + (screen_col >> 3)] |= 1 << (BITS_PER_BYTE - 1 - (screen_col & (BITS_PER_BYTE - 1)));
                }
            }
        }
    }
}

void plot_32bit_bitmap(UINT32 *base, int row, int col, const UINT32 *bitmap, UINT16 height)
{
    UINT32 mask;
    UINT8 *byte_base;
    int curr_row;
    int curr_col;
    int screen_row;
    int screen_col;

    byte_base = (UINT8 *)base;

    for (curr_row = 0; curr_row < height; curr_row++)
    {
        screen_row = row + curr_row;

        for (curr_col = 0; curr_col < 32; curr_col++)
        {
            screen_col = col + curr_col;
            mask = 1UL << (31 - curr_col);

            if (screen_row >= 0 && screen_row < SCREEN_HEIGHT && screen_col >= 0 && screen_col < SCREEN_WIDTH)
            {
                if (bitmap[curr_row] & mask)
                {
                    byte_base[screen_row * BYTES_PER_SCANLINE + (screen_col >> 3)] |= 1 << (BITS_PER_BYTE - 1 - (screen_col & (BITS_PER_BYTE - 1)));
                }
            }
        }
    }
}

void plot_character(UINT8 *base, int row, int col, char ch)
{
    const UINT8 *glyph;
    UINT8 mask;
    int i, j;
    int curr_row;
    int curr_col;

    if (IS_PRINTABLE(ch))
    {
        glyph = GLYPH_START(ch);

        for (i = 0; i < FONT_HEIGHT; i++)
        {
            for (j = 0; j < BITS_PER_BYTE; j++)
            {
                curr_row = row + i;
                curr_col = col + j;
                mask = 1 << (BITS_PER_BYTE - 1 - j);

                if (curr_row >= 0 && curr_row < SCREEN_HEIGHT && curr_col >= 0 && curr_col < SCREEN_WIDTH)
                {
                    if (glyph[i] & mask)
                    {
                        base[curr_row * BYTES_PER_SCANLINE + (curr_col >> 3)] |= 1 << (BITS_PER_BYTE - 1 - (curr_col & (BITS_PER_BYTE - 1)));
                    }
                }
            }
        }
    }
}

void plot_string(UINT8 *base, int row, int col, char *ch)
{
    int i;
    int curr_col;

    i = 0;
    curr_col = col;

    while (ch[i] != '\0')
    {
        if (ch[i] == '\n')
        {
            row += FONT_HEIGHT;
            curr_col = col;
        }
        else if (ch[i] == '\r')
        {
            curr_col = col;
        }
        else if (IS_PRINTABLE(ch[i]))
        {
            plot_character(base, row, curr_col, ch[i]);
            curr_col += BITS_PER_BYTE;
        }

        i++;
    }
}