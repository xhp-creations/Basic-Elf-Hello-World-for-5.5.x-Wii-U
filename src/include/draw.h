#ifndef DRAW_H
#define DRAW_H
#include "program.h"
#include <gctypes.h>

void flipBuffers();
void fillScreen(char r, char g, char b);
void drawString(int x1, int y1, int x2, int y2, char * string);
void paintPixel(int x, int y,char r, char g, char b, int zoom);

#endif /* DRAW_H */