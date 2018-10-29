#pragma once

#include <Windows.h>
#include <stdio.h>

#include "ConsoleHandling.h"
 
#define MAX_X 800
#define MAX_Y 800

class CWindow : private ConsoleHandling
{
private:
	
	HANDLE hChildOutputR,
		   hChildOutputW,
		   hChildInputR,
		   hChildinputW;

	STARTUPINFO SI;
	PROCESS_INFORMATION PI;
	SECURITY_ATTRIBUTES SA;

public:

	CWindow();
	~CWindow();
	void createConsoleWindow();

private:

};