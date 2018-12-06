#pragma once
#include "Entity.h"

class MenuElement :
	public Entity
{
private:

	const std::string Identifier;

	void* NextWindow;

public:

	void SetNextWindow(void*);

	MenuElement(OutBuffer titel, const std::string indentifier, SMALL_RECT dimensoins);
	~MenuElement();

	inline std::string GetIdentifier() { return Identifier; }
	inline void* _GetNextWindow() {return NextWindow; }

private:



};