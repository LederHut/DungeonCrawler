#pragma once
#include "Entitys.h"

class Player : public Entitys
{
private:



public:

	Player(SMALL_RECT pos, std::string indentifier, bool b = 0);
	~Player();

	inline SMALL_RECT* GetPToDimensions() { return &Dimensions; };

private:



};

