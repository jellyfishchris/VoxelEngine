#ifndef TEXTUREALTAS_H
#define TEXTUREALTAS_H

#include <glm\glm.hpp>
#include "Texture.h"

class TextureAtlas
{
public:
	TextureAtlas(Texture* t, unsigned int size);
	~TextureAtlas();

	void SetTexture(int pos);
	int Init();

	Texture* GetTexture(){return m_texture;}

	unsigned int GetSize(){return m_size;}
	glm::vec2& GetBotLeft(){return m_bl;}
	glm::vec2& GetBotRight();
	glm::vec2& GetTopLeft(){return m_tl;}
	glm::vec2& GetTopRight(){return m_tr;}
private:
	int m_numX;
	int m_numY;

	unsigned int m_num;
	unsigned int m_size;

	Texture* m_texture;

	glm::vec2 m_bl;
	glm::vec2 m_br;
	glm::vec2 m_tl;
	glm::vec2 m_tr;
};

#endif

