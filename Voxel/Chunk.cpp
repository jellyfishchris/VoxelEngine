#include "Chunk.h"
#include "BitDef.h"

Chunk::Chunk(int posX, int posY, int posZ)
	: m_posX(posX), m_posY(posY), m_posZ(posZ)
{
	Init();
}

void Chunk::Init()
{
	m_blocks = new Block[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
	//m_blocks.resize(CHUNK_SIZE);
	int type = 1;
	int i = 0;
	for(int z = 0; z < CHUNK_SIZE; z++)
	{
		//m_blocks[z].resize(CHUNK_SIZE);
		for(int y = 0; y < CHUNK_SIZE; ++y)
		{
			//m_blocks[z][y].resize(CHUNK_SIZE);
			for(int x = 0; x <CHUNK_SIZE; ++x)
			{
				
				type++;
				GetBlock(i)->m_type = type;
				type %= 4;
				i++;
			}
			
		}
	}

	//noise::module::Perlin myModule;
	//noise::utils::NoiseMap heightMap;
	//utils::NoiseMapBuilderPlane heightMapBuilder;
	//heightMapBuilder.SetSourceModule (myModule);
	//heightMapBuilder.SetDestNoiseMap (heightMap);
	//heightMapBuilder.SetDestSize (CHUNK_SIZE, CHUNK_SIZE);
	//heightMapBuilder.SetBounds (3, 5, 3, 5);
	//heightMapBuilder.Build ();


	//for(unsigned int z = 0; z < CHUNK_SIZE; z++)
	//{
	//	for(unsigned int x = 0; x < CHUNK_SIZE; x++)
	//	{
	//		float h = heightMap.GetValue(x,z);
	//		h = abs(h);
	//		h *= (CHUNK_SIZE / 2) - 1;
	//		for(unsigned int y = 0; y <= h; y++)
	//		{
	//			GetBlock(x,y,z)->m_type = 1;//(rand() % 4) + 1;
	//		}
	//	}
	//}

	m_tree = new Octree();
	//m_tree->Init(m_blocks);

}

void Chunk::SetFaces( byte* faces, int startx, int starty, int startz, int blockSize)
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

	for(int z = 0; z < blockSize; z++)
	{
		for(int y = 0; y < blockSize; y++)
		{
			for(int x = 0; x < blockSize; x++)
			{
				if(startx + x - 1 < 0 || GetBlock(startx + x - 1, starty + y, startz + z)->m_type == 0)
				{*faces |= BIT_ONE;}
				//else{faces[0] = false;}
				if(startx + x + 1 >= CHUNK_SIZE || GetBlock(startx + x + 1, starty + y, startz + z)->m_type == 0)
				{*faces |= BIT_TWO;}
				//else{faces[1] = false;}

				//Top & Bottom
				if(starty + y - 1 < 0 || GetBlock(startx + x, starty + y - 1, startz + z)->m_type == 0)
				{*faces |= BIT_THREE;}

				if(starty + y + 1 >= CHUNK_SIZE || GetBlock(startx + x, starty + y + 1, startz + z)->m_type == 0)
				{*faces |= BIT_FOUR;}
				//else{faces[3] = false;}

				//Front & Back
				if(startz + z - 1 < 0 || GetBlock(startx + x, starty + y, startz + z - 1)->m_type == 0)
				{*faces |= BIT_FIVE;}
				//else{faces[4] = false;}
				if(startz + z + 1 >= CHUNK_SIZE || GetBlock(startx + x, starty + y, startz + z + 1)->m_type == 0)
				{*faces |= BIT_SIX;}
				//else{faces[5] = false;}
			}
		}
	}
	//std::cout << "(" << faces[0] << "," << faces[1] << "," << faces[2] << "," << faces[3] << "," << faces[4] << "," << faces[5] << " - " << startx << "," << starty << "," << startz << ")" << true << "\n";
}
void Chunk::CheckChildrenNode(BlockNode* node, int startx, int starty, int startz, int deltax, int deltay, int deltaz )
{
	if(node->m_nodes[0] != nullptr)
	{
		for(unsigned int z = 0; z < 2; z++)
		{
			for(unsigned int y = 0; y < 2; y++)
			{
				for(unsigned int x = 0; x < 2; x++)
				{
					if(node->m_nodes[x + (y * 2) + (z * 2 * 2)]->m_nodes[0] == nullptr)
					{

					}
					CheckChildrenNode(node->m_nodes[x + (y * 2) + (z * 2 * 2)], startx + (x * (deltax / 2)), starty + (y * (deltay / 2)), startz + (z * (deltaz / 2)), deltax / 2, deltay / 2, deltaz / 2);
				}
			}
		}
	}
	else
	{
		if(node->m_block.m_type != 0)
		{
			byte faces = 0;
			byte active = 0;

			SetFaces(&faces, startx, starty, startz, deltax);
			if(faces != active)
			{
				m_texture->SetTexture(node->m_block.m_type);
				CreateBlock(faces, (float)(startx * Block::BLOCK_SIZE), (float)(starty * Block::BLOCK_SIZE), (float)(startz * Block::BLOCK_SIZE), (float)((startx + deltax) * Block::BLOCK_SIZE), (float)((starty + deltay) * Block::BLOCK_SIZE), (float)((startz + deltaz) * Block::BLOCK_SIZE));
		
			}
			//bool faces[6];
			//m_texture->SetTexture(node->m_block.m_type);
			//for(int i = 0; i < 6; ++i){faces[i] = false;}
			//SetFaces(faces, startx, starty, startz, deltax);
			//CreateBlock(faces, (float)(startx * Block::BLOCK_SIZE), (float)(starty * Block::BLOCK_SIZE), (float)(startz * Block::BLOCK_SIZE), (float)((startx + deltax) * Block::BLOCK_SIZE), (float)((starty + deltay) * Block::BLOCK_SIZE), (float)((startz + deltaz) * Block::BLOCK_SIZE));

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

	for(int z = 0; z < CHUNK_SIZE; ++z)
	{
		for(int y = 0; y < CHUNK_SIZE; ++y)
		{
			for(int x = 0; x < CHUNK_SIZE; ++x)
			{
				byte faces = 0;
				byte active = 0;
				
				SetFaces(&faces,x,y,z,1);
				if(faces != active)
				{
					m_texture->SetTexture(GetBlock(x,y,z)->m_type);
					CreateBlock(faces,x,y,z);
				}
			}
		}
	}
	//CheckChildrenNode(m_tree->GetNode(), 0, 0, 0, CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE );
	if(m_model->GetArrayVert().size() > 0)
	{
		m_enabled = true;


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
	delete m_blocks;
	//m_blocks.clear();
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

void Chunk::CreateBlock(byte faces, float x, float y, float z )
{
	CreateBlock(faces, x, y, z, x + Block::BLOCK_SIZE, y + Block::BLOCK_SIZE, z + Block::BLOCK_SIZE);
}

void Chunk::CreateBlock( byte faces, float startx, float starty, float startz, float endx, float endy, float endz )
{
	glm::vec3 p1(startx, starty, endz);
	glm::vec3 p2(endx, starty, endz);
	glm::vec3 p3(endx, endy, endz);
	glm::vec3 p4(startx, endy, endz);
	glm::vec3 p5(endx, starty, startz);
	glm::vec3 p6(startx, starty, startz);
	glm::vec3 p7(startx, endy, startz);
	glm::vec3 p8(endx, endy, startz);

	unsigned int v1; unsigned int v2; unsigned int v3; unsigned int v4; unsigned int v5; unsigned int v6; unsigned int v7; unsigned int v8;

	glm::vec3 n1(0.0, 0.0,-1.0);

	if((faces & (byte)BIT_SIX) == (byte)BIT_SIX)
	{	
		v1 = m_model->AddVertexToMesh(p1, n1, m_texture->GetBotRight());  
		v2 = m_model->AddVertexToMesh(p2, n1, m_texture->GetTopRight()); 
		v3 = m_model->AddVertexToMesh(p3, n1, m_texture->GetTopLeft()); 
		v4 = m_model->AddVertexToMesh(p4, n1,  m_texture->GetBotLeft()); 

		m_model->AddTriangleToMesh(v1,v2,v3);
		m_model->AddTriangleToMesh(v1,v3,v4);
	}
	if((faces & (byte)BIT_FIVE) == (byte)BIT_FIVE)
	{
		n1 = glm::vec3(0.0f, 0.0f, 1.0f);

		v5 = m_model->AddVertexToMesh( p5, n1, m_texture->GetBotRight());
		v6 = m_model->AddVertexToMesh( p6, n1, m_texture->GetTopRight());
		v7 = m_model->AddVertexToMesh( p7, n1, m_texture->GetTopLeft());
		v8 = m_model->AddVertexToMesh( p8, n1, m_texture->GetBotLeft());

		m_model->AddTriangleToMesh( v5, v6, v7);
		m_model->AddTriangleToMesh( v5, v7, v8);
	}
	if((faces & (byte)BIT_TWO) == (byte)BIT_TWO)
	{
		n1 = glm::vec3(-1.0f, 0.0f, 0.0f);

		v2 = m_model->AddVertexToMesh( p2, n1, m_texture->GetBotRight());  
		v5 = m_model->AddVertexToMesh( p5, n1, m_texture->GetTopRight()); 
		v8 = m_model->AddVertexToMesh( p8, n1, m_texture->GetTopLeft()); 
		v3 = m_model->AddVertexToMesh( p3, n1, m_texture->GetBotLeft()); 

		m_model->AddTriangleToMesh( v2, v5, v8);
		m_model->AddTriangleToMesh( v2, v8, v3);

	}
	if((faces & (byte)BIT_ONE) == (byte)BIT_ONE)
	{
		n1 = glm::vec3(1.0f, 0.0f, 0.0f);

		v6 = m_model->AddVertexToMesh( p6, n1, m_texture->GetBotRight());
		v1 = m_model->AddVertexToMesh( p1, n1, m_texture->GetTopRight());
		v4 = m_model->AddVertexToMesh( p4, n1, m_texture->GetTopLeft());
		v7 = m_model->AddVertexToMesh( p7, n1, m_texture->GetBotLeft());

		m_model->AddTriangleToMesh( v6, v1, v4);
		m_model->AddTriangleToMesh( v6, v4, v7);
	}
	if((faces & (byte)BIT_FOUR) == (byte)BIT_FOUR)
	{
		n1 = glm::vec3(0.0f, -1.0f, 0.0f);

		v4 = m_model->AddVertexToMesh( p4, n1, m_texture->GetBotRight());
		v3 = m_model->AddVertexToMesh( p3, n1, m_texture->GetTopRight());
		v8 = m_model->AddVertexToMesh( p8, n1, m_texture->GetTopLeft());
		v7 = m_model->AddVertexToMesh( p7, n1, m_texture->GetBotLeft());

		m_model->AddTriangleToMesh( v4, v3, v8);
		m_model->AddTriangleToMesh( v4, v8, v7);

	}
	if((faces & (byte)BIT_THREE) == (byte)BIT_THREE)
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

Block* Chunk::GetBlock( int i )
{
	return &m_blocks[i];
}


