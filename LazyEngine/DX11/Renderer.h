#pragma once
#ifndef RENDERER_H_
#define RENDERER_H_

#include "DeviceManager.h"
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

		void CreateDeviceDependentResources(std::shared_ptr<LevelLoader> levelLoader);
		void CreateWindowSizeDependentResources();
		void Update(std::shared_ptr<LevelLoader>);
		void Render(std::shared_ptr<LevelLoader>);

	private:
		HRESULT CreateShaders();
		HRESULT CreateCube(std::shared_ptr<LevelLoader> levelLoader);
		void    CreateViewAndPerspective();

		//-----------------------------------------------------------------------------
		// Pointer to device resource manager
		//-----------------------------------------------------------------------------
		std::shared_ptr<DeviceResources> m_deviceResources;

		//-----------------------------------------------------------------------------
		// Variables for rendering the cube
		//-----------------------------------------------------------------------------
		typedef struct _constantBufferStruct {
			DirectX::XMFLOAT4X4 world;
			DirectX::XMFLOAT4X4 view;
			DirectX::XMFLOAT4X4 projection;
			DirectX::XMFLOAT4 framecount;
			DirectX::XMFLOAT4 color;
		} ConstantBufferStruct;

		// Assert that the constant buffer remains 16-byte aligned.
		static_assert((sizeof(ConstantBufferStruct) % 16) == 0, "Constant Buffer size must be 16-byte aligned");

		//-----------------------------------------------------------------------------
		// Per-vertex data
		//-----------------------------------------------------------------------------
		typedef struct _vertexPositionColor
		{
			DirectX::XMFLOAT3 pos;
			DirectX::XMFLOAT3 color;
			DirectX::XMFLOAT3 normal;
		} VertexPositionColor;

		//-----------------------------------------------------------------------------
		// Per-vertex data (extended)
		//-----------------------------------------------------------------------------
		typedef struct _vertexPositionColorTangent
		{
			DirectX::XMFLOAT3 pos;
			DirectX::XMFLOAT3 normal;
			DirectX::XMFLOAT3 tangent;
		} VertexPositionColorTangent;

		ConstantBufferStruct m_constantBufferData;
		unsigned int  m_indexCount;
		unsigned int  m_frameCount;

		//Global Object array


		//-----------------------------------------------------------------------------
		// Direct3D device resources
		//-----------------------------------------------------------------------------
		//ID3DXEffect* m_pEffect;
		Microsoft::WRL::ComPtr<ID3D11Buffer>            m_pVertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer>            m_pIndexBuffer;
		Microsoft::WRL::ComPtr<ID3D11VertexShader>      m_pVertexShader;
		Microsoft::WRL::ComPtr<ID3D11InputLayout>       m_pInputLayout;
		Microsoft::WRL::ComPtr<ID3D11InputLayout>       m_pInputLayoutExtended;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>       m_pPixelShader;
		Microsoft::WRL::ComPtr<ID3D11Buffer>            m_pConstantBuffer;
	};
};
#endif