#ifndef SDLRENDERER
#define SDLRENDERER


#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Renderer.h"

class SDLRenderer : public Renderer
{
	public:
		SDLRenderer(void);
		~SDLRenderer(void);

		void Initialize(int width, int height, unsigned int fpsCap, std::vector<unsigned int>& settings);
		virtual void Initialize(int width, int height, unsigned int fpsCap);
		const void Update(const float& dt);
		const void Draw(const float& dt);
		void HandleInput(float dt, SDL_Event* inputEvent );
		void HandleEvents(float dt);
	private:
		SDL_Surface* m_screen;
};

#endif
