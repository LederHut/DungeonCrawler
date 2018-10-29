#include "Entity.h"


Entity::Entity()
{
}

Entity::Entity(OutBuffer str, SMALL_RECT dimensions, FLAG entityflags, unsigned color, std::string identifier)
	:MainOutBuffer(str),
	OuterDimensions(dimensions),
	Indentifier(identifier),
	Active(0),
	Color(color)

{
	if (identifier.length() != 1)
	{
		return;
	}
	if (entityflags == MAP)
	{

		OuterLength = OuterDimensions.Right - OuterDimensions.Left;
		OuterHeigth = OuterDimensions.Bottom - OuterDimensions.Top;

		MainOutBuffer.resize(OuterDimensions.Bottom * OuterDimensions.Right, ' ');

	}
	if (entityflags == IN_GAME_OBJECT)
	{

		//TODO: setup ingame object constructer for example palyer enemy or interactable objects

		OuterLength = 1;
		OuterHeigth = 1;

		OuterDimensions.Right = OuterDimensions.Left;
		OuterDimensions.Bottom = OuterDimensions.Top;
	}
}

Entity::~Entity()
{
}