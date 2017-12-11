#include "MaterialBufferCPU.h"

namespace LE {

	MaterialBufferCPU::MaterialBufferCPU(ID3D11Device* device,ID3D11DeviceContext* context,std::string name){
		
		m_device = (device);
		m_context = (context);
		m_bUseNormalMap = (false);
		strncpy(m_name, name.c_str(), 256);
	}

	void MaterialBufferCPU::ReadDataFromFile() {

		char base[1024];
		strcpy(base, "..\\LazyEngine\\meshes\\Material\\");
		strcat(base, m_name);
		strcat(base, ".mat");
		FileReader fr(base);

		Primitives::Float32 colorComponents,Emissive;
		fr.readNextFloat(colorComponents);
		color[0]= colorComponents;

		fr.readNextFloat(colorComponents);
		color[1] = colorComponents;

		fr.readNextFloat(colorComponents);
		color[2] = colorComponents;

		fr.readNextFloat(colorComponents);
		alpha = colorComponents;
		
		fr.readNextFloat(Emissive);
		emissive = Emissive;

		fr.readNextInt(num_textures);
		m_hTextures.setSize(num_textures);
		char texturePath[1024] = "..\\LazyEngine\\meshes\\Textures\\";
		char textureType[256];
		char texFileName[256];
		TextureType type;
		for (unsigned int j = 0; j < num_textures; j++) {
			fr.readNextNonEmptyLine(textureType, 256);
			if (strcmp(textureType, "NormalMap") == 0) {
				type = TextureType::BumpMap;
				m_bUseNormalMap = true;
			}
			else {
				type = TextureType::ColorTexture;
			}
			fr.readNextNonEmptyLine(texFileName, 256);
			
			Handle hTexture = Handle(sizeof(Texture));
			if (!TextureManager::getInstance()->getTexture(texturePath, texFileName, hTexture))
			{
				TextureManager::getInstance()->addTexture(texturePath, texFileName, type);
				TextureManager::getInstance()->getTexture(texturePath, texFileName, hTexture);
			}
			m_hTextures.addElement(hTexture);

		}
		fr.~FileReader();

	}

	Primitives::Bool MaterialBufferCPU::isDetailedMesh() {

		return m_bUseNormalMap;

	}

	
};