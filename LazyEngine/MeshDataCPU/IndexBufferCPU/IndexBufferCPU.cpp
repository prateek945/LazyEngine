#include "IndexBufferCPU.h"

namespace LE {

	IndexBufferCPU::IndexBufferCPU(std::string name) : m_name(name) {
	}



	void IndexBufferCPU::addData(Primitives::Float32 vert) {
		m_data.push_back(vert);
	}

	Primitives::Int16 IndexBufferCPU::getVertAtIndex(Primitives::Int32 index, LEVector3& vert) {

		if (index * 3 >= m_data.size()) return (Primitives::Int16) 0;
		else {
			vert.m_x = m_data.at(index * 3);
			vert.m_y = m_data.at(index * 3 + 1);
			vert.m_z = m_data.at(index * 3 + 2);

		}
		return (Primitives::Int16) 1;

	}
	//Function to get number of vertices within this mesh
	Primitives::Int32  IndexBufferCPU::getNumVerts() {
		return m_count;
	}
	//Function to get the mesh name
	std::string IndexBufferCPU::getMeshName() {
		if (!m_name.empty()) return m_name;
		else return NULL;
	}
	//Function to set mesh name return 1 if successful else 0
	Primitives::Int16 IndexBufferCPU::setMeshName(std::string name) {
		if (name.empty()) return 0;
		m_name = name; return 1;
	}

	void IndexBufferCPU::ReadDataFromFile() {
		char base[1024];
		strcpy(base, "..\\LazyEngine\\meshes\\IndexBuffers\\");
		strcat(base, m_name.c_str());
		strcat(base, ".ib");
		FileReader fr(base);


		fr.readNextInt(m_count);
		for (unsigned int j = 0; j < m_count * 3; j++) {
			Primitives::Float32 temp;
			fr.readNextFloat(temp);
			addData(temp);
		}
	}
};