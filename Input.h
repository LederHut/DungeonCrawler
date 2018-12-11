#pragma once

#include "Utility.h"

class Input
{
private:

	static INPUT_RECORD _ir[MAX_INPUT_READS];
	static DWORD InputsRead;

public:

	static bool bFree;

	static std::vector<KEY_EVENT_RECORD> KeyEvents;
	static std::vector<MOUSE_EVENT_RECORD> MouseEvents;

	Input();
	~Input();

	void PeekInput(HANDLE& inhandle);
	void ClearInputBuffer(HANDLE& inhandle);

private:

	void EvaluateInput();

};

