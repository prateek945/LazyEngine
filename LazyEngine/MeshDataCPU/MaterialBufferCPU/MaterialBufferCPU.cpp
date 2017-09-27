#include "MaterialBufferCPU.h"

namespace LE {

	MaterialBufferCPU::MaterialBufferCPU(ID3D11Device* context,std::string name):m_context(context),m_name(name),m_bUseNormalMap(false){}

	void MaterialBufferCPU::ReadDataFromFile() {

		char base[1024];
		strcpy(base, "..\\LazyEngine\\meshes\\Material\\");
		strcat(base, m_name.c_str());
		strcat(base, ".mat");
		FileReader fr(base);

		Primitives::Float32 colorComponents,Emissive;
		fr.readNextFloat(colorComponents);
		m_baseParams.color.m_x = colorComponents;

		fr.readNextFloat(colorComponents);
		m_baseParams.color.m_y = colorComponents;

		fr.readNextFloat(colorComponents);
		m_baseParams.color.m_z = colorComponents;

		fr.readNextFloat(colorComponents);
		m_baseParams.alpha = colorComponents;
		
		fr.readNextFloat(Emissive);
		m_baseParams.emissive = Emissive;

		fr.readNextInt(m_baseParams.num_textures);
		
		char texturePath[1024] = "..\\LazyEngine\\meshes\\Textures\\";
		char textureType[256];
		char texFileName[256];
		for (unsigned int j = 0; j < m_baseParams.num_textures; j++) {
			fr.readNextNonEmptyLine(textureType, 256);
			if (strcmp(textureType, "NormalMap")) m_bUseNormalMap = true;
			
			fr.readNextNonEmptyLine(texFileName, 256);
			Handle* hTexture = new Handle(sizeof(Texture));
			Texture *tex = new(hTexture) Texture(texturePath, texFileName, m_context);
			m_hTextures.push_back(hTexture);
		}


	}

	Primitives::Bool MaterialBufferCPU::isDetailedMesh() {

		return m_bUseNormalMap;

	}

	
};