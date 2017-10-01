#ifndef MESHCPU_H_
#define MESHCPU_H_
#include "../Includes/LazyIncludes.h"
#include "../Memory/Handle.h"
#include "../Math/LEVector.h"

#include "VertexBufferCPU\VertexBufferCPU.h"
#include "IndexBufferCPU\IndexBufferCPU.h"
#include "NormalBufferCPU\NormalBufferCPU.h"
#include "MaterialBufferCPU\MaterialBufferCPU.h"
#include "TextureCoordBufferCPU\TextureCoordBufferCPU.h"
#include <D3D11.h>
#include <string>

namespace LE {
	class MeshCPU {
	public:
		Handle *m_hVertexBufferCPU,*m_hIndexBufferCPU,*m_hNormalBufferCPU,*m_hTextureCoordBufferCPU,*m_hMaterialCPU,*m_hTangentBufferCPU;
		Primitives::Bool useTextures,hasTangentBuffer;
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_context;
		std::string m_name;
		MeshCPU(ID3D11Device *device,ID3D11DeviceContext* context,std::string name);
		MeshCPU(ID3D11Device* device,ID3D11DeviceContext* context);
		void ReadDataFromFile();
	};
};

#endif