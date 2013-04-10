#ifndef ENGINE_H
#define ENGINE_H

#include <SDL/SDL.h>
#include "ChunkManager.h"
#include "Camera.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "TextureAtlas.h"

class Engine
{
public:
	Engine(void);
	~Engine(void);

	void Initialize(int width, int height, unsigned int fpsCap, std::vector<Uint32>& settings);
	void Initialize(int width, int height, unsigned int fpsCap);
	void LoadAtlas(std::string filename);
	void Shutdown();
	void Execute();
	void Update(float dt);
	void Draw(float dt);
	void HandleEvents(float dt);

	bool GetRunning(){return m_running;}
	bool GetInitialized(){return m_initialized;}
	unsigned int GetFpsCap(){return m_fpsCap;}
private:
	void HandleInput(float dt, SDL_Event* inputEvent);

	bool m_running;
	bool m_initialized;
	int m_width;
	int m_height;
	TextureAtlas* m_textureAtlas;
	unsigned int m_fpsCap;
	Camera* m_frustumCamera;
	SDL_Surface* m_screen;
	SDL_Event tempEvent;
	ChunkManager* m_chunks;
};

#endif

