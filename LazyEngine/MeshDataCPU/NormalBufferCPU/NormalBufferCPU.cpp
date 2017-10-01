#include "NormalBufferCPU.h"
namespace LE {

	NormalBufferCPU::NormalBufferCPU(std::string name) : m_name(name) {
	}



	void NormalBufferCPU::addData(Primitives::Float32 vert) {
		m_data.push_back(vert);
	}

	Primitives::Int16 NormalBufferCPU::getVertAtIndex(Primitives::Int32 index) {

		return m_data.at(index);

	}
	//Function to get number of vertices within this mesh
	Primitives::Int32  NormalBufferCPU::getNumVerts() {
		return m_count;
	}
	//Function to get the mesh name
	std::string NormalBufferCPU::getMeshName() {
		if (!m_name.empty()) return m_name;
		else return NULL;
	}
	//Function to set mesh name return 1 if successful else 0
	Primitives::Int16 NormalBufferCPU::setMeshName(std::string name) {
		if (name.empty()) return 0;
		m_name = name; return 1;
	}

	void NormalBufferCPU::ReadDataFromFile() {
		char base[1024];
		strcpy(base, "..\\LazyEngine\\meshes\\NormalBuffer\\");
		strcat(base, m_name.c_str());
		strcat(base, ".nb");
		FileReader fr(base);


		fr.readNextInt(m_count);
		for (unsigned int j = 0; j < m_count * 3; j++) {
			Primitives::Float32 temp;
			fr.readNextFloat(temp);
			addData(temp);
		}
	}
};