#pragma once
#include "Entity.h"

class Player : public Entity
{
private:



public:

	Player(SMALL_RECT pos, std::string indentifier, bool b = 0);
	~Player();

	inline SMALL_RECT* GetPToDimensions() { return &Dimensions; };

private:



};

