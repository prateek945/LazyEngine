#include "SamplerStateManager.h"

namespace LE {

	SamplerStateManager* SamplerStateManager::m_globalInstance = 0;


	SamplerStateManager* SamplerStateManager::getInstance() {

		return m_globalInstance;
	}
	SamplerStateManager::SamplerStateManager(){}
	SamplerStateManager::~SamplerStateManager(){}
	void SamplerStateManager::startUp(ID3D11Device* device, ID3D11DeviceContext* context) {

		m_globalInstance = new SamplerStateManager();
		m_globalInstance->m_pDevice = device;
		m_globalInstance->m_pContext = context;
		m_globalInstance->setUpAllSamplerStates();

	}
	void SamplerStateManager::setUpAllSamplerStates() {

		SamplerState ss;
		D3D11_SAMPLER_DESC desc;
		memset(&desc, 0, sizeof(D3D11_SAMPLER_DESC));
		//desc for Sampler_State_Min_Mag_Mip_Linear_U_V_W_Wrap
		desc.MaxAnisotropy = 16;
		desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
		desc.MaxLOD = D3D11_FLOAT32_MAX;
		desc.MinLOD = 1;
		desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		FLOAT borderColor[] = { 0.0,0.0,0.0,1.0 };
		memcpy(desc.BorderColor, borderColor, sizeof(FLOAT) * 4);
		ESamplerState ESS = ESamplerState::Sampler_State_Min_Mag_Mip_Linear_U_V_W_Wrap;
		m_pDevice->CreateSamplerState(&desc, &ss.m_pSamplerState);
		m_samplerStates[ESS] = ss;

	}

	SamplerState SamplerStateManager::getSamplerState(ESamplerState ESS) {

		if (m_samplerStates.find(ESS) != m_samplerStates.end()) {

			return m_samplerStates[ESS];

		}

	}
};