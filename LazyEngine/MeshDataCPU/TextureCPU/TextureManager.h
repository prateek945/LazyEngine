#pragma once
#include "../../Includes/LazyIncludes.h"
#include "../../GeneralMacros/GeneralMacros.h"
#include "../../Memory/Handle.h"
#include "Texture.h"
#include "SamplerState.h"
#include <map>
#include <string>
namespace LE {

	class TextureManager {

		map<string, Handle> m_hTextures;
		map<ESamplerState, Handle> m_hSamplerStates;
		static TextureManager *m_globalInstance;
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pContext;

	public:

		TextureManager() {};
		~TextureManager() {};

		void startUp(ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pContext);
		static TextureManager* getInstance();
		void addTexture(const char* base, const char* name, TextureType tt);
		void removeTexture(const char* base, const char* name);
		bool getTexture(const char* base, const char* name, Handle &hEffect);
		map<string, Handle> getAllTextures();
		
	};
};