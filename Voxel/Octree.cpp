#include "Octree.h"

BlockNode::~BlockNode()
{
	for(int i = 0; i < 8; i++)
	{
		if(m_nodes[i] != nullptr)
		{
			delete m_nodes[i];
		}
	}
}

BlockNode::BlockNode()
{
	for(int i = 0; i < 8; i++)
	{
		m_nodes[i] = nullptr;
	}
}


Octree::Octree()
	: m_width(Chunk::CHUNK_SIZE), m_depth(Chunk::CHUNK_SIZE), m_height(Chunk::CHUNK_SIZE), m_root(nullptr)
{
	//bool val = BuildNode(m_root, chunk, 0, 0, 0, m_width, m_height, m_depth);
}


Octree::~Octree(void)
{
}

std::string Octree::BuildString()
{
	std::stringstream ss; 
	ss << "Hello";

	return ss.str();
}

bool Octree::CheckLinkArea( BlockNode* base, int startx, int starty, int startz, int deltax, int deltay, int deltaz )
{
	if(base != nullptr && m_c != nullptr)
	{
		char type;
		bool returnVal = true;
		bool started = false;
		for(unsigned int z = 0; z < 2; z++)
		{
			for(unsigned int y = 0; y < 2; y++)
			{
				for(unsigned int x = 0; x < 2; x++)
				{
					
					TypeChecker tc = CheckArea(startx + (x * (deltax / 2)), starty + (y * (deltay / 2)), startz + (z * (deltaz / 2)), (deltax / 2), (deltay / 2), (deltaz / 2));
					if(!started)
					{
						type = tc.m_type;
						started = true;
					}
					/* -- NEED TO FIX (Speed problem) -- Checking if the whole node is considant by checking each subsection, then later checking those subsections as whole nodes*/
					if(!tc.m_val)
						return false;
					if(tc.m_type != type)
						return false;
				}
			}
		}
		base->m_block.m_type = type;
		return returnVal;
	}
	base->m_block.m_type = 0;
	return true;
}

TypeChecker Octree::CheckArea( int startx, int starty, int startz, int deltax, int deltay, int deltaz )
{
	char type = 0;
	bool started = false;
	for(unsigned int z = startz; z < deltaz + startz; z++)
	{
		for(unsigned int y = starty; y < deltay + starty; y++)
		{
			for(unsigned int x = startx; x < deltax + startx; x++)
			{
				if(!started)
				{
					type = m_c->GetBlock(x, y, z)->m_type;
					started = true;
				}
				else
				{
					if(m_c->GetBlock(x, y, z)->m_type != type)
					{
						return TypeChecker(type, false);
					}
				}
			}
		}
	}
	if(!started)
	{
		return TypeChecker(m_c->GetBlock(startx,starty, startz)->m_type, true);
	}
	return TypeChecker(type, true);
}

void Octree::SetData( Chunk* c )
{
	m_c = c;
}
void Octree::BuildNodes( BlockNode* base, int startx, int starty, int startz, int deltax, int deltay, int deltaz )
{
	bool val = CheckLinkArea(base, startx, starty, startz, deltax, deltay, deltaz);

	if(!val)
	{
		for(unsigned int z = 0; z < 2; z++)
		{
			for(unsigned int y = 0; y < 2; y++)
			{
				for(unsigned int x = 0; x < 2; x++)
				{
					base->m_nodes[x + (y * 2) + (z * 2 * 2)] = new BlockNode();
					BuildNodes(base->m_nodes[x + (y * 2) + (z * 2 * 2)], startx + (x * deltax / 2), starty + (y * deltay / 2), startz + (z * deltaz / 2), deltax / 2, deltay / 2, deltaz / 2);
				}
			}
		}
	}
}

Block* Octree::GetBlock( int x, int y, int z )
{
	BlockNode* node = m_root;
	int width = Chunk::CHUNK_SIZE, height = Chunk::CHUNK_SIZE, depth = Chunk::CHUNK_SIZE;
	int startx = 0, starty = 0, startz = 0;

	while(node != nullptr)
	{
		int xpos, ypos, zpos;

		if(x > startx + (width / 2) - 1){ xpos = 1;}
		else{ xpos = 0;}
		if(y > starty + (height / 2) - 1){ypos = 1;}
		else{ypos = 0;}
		if(z > startz + (depth / 2) - 1){zpos = 1;}
		else{zpos = 0;}

		if(node->m_nodes[(zpos * 4) + (ypos * 2) + xpos] == nullptr)
		{
			std::cout << (int)node->m_block.m_type;
			return &node->m_block;
		}
		node = node->m_nodes[(zpos * 4) + (ypos * 2) + xpos];
		width /= 2; height /= 2; depth /= 2;
	}
}

bool Octree::Init()
{
	if(m_root != nullptr)
		delete m_root;
	m_root = new BlockNode();

	BuildNodes(m_root, 0, 0, 0, Chunk::CHUNK_SIZE, Chunk::CHUNK_SIZE, Chunk::CHUNK_SIZE);

	return true;
}



