#include "VertexBufferCPU.h"
namespace LE {

	VertexBufferCPU::VertexBufferCPU(std::string name){
		m_name = name;
	}

	
	void VertexBufferCPU::addData(Primitives::Float32 vert){
		m_data.addElement(vert);
	}

	Primitives::Float32 VertexBufferCPU::getVertAtIndex(Primitives::Int32 index){
		
		return m_data.getElement(index);

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

	void VertexBufferCPU::ReadDataFromFile() {
		char base[1024];
		strcpy(base, "..\\LazyEngine\\meshes\\VertexBuffer\\");
		strcat(base, m_name.c_str());
		strcat(base, ".vb");
		FileReader fr(base);


		fr.readNextInt(m_count);
		m_data.setSize(m_count*3);
		for (unsigned int j = 0; j < m_count * 3; j++) {
			Primitives::Float32 temp;
			fr.readNextFloat(temp);
			addData(temp);
		}
	}
};