#include "MainWindow.h"

const char *MainWindow::className_ = "AsteroidsWindowClass";

MainWindow::MainWindow(HINSTANCE hInstance) :
	moduleInstance_(hInstance)
{
	CreateClass();
	CreateMainWindow();
}

MainWindow::~MainWindow()
{
	DestroyMainWindow();
	DestroyClass();
}

HWND MainWindow::GetHandle() const
{
	return window_;
}

void MainWindow::CreateClass()
{
	WNDCLASSEX classDesc;
	ZeroMemory(&classDesc, sizeof(classDesc));

	classDesc.cbSize = sizeof(classDesc);
	classDesc.style = CS_HREDRAW | CS_VREDRAW;
	classDesc.lpfnWndProc = &MessageCallback;
	classDesc.cbClsExtra = 0;
	classDesc.cbWndExtra = 0;
	classDesc.hInstance = moduleInstance_;
	classDesc.hIcon = 0;
	classDesc.hCursor = 0;
	classDesc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	classDesc.lpszMenuName = 0;
	classDesc.lpszClassName = className_;
	classDesc.hIconSm = 0;

	windowClass_ = RegisterClassEx(&classDesc);
}

void MainWindow::DestroyClass()
{
	UnregisterClass(className_, moduleInstance_);
}

void MainWindow::CreateMainWindow()
{
	//**NOTE: I would have expected WS_EX_CLIENTEDGE to be needed here,
	// but if it's included then is causes the window adjustment to
	// be off by a couple of pixels
	DWORD windowStyleEx =
		WS_EX_WINDOWEDGE |
		WS_EX_APPWINDOW;
	DWORD windowStyle =
		WS_THICKFRAME |
		WS_BORDER |
		WS_SYSMENU |
		WS_MINIMIZEBOX |
		WS_MAXIMIZEBOX;

	RECT clientSize;
	ZeroMemory(&clientSize, sizeof(clientSize));
	clientSize.right = 800;
	clientSize.bottom = 600;
	AdjustWindowRectEx(&clientSize,
		windowStyle,
		true,
		windowStyleEx);

	window_ = CreateWindowEx(
		windowStyleEx,
		(LPCTSTR)windowClass_,
		"Space Invaders",
		windowStyle | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		clientSize.right - clientSize.left,
		clientSize.bottom - clientSize.top,
		0,
		0,
		moduleInstance_,
		0);
}

void MainWindow::DestroyMainWindow()
{
	DestroyWindow(window_);
}

LRESULT MainWindow::MessageCallback(HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	if (uMsg == WM_CLOSE)
	{
		PostQuitMessage(0);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
