#include "ChunkManager.h"


ChunkManager::ChunkManager(TextureAtlas* atlas)
{
	m_atlas = atlas;
	for(int i = 0; i < 1; i++)
	{
		for(int j = 0; j < 1; j++)
		{
			for(int k = 0; k < 1; k++)
			{
				m_pChunks[i][j][k] = new Chunk(i,k);
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
	glPushMatrix();
	for(int i = 0; i < 1; i++)
	{
		glPushMatrix();
		glTranslatef((i * Chunk::CHUNK_SIZE * Block::BLOCK_SIZE), 0, 0);
		for(int j = 0; j < 1; j++)
		{
			for(int k = 0; k < 1; k++)
			{
				glPushMatrix();
				glTranslatef(0, 0, (k * Chunk::CHUNK_SIZE * Block::BLOCK_SIZE));
				m_pChunks[i][j][k]->Draw();
				glPopMatrix();			
			}
		}
		glPopMatrix();
	}
	glPopMatrix();
}
