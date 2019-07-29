#include "math.h"


void draw_rectangle(unsigned *buf, unsigned svw, unsigned svh,
	unsigned x, unsigned y, unsigned width, unsigned height, unsigned color)
{
	for (unsigned i = y; i <= y+height && i < svh - 1; i++)
	{
		for (unsigned j = x; j < x+width ; j++)
		{
			buf[i*svw + j] = color;
		}
	}
}