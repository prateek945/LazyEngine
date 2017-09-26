#pragma once
#include "../../Includes/LazyIncludes.h"
#include <string>
#include <D3D11.h>
//#include <D3D11tex.h>
namespace LE {
	
	class Texture {
		std::string location;
		ID3D11ShaderResourceView* m_texture;
		ID3D11Device* m_context;
	public:
		Texture(std::string Path, std::string FileName,ID3D11Device* context);
		Texture(ID3D11Device* context);
		Texture(const Texture& copytex);
		bool Initialize();
		ID3D11ShaderResourceView* GetTexture();
		void Release();
		void setTextureLocation(std::string loc);
		std::string getTextureLocation();
	};

};
