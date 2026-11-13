#include <osbind.h>

#include "TYPES.H"
#include "raster.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
static void waitForKey(void)
{
    Cconin();
}

static void clearAfterCase(UINT32 *base)
{
    clearScreen(base);
}

static void clearAndWait(UINT32 *base)
{
    clearAfterCase(base);
}

static void tstClearRegion(UINT32 *base)
{
    plotRectangle(base, 0, 0, 10, 10);
    waitForKey();
    clearRegion(base, 0, 0, 10, 10);
    waitForKey();
}

static void tstClearScreen(UINT32 *base)
{
    clearScreen(base);
    waitForKey();
}

static void tstPlotPixel(UINT8 *base)
{
    plotPixel(base, 0, 0);
    waitForKey();
    clearAfterCase((UINT32 *)base);

    plotPixel(base, 0, SCREEN_WIDTH - 1);
    waitForKey();
    clearAfterCase((UINT32 *)base);

    plotPixel(base, SCREEN_HEIGHT - 1, SCREEN_WIDTH - 1);
    waitForKey();
    clearAfterCase((UINT32 *)base);

    plotPixel(base, SCREEN_HEIGHT - 1, 0);
    waitForKey();
    clearAfterCase((UINT32 *)base);
}

static void tstPlotHorizontalLine(UINT32 *base)
{
    plotHorizontalLine(base, 0, 0, 80);
    waitForKey();
    clearAfterCase(base);

    plotHorizontalLine(base, 0, SCREEN_WIDTH - 80, 80);
    waitForKey();
    clearAfterCase(base);

    plotHorizontalLine(base, SCREEN_HEIGHT - 1, SCREEN_WIDTH - 80, 80);
    waitForKey();
    clearAfterCase(base);

    plotHorizontalLine(base, SCREEN_HEIGHT - 1, 0, 80);
    waitForKey();
    clearAfterCase(base);
}

static void tstPlotVerticalLine(UINT32 *base)
{
    plotVerticalLine(base, 0, 0, 80);
    waitForKey();
    clearAfterCase(base);

    plotVerticalLine(base, 0, SCREEN_WIDTH - 1, 80);
    waitForKey();
    clearAfterCase(base);

    plotVerticalLine(base, SCREEN_HEIGHT - 80, SCREEN_WIDTH - 1, 80);
    waitForKey();
    clearAfterCase(base);

    plotVerticalLine(base, SCREEN_HEIGHT - 80, 0, 80);
    waitForKey();
    clearAfterCase(base);
}

static void tstPlotLine(UINT32 *base)
{
    plotLine(base, 0, 0, 80, 80);
    waitForKey();
    clearAfterCase(base);

    plotLine(base, 0, SCREEN_WIDTH - 1, 80, SCREEN_WIDTH - 81);
    waitForKey();
    clearAfterCase(base);

    plotLine(base, SCREEN_HEIGHT - 81, SCREEN_WIDTH - 81, SCREEN_HEIGHT - 1, SCREEN_WIDTH - 1);
    waitForKey();
    clearAfterCase(base);

    plotLine(base, SCREEN_HEIGHT - 81, 0, SCREEN_HEIGHT - 1, 80);
    waitForKey();
    clearAfterCase(base);
}

static void tstPlotRectangle(UINT32 *base)
{
    plotRectangle(base, 0, 0, 40, 80);
    waitForKey();
    clearAndWait(base);

    plotRectangle(base, 0, SCREEN_WIDTH - 80, 40, 80);
    waitForKey();
    clearAndWait(base);

    plotRectangle(base, SCREEN_HEIGHT - 40, SCREEN_WIDTH - 80, 40, 80);
    waitForKey();
    clearAndWait(base);

    plotRectangle(base, SCREEN_HEIGHT - 40, 0, 40, 80);
    waitForKey();
    clearAndWait(base);
}

static void tstPlotSquare(UINT32 *base)
{
    plotSquare(base, 0, 0, 40);
    waitForKey();
    clearAndWait(base);

    plotSquare(base, 0, SCREEN_WIDTH - 40, 40);
    waitForKey();
    clearAndWait(base);

    plotSquare(base, SCREEN_HEIGHT - 40, SCREEN_WIDTH - 40, 40);
    waitForKey();
    clearAndWait(base);

    plotSquare(base, SCREEN_HEIGHT - 40, 0, 40);
    waitForKey();
    clearAndWait(base);
}

static void tstPlotTriangle(UINT32 *base)
{
    plotTriangle(base, 0, 0, 40, 40, 0);
    waitForKey();
    clearAndWait(base);

    plotTriangle(base, 0, SCREEN_WIDTH - 1, 40, 40, 1);
    waitForKey();
    clearAndWait(base);

    plotTriangle(base, SCREEN_HEIGHT - 1, SCREEN_WIDTH - 1, 40, 40, 3);
    waitForKey();
    clearAndWait(base);

    plotTriangle(base, SCREEN_HEIGHT - 1, 0, 40, 40, 2);
    waitForKey();
    clearAndWait(base);
}

static void tstPlot8bitBitmap(UINT8 *base)
{
    static const UINT8 bitmap[] = {
        0x00, 0x0E, 0x0E, 0x1C, 0x78, 0x38, 0x20, 0x00
    };

    plot8bitBitmap(base, 0, 0, bitmap, 8);
    waitForKey();
    clearAfterCase((UINT32 *)base);

    plot8bitBitmap(base, 0, SCREEN_WIDTH - 8, bitmap, 8);
    waitForKey();
    clearAfterCase((UINT32 *)base);

    plot8bitBitmap(base, SCREEN_HEIGHT - 8, SCREEN_WIDTH - 8, bitmap, 8);
    waitForKey();
    clearAfterCase((UINT32 *)base);
    
    plot8bitBitmap(base, SCREEN_HEIGHT - 8, 0, bitmap, 8);
    waitForKey();
    clearAfterCase((UINT32 *)base);
}

static void tstPlot16bitBitmap(UINT16 *base)
{
    static const UINT16 bitmap[] = {
        0x0000, 0x0078, 0x00FC, 0x00FC,
        0x00FC, 0x00F8, 0x01E0, 0x27F0,
        0x3FE0, 0x3FC0, 0x1FC0, 0x0F80,
        0x0780, 0x0480, 0x0480, 0x0000
    };

    plot16bitBitmap(base, 0, 0, bitmap, 16);
    waitForKey();
    clearAfterCase((UINT32 *)base);

    plot16bitBitmap(base, 0, SCREEN_WIDTH - 16, bitmap, 16);
    waitForKey();
    clearAfterCase((UINT32 *)base);

    plot16bitBitmap(base, SCREEN_HEIGHT - 16, SCREEN_WIDTH - 16, bitmap, 16);
    waitForKey();
    clearAfterCase((UINT32 *)base);

    plot16bitBitmap(base, SCREEN_HEIGHT - 16, 0, bitmap, 16);
    waitForKey();
    clearAfterCase((UINT32 *)base);
}

static void tstPlot32bitBitmap(UINT32 *base)
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

    plot32bitBitmap(base, 0, 0, bitmap, 32);
    waitForKey();
    clearAndWait(base);

    plot32bitBitmap(base, 0, SCREEN_WIDTH - 32, bitmap, 32);
    waitForKey();
    clearAndWait(base);

    plot32bitBitmap(base, SCREEN_HEIGHT - 32, SCREEN_WIDTH - 32, bitmap, 32);
    waitForKey();
    clearAndWait(base);

    plot32bitBitmap(base, SCREEN_HEIGHT - 32, 0, bitmap, 32);
    waitForKey();
    clearAndWait(base);
}

static void tstPlotCharacter(UINT8 *base)
{
    plotCharacter(base, 0, 0, 'A');
    waitForKey();
    clearAndWait((UINT32 *)base);

    plotCharacter(base, 0, SCREEN_WIDTH - 8, 'A');
    waitForKey();
    clearAndWait((UINT32 *)base);

    plotCharacter(base, SCREEN_HEIGHT - 8, SCREEN_WIDTH - 8, 'A');
    waitForKey();
    clearAndWait((UINT32 *)base);

    plotCharacter(base, SCREEN_HEIGHT - 8, 0, 'A');
    waitForKey();
    clearAndWait((UINT32 *)base);
}

static void tstPlotString(UINT8 *base)
{
    plotString(base, 0, 0, "TEST");
    waitForKey();
    clearAndWait((UINT32 *)base);

    plotString(base, 0, SCREEN_WIDTH - 32, "TEST");
    waitForKey();
    clearAndWait((UINT32 *)base);

    plotString(base, SCREEN_HEIGHT - 8, SCREEN_WIDTH - 32, "TEST");
    waitForKey();
    clearAndWait((UINT32 *)base);

    plotString(base, SCREEN_HEIGHT - 8, 0, "TEST");
    waitForKey();
    clearAndWait((UINT32 *)base);
}


int main(void){
    UINT32 *base;

    base = Physbase();

    tstClearRegion(base);
    tstClearScreen(base);
    tstPlotPixel((UINT8 *)base);
    tstPlotHorizontalLine(base);
    tstPlotVerticalLine(base);
    tstPlotLine(base);
    tstPlotRectangle(base);
    tstPlotSquare(base);
    tstPlotTriangle(base);
    tstPlot8bitBitmap((UINT8 *)base);
    tstPlot16bitBitmap((UINT16 *)base);
    tstPlot32bitBitmap(base);
    tstPlotCharacter((UINT8 *)base);
    tstPlotString((UINT8 *)base);

    clearScreen(base);
    return 0;
}