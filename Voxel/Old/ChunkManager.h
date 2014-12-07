#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H


#include <list>
#include "Chunk.h"
#include "Singleton.h"

class ChunkManager : public Singleton<ChunkManager>
{
public:
	ChunkManager();
	~ChunkManager(void);

	void Init(TextureAtlas* atlas);
	void Draw();
	Chunk* GetChunk(int x, int y, int z);
	static const int CHUNKS_X = 10; 
	static const int CHUNKS_Y = 1;
	static const int CHUNKS_Z = 10; 
private:
	TextureAtlas* m_atlas;
	std::list<Chunk*> m_renderList;
	Chunk* m_pChunks[CHUNKS_X][CHUNKS_Y][CHUNKS_Z];
};

#endif
