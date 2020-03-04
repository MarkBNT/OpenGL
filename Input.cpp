#include "Input.h"
#include "Includes.h"

Input * Input::intance = NULL; 

Input::Input()
{
}


Input::~Input()
{
}

bool Input::fTeclas()
{
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				return false;
			}
		}
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			return false;
		}
	}
}

Input * Input::getInstance()
{
	if (instance == NULL)
	{
		instance = new Input();
	}

	return instance;
}
