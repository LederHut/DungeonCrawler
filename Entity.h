#pragma once

#include "Utility.h"

class Entity
{
	int test;
protected:
	
	OutBuffer MainOutBuffer;

	SMALL_RECT Dimensions;

	unsigned int Length,
				 Heigth;

	bool Active{ 0 };

public:

	Entity(SMALL_RECT);
	~Entity();

	inline void SetActive(bool b) { Active = b; }

	inline OutBuffer GetMainOutBuffer() { return MainOutBuffer; }
	inline SMALL_RECT GetDimensions() { return Dimensions; }
	inline unsigned GetHeigth() { return Heigth; }
	inline unsigned GetLength() { return Length; }
	inline bool* GetPToActive() { return &Active; }

private:

};

