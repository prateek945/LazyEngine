#pragma once
#include "../../Includes/LazyIncludes.h"
#include <d3d11.h>

namespace LE {
	enum ESamplerState : UINT8 {

		Sampler_State_Min_Mag_Mip_Linear_U_V_W_Wrap

	};
	struct SamplerState {
		ID3D11SamplerState* m_pSamplerState;
	};

};
