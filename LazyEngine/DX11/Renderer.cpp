#include <string>
#include <ppltasks.h>
#include <D3Dcompiler.h>

#include "Renderer.h"

namespace LE {



	//-----------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------
	Renderer::Renderer(std::shared_ptr<DeviceResources> deviceResources)
		:
		m_frameCount(0),
		m_deviceResources(deviceResources)
	{
		m_frameCount = 0; // init frame count
	}

	//-----------------------------------------------------------------------------
	// Create Direct3D shader resources by loading the .cso files.
	//-----------------------------------------------------------------------------
	HRESULT Renderer::CreateShaders()
	{
		HRESULT hr = S_OK;

		// Use the Direct3D device to load resources into graphics memory.
		ID3D11Device* device = m_deviceResources->GetDevice();
		DWORD dwShaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
		// Set the D3D10_SHADER_DEBUG flag to embed debug information in the shaders.
		// Setting this flag improves the shader debugging experience, but still allows 
		// the shaders to be optimized and to run exactly the way they will run in 
		// the release configuration of this program.
		dwShaderFlags |= D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#endif
		// You'll need to use a file loader to load the shader bytecode. In this
		// example, we just use the standard library.
		
		ID3DBlob* compiledCodeBlob = NULL;
		ID3DBlob* errorBlob = NULL;
		WCHAR *shaderFile = L"C:\\LazyEngine\\LazyEngine\\LazyEngine\\DX11\\CubeVertexShader.hlsl";
		
		hr = D3DCompileFromFile(
			shaderFile,
			NULL,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main",
			"vs_4_1",
			dwShaderFlags,
			0,
			&compiledCodeBlob,
			&errorBlob
		);
		if (errorBlob) {
			OutputDebugStringA((LPCSTR)errorBlob->GetBufferPointer());
		}
		hr = device->CreateVertexShader(
			compiledCodeBlob->GetBufferPointer(),
			compiledCodeBlob->GetBufferSize(),
			nullptr,
			&m_pVertexShader
		);
		
		D3D11_INPUT_ELEMENT_DESC iaDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
			0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },

			{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT,
			0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },

			{"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,
			0,24,D3D11_INPUT_PER_VERTEX_DATA,0}
		};

		hr = device->CreateInputLayout(
			iaDesc,
			ARRAYSIZE(iaDesc),
			compiledCodeBlob->GetBufferPointer(),
			compiledCodeBlob->GetBufferSize(),
			&m_pInputLayout
		);

		compiledCodeBlob = NULL;
		errorBlob = NULL;


		shaderFile = L"C:\\LazyEngine\\LazyEngine\\LazyEngine\\DX11\\CubePixelShader.hlsl";

		hr = D3DCompileFromFile(
			shaderFile,
			NULL,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main",
			"ps_4_1",
			dwShaderFlags,
			0,
			&compiledCodeBlob,
			&errorBlob
		);
		if (errorBlob) {
			OutputDebugStringA((LPCSTR)errorBlob->GetBufferPointer());
		}
		hr = device->CreatePixelShader(
			compiledCodeBlob->GetBufferPointer(),
			compiledCodeBlob->GetBufferSize(),
			nullptr,
			m_pPixelShader.GetAddressOf()
		);

	

		CD3D11_BUFFER_DESC cbDesc(
			sizeof(ConstantBufferStruct),
			D3D11_BIND_CONSTANT_BUFFER
		);

		hr = device->CreateBuffer(
			&cbDesc,
			nullptr,
			m_pConstantBuffer.GetAddressOf()
		);
		return hr;
	}

	HRESULT Renderer::CreateCube(std::shared_ptr<LevelLoader> levelLoader)
	{
		HRESULT hr = S_OK;

		// Use the Direct3D device to load resources into graphics memory.
		ID3D11Device* device = m_deviceResources->GetDevice();
		vector<VertexPositionColor> allVerts ;
		// Create cube geometry.
		int numgpuverts = ((levelLoader.get()->gpubuffer.m_vertices.size()*4) / sizeof(VertexPositionColor));
		int vertsize = sizeof(VertexPositionColor) / 4;
		for (unsigned int i = 0; i < numgpuverts; i++) {
			VertexPositionColor vpc = {};
			vpc.pos.x = levelLoader.get()->gpubuffer.m_vertices.at(vertsize*i);
			vpc.pos.y = (levelLoader.get()->gpubuffer.m_vertices.at(vertsize*i+1));
			vpc.pos.z = (levelLoader.get()->gpubuffer.m_vertices.at(vertsize*i+2));
			vpc.color.x = (levelLoader.get()->gpubuffer.m_vertices.at(vertsize*i+3));
			vpc.color.y = (levelLoader.get()->gpubuffer.m_vertices.at(vertsize*i+4));
			vpc.color.z = (levelLoader.get()->gpubuffer.m_vertices.at(vertsize*i+5));
			vpc.normal.x = (levelLoader.get()->gpubuffer.m_vertices.at(vertsize*i + 6));
			vpc.normal.y = (levelLoader.get()->gpubuffer.m_vertices.at(vertsize*i + 7));
			vpc.normal.z = (levelLoader.get()->gpubuffer.m_vertices.at(vertsize*i + 8));
			allVerts.push_back(vpc);
		}

		// Create vertex buffer:
		
		CD3D11_BUFFER_DESC vDesc(
			allVerts.size()*sizeof(VertexPositionColor),
			D3D11_BIND_VERTEX_BUFFER
		);
		vDesc.ByteWidth;
		D3D11_SUBRESOURCE_DATA vData;
		ZeroMemory(&vData, sizeof(D3D11_SUBRESOURCE_DATA));
		vData.pSysMem = &(allVerts[0]);
		vData.SysMemPitch = 0;
		vData.SysMemSlicePitch = 0;
		

		hr = device->CreateBuffer(
			&vDesc,
			&vData,
			&m_pVertexBuffer
		);

		
		

		
		vector<Primitives::UInt16> allIndices;
		numgpuverts =levelLoader.get()->gpubuffer.m_indices.size();
		for (unsigned int i = 0; i < numgpuverts; i++) {
			allIndices.push_back(levelLoader.get()->gpubuffer.m_indices.at(i));
		}

		CD3D11_BUFFER_DESC iDesc(
			allIndices.size()*sizeof(Primitives::UInt16),
			D3D11_BIND_INDEX_BUFFER
		);

		D3D11_SUBRESOURCE_DATA iData;
		ZeroMemory(&iData, sizeof(D3D11_SUBRESOURCE_DATA));
		iData.pSysMem = &allIndices.front();
		iData.SysMemPitch = 0;
		iData.SysMemSlicePitch = 0;

		hr = device->CreateBuffer(
			&iDesc,
			&iData,
			&m_pIndexBuffer
		);

		return hr;
	}

	//-----------------------------------------------------------------------------
	// Create the view matrix and create the perspective matrix.
	//-----------------------------------------------------------------------------
	void Renderer::CreateViewAndPerspective()
	{
		// Use DirectXMath to create view and perspective matrices.

		DirectX::XMVECTOR eye = DirectX::XMVectorSet(0.0f, 1.0f, 6.5f, 0.f);
		DirectX::XMVECTOR at = DirectX::XMVectorSet(0.0f, 1.0f, -1.0f, 0.f);
		DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.f);

		DirectX::XMStoreFloat4x4(
			&m_constantBufferData.view,
			DirectX::XMMatrixTranspose(
				DirectX::XMMatrixLookAtRH(
					eye,
					at,
					up
				)
			)
		);

		float aspectRatio = m_deviceResources->GetAspectRatio();

		DirectX::XMStoreFloat4x4(
			&m_constantBufferData.projection,
			DirectX::XMMatrixTranspose(
				DirectX::XMMatrixPerspectiveFovRH(
					DirectX::XMConvertToRadians(85),
					aspectRatio,
					0.01f,
					100.0f
				)
			)
		);
	}

	//-----------------------------------------------------------------------------
	// Create device-dependent resources for rendering.
	//-----------------------------------------------------------------------------
	void Renderer::CreateDeviceDependentResources(std::shared_ptr<LevelLoader> levelLoader)
	{
		// Compile shaders using the Effects library.
		CreateShaders();
		CreateCube(levelLoader);
	}

	void Renderer::CreateWindowSizeDependentResources()
	{
		// Create the view matrix and the perspective matrix.
		CreateViewAndPerspective();
	}


	//-----------------------------------------------------------------------------
	// Update the scene.
	//-----------------------------------------------------------------------------
	void UpdateMatricesPostPhysics(std::shared_ptr<LevelLoader> levelLoader,Primitives::UInt16 framecount) {
		Physics* gHPhysics = PhysicsManager::getInstance()->get();
		Primitives::UInt16 currFrame = framecount % 2;
		for (unsigned int i = 0; i < gHPhysics->objects[currFrame].size();i++) {
			levelLoader.get()->g_gameObjs[gHPhysics->objects[currFrame].at(i)->metaData.ObjId].objMatrix =
				gHPhysics->objects[currFrame].at(i)->metaData.objMat;
		}
	}
	void Renderer::Update(std::shared_ptr<LevelLoader> levelLoader)
	{
		 //Rotate the cube 1 degree per frame.
		/*DirectX::XMStoreFloat4x4(&m_constantBufferData.world,
			DirectX::XMMatrixIdentity());*/

		UINT size = levelLoader->g_gameObjs.size();
		if (g_frameCount == MAXINT32) g_frameCount = 0;
		
		m_constantBufferData.framecount.x = g_frameCount;
		if (g_runPhysics) {
			PhysicsManager::getInstance()->get()->UpdateCollisions(g_frameCount);
			PhysicsManager::getInstance()->get()->ResolveCollisions(g_frameCount);
			UpdateMatricesPostPhysics(levelLoader, g_frameCount);
		}
		
	}

	//-----------------------------------------------------------------------------
	// Render the cube.
	//-----------------------------------------------------------------------------
	void Renderer::Render(std::shared_ptr<LevelLoader> levelLoader)
	{
		// Use the Direct3D device context to draw.
		ID3D11DeviceContext* context = m_deviceResources->GetDeviceContext();
		ID3D11RenderTargetView* renderTarget = m_deviceResources->GetRenderTargets();
		ID3D11DepthStencilView* depthStencil = m_deviceResources->GetDepthStencil();
		const float background[] = { 0.69f, 0.69f, 0.69f, 1.000f };

		context->ClearRenderTargetView(
			renderTarget,
			background
		);

		context->ClearDepthStencilView(
			depthStencil,
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
			1.0f,
			0);

		context->OMSetRenderTargets(
			1,
			&renderTarget,
			depthStencil
		);
		UINT stride = sizeof(VertexPositionColor);
		UINT offset = 0;

		context->IASetVertexBuffers(
			0,
			1,
			m_pVertexBuffer.GetAddressOf(),
			&stride,
			&offset
		);

		context->IASetIndexBuffer(
			m_pIndexBuffer.Get(),
			DXGI_FORMAT_R16_UINT,
			0
		);
		
		
		context->VSSetShader(
			m_pVertexShader.Get(),
			nullptr,
			0
		);

		context->PSSetShader(
			m_pPixelShader.Get(),
			nullptr,
			0
		);
		
		context->IASetInputLayout(m_pInputLayout.Get());
		for (unsigned int i = 0; i < levelLoader.get()->num_gameObjs; i++) {
			//levelLoader.get()->g_gameObjs[i].objMatrix;
			if (levelLoader.get()->g_gameObjs[i].getObjId() == 2) {
				context->IASetPrimitiveTopology(
					D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST
				);
			}
			else {
				context->IASetPrimitiveTopology(
					D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST
				);
			}
			if (levelLoader.get()->g_gameObjs[i].isVisible) {
				m_constantBufferData.world._11 = levelLoader.get()->g_gameObjs[i].objMatrix.m_values[0][0];
				m_constantBufferData.world._12 = levelLoader.get()->g_gameObjs[i].objMatrix.m_values[0][1];
				m_constantBufferData.world._13 = levelLoader.get()->g_gameObjs[i].objMatrix.m_values[0][2];
				m_constantBufferData.world._14 = levelLoader.get()->g_gameObjs[i].objMatrix.m_values[0][3];
				m_constantBufferData.world._21 = levelLoader.get()->g_gameObjs[i].objMatrix.m_values[1][0];
				m_constantBufferData.world._22 = levelLoader.get()->g_gameObjs[i].objMatrix.m_values[1][1];
				m_constantBufferData.world._23 = levelLoader.get()->g_gameObjs[i].objMatrix.m_values[1][2];
				m_constantBufferData.world._24 = levelLoader.get()->g_gameObjs[i].objMatrix.m_values[1][3];
				m_constantBufferData.world._31 = levelLoader.get()->g_gameObjs[i].objMatrix.m_values[2][0];
				m_constantBufferData.world._32 = levelLoader.get()->g_gameObjs[i].objMatrix.m_values[2][1];
				m_constantBufferData.world._33 = levelLoader.get()->g_gameObjs[i].objMatrix.m_values[2][2];
				m_constantBufferData.world._34 = levelLoader.get()->g_gameObjs[i].objMatrix.m_values[2][3];
				m_constantBufferData.world._41 = levelLoader.get()->g_gameObjs[i].objMatrix.m_values[3][0];
				m_constantBufferData.world._42 = levelLoader.get()->g_gameObjs[i].objMatrix.m_values[3][1];
				m_constantBufferData.world._43 = levelLoader.get()->g_gameObjs[i].objMatrix.m_values[3][2];
				m_constantBufferData.world._44 = levelLoader.get()->g_gameObjs[i].objMatrix.m_values[3][3];
				m_constantBufferData.color.x = levelLoader.get()->g_gameObjs[i].diffuseColor.m_x;
				m_constantBufferData.color.y = levelLoader.get()->g_gameObjs[i].diffuseColor.m_y;
				m_constantBufferData.color.z = levelLoader.get()->g_gameObjs[i].diffuseColor.m_z;
				m_constantBufferData.color.w = levelLoader.get()->g_gameObjs[i].alpha;
				context->UpdateSubresource(
					m_pConstantBuffer.Get(),
					0,
					nullptr,
					&m_constantBufferData,
					sizeof(ConstantBufferStruct),
					0
				);


				context->VSSetConstantBuffers(
					0,
					1,
					m_pConstantBuffer.GetAddressOf()
				);

				// Set up the pixel shader stage.

				string key = levelLoader.get()->g_gameObjs[i].objectName;
				UINT startIndexLocation = levelLoader.get()->m_instances.at(key).second;
				UINT startVertexLocation = levelLoader.get()->m_instances.at(key).first/(sizeof(VertexPositionColor)*0.25f);
				UINT index_count = levelLoader.get()->g_gameObjs[i].num_indices * 3;
				// Calling Draw tells Direct3D to start sending commands to the graphics device.
				context->DrawIndexedInstanced(
					index_count,
					1,
					startIndexLocation,
					startVertexLocation,
					0
				);
			}
			
		}
	}

	//-----------------------------------------------------------------------------
	// Clean up cube resources when the Direct3D device is lost or destroyed.
	//-----------------------------------------------------------------------------
	Renderer::~Renderer()
	{
		// ComPtr will clean up references for us. But be careful to release
		// references to anything you don't need whenever you call Flush or Trim.
		// As always, clean up your system (CPU) memory resources before exit.
	}

};