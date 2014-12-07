#include "SDLInputHandler.h"


SDLInputHandler::SDLInputHandler(void)
{
}


SDLInputHandler::~SDLInputHandler(void)
{
}

void SDLInputHandler::PollInput( float dt )
{
	while(SDL_PollEvent(&tempEvent)) {

		std::unique_ptr<InputEvent> e(new InputEvent(tempEvent.type, tempEvent.key.keysym.sym, tempEvent.motion.x, tempEvent.motion.y));
		HandleInput(dt,*e);
	}
}

void SDLInputHandler::HandleInput( float dt, InputEvent& e )
{
	switch(e.GetType()) 
	{
	case SDL_MOUSEMOTION:
		//m_frustumCamera->RotateY((e.motion.x - m_width/2)/10.0f);
		//m_frustumCamera->RotateX((e.motion.y - m_height/2)/10.0f);
		break;
	case SDL_KEYDOWN:
		switch( e.GetKey() )
		{
		case SDLK_ESCAPE:
			
			//m_running = false;
			break;
		case SDLK_w:
			//m_frustumCamera->Translate(m_frustumCamera->Forward());
			break;
		case SDLK_s:
			//m_frustumCamera->Translate(-m_frustumCamera->Forward());
			break;
		case SDLK_a:
			//m_frustumCamera->Translate(-m_frustumCamera->Right());
			break;
		case SDLK_d:
			//m_frustumCamera->Translate(m_frustumCamera->Right());
			break;
		}
		break;
	}
}


