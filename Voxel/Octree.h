#ifndef OCTREE_H
#define OCTREE_H

#include "Chunk.h"
#include <sstream>

class Chunk;

struct TypeChecker
{
	TypeChecker::TypeChecker(int type, bool val): m_type(type), m_val(val){}
	char m_type;
	bool m_val;
};

struct BlockNode
{
	/*
		0 - Front bot left
		1 - Front bot right
		2 - Front top left
		3 - Front top right
		4 - Back bot left
		5 - Back bot right
		6 - Back top left
		7 - Back top right
	*/
	BlockNode();
	~BlockNode();
	BlockNode* m_nodes[8];
	Block m_block;
};

class Octree
{
public:
	Octree();
	~Octree(void);

	std::string BuildString();
	BlockNode* GetNode(){return m_root;}
	Block* GetBlockTree(int x, int y, int z);
	Block* GetBlock(int x, int y, int z);
	Block* GetBlock(int i);
	bool Init(Block* voxelData);
private:
	/* Returns true - stop building
	   Return false - each one of the nodes needs to be checked */
	bool CheckLinkArea(BlockNode* base, int startx, int starty, int startz, int deltax, int deltay, int deltaz);
	TypeChecker CheckArea( int startx, int starty, int startz, int deltax, int deltay, int deltaz );

	void BuildNodes(BlockNode* base, int startx, int starty, int startz, int deltax, int deltay, int deltaz);

	BlockNode* m_root;
	Block* m_blocks;

	int m_width;
	int m_height;
	int m_depth;
};

#endif