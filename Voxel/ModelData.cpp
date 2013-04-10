#include "ModelData.h"


unsigned int Model::AddVertexToMesh(Vertex v)
{
	m_vertices.push_back(v);
	return m_vertices.size() - 1;
}

unsigned int Model::AddVertexToMesh( glm::vec3 coords, glm::vec3 normal, glm::vec2 colour )
{
	Vertex v;
	v.m_x = coords.x;v.m_y = coords.y;v.m_z = coords.z;
	v.m_nx = normal.x; v.m_ny = normal.y; v.m_nz = normal.z;
	v.m_s = colour.x; v.m_t = colour.y; v.m_u = colour.x;
	m_vertices.push_back(v);
	return m_vertices.size() - 1;
}

void Model::AddTriangleToMesh( int v1, int v2, int v3 )
{
	//int* i = new int(3);
	//i[0] = v1; i[1] = v2; i[2] = v3;

	//m_triangles.push_back(i);
	m_triangles.push_back(v1);
	m_triangles.push_back(v2);
	m_triangles.push_back(v3);
}

void Model::AddTriangleToMesh( int v )
{
	m_triangles.push_back(v);
}

void Model::EndPart( unsigned int i )
{
	m_triangles.push_back(i);
}
