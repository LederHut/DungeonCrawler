#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

#define MAX_X 200
#define MAX_Y 50
#define MAX_INPUTS_READ 128

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
		      SecondOutBuffer; //TODO: wirte a overide for the -> operator to sync the second and main buffer on use.

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
		InnerLength = InnerDimensions.Right - InnerDimensions.Left;
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
					temp.replace((y * length) + 1, title.length(), title);
				}
			}
		}
		outbuffer = temp;
	}

	static void SetOutBuffer(OutBuffer &outbufferdes,
							 unsigned bufferdeslength,
							 OutBuffer frombuffer,
							 SMALL_RECT frombufferdestination,
							 unsigned frombufferlength,
							 unsigned frombufferheight)
	{
		for (size_t y = 0; y < frombufferheight; y++)
		{
			for (size_t x = 0; x < frombufferlength; x++)
			{
				outbufferdes[((y + frombufferdestination.Top) * bufferdeslength) + (x + frombufferdestination.Left)] = frombuffer[x];
			}
		}

	}

	static bool IsKeyPressed(char character, bool* pressedkeys) 
	{
		switch (character)
		{
		default:
			return false;
		case 'a':
			if (pressedkeys[0] == true)
			{
				pressedkeys[0] = false;
				return true;
			}
			else { return false; }
		case 'b':
			if (pressedkeys[1] == true)
			{
				pressedkeys[1] = false;
				return true;
			}
			else { return false; }
		case 'c':
			if (pressedkeys[2] == true)
			{
				pressedkeys[2] = false;
				return true;
			}
			else { return false; }
		case 'd':
			if (pressedkeys[3] == true)
			{
				pressedkeys[3] = false;
				return true;
			}
			else { return false; }
		case 'e':
			if (pressedkeys[4] == true)
			{
				pressedkeys[4] = false;
				return true;
			}
			else { return false; }
		case 'f':
			if (pressedkeys[5] == true)
			{
				pressedkeys[5] = false;
				return true;
			}
			else { return false; }
		case 'g':
			if (pressedkeys[6] == true)
			{
				pressedkeys[6] = false;
				return true;
			}
			else { return false; }
		case 'h':
			if (pressedkeys[7] == true)
			{
				pressedkeys[7] = false;
				return true;
			}
			else { return false; }
		case 'i':
			if (pressedkeys[8] == true)
			{
				pressedkeys[8] = false;
				return true;
			}
			else { return false; }
		case 'j':
			if (pressedkeys[9] == true)
			{
				pressedkeys[9] = false;
				return true;
			}
			else { return false; }
		case 'k':
			if (pressedkeys[10] == true)
			{
				pressedkeys[10] = false;
				return true;
			}
			else { return false; }
		case 'l':
			if (pressedkeys[11] == true)
			{
				pressedkeys[11] = false;
				return true;
			}
			else { return false; }
		case 'm':
			if (pressedkeys[12] == true)
			{
				pressedkeys[12] = false;
				return true;
			}
			else { return false; }
		case 'n':
			if (pressedkeys[13] == true)
			{
				pressedkeys[13] = false;
				return true;
			}
			else { return false; }
		case 'o':
			if (pressedkeys[14] == true)
			{
				pressedkeys[14] = false;
				return true;
			}
			else { return false; }
		case 'p':
			if (pressedkeys[15] == true)
			{
				pressedkeys[15] = false;
				return true;
			}
			else { return false; }
		case 'q':
			if (pressedkeys[16] == true)
			{
				pressedkeys[16] = false;
				return true;
			}
			else { return false; }
		case 'r':
			if (pressedkeys[17] == true)
			{
				pressedkeys[17] = false;
				return true;
			}
			else { return false; }
		case 's':
			if (pressedkeys[18] == true)
			{
				pressedkeys[18] = false;
				return true;
			}
			else { return false; }
		case 't':
			if (pressedkeys[19] == true)
			{
				pressedkeys[19] = false;
				return true;
			}
			else { return false; }
		case 'u':
			if (pressedkeys[20] == true)
			{
				pressedkeys[20] = false;
				return true;
			}
			else { return false; }
		case 'v':
			if (pressedkeys[21] == true)
			{
				pressedkeys[21] = false;
				return true;
			}
			else { return false; }
		case 'w':
			if (pressedkeys[22] == true)
			{
				pressedkeys[22] = false;
				return true;
			}
			else { return false; }
		case 'x':
			if (pressedkeys[23] == true)
			{
				pressedkeys[23] = false;
				return true;
			}
			else { return false; }
		case 'y':
			if (pressedkeys[24] == true)
			{
				pressedkeys[24] = false;
				return true;
			}
			else { return false; }
		case 'z':
			if (pressedkeys[25] == true)
			{
				pressedkeys[25] = false;
				return true;
			}
			else { return false; }

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