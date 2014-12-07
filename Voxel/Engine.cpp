#include "Engine.h"


Engine::Engine(void)
{
	MAX_UPDATES_PER_SECOND = 25;    /* !!! */
	MAX_CONSECUTIVE_UPDATES = 5; 	/* !!! */
	SKIP_TICKS = 1000/MAX_UPDATES_PER_SECOND; /* !!! */
}


Engine::~Engine(void)
{
}

void Engine::GameLoop()
{
	DWORD next_tick = GetTickCount();
	unsigned int loops;
	float interpolation;
	
	while( true ) {

		loops = 0;
		while( GetTickCount() > next_tick && loops < MAX_CONSECUTIVE_UPDATES) {
			Update();

			next_tick += SKIP_TICKS;
			loops++;
		}

		interpolation = float( GetTickCount() + SKIP_TICKS - next_tick ) / float( SKIP_TICKS );
		Render( interpolation );
	}
}

void Engine::Update()
{
	m_input->PollInput((float)SKIP_TICKS);
}

void Engine::Render( float dt )
{
	m_renderer->Update(dt);
}
