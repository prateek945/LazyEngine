#pragma once

#include "../../Includes/LazyIncludes.h"
#include "../../GeneralMacros/GeneralMacros.h"
#include "../../Memory/Handle.h"
#include "SamplerState.h"
#include <map>
namespace LE {

	class SamplerStateManager {

		static SamplerStateManager* m_globalInstance;
		std::map<ESamplerState, SamplerState> m_samplerStates;
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pContext;
	public:

		SamplerStateManager();
		~SamplerStateManager();
		static SamplerStateManager* getInstance();
		void startUp(ID3D11Device* device, ID3D11DeviceContext* context);
		void setUpAllSamplerStates();
		SamplerState getSamplerState(ESamplerState);


	};

};
