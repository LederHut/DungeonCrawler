#include "MenuElement.h"


MenuElement::MenuElement(SMALL_RECT dimensions, const std::string indentifier, OutBuffer titel)
	:Identifier(indentifier),
	 Entitys(dimensions)
{
	if (Identifier.length() != 1)
	{
		return;
	}
	MainOutBuffer.append(titel);
	MainOutBuffer.append(("[" + Identifier + "]"));
	Length = MainOutBuffer.length();
	Heigth = 1;

	Dimensions.Right = Dimensions.Left;
	Dimensions.Bottom = Dimensions.Top;
}


MenuElement::~MenuElement()
{
}

void MenuElement::SetNextWindow(void* mw)
{
	NextWindow = mw;
}