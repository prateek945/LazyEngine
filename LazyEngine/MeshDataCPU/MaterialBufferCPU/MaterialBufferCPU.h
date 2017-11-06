#pragma once
#include "../../Includes/LazyIncludes.h"
#include "../TextureCPU/Texture.h"
#include "../../Math/LEVector.h"
#include "../../Memory/Handle.h"
#include "../../LazyFiling/FileHandler.h"
#include "../../Utils/LArray.h"
#include "../TextureCPU/TextureManager.h"
#include <string>
#include <vector>
namespace LE {
	struct BaseParams {
		LEVector3 color;
		Primitives::Float32 alpha;
		Primitives::Float32 specular;
		Primitives::Int32 num_textures;
		Primitives::Float32 emissive;
	};
	class MaterialBufferCPU {

		float color[3];
		Primitives::Float32 alpha;
		Primitives::Float32 specular;
		Primitives::Int32 num_textures;
		Primitives::Float32 emissive;
		LArray<Handle> m_hTextures;
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_context;
		char m_name[256];
		Primitives::Bool m_bUseNormalMap;
	public:
		MaterialBufferCPU(ID3D11Device* device,ID3D11DeviceContext* context,std::string name);
		Primitives::Bool isDetailedMesh();
		void ReadDataFromFile();
		

	};
};
