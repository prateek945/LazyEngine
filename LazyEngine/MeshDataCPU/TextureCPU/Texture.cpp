#include "Texture.h"

namespace LE {

	Texture::Texture(std::string Path, std::string FileName,ID3D11Device* context){
		location = std::string(Path + FileName);
		m_context = context;
		m_texture = 0;
	}
	Texture::Texture(ID3D11Device* context){
		m_context = context;
		m_texture = 0;
	}
	Texture::Texture(const Texture& copytex){
		*this = copytex;
	}
	bool Texture::Initialize(){
		HRESULT hr;
		if (!location.empty()) {
			hr = D3DX11CreateShaderResourceViewFromFile(m_context, location.c_str(), NULL, NULL, &m_texture, NULL);
		}
		if (SUCCEEDED(hr)) return true;
		return false;

	}
	ID3D11ShaderResourceView* Texture::GetTexture(){
		return m_texture;
	}
	void Texture::Release(){
		if (m_texture) {
			m_texture->Release();
			m_texture = 0;
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