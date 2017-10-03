#include "Texture.h"

namespace LE {

	Texture::Texture(ID3D11Device* device, ID3D11DeviceContext* context,std::string Path, std::string FileName){
		location = std::string(Path + FileName);
		m_device = device;
		m_context = context;
		m_texture = 0;
		m_textureView = 0;
	}
	Texture::Texture(ID3D11Device* device){
		
		m_texture = 0;
	}
	Texture::Texture(const Texture& copytex){
		*this = copytex;
	}
	bool Texture::Initialize(){
		HRESULT hr;
		if (!location.empty()) {
			WCHAR *path = nullptr; 
			mbstowcs(path, location.c_str(), 256);
			
			hr = DirectX::CreateWICTextureFromFile(m_device,m_context,path,&m_texture,&m_textureView);
			
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

	std::string Texture::getTextureLocation() {
		if (!location.empty()) return location;
		return false;
	}

	void Texture::setTextureLocation(std::string loc) {
		location = loc;
		if (m_texture) {
			Release();
			Initialize();
		}
		else {
			Initialize();
		}
	}
};