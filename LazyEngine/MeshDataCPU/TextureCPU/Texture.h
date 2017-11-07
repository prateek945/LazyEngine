#pragma once
#include "../../Includes/LazyIncludes.h"
#include <string>
#include <D3D11.h>

#include "../../Utils/DDS_Loader.h"
#include "../../Memory/Handle.h"
#include "SamplerState.h"
//#include <D3D11tex.h>
namespace LE {
	enum TextureType : Primitives::Int16{
		ColorTexture = 0,
		BumpMap,
		CubeTexture
	};
	class Texture {
		char location[256];
		ID3D11Texture2D* m_texture;
		ID3D11ShaderResourceView* m_textureView;
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_context;
		TextureType textureType;
		ESamplerState samplerState;
	public:
		Texture(ID3D11Device* device, ID3D11DeviceContext* context, std::string Path, std::string FileName,TextureType tt);
		Texture(ID3D11Device* context);
		Texture(const Texture& copytex);
		bool Initialize();
		ID3D11ShaderResourceView* GetTexture();
		void Release();
		void setTextureLocation(char* loc);
		char* getTextureLocation();
	};

};
