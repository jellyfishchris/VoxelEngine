#include "ChunkManager.h"


ChunkManager::ChunkManager()
{

}


void ChunkManager::Init( TextureAtlas* atlas )
{
	m_atlas = atlas;

	for(int i = 0; i < CHUNKS_X; i++)
	{
		for(int j = 0; j < CHUNKS_Y; j++)
		{
			for(int k = 0; k < CHUNKS_Z; k++)
			{
				m_pChunks[i][j][k] = new Chunk(i,j,k);
				if(i == 0)
					m_pChunks[i][j][k]->Init(true);
				else
					m_pChunks[i][j][k]->Init(false);
			}
		}
	}
	for(int i = 0; i < CHUNKS_X; i++)
	{
		for(int j = 0; j < CHUNKS_Y; j++)
		{
			for(int k = 0; k < CHUNKS_Z; k++)
			{
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
	for(int i = 0; i < CHUNKS_X; i++)
	{
		for(int j = 0; j < CHUNKS_Y; j++)
		{
			for(int k = 0; k < CHUNKS_Z; k++)
			{
				glPushMatrix();
				glTranslatef((float)(i * Chunk::CHUNK_SIZE * Block::BLOCK_SIZE), (float)(j * Chunk::CHUNK_SIZE * Block::BLOCK_SIZE), (float)(k * Chunk::CHUNK_SIZE * Block::BLOCK_SIZE));
				m_pChunks[i][j][k]->Draw();
				glPopMatrix();			
			}
		}
	}
}

Chunk* ChunkManager::GetChunk( int x, int y, int z )
{
	if((x >= 0) && (x < CHUNKS_X) && (y >= 0) && (y < CHUNKS_Y) && (z >= 0) && (z < CHUNKS_Z))
		return m_pChunks[x][y][z];
	else
		return nullptr;
}
