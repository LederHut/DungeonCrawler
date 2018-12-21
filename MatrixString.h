#pragma once

#include "Entity.h"

class MatrixString :
	public Entity
{
private:

	unsigned int UpdateCounter,
				 MaxUpdates;

	bool Growth,
		 Shift{ 0 };

	SHORT InitialLeft;

public:

	MatrixString(SMALL_RECT dimesnions, bool growth = 0);
	~MatrixString();

	void Update() override;
	void RePopulateMatrixString();

private:



};

