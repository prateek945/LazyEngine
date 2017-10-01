#pragma once
#include "../../Includes/LazyIncludes.h"
#include "../TextureCPU/Texture.h"
#include "../../Math/LEVector.h"
#include "../../Memory/Handle.h"
#include "../../LazyFiling/FileHandler.h"
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

		BaseParams m_baseParams;
		std::vector<Handle*> m_hTextures;
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_context;
		std::string m_name;
		Primitives::Bool m_bUseNormalMap;
	public:
		MaterialBufferCPU(ID3D11Device* device,ID3D11DeviceContext* context,std::string name);
		Primitives::Bool isDetailedMesh();
		void ReadDataFromFile();
		

	};
};
