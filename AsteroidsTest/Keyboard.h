#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include <Windows.h>

class Keyboard
{
public:

	enum KeyState
	{
		KEY_STATE_NONE = 0,
		KEY_STATE_PRESSED = 1 << 0,
		KEY_STATE_HELD = 1 << 1,
		KEY_STATE_RELEASED = 1 << 2,
	};

	Keyboard();

	void Update();

	bool IsKeyPressed(int virtualKey) const;
	bool IsKeyHeld(int virtualKey) const;
	bool IsKeyReleased(int virtualKey) const;

	unsigned char GetKeyState(int virtualKey) const;

private:

	unsigned char keys_[VK_OEM_CLEAR+1];

};

#endif // KEYBOARD_H_INCLUDED
