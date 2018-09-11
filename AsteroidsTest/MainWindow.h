#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <Windows.h>

class MainWindow
{
public:
	MainWindow(HINSTANCE hInstance);
	~MainWindow();

	HWND GetHandle() const;

private:
	MainWindow(const MainWindow &);
	void operator=(const MainWindow &);

	void CreateClass();
	void DestroyClass();
	void CreateMainWindow();
	void DestroyMainWindow();

	static LRESULT CALLBACK MessageCallback(HWND hwnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam);

	HINSTANCE moduleInstance_;
	ATOM windowClass_;
	HWND window_;
	static const char *className_;
};

#endif // MAINWINDOW_H_INCLUDED
