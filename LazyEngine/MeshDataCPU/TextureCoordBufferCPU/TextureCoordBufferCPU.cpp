#include "TextureCoordBufferCPU.h"
namespace LE {

	TextureCoordBufferCPU::TextureCoordBufferCPU(Primitives::Int32 count, std::string name) :m_count(count), m_name(name) {
	}

	TextureCoordBufferCPU::TextureCoordBufferCPU(Primitives::Int32 count) : m_count(count) {
	}

	void TextureCoordBufferCPU::addData(Primitives::Float32 vert) {
		m_data.push_back(vert);
	}

	Primitives::Int16 TextureCoordBufferCPU::getVertAtIndex(Primitives::Int32 index, LEVector3& vert) {

		if (index * 3 >= m_data.size()) return (Primitives::Int16) 0;
		else {
			vert.m_x = m_data.at(index * 3);
			vert.m_y = m_data.at(index * 3 + 1);
			vert.m_z = m_data.at(index * 3 + 2);

		}
		return (Primitives::Int16) 1;

	}
	//Function to get number of vertices within this mesh
	Primitives::Int32  TextureCoordBufferCPU::getNumVerts() {
		return m_count;
	}
	//Function to get the mesh name
	std::string TextureCoordBufferCPU::getMeshName() {
		if (!m_name.empty()) return m_name;
		else return NULL;
	}
	//Function to set mesh name return 1 if successful else 0
	Primitives::Int16 TextureCoordBufferCPU::setMeshName(std::string name) {
		if (name.empty()) return 0;
		m_name = name; return 1;
	}
};