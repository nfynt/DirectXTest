#include <Windows.h>
#include "System.h"

int __stdcall WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	System *systemInstance = new System(hInstance);

	systemInstance->Initialise();
	systemInstance->Test();
	systemInstance->SetNextState("BootState");
	systemInstance->Run();
	systemInstance->Terminate();

	return 0;
}
