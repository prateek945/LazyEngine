#pragma once
#include "../../Includes/LazyIncludes.h"
#include "../../GeneralMacros/GeneralMacros.h"

#include <d3d11.h>
namespace LE {
	class Effect {
	
		char m_EffectName[256];
		char m_ShaderBase[256];
		ID3D11VertexShader *m_vertexShader;
		ID3D11PixelShader *m_pixelShader;
		ID3D11InputLayout *m_inputLayout;

	public:
		Effect();
		Effect(const char* base,const char* name);
		void setEffectBase(const char* base);
		void getEffectBase(char* &base);
		void setEffectName(const char* name);
		void getEffectName(char* &name);
		ID3D11VertexShader* getVertexShader();
		ID3D11PixelShader* getPixelShader();
		ID3D11InputLayout* getInputLayout();
		void setVertexShader(ID3D11VertexShader* vs);
		void setPixelShader(ID3D11PixelShader* ps);
		void setInputLayout(ID3D11InputLayout* il);
		
	};

};