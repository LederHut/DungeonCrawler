#pragma once
#include "Entity.h"

class Terrain :
	public Entity
{
private:

	COLOR_INFO ColorInfo;

public:

	Terrain(SMALL_RECT pos, const std::string indentifier, WORD attribute, bool b = 1);
	~Terrain();

	inline COLOR_INFO GetColorInfo() { return ColorInfo; }

private:



};

