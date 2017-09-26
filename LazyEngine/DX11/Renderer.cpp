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
		WCHAR *shaderFile = L"..\\LazyEngine\\DX11\\CubeVertexShader.hlsl";
		
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


		shaderFile = L"..\\LazyEngine\\DX11\\CubePixelShader.hlsl";

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
			vpc.pos.m_x = levelLoader.get()->gpubuffer.m_vertices.at(vertsize*i);
			vpc.pos.m_y = (levelLoader.get()->gpubuffer.m_vertices.at(vertsize*i+1));
			vpc.pos.m_z = (levelLoader.get()->gpubuffer.m_vertices.at(vertsize*i+2));
			vpc.color.m_x = (levelLoader.get()->gpubuffer.m_vertices.at(vertsize*i+3));
			vpc.color.m_y = (levelLoader.get()->gpubuffer.m_vertices.at(vertsize*i+4));
			vpc.color.m_z = (levelLoader.get()->gpubuffer.m_vertices.at(vertsize*i+5));
			vpc.normal.m_x = (levelLoader.get()->gpubuffer.m_vertices.at(vertsize*i + 6));
			vpc.normal.m_y = (levelLoader.get()->gpubuffer.m_vertices.at(vertsize*i + 7));
			vpc.normal.m_z = (levelLoader.get()->gpubuffer.m_vertices.at(vertsize*i + 8));
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

		LEVector3 eye(0.0f, 2.0f, -5.0f);
		LEVector3 at(0.0f, 0.0f, 1.0f);
		LEVector3 up(0.0f, 1.0f, 0.0f);
		float aspectRatio = m_deviceResources->GetAspectRatio();
		m_hMainCamera = new Handle(sizeof(Camera));
		Camera *MainCamera = new(m_hMainCamera->getAddress()) Camera(eye, at, up, 90.0f, aspectRatio, 0.01f, 100.0f);
		m_constantBufferData.view = MainCamera->getViewMatrix();//.getTranspose();
		m_constantBufferData.projection = MainCamera->getProjectionMatrix();// .getTranspose();
	}

	//-----------------------------------------------------------------------------
	// Create device-dependent resources for rendering.
	//-----------------------------------------------------------------------------
	void Renderer::CreateDeviceDependentResources(std::shared_ptr<LevelLoader> levelLoader)
	{
		// Compile shaders using the Effects library.
		m_keyboard = make_unique<DirectX::Keyboard>();
		m_mouse = make_unique<DirectX::Mouse>();
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
		Camera* mainCam = m_hMainCamera->getObject<Camera>();
		
		auto kb = DirectX::Keyboard::Get().GetState();
		if (kb.NumPad4) {
			int prevFrame = !(g_frameCount % 2);
			PhysicsManager::getInstance()->get()->objects[prevFrame].at(0)->metaData.Velocity.m_x = -1.0f;
		}
		if (kb.NumPad6) {
			int prevFrame = !(g_frameCount % 2);
			PhysicsManager::getInstance()->get()->objects[prevFrame].at(0)->metaData.Velocity.m_x = 1.0f;
		}
		if (kb.P) {
			g_runPhysics = true;
		}
		if (kb.Up) {
			
			mainCam->TurnUp(0.01f);

		}
		if (kb.Down) {
		
			mainCam->TurnDown(0.01f);

		}
		if (kb.Left) {
			Camera *mainCam = m_hMainCamera->getObject<Camera>();
			mainCam->TurnLeft(0.01f);

		}
		if (kb.Right) {
			
			mainCam->TurnRight(0.01f);

		}
		if (kb.W) {
			
			mainCam->MoveUp(1.f);

		}
		if (kb.S) {
			
			mainCam->MoveDown(1.f);

		}
		if (kb.A) {
			
			mainCam->MoveLeft(1.f);

		}
		if (kb.D) {
			
			mainCam->MoveRight(1.f);

		}
		if (kb.R) {
			mainCam->Reset();
		}
		UINT size = levelLoader->g_gameObjs.size();
		if (g_frameCount == MAXINT32) g_frameCount = 0;
		
		//mainCam->TurnLeft(0.01f);
		mainCam->ReCalculateView();
		mainCam->ReCalculateProjection();
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
		//m_constantBufferData.view = m_hMainCamera->getObject<Camera>()->getViewMatrix();
		//m_constantBufferData.projection = m_hMainCamera->getObject<Camera>()->getProjectionMatrix();
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
			m_constantBufferData.view = m_hMainCamera->getObject<Camera>()->getViewMatrix();
			m_constantBufferData.projection = m_hMainCamera->getObject<Camera>()->getProjectionMatrix();
			if (levelLoader.get()->g_gameObjs[i].isVisible) {
				
				m_constantBufferData.world = levelLoader.get()->g_gameObjs[i].objMatrix;
				m_constantBufferData.color = levelLoader.get()->g_gameObjs[i].diffuseColor;
				m_constantBufferData.aplha = levelLoader.get()->g_gameObjs[i].alpha;
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