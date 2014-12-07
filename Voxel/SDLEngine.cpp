#include "SDLEngine.h"


SDLEngine::SDLEngine(void)
{
	m_renderer = new SDLRenderer();
	m_renderer->Initialize(800,800,60);
	m_input = new SDLInputHandler();
}


SDLEngine::~SDLEngine(void)
{
}

void SDLEngine::HandleEvents( float dt )
{

}
