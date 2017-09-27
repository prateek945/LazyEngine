#include "MeshCPU.h"

namespace LE {

	MeshCPU::MeshCPU(ID3D11Device* context, std::string name):m_context(context),m_name(name){
		//First add material
		m_hMaterialCPU = new Handle(sizeof(MaterialBufferCPU));
		MaterialBufferCPU *material = new(m_hMaterialCPU) MaterialBufferCPU(m_context, m_name);
		material->ReadDataFromFile();
		//Vertex Data
		m_hVertexBufferCPU = new Handle(sizeof(VertexBufferCPU));
		VertexBufferCPU *vb = new(m_hVertexBufferCPU) VertexBufferCPU(m_name);
		vb->ReadDataFromFile();
		//Index Data
		m_hIndexBufferCPU = new Handle(sizeof(IndexBufferCPU));
		IndexBufferCPU *ib = new(m_hIndexBufferCPU) IndexBufferCPU(m_name);
		ib->ReadDataFromFile();
		//Normal Data
		m_hNormalBufferCPU = new Handle(sizeof(NormalBufferCPU));
		NormalBufferCPU *nb = new(m_hVertexBufferCPU) NormalBufferCPU(m_name);
		nb->ReadDataFromFile();
		//TextureCoord Data
		m_hTextureCoordBufferCPU = new Handle(sizeof(TextureCoordBufferCPU));
		TextureCoordBufferCPU *tcb = new(m_hVertexBufferCPU) TextureCoordBufferCPU(m_name);
		tcb->ReadDataFromFile();
		//if material uses normal map probably has tangent data too.
		if (m_hMaterialCPU->getObject<MaterialBufferCPU>()->isDetailedMesh()) {
			m_hTangentBufferCPU = new Handle(sizeof(NormalBufferCPU));
			NormalBufferCPU *vb = new(m_hVertexBufferCPU) NormalBufferCPU(m_name);
			vb->ReadDataFromFile();
		}

		

	}
	
	MeshCPU::MeshCPU(ID3D11Device* context):m_context(context){}



};