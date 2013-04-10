#include "TextureAtlas.h"


TextureAtlas::TextureAtlas(Texture* t, unsigned int size)
{
	m_texture = t;
	m_size = size;
}

TextureAtlas::~TextureAtlas(void)
{
}

int TextureAtlas::Init()
{
	if(m_texture != nullptr)
	{
		if(m_texture->width % m_size == 0 && m_texture->height % m_size == 0)
		{
			m_numX = m_texture->width / m_size;
			m_numY = m_texture->height / m_size;

			m_num = m_numX * m_numY;

			return m_num;
		}
	}
	return -1;
}

void TextureAtlas::SetTexture( int pos)
{
	int tempx = pos % m_numX;
	int tempy = (pos - tempx) / m_numY;

	float minx,maxx;
	float miny,maxy;

	minx = (1.0f / m_numX) * (tempx - 1);
	maxx = (1.0f / m_numX) * tempx;
	miny = (1.0f / m_numY) * (tempy - 1);
	maxy = (1.0f / m_numY) * tempy;

	m_bl = glm::vec2(minx, miny);
	m_br = glm::vec2(minx, maxy);
	m_tl = glm::vec2(maxx, miny);
	m_tr = glm::vec2(maxx, maxy);
}

glm::vec2& TextureAtlas::GetBotRight()
{
	return m_br;
}



