#pragma once
#include "../../Includes/LazyIncludes.h"
#include "../TextureCPU/Texture.h"
#include "../../Math/LEVector.h"
#include "../../Memory/Handle.h"
#include <string>
#include <vector>
namespace LE {
	struct BaseParams {
		LEVector3 color;
		Primitives::Float32 alpha;
		Primitives::Float32 specular;
		Primitives::Float32 num_textures;
		Primitives::Float32 emissive;
	};
	class MaterialBufferCPU {

		BaseParams m_baseParams;
		std::vector<Handle*> m_hTextures;

	public:
		MaterialBufferCPU();
		void ReadDataFromFile();
		

	};
};
