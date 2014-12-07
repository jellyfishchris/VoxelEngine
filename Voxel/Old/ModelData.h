#ifndef MODELDATA_H
#define MODELDATA_H

#include <glm/glm.hpp>
#include <iostream>
#include <vector>

struct Vertex
{
	float m_x, m_y, m_z;        //Vertex
	float m_nx, m_ny, m_nz;     //Normal
	float m_s, m_t, m_u;
};

class Model
{
	public:
		void EndPart(unsigned int i);
		unsigned int AddVertexToMesh(glm::vec3 coords, glm::vec3 normal, glm::vec2 colour);
		unsigned int AddVertexToMesh(Vertex v);
		void AddTriangleToMesh(int v);
		void AddTriangleToMesh(int v1, int v2, int v3);
		
		std::vector<unsigned int>& GetArrayTri(){return m_triangles;}
		std::vector<Vertex>& GetArrayVert(){return m_vertices;}
	private:
		std::vector<unsigned int> m_triangles;
		std::vector<Vertex> m_vertices;
};


#endif