#pragma once
#ifndef RENDERER_H_
#define RENDERER_H_

#include "DeviceManager.h"
#include "ShaderIDEnum.h"
#include "CameraUtils/Camera.h"
#include "../Memory/Handle.h"
#include "../Math/Matrix4X4.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <memory>
#include <DirectXMath.h>
namespace LE {


	//-----------------------------------------------------------------------------
	// Class declarations
	//-----------------------------------------------------------------------------
	
	class Renderer
	{
	public:
		Renderer(std::shared_ptr<DeviceResources> deviceResources);
		~Renderer();
		Handle *m_hMainCamera;
		std::unique_ptr<DirectX::Keyboard> m_keyboard;
		std::unique_ptr<DirectX::Mouse> m_mouse;
		std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> tracker;
		void CreateDeviceDependentResources(std::shared_ptr<LevelLoader> levelLoader);
		void CreateWindowSizeDependentResources();
		void Update(std::shared_ptr<LevelLoader>);
		void Render(std::shared_ptr<LevelLoader>);

	private:
		HRESULT CompileShaders(std::shared_ptr<LevelLoader> levelLoader);
		HRESULT CreateGPUBuffers(std::shared_ptr<LevelLoader> levelLoader);
		void    CreateViewAndPerspective();
		
		//-----------------------------------------------------------------------------
		// Pointer to device resource manager
		//-----------------------------------------------------------------------------
		std::shared_ptr<DeviceResources> m_deviceResources;

		//-----------------------------------------------------------------------------
		// Variables for rendering the cube
		//-----------------------------------------------------------------------------
		typedef struct _constantBufferStruct {
			Matrix4X4 world;
			Matrix4X4 view;
			Matrix4X4 projection;
			LEVector3 color;
			float aplha;
			float eyePos[4];
			float detailedMesh[4];
			float toggles[4];
			
		} ConstantBufferStruct;
		
		
		// Assert that the constant buffer remains 16-byte aligned.
		static_assert((sizeof(ConstantBufferStruct) % 16) == 0, "Constant Buffer size must be 16-byte aligned");

		//-----------------------------------------------------------------------------
		// Per-vertex data
		//-----------------------------------------------------------------------------
		typedef struct _vertexPositionTexCoord
		{
			LEVector3 pos;
			Primitives::Float32 textCoords[2];
		} VertexPositionTexCoord;

		//-----------------------------------------------------------------------------
		// Per-vertex data (extended)
		//-----------------------------------------------------------------------------
		typedef struct _vertexPositionNormalTangent
		{
			LEVector3 pos;
			Primitives::Float32 textCoords[2];
			LEVector3 normal;
			LEVector3 tangent;
		} VertexPositionNormalTangent;

		ConstantBufferStruct m_constantBufferData;
		unsigned int  m_indexCount;
		unsigned int  m_frameCount;

		//Toggle Values

		bool toggleBuffers_ADNS[4] = { true,false,false, false };
		//Global Object array

		std::vector<WCHAR*> shaderFiles;
		//-----------------------------------------------------------------------------
		// Direct3D device resources
		//-----------------------------------------------------------------------------
		//ID3DXEffect* m_pEffect;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			m_pGBufferDiffuse;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			m_pGBufferNormal;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			m_pGBufferSpecular;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			m_pGBufferDepth;
		
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>			m_pSRVGBufferDiffuse;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>			m_pSRVGBufferNormal;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>			m_pSRVGBufferSpecular;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>			m_pSRVGBufferDepth;

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>			m_pRTGBufferDiffuse;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>			m_pRTGBufferNormal;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>			m_pRTGBufferSpecular;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>			m_pRTLightPass;

		ID3D11ShaderResourceView* m_SRVArray[3];
		ID3D11RenderTargetView* m_renderTargetViewArray[4];

		Microsoft::WRL::ComPtr<ID3D11Buffer>            m_pVertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer>            m_pIndexBuffer;

		Microsoft::WRL::ComPtr<ID3D11Buffer>            m_pVertrexBufferQuad;
		Microsoft::WRL::ComPtr<ID3D11Buffer>            m_pIndexBufferQuad;
		std::vector<std::pair<ShaderID,Microsoft::WRL::ComPtr<ID3D11VertexShader>>>      m_pVertexShaders;
		std::vector<std::pair<ShaderID, Microsoft::WRL::ComPtr<ID3D11InputLayout>>>      m_pInputLayouts;
		std::vector<std::pair<ShaderID, Microsoft::WRL::ComPtr<ID3D11PixelShader>>>      m_pPixelShaders;
		Microsoft::WRL::ComPtr<ID3D11Buffer>            m_pConstantBuffer;
		map<ShaderID, D3D11_INPUT_ELEMENT_DESC>		m_inputLayouts;
	};
};
#endif