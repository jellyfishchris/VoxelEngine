#ifndef SDLENGINE_H
#define SDLENGINE_H

#include "Engine.h"
#include "SDLInputHandler.h"
#include "SDLRenderer.h"

class SDLEngine : public Engine
{
public:
	SDLEngine(void);
	~SDLEngine(void);
	void HandleEvents(float dt);
};

#endif
