#ifndef SDLINPUTHANDLER_H
#define SDLINPUTHANDLER_H

#include <iostream>
#include <SDL/SDL.h>
#include <memory>
#include "InputHandler.h"

class SDLInputHandler : public InputHandler
{
	public:
		SDLInputHandler(void);
		~SDLInputHandler(void);

		void PollInput(float dt);
		void HandleInput(float dt, InputEvent& e);
	private:
		SDL_Event tempEvent;
		
};

#endif