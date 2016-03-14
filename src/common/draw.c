#include "draw.h"

void flipBuffers()
{
	int buf0_size = OSScreenGetBufferSizeEx(0);
	int buf1_size = OSScreenGetBufferSizeEx(1);
	DCFlushRange((void *)0xF4000000, buf0_size);
	DCFlushRange((void *)0xF4000000 + buf0_size, buf1_size);
	OSScreenFlipBuffersEx(0);
	OSScreenFlipBuffersEx(1);
}

void fillScreen(char r,char g,char b)
{
	uint32_t num = (r << 24) | (g << 16) | (b << 8) | 0;
	OSScreenClearBufferEx(0, num);
	OSScreenClearBufferEx(1, num);
}

void drawString(int x1, int y1, int x2, int y2, char * string)
{
	OSScreenPutFontEx(0, x2, y2, string);
	OSScreenPutFontEx(1, x1, y1, string);
}

// Handles drawing to the TV and DRC at each zoom level
void paintPixel(int x, int y, char r, char g, char b, int zoom)
{
	uint32_t num = (r << 24) | (g << 16) | (b << 8) | 255; // You could pass alpha values, but they have no effect on basic framebuffer graphics, need to get into GX2 graphics to worry about alpha values
	
	if (zoom == 0) { // If you want DRC upscaled to fill TV screen
		int a;
		for (a = 0; a < 2; a++) {
			int x1 = ( ( x * 3 ) / 2 ) + a;
			int y1 = ( ( y * 3 ) / 2 ) + a;
			int x2 = ( ( x * 3 ) / 2 ) + ( 1 - a );
			int y2 = ( ( y * 3 ) / 2 ) + a;
			OSScreenPutPixelEx( 0, x1, y1, num );
			OSScreenPutPixelEx( 0, x2, y2, num );
		}
		OSScreenPutPixelEx( 1, x, y, num );
	}
	
	if (zoom == 1) { // If you just want what is on DRC centered on TV screen with no upscaling
		OSScreenPutPixelEx( 0, x + FULLSCREEN_X_OFFSET, y + FULLSCREEN_Y_OFFSET, num );
		OSScreenPutPixelEx( 1, x, y, num );
	}
}