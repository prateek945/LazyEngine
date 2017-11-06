#include "Texture.h"

namespace LE {

	Texture::Texture(ID3D11Device* device, ID3D11DeviceContext* context,std::string Path, std::string FileName, TextureType tt){
		strncpy(location, "", 256);
		strncpy(location, Path.c_str(), 256);
		strcat(location, FileName.c_str());
		m_device = device;
		m_context = context;
		m_texture = 0;
		m_textureView = 0;
		textureType = tt;
	}
	Texture::Texture(ID3D11Device* device){
		
		m_texture = 0;
	}
	Texture::Texture(const Texture& copytex){
		*this = copytex;
	}
	bool Texture::Initialize(){
		HRESULT hr = NULL;
		if (strcmp(location,"") != 0) {
			WCHAR path ; 
		//	mbstowcs(&path, location.c_str(), 256);
			DDS::DDSTextureInSystemMemory dds;
			DDS::loadDDSFromFile(location, &dds);
			bool willHaveMips = false;
			if (dds.mips > 0)
				willHaveMips = true;
			DXGI_FORMAT destApiFormat = DXGI_FORMAT_UNKNOWN;
			if (dds.components == 1)
			{
				if (dds.uncompressedFormat == DDS_LUMINANCE)
					destApiFormat = DXGI_FORMAT_R8_UNORM;
			}
			else if (dds.components == 4)
			{
				if (dds.uncompressedFormat == DDS_RGBA)
					destApiFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
				else if (dds.uncompressedFormat == DDS_RGB)
					destApiFormat = DXGI_FORMAT_B8G8R8X8_UNORM;
			}
			

			D3D11_TEXTURE2D_DESC desc;
			desc.Width = dds.width;
			desc.Height = dds.height;
			desc.MipLevels = willHaveMips ? 0 : 1;
			desc.ArraySize = 1;
			desc.Format = destApiFormat;
			desc.SampleDesc.Count = 1;
			desc.SampleDesc.Quality = 0;
			desc.Usage = D3D11_USAGE_IMMUTABLE; // immutable since data wont change
			desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;


			D3D11_SUBRESOURCE_DATA datas[32];
			Primitives::Int32 w, h;
			w = dds.width;
			h = dds.height;
			//in case mips are already loaded (and not generated) we need to pass in array of the datas
			for (uint32_t i = 0; i < dds.mips; i++)
			{
				D3D11_SUBRESOURCE_DATA &data = datas[i];
				data.pSysMem = dds.image[0].pixels[/*mip=*/i];
				data.SysMemPitch = dds.components * w;
				data.SysMemSlicePitch = 0; // unused since 2d texture

				w /= 2; h /= 2;
				if (w == 0) w = 1;
				if (h == 0) h = 1;
			}
			//hr = DirectX::CreateWICTextureFromFile(m_device,m_context,&path,&m_texture,&m_textureView);
			hr = m_device->CreateTexture2D(&desc, datas, &m_texture);
			if (!SUCCEEDED(hr)) return false;
			hr = m_device->CreateShaderResourceView(m_texture, NULL, &m_textureView);
		}
		if (SUCCEEDED(hr)) return true;
		return false;

	}
	ID3D11ShaderResourceView* Texture::GetTexture(){
		return m_textureView;
	}
	void Texture::Release(){
		if (m_textureView) {
			m_textureView->Release();
			m_textureView = 0;
		}
	}

	char* Texture::getTextureLocation() {
		if (strcmp(location, "") != 0) return location;
		return false;
	}

	void Texture::setTextureLocation(char* loc) {
		location[0] = *loc;
		if (m_texture) {
			Release();
			Initialize();
		}
		else {
			Initialize();
		}
	}
};