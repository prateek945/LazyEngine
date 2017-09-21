#include "VertexBufferCPU.h"
namespace LE {

	VertexBufferCPU::VertexBufferCPU(Primitives::Int32 count, std::string name):m_count(count),m_name(name){
	}

	VertexBufferCPU::VertexBufferCPU(Primitives::Int32 count):m_count(count){
	}

	void VertexBufferCPU::addData(Primitives::Float32 vert){
		m_data.push_back(vert);
	}

	Primitives::Int16 VertexBufferCPU::getVertAtIndex(Primitives::Int32 index, LEVector3& vert){
		
		if (index * 3 >= m_data.size()) return (Primitives::Int16) 0;
		else {
			vert.m_x = m_data.at(index*3);
			vert.m_y = m_data.at(index*3 + 1);
			vert.m_z = m_data.at(index*3 + 2);

		}
		return (Primitives::Int16) 1;

	}
	//Function to get number of vertices within this mesh
	Primitives::Int32  VertexBufferCPU::getNumVerts(){
		return m_count;
	}
	//Function to get the mesh name
	std::string VertexBufferCPU::getMeshName(){
		if (!m_name.empty()) return m_name;
		else return NULL;
	}
	//Function to set mesh name return 1 if successful else 0
	Primitives::Int16 VertexBufferCPU::setMeshName(std::string name){
		if (name.empty()) return 0;
		m_name = name; return 1;
	}
};