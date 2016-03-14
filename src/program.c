#include "program.h"
#include "draw.h"

unsigned int vpad_handle = 0;
unsigned int (*VPADRead)(int controller, VPADData *buffer, unsigned int num, int *error);

int memcmp(void *ptr1, void *ptr2, uint32_t length) // Implement our own memcmp
{
	uint8_t *check1 = (uint8_t*) ptr1;
	uint8_t *check2 = (uint8_t*) ptr2;
	uint32_t i;
	for (i = 0; i < length; i++)
	{
		if (check1[i] != check2[i]) return 1;
	}

	return 0;
}

void* memcpy(void* dst, const void* src, uint32_t size) // Implement our own memcpy
{
	uint32_t i;
	for (i = 0; i < size; i++)
		((uint8_t*) dst)[i] = ((const uint8_t*) src)[i];
	return dst;
}

void _osscreeninit()
{
	OSScreenInit();
	int buf0_size = OSScreenGetBufferSizeEx(0);
	OSScreenSetBufferEx(0, (void *)0xF4000000);
	OSScreenSetBufferEx(1, (void *)0xF4000000 + buf0_size);
}

void _clearscreen()
{
	int ii;
	for( ii = 0; ii < 2; ii++ )
	{
		fillScreen(0, 0, 0);
		flipBuffers();
	}
}

void _main()
{
	void*(*memcpy)(void *dest, void *src, uint32_t length);
	OSDynLoad_FindExport(coreinit_handle, 0, "memcpy", &memcpy);
	
	OSDynLoad_Acquire("vpad.rpl", &vpad_handle);
	OSDynLoad_FindExport(vpad_handle, 0, "VPADRead", &VPADRead);

	_osscreeninit();
	_clearscreen();
	
	fillScreen(0, 0, 0);

	VPADData vpad_data;
	int error;
	while(1)
	{
		VPADRead(0, &vpad_data, 1, &error);
		
		fillScreen(0, 0, 0);
		drawString(0, 0, 0, 0, "Hello World!");
		flipBuffers();
		
		if (vpad_data.btn_trigger & BUTTON_HOME) {
			break;
		}
	}
	_clearscreen();
}
