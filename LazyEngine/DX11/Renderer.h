#pragma once
#ifndef RENDERER_H_
#define RENDERER_H_

#include "DeviceManager.h"
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
			Matrix4X4 world;
			Matrix4X4 view;
			Matrix4X4 projection;
			LEVector3 color;
			float aplha;
			
		} ConstantBufferStruct;

		// Assert that the constant buffer remains 16-byte aligned.
		static_assert((sizeof(ConstantBufferStruct) % 16) == 0, "Constant Buffer size must be 16-byte aligned");

		//-----------------------------------------------------------------------------
		// Per-vertex data
		//-----------------------------------------------------------------------------
		typedef struct _vertexPositionColor
		{
			LEVector3 pos;
			LEVector3 color;
			LEVector3 normal;
		} VertexPositionColor;

		//-----------------------------------------------------------------------------
		// Per-vertex data (extended)
		//-----------------------------------------------------------------------------
		typedef struct _vertexPositionColorTangent
		{
			LEVector3 pos;
			LEVector3 normal;
			LEVector3 tangent;
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