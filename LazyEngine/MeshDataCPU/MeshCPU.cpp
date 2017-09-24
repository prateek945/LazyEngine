#include "MeshCPU.h"

namespace LE {

	MeshCPU::MeshCPU(ID3D11Device* context, std::string name):m_context(context),m_name(name){
			m_hMaterialCPU = new(MaterialCPU)
	}
	
	MeshCPU::MeshCPU(ID3D11Device* context):m_context(context){}



};