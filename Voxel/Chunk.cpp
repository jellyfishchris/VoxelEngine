#include "Chunk.h"

Chunk::Chunk(int posX, int posZ)
	: m_posX(posX), m_posZ(posZ)
{
	Init();
}

void Chunk::Init()
{
	m_blocks.resize(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
	m_tree = new Octree();
	m_tree->SetData(this);
	m_tree->Init();
	m_blocks.clear();
}

Chunk::Chunk()
{

}

void Chunk::SetFaces( bool* faces, int i, int x, int y, int z)
{
	////Left & Right
	//if(x -1 < 0 || m_blocks[i - 1].m_type == 0)
	//{faces[0] = true;}
	//else{faces[0] = false;}
	//if(x + 1 >= CHUNK_SIZE || m_blocks[i + 1].m_type == 0)
	//{faces[1] = true;}
	//else{faces[1] = false;}

	////Top & Bottom
	//if(y - 1 < 0 || m_blocks[i - CHUNK_SIZE].m_type == 0)
	//{faces[2] = true;}
	//else{faces[2] = false;}
	//if(y + 1 >= CHUNK_SIZE || m_blocks[i + CHUNK_SIZE].m_type == 0)
	//{faces[3] = true;}
	//else{faces[3] = false;}

	////Front & Back
	//if(z - 1 < 0 || m_blocks[i - CHUNK_SIZE * CHUNK_SIZE].m_type == 0)
	//{faces[4] = true;}
	//else{faces[4] = false;}
	//if(z + 1 >= CHUNK_SIZE || m_blocks[i + CHUNK_SIZE * CHUNK_SIZE].m_type == 0)
	//{faces[5] = true;}
	//else{faces[5] = false;}
	//



	//Left & Right
	if(x -1 < 0 || m_tree->GetBlock(x - 1, y, z)->m_type == 0)
	{faces[0] = true;}
	else{faces[0] = false;}
	if(x + 1 >= CHUNK_SIZE || m_tree->GetBlock(x + 1, y, z)->m_type == 0)
	{faces[1] = true;}
	else{faces[1] = false;}

	//Top & Bottom
	if(y - 1 < 0 || m_tree->GetBlock(x, y - 1, z)->m_type == 0)
	{faces[2] = true;}
	else{faces[2] = false;}
	if(y + 1 >= CHUNK_SIZE || m_tree->GetBlock(x, y + 1, z)->m_type == 0)
	{faces[3] = true;}
	else{faces[3] = false;}

	//Front & Back
	if(z - 1 < 0 || m_tree->GetBlock(x, y, z - 1)->m_type == 0)
	{faces[4] = true;}
	else{faces[4] = false;}
	if(z + 1 >= CHUNK_SIZE || m_tree->GetBlock(x, y, z + 1)->m_type == 0)
	{faces[5] = true;}
	else{faces[5] = false;}
}
void Chunk::CheckChildrenNode( BlockNode* node, int startx, int starty, int startz, int deltax, int deltay, int deltaz )
{
	if(node->m_nodes[0] != nullptr)
	{
		for(unsigned int z = 0; z < 2; z++)
		{
			for(unsigned int y = 0; y < 2; y++)
			{
				for(unsigned int x = 0; x < 2; x++)
				{
					CheckChildrenNode(node->m_nodes[x + (y * 2) + (z * 2 * 2)], startx + (x * (deltax / 2)), starty + (y * (deltay / 2)), startz + (z * (deltaz / 2)), deltax / 2, deltay / 2, deltaz / 2);
				}
			}
		}
	}
	else
	{
		if(node->m_block.m_type != 0)
		{
			for(unsigned int z = 0; z < deltaz; z++)
			{
				for(unsigned int y = 0; y < deltay; y++)
				{
					for(unsigned int x = 0; x < deltax; x++)
					{
						int i = (startx + x) + ((starty + y) * CHUNK_SIZE) + ((startz + z) * CHUNK_SIZE * CHUNK_SIZE);
						bool faces[6];
						m_texture->SetTexture(node->m_block.m_type);
						SetFaces(faces, i, startx + x, starty + y, startz + z);
						
						CreateBlock(faces, ((startx  + x) * Block::BLOCK_SIZE), ((starty + y) * Block::BLOCK_SIZE), ((startz + z) * Block::BLOCK_SIZE));
					}
				}
			}

		}
	}
}
void Chunk::CreateVBO(TextureAtlas* texture )
{
	if(m_model == nullptr)
	{
		delete m_model;
	}
	m_model = new Model();
	m_texture = texture;

	CheckChildrenNode( m_tree->GetNode(), 0, 0, 0, CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE );
	m_tree->GetNode();
	if(m_model->GetArrayVert().size() > 0)
	{
		m_enabled = true;
		GLenum init = glewInit();

		GLuint vboID, iboID;
		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, m_model->GetArrayVert().size() * sizeof(Vertex), &(m_model->GetArrayVert()[0]), GL_STATIC_DRAW);

		glGenBuffers(1, &iboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_model->GetArrayTri().size() * sizeof(unsigned int), &m_model->GetArrayTri()[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));   //The starting point of the VBO, for the vertices
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));   //The starting point of normals, 12 bytes away
		glClientActiveTexture(GL_TEXTURE0);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(24));   //The starting point of texcoords, 24 bytes away

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);

		m_iboID = iboID;
		m_vboID = vboID;
		m_texture = texture;
	}
	else
	{
		m_enabled = false;
	}
}


Chunk::~Chunk(void)
{
	// Delete the blocks
	//for (int i = 0; i < CHUNK_SIZE_X; ++i)
	//{
	//	for (int j = 0; j < CHUNK_SIZE_Y; ++j)
	//	{
	//		delete [] m_blocks[i][j];
	//	}

	//	delete [] m_blocks[i];
	//}
	//delete [] m_blocks;
}

void Chunk::Draw()
{
	if(m_enabled == true)
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture->GetTexture()->texID);
		glDrawElements(GL_TRIANGLES, m_model->GetArrayTri().size(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	}
}

void Chunk::Update( float dt )
{

}

void Chunk::CreateBlock(bool* faces, float x, float y, float z )
{
	glm::vec3 p1(x, y, z + Block::BLOCK_SIZE);
	glm::vec3 p2(x + Block::BLOCK_SIZE, y, z + Block::BLOCK_SIZE);
	glm::vec3 p3(x + Block::BLOCK_SIZE, y + Block::BLOCK_SIZE, z + Block::BLOCK_SIZE);
	glm::vec3 p4(x, y + Block::BLOCK_SIZE, z + Block::BLOCK_SIZE);
	glm::vec3 p5(x + Block::BLOCK_SIZE, y, z);
	glm::vec3 p6(x, y, z);
	glm::vec3 p7(x, y + Block::BLOCK_SIZE, z);
	glm::vec3 p8(x + Block::BLOCK_SIZE, y + Block::BLOCK_SIZE, z);

	unsigned int v1; unsigned int v2; unsigned int v3; unsigned int v4; unsigned int v5; unsigned int v6; unsigned int v7; unsigned int v8;
	
	glm::vec3 n1(0.0, 0.0,-1.0);

	if(faces[5])
	{	
		v1 = m_model->AddVertexToMesh(p1, n1, m_texture->GetBotRight());  
		v2 = m_model->AddVertexToMesh(p2, n1, m_texture->GetTopRight()); 
		v3 = m_model->AddVertexToMesh(p3, n1, m_texture->GetTopLeft()); 
		v4 = m_model->AddVertexToMesh(p4, n1,  m_texture->GetBotLeft()); 

		m_model->AddTriangleToMesh(v1,v2,v3);
		m_model->AddTriangleToMesh(v1,v3,v4);
	}
	if(faces[4])
	{
		n1 = glm::vec3(0.0f, 0.0f, 1.0f);

		v5 = m_model->AddVertexToMesh( p5, n1, m_texture->GetBotRight());
		v6 = m_model->AddVertexToMesh( p6, n1, m_texture->GetTopRight());
		v7 = m_model->AddVertexToMesh( p7, n1, m_texture->GetTopLeft());
		v8 = m_model->AddVertexToMesh( p8, n1, m_texture->GetBotLeft());

		m_model->AddTriangleToMesh( v5, v6, v7);
		m_model->AddTriangleToMesh( v5, v7, v8);
	}
	if(faces[1])
	{
		n1 = glm::vec3(-1.0f, 0.0f, 0.0f);

		v2 = m_model->AddVertexToMesh( p2, n1, m_texture->GetBotRight());  
		v5 = m_model->AddVertexToMesh( p5, n1, m_texture->GetTopRight()); 
		v8 = m_model->AddVertexToMesh( p8, n1, m_texture->GetTopLeft()); 
		v3 = m_model->AddVertexToMesh( p3, n1, m_texture->GetBotLeft()); 

		m_model->AddTriangleToMesh( v2, v5, v8);
		m_model->AddTriangleToMesh( v2, v8, v3);

	}
	if(faces[0])
	{
		n1 = glm::vec3(1.0f, 0.0f, 0.0f);

		v6 = m_model->AddVertexToMesh( p6, n1, m_texture->GetBotRight());
		v1 = m_model->AddVertexToMesh( p1, n1, m_texture->GetTopRight());
		v4 = m_model->AddVertexToMesh( p4, n1, m_texture->GetTopLeft());
		v7 = m_model->AddVertexToMesh( p7, n1, m_texture->GetBotLeft());

		m_model->AddTriangleToMesh( v6, v1, v4);
		m_model->AddTriangleToMesh( v6, v4, v7);
	}
	if(faces[3])
	{
		n1 = glm::vec3(0.0f, -1.0f, 0.0f);

		v4 = m_model->AddVertexToMesh( p4, n1, m_texture->GetBotRight());
		v3 = m_model->AddVertexToMesh( p3, n1, m_texture->GetTopRight());
		v8 = m_model->AddVertexToMesh( p8, n1, m_texture->GetTopLeft());
		v7 = m_model->AddVertexToMesh( p7, n1, m_texture->GetBotLeft());

		m_model->AddTriangleToMesh( v4, v3, v8);
		m_model->AddTriangleToMesh( v4, v8, v7);

	}
	if(faces[2])
	{
		n1 = glm::vec3(0.0f, 1.0f, 0.0f);

		v6 = m_model->AddVertexToMesh( p6, n1, m_texture->GetBotRight());
		v5 = m_model->AddVertexToMesh( p5, n1, m_texture->GetTopRight());
		v2 = m_model->AddVertexToMesh( p2, n1, m_texture->GetTopLeft());
		v1 = m_model->AddVertexToMesh( p1, n1, m_texture->GetBotLeft());

		m_model->AddTriangleToMesh( v6, v5, v2);
		m_model->AddTriangleToMesh( v6, v2, v1);
	}


}

Block* Chunk::GetBlock( int x, int y, int z )
{
	int i  = x + (y * CHUNK_SIZE) + (z * CHUNK_SIZE * CHUNK_SIZE);
	return &m_blocks[i];
}


