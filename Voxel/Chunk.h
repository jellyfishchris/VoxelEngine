#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include <stack>

#include "Block.h"
#include "ModelData.h"
#include "TextureAtlas.h"
#include "Octree.h"
#include <noise/noise.h>
#include "noiseutils.h"


class Octree;
struct BlockNode;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class Chunk
{
public:
	Chunk(int posX, int posY, int posZ);
	~Chunk(void);

	void Init();
	void Draw();
	void Update(float dt);
	void CreateVBO(TextureAtlas* texture);
	Block* GetBlock(int i);
	Block* GetBlock(int x, int y, int z);

	int GetPosX(){return m_posX;}
	int GetPosY(){return m_posY;}
	int GetPosZ(){return m_posZ;}

	static const int CHUNK_SIZE = 64; 
private:
	void CheckChildrenNode(BlockNode* node, int startx, int starty, int startz, int deltax, int deltay, int deltaz);
	void CreateBlock(byte faces, float x, float y, float z);
	void CreateBlock(byte faces, float startx, float starty, float startz, float endx, float endy, float endz);
	void SetFaces(byte* faces, int startx, int starty, int startz, int blockSize);

	int m_posX;
	int m_posY;
	int m_posZ;

	bool m_enabled;
	GLuint m_vboID;
	GLuint m_iboID;
	GLuint m_vaoID;
	
	TextureAtlas* m_texture;
	Octree* m_tree;
	Block* m_blocks;
	Model* m_model;
};

#endif
