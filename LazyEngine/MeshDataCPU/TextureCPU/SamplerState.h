#pragma once
#include "../../Includes/LazyIncludes.h"
#include <d3d11.h>

namespace LE {
	enum ESamplerState {

	};
	class SamplerState {
		ID3D11SamplerState* m_pSamplerState;
	public:
		SamplerState();
		
		void InitialiseSampler();

	};

};
