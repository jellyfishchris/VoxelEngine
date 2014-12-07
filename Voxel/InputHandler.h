#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "InputEvent.h"

class InputHandler
{
	public:
		virtual void PollInput(float dt) = 0;
		virtual void HandleInput(float dt, InputEvent& e) = 0;
};

#endif