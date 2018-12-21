#pragma once

#include "Input.h"

class Entity:
	public Input
{
protected:
	
	OutBuffer MainOutBuffer;

	SMALL_RECT Dimensions;

	SHORT Length,
		  Heigth;

	bool Active{ 0 };

public:

	Entity(SMALL_RECT);
	~Entity();

	inline void SetActive(bool b) { Active = b; }

 	virtual void Update(){}

	inline OutBuffer GetMainOutBuffer() { return MainOutBuffer; }
	inline SMALL_RECT GetDimensions() { return Dimensions; }
	inline unsigned GetHeigth() { return Heigth; }
	inline unsigned GetLength() { return Length; }
	inline bool* GetPToActive() { return &Active; }
	inline bool GetActive() { return Active; }

private:

};

