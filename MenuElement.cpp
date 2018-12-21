#include "pch.h"
#include "MenuElement.h"


MenuElement::MenuElement(OutBuffer titel, std::string indentifier, SMALL_RECT dimensions):
	Identifier(indentifier),
	isSelected(false),
	NextWindow(nullptr),
	Entity(dimensions)
{
	if (Identifier.length() != 1)
	{
		return;
	}

	MainOutBuffer.append(titel);
	MainOutBuffer.append(("[" + Identifier + "]"));

	IdPos = titel.size() + 1;
	CrossPos = IdPos + 2;
	Length = (SHORT)MainOutBuffer.length();
	Heigth = 1;

	Dimensions.Right = Dimensions.Left;
	Dimensions.Bottom = Dimensions.Top;
}


MenuElement::~MenuElement()
{
}

void MenuElement::SetTerrain(Terrain* t)
{
	MainOutBuffer[IdPos] = t->GetMainOutBuffer()[0];
	MainOutBuffer.append("[ ]");

	ColorInfo.Coord = { IdPos + 1, Dimensions.Top };
	ColorInfo.Attribute[0] = t->GetColorInfo().Attribute[0];
	ColorInfo.Length = 1;

	Length += 3;
}

void MenuElement::SetNextWindow(void* mw)
{
	NextWindow = mw;
}

void MenuElement::Select()
{
	isSelected = true;
	MainOutBuffer[CrossPos] = 'X';
}

void MenuElement::UnSelect()
{
	isSelected = false;
	MainOutBuffer[CrossPos] = ' ';
}
