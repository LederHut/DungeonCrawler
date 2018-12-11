#include "Terrain.h"


Terrain::Terrain(SMALL_RECT pos, const std::string indentifier, WORD attribute, bool b)
	:Entity(pos)
{

	SetActive(b);

	MainOutBuffer.append(indentifier);
	Length = (unsigned int)MainOutBuffer.length();
	Heigth = 1;

	Dimensions.Right = Dimensions.Left;
	Dimensions.Bottom = Dimensions.Top;

	ColorInfo.Length = Length;
	ColorInfo.Coord = { Dimensions.Left,Dimensions.Top };
	ColorInfo.Attribute[0] = attribute;

}

Terrain::~Terrain()
{
}
