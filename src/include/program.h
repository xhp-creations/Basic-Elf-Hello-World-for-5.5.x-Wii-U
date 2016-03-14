#ifndef PROGRAM_H
#define PROGRAM_H
#include "init.h"
#include <gctypes.h>
#include "vpad.h"

#define FULLSCREEN_DRC_X_OFFSET 0 // Offsets to center on DRC and TV if you want to modify drawing functions
#define FULLSCREEN_DRC_Y_OFFSET 0
#define FULLSCREEN_X_OFFSET 213
#define FULLSCREEN_Y_OFFSET 120

extern unsigned int vpad_handle;
extern unsigned int (*VPADRead)(int controller, VPADData *buffer, unsigned int num, int *error);

int memcmp(void *ptr1, void *ptr2, uint32_t length);
void* memcpy(void* dst, const void* src, uint32_t size);
void _osscreeninit();
void _clearscreen();
void _main();

#endif /* PROGRAM_H */