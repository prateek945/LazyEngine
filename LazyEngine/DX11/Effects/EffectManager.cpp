#include "EffectManager.h"

namespace LE {

	EffectManager* EffectManager::m_globalInstance = 0;

	EffectManager* EffectManager::getInstance() {
		return m_globalInstance;
	}

	void EffectManager::startUp() {
		m_globalInstance = new EffectManager();
	}

	void EffectManager::addEffect(const char*base,const char* name,ShaderID layout) {

		Handle h = Handle(sizeof(Effect));
		Effect* effect = new(h.getAddress()) Effect(base,name,layout);
		char fullPath[256];
		strncpy(fullPath, base, 256);
		
		strcat(fullPath, name);
		std::string sFullPath(fullPath);
		m_hEffects[sFullPath] = h;

	}

	void EffectManager::removeEffect(const char*base, const char* name) {
		char fullPath[256];
		strncpy(fullPath, base, 256);
		strcat(fullPath, name);
		std::string sFullPath(fullPath);
		m_hEffects.erase(sFullPath);
	}

	bool EffectManager::getEffect(const char*base, const char* name,Handle &hEffect) {
		char fullPath[256];
		strncpy(fullPath, base, 256);
		strcat(fullPath, name);
		std::string sFullPath(fullPath);
		std::map<std::string, Handle>::iterator it = m_hEffects.find(sFullPath);
		if (it == m_hEffects.end()) return false;
		else hEffect = it->second;
		return true;

	}

	std::map<std::string, Handle> EffectManager::getAllEffects() {
		return m_hEffects;

	}

};