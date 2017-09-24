#ifndef MESHCPU_H_
#define MESHCPU_H_
#include "../Includes/LazyIncludes.h"
#include "../Memory/Handle.h"
#include "../Math/LEVector.h"
#include "VertexBufferCPU\VertexBufferCPU.h"
#include "NormalBufferCPU\NormalBufferCPU.h"
#include "MaterialBufferCPU\MaterialBufferCPU.h"
#include "TextureCoordBufferCPU\TextureCoordBufferCPU.h"
#include <D3D11.h>
#include <string>
namespace LE {
	class MeshCPU {
	public:
		Handle* m_hVertexBufferCPU,m_hNormalBufferCPU,m_hTextureCoordBufferCPU,m_hMaterialCPU;
		Primitives::Bool useTextures,hasTangentBuffer;
		ID3D11Device* m_context;
		std::string m_name;
		MeshCPU(ID3D11Device *context,std::string name);
		MeshCPU(ID3D11Device* context);
		void ReadDataFromFile();
	};
};

#endif