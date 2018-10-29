
#include "MenuWindow.h"


MenuWindow::MenuWindow(std::string title, SMALL_RECT dimensions,bool active)
	:WinInfo(title,dimensions,active)
{
	Utility::DoBorder(WinInfo.Title, WinInfo.MainOutBuffer, WinInfo.OuterDimensions);
}

MenuWindow::~MenuWindow()
{
}

void MenuWindow::AddMenuElement(MenuElement* me)
{
	Utility::SetOutBuffer(WinInfo.SecondOutBuffer,
						  WinInfo.InnerLength,
						  me->GetMainOutBuffer(),
						  me->GetDimensions(),
						  me->GetLength(),
						  me->GetHeigth());

	MenuElements.push_back(me);

}

//TODO: Refacture the DoText func in the TextWindow.cpp for this purpose.
void MenuWindow::AddText()
{
	
	/*unsigned z(0),
		t(0);

	float f(0.0f);

	std::string str = "> ";
	str.append(text);

	StringLengthHistory.push_back(str.length());

	if (WinInfo.InnerHeigth - 1 > (unsigned)((float)TextHistory + (float)str.length() / (float)WinInfo.InnerLength))
	{
		for (; z < str.length(); TextHistory++)
		{
			for (size_t x = 0; x < WinInfo.InnerLength;)
			{
				WinInfo.SecondOutBuffer[(TextHistory * WinInfo.InnerLength + 1) + x] = str[z];
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
		unsigned temp((unsigned)((float)StringLengthHistory[0] / (float)WinInfo.InnerLength));

		WinInfo.SecondOutBuffer.erase(0, WinInfo.InnerLength * (temp == 0 ? 1 : temp));
		WinInfo.SecondOutBuffer.resize(WinInfo.InnerDimensions.Bottom * WinInfo.InnerDimensions.Right, ' ');


		TextHistory -= temp == 0 ? 1 : temp;

		StringLengthHistory.erase(StringLengthHistory.begin());

		return;
	}*/
}
