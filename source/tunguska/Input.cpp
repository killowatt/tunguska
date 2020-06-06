#include "Input.h"

uint8 Input::keys[SDL_NUM_SCANCODES];
const uint8* Input::keysState = nullptr;

void Input::ClearKeyState()
{
	for (uint8& key : keys)
	{
		key = 32;
	}
}

void Input::Update()
{
	keysState = SDL_GetKeyboardState(nullptr);
}

bool Input::GetKey(SDL_Scancode key)
{
	return keysState && keysState[key];
}

bool Input::GetKeyDown(SDL_Scancode key)
{
	return keys[key] == SDL_PRESSED;
}

bool Input::GetKeyUp(SDL_Scancode key)
{
	return keys[key] == SDL_RELEASED;
}