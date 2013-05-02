#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include <list>
#include "Chunk.h"

class ChunkManager
{
public:
	ChunkManager(TextureAtlas* atlas);
	~ChunkManager(void);

	void Draw();

	TextureAtlas* m_atlas;
	std::list<Chunk*> m_renderList;
	Chunk* m_pChunks[8][2][8];
};

#endif
