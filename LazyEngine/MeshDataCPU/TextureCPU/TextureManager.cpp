#include "TextureManager.h"

namespace LE {

	TextureManager* TextureManager::m_globalInstance = 0;

	TextureManager* TextureManager::getInstance() {
		return m_globalInstance;
	}

	void TextureManager::startUp(ID3D11Device* device, ID3D11DeviceContext* context) {
		
		m_globalInstance = new TextureManager();
		m_globalInstance->m_pDevice = device;
		m_globalInstance->m_pContext = context;
		SamplerStateManager::getInstance()->startUp(device, context);
		
	}

	void TextureManager::addTexture(const char* base, const char* name,TextureType tt) {

		Handle h_texture(sizeof(Texture));
		std::string path = string(base);
		string text_name = string(name);
		path.append(text_name);
		Texture* tex = new(h_texture.getAddress()) Texture(m_pDevice,m_pContext,path,text_name,tt);
		m_hTextures[path] = h_texture;

	}
	void TextureManager::removeTexture(const char* base, const char* name) {
		std::string path = string(base);
		string text_name = string(name);
		path.append(text_name);
		m_hTextures.erase(path);
	}
	bool TextureManager::getTexture(const char* base, const char* name, Handle &hTexture) {
		std::string path = string(base);
		string text_name = string(name);
		path.append(text_name);
		if (m_hTextures.find(path) == m_hTextures.end()) return false;
		hTexture = m_hTextures[path];
		return true;
	}
	std::map<std::string, Handle> TextureManager::getAllTextures() {
		return m_hTextures;
	}

};
