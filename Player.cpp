#include "Player.h"



Player::Player(SMALL_RECT pos, std::string indentifier, WORD attribute, bool b)
	:Entity(pos)
{
	SetActive(b);

	MainOutBuffer.append(indentifier);
	Length = (unsigned int)MainOutBuffer.length();
	Heigth = 1;

	Dimensions.Right = Dimensions.Left;
	Dimensions.Bottom = Dimensions.Top;

	ColorInfo.Length = Length;
	ColorInfo.Coord = {Dimensions.Left,Dimensions.Top};
	ColorInfo.Attribute[0] = attribute;
}

Player::~Player()
{
}

void Player::Update()
{

	Movement();

}

void Player::Movement()
{

	for (auto itr = KeyEvents.begin(); itr != KeyEvents.end(); itr++)
	{
		if ('w' == itr->uChar.AsciiChar)
		{
			if (Dimensions.Top == Boundaries.Top)
			{
				KeyEvents.erase(itr);
				break;
			}
			else
			{
				Dimensions.Top--;
				Dimensions.Bottom--;
				ColorInfo.Coord.Y--;
			}
			KeyEvents.erase(itr);
			break;
		}
		else if ('a' == itr->uChar.AsciiChar)
		{
			if (Dimensions.Top == Boundaries.Top)
			{
				KeyEvents.erase(itr);
				break;
			}
			else
			{
				Dimensions.Left--;
				Dimensions.Right--;
				ColorInfo.Coord.X--;
			}
			KeyEvents.erase(itr);
			break;
		}
		else if ('s' == itr->uChar.AsciiChar)
		{
			if (Dimensions.Top == Boundaries.Top)
			{
				KeyEvents.erase(itr);
				break;
			}
			else
			{
				Dimensions.Top++;
				Dimensions.Bottom++;
				ColorInfo.Coord.Y++;
			}
			KeyEvents.erase(itr);
			break;
		}
		else if ('d' == itr->uChar.AsciiChar)
		{
			if (Dimensions.Top == Boundaries.Top)
			{
				KeyEvents.erase(itr);
				break;
			}
			else
			{
				Dimensions.Left++;
				Dimensions.Right++;
				ColorInfo.Coord.X++;
			}
			KeyEvents.erase(itr);
			break;
		}
	}

}
