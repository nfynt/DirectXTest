#include "Keyboard.h"

Keyboard::Keyboard()
{
	ZeroMemory(keys_, sizeof(keys_));
}

void Keyboard::Update()
{
	BYTE keyState[256];
	ZeroMemory(keyState, sizeof(keyState));
	GetKeyboardState(keyState);

	const unsigned char HIGH_BIT = 1 << 7;
	for (int i = VK_LBUTTON; i <= VK_OEM_CLEAR; i++)
	{
		bool isDown = (keyState[i] & HIGH_BIT) != 0;
		bool wasDown = (keys_[i] & KEY_STATE_HELD) != 0;
		unsigned char newState = 0;
		if (isDown)
		{
			newState |= KEY_STATE_HELD;
		}
		if (isDown && !wasDown)
		{
			newState |= KEY_STATE_PRESSED;
		}
		if (!isDown && wasDown)
		{
			newState |= KEY_STATE_RELEASED;
		}

		keys_[i] = newState;
	}
}

bool Keyboard::IsKeyPressed(int virtualKey) const
{
	return (keys_[virtualKey] & KEY_STATE_PRESSED) != 0;
}

bool Keyboard::IsKeyHeld(int virtualKey) const
{
	return (keys_[virtualKey] & KEY_STATE_HELD) != 0;
}

bool Keyboard::IsKeyReleased(int virtualKey) const
{
	return (keys_[virtualKey] & KEY_STATE_RELEASED) != 0;
}

unsigned char Keyboard::GetKeyState(int virtualKey) const
{
	return keys_[virtualKey];
}
