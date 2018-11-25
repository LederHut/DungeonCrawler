
#include "TextWindow.h"


TextWindow::TextWindow(std::string title, SMALL_RECT dimensions)
	:WinInfo(title,dimensions),
	 TextHistory(0)
{
	Utility::DoBorder(WinInfo.Title, WinInfo.MainOutBuffer , WinInfo.OuterDimensions);
}


TextWindow::~TextWindow()
{

}

void TextWindow::WriteLine(std::string text)
{
	if (text != "")
	{
		DoLine(text);
	}
	else { return; } //TODO: Error Handling
	
}

void TextWindow::WriteText(std::string text)
{
	if (text != "")
	{
		DoText(text);
	}
	else { return; } //TODO: Error Handling
}

void TextWindow::WriteStaticText(STATIC_TEXT st)
{
	DoLine(st);
}

//FIX: Stackoverflow when outputing to long string for the textwindow to show.
//FIX: Calling the WriteText func twice in the same loop will kinda break the text output.
void TextWindow::DoText(std::string text) 
{
	unsigned z(0);

	std::string str("> ");
	str.append(text);

	StringLengthHistory.push_back(str.length());
	
	if (WinInfo.InnerHeigth > (unsigned)((float)TextHistory + (float)str.length() / (float)WinInfo.InnerLength))
	{
		for (; z < str.length(); TextHistory++)
		{
			for (size_t x = 0; x <  WinInfo.InnerLength;)
			{
				WinInfo.SecondOutBuffer[(TextHistory * WinInfo.InnerLength) + x] = str[z];
				if (z < str.length())
				{
					x++;
					z++;
				}
				else
				{
					break;
				}
				
			}
		}
		
	}
	else
	{
		unsigned textheigth((unsigned)((float)StringLengthHistory[0] / (float)WinInfo.InnerLength));

		WinInfo.SecondOutBuffer.erase(0, WinInfo.InnerLength * (textheigth == 0 ? 1 : textheigth));
		WinInfo.SecondOutBuffer.resize(WinInfo.InnerDimensions.Bottom * WinInfo.InnerDimensions.Right, ' ');
		

		TextHistory -= textheigth == 0 ? 1 : textheigth;

		StringLengthHistory.erase(StringLengthHistory.begin());

		return;
	}
}

void TextWindow::DoLine(std::string text)
{
	unsigned z(0);

	std::string str = "> ";
	str.append(text);

	if (TextHistory != WinInfo.InnerHeigth - 1)
	{
		for (size_t x = 0; x < str.length(); x++)
		{
			WinInfo.SecondOutBuffer[(TextHistory * WinInfo.InnerLength + 1) + x] = str[z];
			z++;
		}
		TextHistory++;
	}
	else
	{
		WinInfo.SecondOutBuffer.erase(0, WinInfo.InnerLength);
		WinInfo.SecondOutBuffer.resize(WinInfo.InnerDimensions.Bottom * WinInfo.InnerDimensions.Right, ' ');

		TextHistory--;

		return;
	}
}
	
void TextWindow::DoLine(STATIC_TEXT st)
{
	std::string str = st.Text;

	for (size_t y = 0; y < st.TextHeigth; y++)
	{
		for (size_t x = 0; x < str.length(); x++)
		{
			WinInfo.SecondOutBuffer[(y * WinInfo.InnerLength + 1) + x] = str[x];
		}
	}
}
