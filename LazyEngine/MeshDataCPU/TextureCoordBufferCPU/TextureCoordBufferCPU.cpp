#include "TextureCoordBufferCPU.h"
namespace LE {

	TextureCoordBufferCPU::TextureCoordBufferCPU( std::string name): m_name(name) {
	}



	void TextureCoordBufferCPU::addData(Primitives::Float32 vert) {
		m_data.addElement(vert);
	}

	Primitives::Int16 TextureCoordBufferCPU::getVertAtIndex(Primitives::Int32 index) {

		return m_data.getElement(index);

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

	void TextureCoordBufferCPU::ReadDataFromFile() {
		char base[1024];
		strcpy(base, "..\\LazyEngine\\meshes\\TexCoordBuffer\\");
		strcat(base, m_name.c_str());
		strcat(base, ".tcb");
		FileReader fr(base);


		fr.readNextInt(m_count);
		m_data.setSize(m_count * 2);
		for (unsigned int j = 0; j < m_count * 2; j++) {
			Primitives::Float32 temp;
			fr.readNextFloat(temp);
			addData(temp);
		}
	}
};