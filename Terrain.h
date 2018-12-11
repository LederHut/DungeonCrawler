#pragma once
#include "Entity.h"

class Terrain :
	public Entity
{
private:

	COLOR_INFO ColorInfo;

public:

	Terrain(SMALL_RECT, const std::string indentifier, WORD attribute, bool b = 1);
	~Terrain();

private:



};

