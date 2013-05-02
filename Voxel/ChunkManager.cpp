#include "ChunkManager.h"


ChunkManager::ChunkManager(TextureAtlas* atlas)
{
	m_atlas = atlas;

	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			for(int k = 0; k < 8; k++)
			{
				m_pChunks[i][j][k] = new Chunk(i,j,k);
				m_pChunks[i][j][k]->CreateVBO(atlas);
			}
		}
	}

}


ChunkManager::~ChunkManager(void)
{
}

void ChunkManager::Draw()
{
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			for(int k = 0; k < 8; k++)
			{
				glPushMatrix();
				glTranslatef((float)(i * Chunk::CHUNK_SIZE * Block::BLOCK_SIZE), (float)(j * Chunk::CHUNK_SIZE * Block::BLOCK_SIZE), (float)(k * Chunk::CHUNK_SIZE * Block::BLOCK_SIZE));
				m_pChunks[i][j][k]->Draw();
				glPopMatrix();			
			}
		}
	}
}
