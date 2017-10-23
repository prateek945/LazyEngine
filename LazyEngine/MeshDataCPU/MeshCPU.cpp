#include "MeshCPU.h"

namespace LE {

	MeshCPU::MeshCPU(ID3D11Device* device,ID3D11DeviceContext* context, std::string name):m_context(context),m_device(device),m_name(name){
		//First add material
		m_name = name;
		m_device = device;
		m_context = context;
		m_hMaterialCPU = Handle(sizeof(MaterialBufferCPU));
		void* add = m_hMaterialCPU.getAddress();
		MaterialBufferCPU *material = new(m_hMaterialCPU.getAddress()) MaterialBufferCPU(m_device,m_context, m_name);
		material->ReadDataFromFile();
		//Vertex Data
		m_hVertexBufferCPU = Handle(sizeof(VertexBufferCPU));
		VertexBufferCPU *vb = new(m_hVertexBufferCPU.getAddress()) VertexBufferCPU(m_name);
		vb->ReadDataFromFile();
		//Index Data
		m_hIndexBufferCPU =  Handle(sizeof(IndexBufferCPU));
		IndexBufferCPU *ib = new(m_hIndexBufferCPU.getAddress()) IndexBufferCPU(m_name);
		ib->ReadDataFromFile();
		//Normal Data
		m_hNormalBufferCPU =  Handle(sizeof(NormalBufferCPU));
		NormalBufferCPU *nb = new(m_hNormalBufferCPU.getAddress()) NormalBufferCPU(m_name);
		nb->ReadDataFromFile();
		//TextureCoord Data
		m_hTextureCoordBufferCPU =  Handle(sizeof(TextureCoordBufferCPU));
		TextureCoordBufferCPU *tcb = new(m_hTextureCoordBufferCPU.getAddress()) TextureCoordBufferCPU(m_name);
		tcb->ReadDataFromFile();
		//if material uses normal map probably has tangent data too.
		if (m_hMaterialCPU.getObject<MaterialBufferCPU>()->isDetailedMesh()) {
			m_hTangentBufferCPU = Handle(sizeof(NormalBufferCPU));
			NormalBufferCPU *tanb = new(m_hTangentBufferCPU.getAddress()) NormalBufferCPU(m_name);
			tanb->ReadDataFromFile();
		}

		

	}
	
	MeshCPU::MeshCPU(ID3D11Device* device,ID3D11DeviceContext* context):m_context(context),m_device(device){}



};