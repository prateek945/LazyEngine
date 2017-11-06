#pragma once
#include "../../Includes/LazyIncludes.h"
#include "../../Memory/Handle.h"
#include "../../GeneralMacros/GeneralMacros.h"
#include "../../Utils/LArray.h"
#include <map>
#include "Effect.h"
namespace LE {
	class EffectManager {

		std::map<std::string, Handle> m_hEffects;
		static EffectManager *m_globalInstance;
	public:

		EffectManager() {};
		~EffectManager() {};

		void startUp();
		static EffectManager* getInstance();
		void addEffect(const char* base,const char* name,ShaderID layout);
		void removeEffect(const char* base,const char* name);
		bool getEffect(const char* base,const char* name,Handle &hEffect);
		std::map<std::string, Handle> getAllEffects();

	};

};
