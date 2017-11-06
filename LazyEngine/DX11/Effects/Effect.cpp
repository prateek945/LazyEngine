#include "Effect.h"

namespace LE {
	Effect::Effect() :m_ShaderBase(""),m_EffectName("") ,m_vertexShader(NULL), m_pixelShader(NULL) {}

	Effect::Effect(const char* base,const char* name,ShaderID layout) : m_vertexShader(NULL), m_pixelShader(NULL), m_layout(layout){
		strncpy(m_ShaderBase, base, 256);
		strncpy(m_EffectName, name, 256);
	}

	void Effect::setEffectBase(const char* base) {
		strncpy(m_ShaderBase, base, 256);
	}

	void Effect::getEffectBase(char* &base) {
		strncpy(base, m_ShaderBase, 256);
	}

	void Effect::setEffectName(const char* name) {
		strncpy(m_EffectName, name, 256);
	}

	void Effect::getEffectName(char* &name) {
		strncpy(name, m_EffectName, 256);
	}

	ID3D11VertexShader* Effect::getVertexShader() {

		return m_vertexShader;

	}

	ID3D11PixelShader* Effect::getPixelShader() {

		return m_pixelShader;

	}
	ID3D11InputLayout* Effect::getInputLayout() {

		return m_inputLayout;
	}
	void Effect::setVertexShader(ID3D11VertexShader* vs) {

		m_vertexShader = vs;

	}
	void Effect::setPixelShader(ID3D11PixelShader* ps) {

		m_pixelShader = ps;
	}
	void Effect::setInputLayout(ID3D11InputLayout* il) {

		m_inputLayout = il;
	}
	
};