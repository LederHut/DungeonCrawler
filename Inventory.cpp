#include "Inventory.h"



Inventory::Inventory(SMALL_RECT pos, std::string indentifier, bool b)
	:Entity(pos)
{
	SetActive(b);


}

Inventory::~Inventory()
{
}
