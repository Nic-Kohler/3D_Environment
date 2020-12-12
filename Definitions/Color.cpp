#include "Color.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

	Color::Color(unsigned short r, unsigned short g, unsigned short b)
	{
		Alpha = 0;
		Red = r;
		Green = g;
		Blue = b;
	}

	Color::Color(unsigned short a, unsigned short r, unsigned short g, unsigned short b)
	{
		Alpha = a;
		Red = r;
		Green = g;
		Blue = b;
	}

	Color::Color(unsigned int hex_argb)
	{
		char buffer[8];
		//itoa(hex_argb, buffer, 16);
		sprintf(buffer, "%X", hex_argb);

		if(strlen(buffer) == 6)
		{
			Alpha = 0;
			Red = (hex_argb & 0xFF0000) >> 16;
			Green = (hex_argb & 0x00FF00) >> 8;
			Blue = (hex_argb & 0x0000FF);
		}
		else if(strlen(buffer) == 8)
		{
			Alpha = (hex_argb & 0xFF000000) >> 24;
			Red = (hex_argb & 0x00FF0000) >> 16;
			Green = (hex_argb & 0x0000FF00) >> 8;
			Blue = (hex_argb & 0x000000FF);
		}
	}

	void Color::Set_RGB(unsigned short r, unsigned short g, unsigned short b)
	{
		Alpha = 0;
		Red = r;
		Green = g;
		Blue = b;
	}

	void Color::Set_RGB(unsigned int hex_rgb)
	{
		Alpha = 0;
		Red = (hex_rgb & 0xFF0000) >> 16;
		Green = (hex_rgb & 0x00FF00) >> 8;
		Blue = (hex_rgb & 0x0000FF);
	}

	void Color::Set_ARGB(unsigned short a, unsigned short r, unsigned short g, unsigned short b)
	{
		Alpha = a;
		Red = r;
		Green = g;
		Blue = b;
	}

	void Color::Set_ARGB(unsigned int hex_argb)
	{
		Alpha = (hex_argb & 0xFF000000) >> 24;
		Red = (hex_argb & 0x00FF0000) >> 16;
		Green = (hex_argb & 0x0000FF00) >> 8;
		Blue = (hex_argb & 0x000000FF);
	}

	unsigned int Color::Get_RGB_Int()
	{
		return ((Red & 0xFF) << 16) + ((Green & 0xFF) << 8) + (Blue & 0xFF);
	}

	unsigned int Color::Get_ARGB_Int()
	{
		return ((Red & 0xFF) << 24) + ((Green & 0xFF) << 16) + ((Blue & 0xFF) << 8) + (Alpha & 0xFF);
	}

	unsigned short Color::Get_Grey_Scale()
	{
		return (unsigned short)round((Red + Green + Blue) / 3);
	}
