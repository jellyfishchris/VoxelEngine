#include "Engine.h"
bool LoadTGA(Texture *, char *);

Engine::Engine(void)
	: m_initialized(false), m_running(false), m_screen(nullptr), m_frustumCamera(nullptr)
{
	
}


Engine::~Engine(void)
{
}

void Engine::Draw(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();

	glLoadMatrixf(glm::value_ptr(m_frustumCamera->GetOri()));
	m_chunks->Draw();
	SDL_GL_SwapBuffers();
}

void Engine::Update( float dt )
{
	SDL_WarpMouse(m_width/2, m_height/2);
	m_frustumCamera->Update(dt);
}

void Engine::HandleInput(float dt, SDL_Event* inputEvent )
{
	switch(inputEvent->type) 
	{
		case SDL_QUIT:
			m_running = false;
			break;
		case SDL_MOUSEMOTION:
			m_frustumCamera->Rotate(-1*((inputEvent->motion.x - m_width/2)/10.0f), glm::vec3(0,1,0));
			m_frustumCamera->Rotate((inputEvent->motion.y - m_height/2)/10.0f, glm::vec3(1,0,0));
			break;
		case SDL_KEYDOWN:
			switch( inputEvent->key.keysym.sym )
			{
				case SDLK_ESCAPE:
					m_running = false;
					break;
				case SDLK_w:
					m_frustumCamera->Translate(m_frustumCamera->GetDir());
					break;
				case SDLK_s:
					m_frustumCamera->Translate(-m_frustumCamera->GetDir());
					break;
				case SDLK_a:
					m_frustumCamera->Translate(-m_frustumCamera->GetSide());
					break;
				case SDLK_d:
					m_frustumCamera->Translate(m_frustumCamera->GetSide());
					break;
			}
			break;
	}
}

void Engine::Initialize(int width, int height, unsigned int fpsCap, std::vector<Uint32>& settings)
{
	if(!m_initialized)
	{
		glEnable(GL_TEXTURE_2D);									// Enable Texture Mapping ( NEW )
		glShadeModel(GL_SMOOTH);									// Enable Smooth Shading
		glClearColor(0.0f, 0.0f, 0.0f, 0.5f);						// Black Background
		glClearDepth(1.0f);											// Depth Buffer Setup
		glEnable(GL_DEPTH_TEST);									// Enables Depth Testing
		glDepthFunc(GL_LEQUAL);										// The Type Of Depth Testing To Do
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Really Nice Perspective Calculations
		if(m_screen == nullptr)
		{

			glDisable(GL_CULL_FACE);
			m_initialized = true;
			Uint32 sumSettings = 0;
			m_width = width;
			m_height = height;
			for(unsigned int i = 0; i < settings.size(); i++)
				sumSettings = sumSettings | settings[i];

			SDL_Init(SDL_INIT_EVERYTHING);
			m_screen = SDL_SetVideoMode(width, height, 8, sumSettings);

			glClearColor (0.7f, 0.9f, 1.0f, 0.0f);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45,width/height,1.0,500.0);
			//	glOrtho(...?);
			glMatrixMode(GL_MODELVIEW);

			SDL_ShowCursor(SDL_DISABLE); 
			SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
		}
		if(m_frustumCamera == nullptr)
		{
			m_frustumCamera = new Camera(glm::vec3(0,0,1),glm::vec3(0,0,0),glm::vec3(0,1,0));
		}
		m_textureAtlas = new TextureAtlas(new Texture(),64);
		LoadAtlas("Colour.tga");
		m_textureAtlas->Init();
		m_chunks = new ChunkManager(m_textureAtlas);
		
		//c.CreateVBO(m_textureAtlas);
		m_fpsCap = fpsCap;
	}

}

void Engine::Initialize( int width, int height, unsigned int fpsCap )
{
	const Uint32 arr[] = {SDL_SWSURFACE,SDL_OPENGL};
	std::vector<Uint32> v(arr, arr + sizeof(arr) / sizeof(arr[0]));
	Initialize(width,height,fpsCap,v);
}

void Engine::Execute()
{
	m_running = true;
	int tPrevious = SDL_GetTicks();
	

	while(m_running)
	{
		int t = SDL_GetTicks();
		float dt = (t - tPrevious) * m_fpsCap / 1000.0f;

		HandleEvents(dt);
		Update(dt);
		Draw(dt);

		tPrevious = t;
	}
	Shutdown();
}

void Engine::HandleEvents(float dt)
{
	//SDL INPUT EVENTS
	while(SDL_PollEvent(&tempEvent)) {
		HandleInput(dt,&tempEvent);
	}
}

void Engine::Shutdown()
{
	SDL_Quit();
}

void Engine::LoadAtlas( std::string filename )
{
	
	LoadTGA(m_textureAtlas->GetTexture(), (char*)filename.c_str());
	int internalFormat;
	int mainFormat;

	internalFormat = GL_RGB;
	mainFormat = GL_BGR;

	glGenTextures(1, &m_textureAtlas->GetTexture()->texID);				// Create The Texture ( CHANGE )
	glBindTexture(GL_TEXTURE_2D, m_textureAtlas->GetTexture()->texID);
	glTexImage2D(GL_TEXTURE_2D, 0, m_textureAtlas->GetTexture()->bpp / 8, m_textureAtlas->GetTexture()->width, m_textureAtlas->GetTexture()->height, 0, m_textureAtlas->GetTexture()->type, GL_UNSIGNED_BYTE, m_textureAtlas->GetTexture()->imageData);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	if (m_textureAtlas->GetTexture()->imageData)						// If Texture Image Exists ( CHANGE )
	{
		free(m_textureAtlas->GetTexture()->imageData);					// Free The Texture Image Memory ( CHANGE )
	}
}
