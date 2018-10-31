#include "Player.h"



Player::Player(SMALL_RECT pos, std::string indentifier, bool b)
	:Entitys(pos)
{
	SetActive(b);

	MainOutBuffer.append(indentifier);
	Length = MainOutBuffer.length();
	Heigth = 1;

	Dimensions.Right = Dimensions.Left;
	Dimensions.Bottom = Dimensions.Top;
}

Player::~Player()
{
}
