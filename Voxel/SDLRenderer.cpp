#include "SDLRenderer.h"


SDLRenderer::SDLRenderer(void)
{
}


SDLRenderer::~SDLRenderer(void)
{
}

void SDLRenderer::Initialize( int width, int height, unsigned int fpsCap, std::vector<unsigned int>& settings )
{
	// Save basic settings
	m_width = width;
	m_height = height;
	m_fpsCap = fpsCap;

	glEnable(GL_TEXTURE_2D);									// Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);									// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);						// Black Background
	glClearDepth(1.0f);											// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);									// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);										// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Really Nice Perspective Calculations
	
	//if(m_screen == nullptr)
	{

		glDisable(GL_CULL_FACE);
		
		Uint32 sumSettings = 0;
		
		for(unsigned int i = 0; i < settings.size(); i++)
			sumSettings = sumSettings | settings[i];

		SDL_Init(SDL_INIT_EVERYTHING);
		/* !!! */
		m_screen = SDL_SetVideoMode(m_width, m_height, 8, sumSettings); 

		glClearColor (0.7f, 0.9f, 1.0f, 0.0f);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45,width/height,1.0,2000.0);
		//	glOrtho(...?);
		glMatrixMode(GL_MODELVIEW);

		SDL_ShowCursor(SDL_DISABLE); 
		SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
		GLenum init = glewInit();
	}
	/* !!! */
	/*if(m_frustumCamera == nullptr)                  
	{
		m_frustumCamera = new Camera(glm::vec3(0,0,1),glm::vec3(0,0,0),glm::vec3(0,1,0));
	}*/

	//m_chunks = new ChunkManager(m_textureAtlas);

	//c.CreateVBO(m_textureAtlas);
	
}

void SDLRenderer::Initialize( int width, int height, unsigned int fpsCap )
{
	const Uint32 arr[] = {SDL_SWSURFACE,SDL_OPENGL};
	std::vector<unsigned int> v(arr, arr + sizeof(arr) / sizeof(arr[0]));
	Initialize(width,height,fpsCap,v);
}

const void SDLRenderer::Update(const float& dt)
{
	int tPrevious = SDL_GetTicks();

	HandleEvents(dt);
	Draw(dt);

}

const void SDLRenderer::Draw( const float& dt )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();

	/* !!! */
	//glLoadMatrixf(glm::value_ptr(glm::translate(m_frustumCamera->Orientation(), -m_frustumCamera->GetPos())));

	SDL_GL_SwapBuffers();
}
void SDLRenderer::HandleEvents( float dt )
{
	//SDL INPUT EVENTS

}
void SDLRenderer::HandleInput( float dt, SDL_Event* inputEvent )
{
	switch(inputEvent->type) 
	{
	case SDL_QUIT:
		/* !!! */
		//m_running = false;
		break;
	case SDL_MOUSEMOTION:

		//m_frustumCamera->RotateY((inputEvent->motion.x - m_width/2)/10.0f);
		//m_frustumCamera->RotateX((inputEvent->motion.y - m_height/2)/10.0f);

		break;
	case SDL_KEYDOWN:
		switch( inputEvent->key.keysym.sym )
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


