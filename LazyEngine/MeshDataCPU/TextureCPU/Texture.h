#pragma once
#include "../../Includes/LazyIncludes.h"
#include <string>
#include <D3D11.h>
#include <WICTextureLoader.h>
#include "../../Memory/Handle.h"
//#include <D3D11tex.h>
namespace LE {
	
	class Texture {
		std::string location;
		ID3D11Resource* m_texture;
		ID3D11ShaderResourceView* m_textureView;
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_context;
		Handle *h_texturedata;
	public:
		Texture(ID3D11Device* device, ID3D11DeviceContext* context, std::string Path, std::string FileName);
		Texture(ID3D11Device* context);
		Texture(const Texture& copytex);
		bool Initialize();
		ID3D11ShaderResourceView* GetTexture();
		void Release();
		void setTextureLocation(std::string loc);
		std::string getTextureLocation();
	};

};
