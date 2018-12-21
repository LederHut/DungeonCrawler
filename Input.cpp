#include "pch.h"
#include "Input.h"

INPUT_RECORD Input::_ir[MAX_INPUT_READS];
DWORD Input::InputsRead;
bool Input::bFree = false;

std::vector<KEY_EVENT_RECORD> Input::KeyEvents;
std::vector<MOUSE_EVENT_RECORD> Input::MouseEvents;

Input::Input()
{
}

Input::~Input()
{
}

void Input::PeekInput(HANDLE& inhandle)
{

	std::this_thread::sleep_for(std::chrono::milliseconds(35));

	if (!PeekConsoleInput(inhandle,
		_ir,
		MAX_INPUT_READS,
		&InputsRead))
	{
		printf("ReadConsoleInput error (%d)", GetLastError());
		return;
	}

	EvaluateInput();

	bFree = true;
}

void Input::ClearInputBuffer(HANDLE& inhandle)
{

	FlushConsoleInputBuffer(inhandle);
	KeyEvents.clear();
	MouseEvents.clear();

}

void Input::EvaluateInput()
{

	for (size_t i = 0; i < InputsRead; i++)
	{
		switch (_ir[i].EventType)
		{
		default:
			break;
		case KEY_EVENT:
			KeyEvents.push_back(_ir[i].Event.KeyEvent);
			break;
		case MOUSE_EVENT:
			MouseEvents.push_back(_ir[i].Event.MouseEvent);
			break;
		}
	}

	std::fill(std::begin(_ir), std::end(_ir),INPUT_RECORD());

}