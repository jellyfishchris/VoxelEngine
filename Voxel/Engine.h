#ifndef ENGINE_H
#define ENGINE_H

#include "Renderer.h"
#include "InputHandler.h"
#include <Windows.h>

class Engine
{
	public:
		Engine(void);
		~Engine(void);

		virtual void HandleEvents(float dt) = 0;
		void GameLoop();

	private:
		void Render(float dt);
		void Update();
	protected:
		Renderer* m_renderer;
		InputHandler* m_input;

		unsigned int MAX_UPDATES_PER_SECOND;// = 25; //fix /* !!! */
		unsigned int MAX_CONSECUTIVE_UPDATES;// = 5; //fix /* !!! */
		unsigned int SKIP_TICKS;// = 1000/MAX_UPDATES_PER_SECOND; //fix /* !!! */
};

#endif
