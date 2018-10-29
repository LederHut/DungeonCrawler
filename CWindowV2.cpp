#include "CWindowV2.h"

CWindow::CWindow()
{
	SA.nLength = sizeof(SECURITY_ATTRIBUTES);
	SA.bInheritHandle = TRUE;
	SA.lpSecurityDescriptor = NULL;

	CreatePipe(&hChildInputR, &hChildinputW, &SA, 0);
	CreatePipe(&hChildOutputR, &hChildOutputW, &SA, 0);

	ZeroMemory(&SI, sizeof(&SI));
	SI.cb = sizeof(&SI);
	ZeroMemory(&PI, sizeof(PI));
	
	SI.lpTitle = (LPSTR)"DungeonCrawler";
	SI.dwXSize = MAX_X;
	SI.dwYSize = MAX_Y;
	SI.hStdInput = hChildInputR;
	SI.hStdOutput = hChildOutputW;
	SI.hStdError = hChildOutputW;
	SI.dwFlags |= STARTF_USESTDHANDLES;
}

CWindow::~CWindow()
{
	CloseHandle(PI.hProcess);
	CloseHandle(PI.hThread);
}

void CWindow::createConsoleWindow()
{
	if (!CreateProcess
	(
		TEXT("C:\\Windows\\system32\\cmd.exe"),
		NULL,
		NULL,
		NULL,
		TRUE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&SI,
		&PI
	))
	{
		printf_s("CreateProcess failed (%d).\n",GetLastError());
		return;
	}
	
}
