#pragma once

#include "pch.h"

#define MAX_X 200
#define MAX_Y 50
#define MAX_INPUT_READS 64

#define iswhole(a) ((int)a == (float)a ? true : false)

typedef std::string OutBuffer;
typedef unsigned FLAG;
typedef void (*ON_KEY_PRESS_CALLBACK_FUNC)();


constexpr char ALPHABET[26] = { 'a','b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
							  'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
							  'u', 'v', 'w', 'x', 'y', 'z' };
							  
							  //'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
							  //'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
							  //'U', 'V', 'W', 'X', 'Y', 'Z'};

struct WINDOW_INFORMATION
{

	OutBuffer MainOutBuffer,
		      SecondOutBuffer;

	SMALL_RECT OuterDimensions,
			   InnerDimensions;

	std::string Title;

	unsigned int OuterLength,
				 OuterHeigth,
				 InnerLength,
				 InnerHeigth;

	bool Active{ 1 };

	WINDOW_INFORMATION(std::string title, SMALL_RECT outerdimensions,bool active = 1)
		:OuterDimensions(outerdimensions),
		 Title(title),
		 Active(active)
	{
		InnerDimensions.Top = OuterDimensions.Top + 1;
		InnerDimensions.Left = OuterDimensions.Left + 1;
		InnerDimensions.Bottom = OuterDimensions.Bottom - 1;
		InnerDimensions.Right = OuterDimensions.Right - 1;

		OuterLength = OuterDimensions.Right - OuterDimensions.Left;
		OuterHeigth = OuterDimensions.Bottom - OuterDimensions.Top;
		InnerLength = InnerDimensions.Right - InnerDimensions.Left + 1;
		InnerHeigth = InnerDimensions.Bottom - InnerDimensions.Top;

		MainOutBuffer.resize(OuterDimensions.Bottom * OuterDimensions.Right, ' ');
		SecondOutBuffer.resize(InnerDimensions.Bottom * InnerDimensions.Right, ' ');
	}
};

struct STATIC_TEXT
{
	std::string Text{" "};

	unsigned LineLength{ 0 },
		     TextHeigth{ 0 };
};

struct COLOR_INFO
{
	DWORD Length;
	WORD Attribute[1];
	COORD Coord;
};

struct ENTITY_INFORMATION
{
	OutBuffer MainOutBuffer;

	SMALL_RECT Dimensions;

	std::string Title;

	unsigned int Length,
				 Heigth;

	ENTITY_INFORMATION(std::string title, SMALL_RECT dimensions)
		:Dimensions(dimensions),
		 Title(title)
	{
		Length = Dimensions.Right - Dimensions.Left;
		Heigth = Dimensions.Bottom - Dimensions.Top;

		MainOutBuffer.resize(Dimensions.Bottom * Dimensions.Right, ' ');
	}
};

struct IN_WINDOW_TEXTFIELD_INFO
{
	OutBuffer MainOutBuffer;

	std::string Text;

	SMALL_RECT Dimensions;

	unsigned int Length,
				 Heigth;

	bool Active{ 0 };

	void SetTextfield(SMALL_RECT dimensions)
	{
		Dimensions = dimensions;

		Length = Dimensions.Right - Dimensions.Left;
		Heigth = Dimensions.Bottom - Dimensions.Top;

		MainOutBuffer.resize(Dimensions.Bottom * Dimensions.Right, ' ');
	}

};

enum
{
	MENU_ELEMENT,
	IN_GAME_OBJECT,
	MAP
};

namespace Utility
{
	static void DoBorder(std::string title,OutBuffer &outbuffer, SMALL_RECT outerdimensions)
	{
		OutBuffer temp;
		temp.resize(outbuffer.length(),' ');

		unsigned length(outerdimensions.Right - outerdimensions.Left),
			     height(outerdimensions.Bottom - outerdimensions.Top);

		if (title.length() > length)
		{
			printf("The title is to long for the TextWindow!");
			return;
		}

		for (size_t y = 0; y < height; y++)
		{
			
			temp[(y * length) + 0] = '|';
			temp[(y * length) + length] = '|';

			if (y == 0 || y == height -1)
			{
				
				for (size_t i = 1; i < length; i++)
				{
					temp[(y * length) + i] = '~';
				}
					
				if (y == 0)
				{
					temp.replace((y * length)+1, title.length(), title);
				}
			}
		}
		outbuffer = temp;
	}

	// # Set an OutBuffer in the scope of the DesOutBuffer.
	// # Thus the dimensions must be in trems of the new scope.
	static void SetOutBuffer(OutBuffer &outbufferdes,
							 unsigned bufferdeslength,
							 OutBuffer frombuffer,
							 SMALL_RECT frombufferdestination,
							 unsigned frombufferlength,
							 unsigned frombufferheight)
	{
		for (size_t y = 0; y != frombufferheight; y++)
		{
			for (size_t x = 0; x != frombufferlength; x++)
			{
				outbufferdes[((y + frombufferdestination.Top) * bufferdeslength) + (x + frombufferdestination.Left)] = frombuffer[x];
			}
		}

	}

	static STATIC_TEXT ToStaticText(std::vector<bool> data)
	{
		STATIC_TEXT st;

		unsigned int n(0);

		for (auto i = data.begin(); i != data.end(); i++)
		{
			bool b = *i;

			if (b)
			{
				st.Text = "1";
					 
			}
			else
			{
				st.Text = "0";
			}
			n++;
		}
		st.TextHeigth = n;
		st.LineLength = 0;
		n = 0;

		return st;
	}

}