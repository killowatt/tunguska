#pragma once

#include "Common.h"
#include "SDL2/SDL.h"

enum class KeyState
{
	None,
	DownThisFrame,
	UpThisFrame
};

class Input
{
public:
	static uint8 keys[SDL_NUM_SCANCODES];
	static const uint8* keysState;

	static void ClearKeyState();

	static void Update();

	static bool GetKey(SDL_Scancode key);

	static bool GetKeyDown(SDL_Scancode key);

	static bool GetKeyUp(SDL_Scancode key);
};