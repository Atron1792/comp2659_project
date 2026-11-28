/*
File Name: raster.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Implements framebuffer clearing, primitive drawing, bitmap plotting,
and font rendering routines.
*/

#include "raster.h"
#include "font.h"
#include <osbind.h>

/*
 PURPOSE: Returns the framebuffer start address stored in the Atari ST video base registers.

 INPUT: None

 OUTPUT: UINT32 * - Address of the active framebuffer.

 ASSUMPTIONS: The low byte of the framebuffer address is zero.
*/
UINT32 *get_video_base()
{
    UINT32 video_address;
    UINT32 old_ssp;

    old_ssp = Super(0);

    video_address = ((UINT32)VIDEO_BASE_HIGH << 16) | ((UINT32)VIDEO_BASE_MID << 8);

    Super(old_ssp);

    return (UINT32 *)video_address;
}
/*
 PURPOSE: Changes the framebuffer start address stored in the Atari ST video base registers.

 INPUT: base (UINT32 *) - 256-byte-aligned framebuffer address.

 OUTPUT: None

 ASSUMPTIONS: The low byte of the framebuffer address is zero.
*/
void set_video_base(UINT32 *base)
{
    UINT32 video_address = (UINT32)base;
    UINT32 old_ssp;

    old_ssp = Super(0);

    VIDEO_BASE_HIGH = video_address >> 16;
    VIDEO_BASE_MID  = video_address >> 8;

    Super(old_ssp);
}

void clearScreen(UINT32 *base)
{
    int i;

    for (i = 0; i < FRAMEBUFFER_WORD_COUNT; i++) {
        *base++ = 0;
    }
}

void clearRegion(UINT32 *base, int row, int col, UINT16 length, UINT16 width)
{
    UINT8 *loc;
    UINT8 first_mask, last_mask;
    int first_byte, last_byte;
    int r, b;

    if (length == 0 || width == 0 || row >= SCREEN_HEIGHT || col >= SCREEN_WIDTH) {
        return;
    }
    if (row < 0) {
        if (length <= -row) {
            return;
        }
        length += row;
        row = 0;
    }
    if (col < 0) {
        if (width <= -col) {
            return;
        }
        width += col;
        col = 0;
    }
    if (length > SCREEN_HEIGHT - row) {
        length = SCREEN_HEIGHT - row;
    }
    if (width > SCREEN_WIDTH - col) {
        width = SCREEN_WIDTH - col;
    }

    first_byte = col >> 3;
    last_byte = (col + width - 1) >> 3;
    first_mask = 0xFF >> (col & 7);
    last_mask = 0xFF << (7 - ((col + width - 1) & 7));
    loc = (UINT8 *)base + row * BYTES_PER_SCANLINE + first_byte;

    for (r = 0; r < length; r++) {
        if (first_byte == last_byte) {
            loc[0] &= ~ (first_mask & last_mask);
        } else {
            loc[0] &= ~ first_mask;
            for (b = 1; b < last_byte - first_byte; b++) {
                loc[b] = 0;
            }
            loc[last_byte - first_byte] &= ~ last_mask;
        }
        loc += BYTES_PER_SCANLINE;
    }
}

void plotPixel(UINT32 *base, int row, int col)
{
    UINT8 *byte_base = (UINT8 *)base;

    if (row >= 0 && row < SCREEN_HEIGHT && col >= 0 && col < SCREEN_WIDTH) {
        byte_base[row * BYTES_PER_SCANLINE + (col >> 3)] |= 0x80 >> (col & 7);
    }
}

void plotHorizontalLine(UINT32 *base, int row, int col, UINT16 length)
{
    UINT8 *loc;
    UINT8 first_mask, last_mask;
    int first_byte, last_byte;
    int b;

    if (row < 0 || row >= SCREEN_HEIGHT || col >= SCREEN_WIDTH || length == 0) {
        return;
    }
    if (col < 0) {
        if (length <= -col) return;
        length += col;
        col = 0;
    }
    if (length > SCREEN_WIDTH - col) {
        length = SCREEN_WIDTH - col;
    }

    first_byte = col >> 3;
    last_byte = (col + length - 1) >> 3;
    first_mask = 0xFF >> (col & 7);
    last_mask = 0xFF << (7 - ((col + length - 1) & 7));
    loc = (UINT8 *)base + row * BYTES_PER_SCANLINE + first_byte;

    if (first_byte == last_byte) {
        *loc |= first_mask & last_mask;
    } else {
        *loc++ |= first_mask;
        for (b = first_byte + 1; b < last_byte; b++) {
            *loc++ = 0xFF;
        }
        *loc |= last_mask;
    }
}

void plotVerticalLine(UINT32 *base, int row, int col, UINT16 length)
{
    UINT8 *loc;
    UINT8 mask;
    int r;

    if (col < 0 || col >= SCREEN_WIDTH || row >= SCREEN_HEIGHT || length == 0) {
        return;
    }
    if (row < 0) {
        if (length <= -row) return;
        length += row;
        row = 0;
    }
    if (length > SCREEN_HEIGHT - row) {
        length = SCREEN_HEIGHT - row;
    }

    mask = 0x80 >> (col & 7);
    loc = (UINT8 *)base + row * BYTES_PER_SCANLINE + (col >> 3);
    for (r = 0; r < length; r++) {
        *loc |= mask;
        loc += BYTES_PER_SCANLINE;
    }
}

void plotLine(UINT32 *base, int start_row, int start_col, int end_row, int end_col)
{
    UINT8 *byte_base;
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

    if (delta_row < 0) {
        delta_row = -delta_row;
        step_row = -1;
    }
    else {
        step_row = 1;
    }

    if (delta_col < 0) {
        delta_col = -delta_col;
        step_col = -1;
    }
    else {
        step_col = 1;
    }

    error = delta_col - delta_row;
    curr_row = start_row;
    curr_col = start_col;

    while (1) {
        if (curr_row >= 0 && curr_row < SCREEN_HEIGHT && curr_col >= 0 && curr_col < SCREEN_WIDTH) {
            byte_base[curr_row * BYTES_PER_SCANLINE + (curr_col >> 3)] |= 0x80 >> (curr_col & 7);
        }

        if (curr_row == end_row && curr_col == end_col) {
            break;
        }

        doubled_error = error + error;

        if (doubled_error > -delta_row) {
            error -= delta_row;
            curr_col += step_col;
        }

        if (doubled_error < delta_col) {
            error += delta_col;
            curr_row += step_row;
        }
    }
}

void plotRectangle(UINT32 *base, int row, int col, UINT16 length, UINT16 width)
{
    UINT8 *loc;
    UINT8 first_mask, last_mask;
    int first_byte, last_byte;
    int r, b;

    if (length == 0 || width == 0 || row >= SCREEN_HEIGHT || col >= SCREEN_WIDTH) {
        return;
    }
    if (row < 0) {
        if (length <= -row) {
            return;
        }
        length += row;
        row = 0;
    }
    if (col < 0) {
        if (width <= -col) {
            return;
        }
        width += col;
        col = 0;
    }
    if (length > SCREEN_HEIGHT - row) {
        length = SCREEN_HEIGHT - row;
    }
    if (width > SCREEN_WIDTH - col) {
        width = SCREEN_WIDTH - col;
    }

    first_byte = col >> 3;
    last_byte = (col + width - 1) >> 3;
    first_mask = 0xFF >> (col & 7);
    last_mask = 0xFF << (7 - ((col + width - 1) & 7));
    loc = (UINT8 *)base + row * BYTES_PER_SCANLINE + first_byte;

    for (r = 0; r < length; r++) {
        if (first_byte == last_byte) {
            loc[0] |= (first_mask & last_mask);
        } else {
            loc[0] |= first_mask;
            for (b = 1; b < last_byte - first_byte; b++) {
                loc[b] = 0xFF;
            }
            loc[last_byte - first_byte] |= last_mask;
        }
        loc += BYTES_PER_SCANLINE;
    }
}

void plotSquare(UINT32 *base, int row, int col, UINT16 side)
{
    UINT8 *byte_base;
    UINT8 mask;
    int curr_row;
    int curr_col;

    byte_base = (UINT8 *)base;

    for (curr_row = row; curr_row < row + (int)side; curr_row++) {
        for (curr_col = col; curr_col < col + (int)side; curr_col++) {
            if (curr_row >= 0 && curr_row < SCREEN_HEIGHT && curr_col >= 0 && curr_col < SCREEN_WIDTH) {
                mask = 1 << (BITS_PER_BYTE - 1 - (curr_col & (BITS_PER_BYTE - 1)));

                byte_base[curr_row * BYTES_PER_SCANLINE + (curr_col >> 3)] |= mask;
            }
        }
    }
}

void plotTriangle(UINT32 *base, int row, int col, UINT16 triangle_base, UINT16 height, UINT8 direction)
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

    if (height == 0 || triangle_base == 0) {
        return;
    }

    for (curr_row = 0; curr_row < height; curr_row++) {
        if (direction == 0 || direction == 1) {
            span = ((curr_row + 1) * triangle_base + height - 1) / height;
        }
        else {
            span = ((height - curr_row) * triangle_base + height - 1) / height;
        }

        if (direction == 0 || direction == 2) {
            start_col = col;
        }
        else {
            start_col = col - span + 1;
        }

        if (direction == 0 || direction == 1) {
            screen_row = row + curr_row;
        }
        else {
            screen_row = row - curr_row;
        }

        for (curr_col = 0; curr_col < span; curr_col++) {
            screen_col = start_col + curr_col;

            if (screen_row >= 0 && screen_row < SCREEN_HEIGHT && screen_col >= 0 && screen_col < SCREEN_WIDTH) {
                mask = 1 << (BITS_PER_BYTE - 1 - (screen_col & (BITS_PER_BYTE - 1)));

                byte_base[screen_row * BYTES_PER_SCANLINE + (screen_col >> 3)] |= mask;
            }
        }
    }
}

void plot8bitBitmap(UINT32 *base, int row, int col, const UINT8 *bitmap, UINT16 height)
{
    UINT8 *loc;
    int r;
    int shift = col & 7; /* col % 8 */

    if (col < 0 || col >= SCREEN_WIDTH || row >= SCREEN_HEIGHT || height == 0) {
        /* Out of bounds; return early */
        return;
    }
    if (row < 0) {
        if (height <= -row) return;
        bitmap -= row;
        height += row;
        row = 0;
    }
    if (height > SCREEN_HEIGHT - row) {
        height = SCREEN_HEIGHT - row;
    }

    loc = (UINT8 *)base + row * BYTES_PER_SCANLINE + (col >> 3);
    for (r = 0; r < height; r++) {
        *loc |= bitmap[r] >> shift;
        if (shift != 0 && (col >> 3) + 1 < BYTES_PER_SCANLINE) {
            loc[1] |= bitmap[r] << (8 - shift);
        }
        loc += BYTES_PER_SCANLINE;
    }
}

void plot16bitBitmap(UINT32 *base, int row, int col, const UINT16 *bitmap, UINT16 height)
{
    UINT16 *loc;
    int r;
    int shift = col & 15; /* col % 16 */

    if (col < 0 || col >= SCREEN_WIDTH || row >= SCREEN_HEIGHT || height == 0) {
        /* Out of bounds; return early */
        return;
    }
    if (row < 0) {
        if (height <= -row) return;
        bitmap -= row;
        height += row;
        row = 0;
    }
    if (height > SCREEN_HEIGHT - row) {
        height = SCREEN_HEIGHT - row;
    }

    loc = (UINT16 *)base + row * WORDS_PER_SCANLINE + (col >> 4);
    for (r = 0; r < height; r++) {
        *loc |= bitmap[r] >> shift;
        if (shift != 0 && (col >> 4) + 1 < WORDS_PER_SCANLINE) {
            loc[1] |= bitmap[r] << (16 - shift);
        }
        loc += WORDS_PER_SCANLINE;
    }
}

void plot32bitBitmap(UINT32 *base, int row, int col, const UINT32 *bitmap, UINT16 height)
{
    UINT32 *loc;
    int r;
    int shift = col & 31; /* col % 32 */

    if (col < 0 || col >= SCREEN_WIDTH || row >= SCREEN_HEIGHT || height == 0) {
        /* Out of bounds; return early */
        return;
    }
    if (row < 0) {
        if (height <= -row) return;
        bitmap -= row;
        height += row;
        row = 0;
    }
    if (height > SCREEN_HEIGHT - row) {
        height = SCREEN_HEIGHT - row;
    }

    loc = (UINT32 *)base + row * LONGS_PER_SCANLINE + (col >> 5);
    for (r = 0; r < height; r++) {
        *loc |= bitmap[r] >> shift;
        if (shift != 0 && (col >> 5) + 1 < LONGS_PER_SCANLINE) {
            loc[1] |= bitmap[r] << (32 - shift);
        }
        loc += LONGS_PER_SCANLINE;
    }
}


void plotCharacter(UINT32 *base, int row, int col, char ch)
{
    const UINT8 *glyph;
    UINT8 *loc;
    UINT8 bits;
    int i, j;
    int curr_row, curr_col;
    int shift;

    if (!IS_PRINTABLE(ch) || row >= SCREEN_HEIGHT || row + FONT_HEIGHT <= 0 || col >= SCREEN_WIDTH || col + BITS_PER_BYTE <= 0) {
        return;
    }

    glyph = GLYPH_START(ch);
    shift = col & 7;

    for (i = 0; i < FONT_HEIGHT; i++) {
        curr_row = row + i;
        if (curr_row < 0 || curr_row >= SCREEN_HEIGHT || glyph[i] == 0) {
            continue;
        }

        if (col >= 0 && col + BITS_PER_BYTE <= SCREEN_WIDTH) {
            loc = (UINT8 *)base + curr_row * BYTES_PER_SCANLINE + (col >> 3);
            bits = glyph[i];
            *loc |= bits >> shift;
            if (shift != 0 && col + BITS_PER_BYTE < SCREEN_WIDTH) {
                loc[1] |= bits << (BITS_PER_BYTE - shift);
            }
        } else {
            for (j = 0; j < BITS_PER_BYTE; j++) {
                curr_col = col + j;
                if (curr_col >= 0 && curr_col < SCREEN_WIDTH && (glyph[i] & (0x80 >> j))) {
                    loc = (UINT8 *)base + curr_row * BYTES_PER_SCANLINE + (curr_col >> 3);
                    *loc |= 0x80 >> (curr_col & 7);
                }
            }
        }
    }
}

void plotString(UINT32 *base, int row, int col, char *ch)
{
    int curr_col = col;
    while (*ch != '\0') {
        if (*ch == '\n') {
            row += FONT_HEIGHT;
            curr_col = col;
        } else if (*ch == '\r') {
            curr_col = col;
        } else if (IS_PRINTABLE(*ch)) {
            plotCharacter(base, row, curr_col, *ch);
            curr_col += BITS_PER_BYTE;
        }
        ch++;
    }
}