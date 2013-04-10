#ifndef BLOCK_H
#define BLOCK_H

#include "windows.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>


class Block
{
public:
	Block::Block();
	static const int BLOCK_SIZE = 1;
	char m_type;
};

#endif