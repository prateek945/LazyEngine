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
		m_frameCount = 0;
		D3D11_INPUT_ELEMENT_DESC simpleShaderIL[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
			0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },

			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,
			0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },

			{ "NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,
			0,20,D3D11_INPUT_PER_VERTEX_DATA,0 }
		};
		m_inputLayouts[ShaderID::StandardShader] = *simpleShaderIL;
		D3D11_INPUT_ELEMENT_DESC DetailedShaderIL[] = 
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
			0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },

			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,
			0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },

			{ "NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,
			0,20,D3D11_INPUT_PER_VERTEX_DATA,0 },

			{ "TANGENT",0,DXGI_FORMAT_R32G32B32_FLOAT,
			0,32,D3D11_INPUT_PER_VERTEX_DATA,0}
		};
		m_inputLayouts[ShaderID::DetialedShader] = *DetailedShaderIL;
		// init frame count
	}

	//-----------------------------------------------------------------------------
	// Create Direct3D shader resources by loading the .cso files.
	//-----------------------------------------------------------------------------
	HRESULT Renderer::CompileShaders(std::shared_ptr<LevelLoader> levelLoader)
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


		ID3DBlob* compiledCodeBlob = NULL;
		ID3DBlob* errorBlob = NULL;

		char vertexShaderPath[256];
		char pixelShaderPath[256];
		WCHAR shaderFile[256];
		EffectManager* _EffectManager = EffectManager::getInstance();
		for (auto const& it : _EffectManager->getAllEffects()) {
			Handle hCurrEffect = it.second;
			Effect* currEffect = hCurrEffect.getObject<Effect>();
			
			strncpy(vertexShaderPath, it.first.c_str(), 256);
			strcat(vertexShaderPath, "_VS.hlsl");
			strncpy(pixelShaderPath, it.first.c_str(), 256);
			strcat(pixelShaderPath, "_PS.hlsl");
			
			mbstowcs(shaderFile, vertexShaderPath, 256);

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
				&(currEffect->m_vertexShader)
			);
			
			ShaderID currLayout = currEffect->m_layout;
			Primitives::UInt32 sizeIL;
			D3D11_INPUT_ELEMENT_DESC* ShaderIL;
			if (currLayout == ShaderID::DetialedShader) {
				D3D11_INPUT_ELEMENT_DESC DetailedShaderIL[] =
				{
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
					0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },

					{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,
					0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },

					{ "NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,
					0,20,D3D11_INPUT_PER_VERTEX_DATA,0 },

					{ "TANGENT",0,DXGI_FORMAT_R32G32B32_FLOAT,
					0,32,D3D11_INPUT_PER_VERTEX_DATA,0 }
				};
				ShaderIL = DetailedShaderIL;
				sizeIL = sizeof(DetailedShaderIL)/sizeof(D3D11_INPUT_ELEMENT_DESC);
			}
			else if(currLayout == ShaderID::StandardShader) {
				D3D11_INPUT_ELEMENT_DESC simpleShaderIL[] =
				{
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
					0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },

					{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,
					0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },

					{ "NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,
					0,20,D3D11_INPUT_PER_VERTEX_DATA,0 }
				};
				ShaderIL = simpleShaderIL;
				sizeIL = sizeof(simpleShaderIL) / sizeof(D3D11_INPUT_ELEMENT_DESC);
			}
			
			hr = device->CreateInputLayout(
				ShaderIL,
				sizeIL,
				compiledCodeBlob->GetBufferPointer(),
				compiledCodeBlob->GetBufferSize(),
				&currEffect->m_inputLayout
			);
			compiledCodeBlob = NULL;
			errorBlob = NULL;



			mbstowcs(shaderFile, pixelShaderPath, 256);

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
				&currEffect->m_pixelShader
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
	}
	HRESULT Renderer::CreateGPUBuffers(std::shared_ptr<LevelLoader> levelLoader)
	{
		HRESULT hr = S_OK;

		// Use the Direct3D device to load resources into graphics memory.
		ID3D11Device* device = m_deviceResources->GetDevice();
		vector<Primitives::Float32> allVerts ;
		// Create cube geometry.
		int numgpuverts = (levelLoader.get()->gpubuffer.m_vertices.size());
		//int vertsize = sizeof(VertexPositionColor) / 4;
		for (unsigned int i = 0; i < numgpuverts; i++) {
			allVerts.push_back(levelLoader.get()->gpubuffer.m_vertices[i]);
		}

		// Create vertex buffer:
		
		CD3D11_BUFFER_DESC vDesc(
			allVerts.size(),
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
		CompileShaders(levelLoader);
		CreateGPUBuffers(levelLoader);
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
		UINT stride = sizeof(VertexPositionNormal);
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
		
		char keyBase[256] = PROJPATH;
		
		for (int i = 0; i < strlen(keyBase); i++) {
			if (keyBase[i] == '\\') {
				keyBase[i] = '/';
			}
		}

		strcat(keyBase, "Meshes/GPUPrograms//");
		
		char shaderName[256] = "";
		EffectManager* _EffectManager = EffectManager::getInstance();
		//m_constantBufferData.view = m_hMainCamera->getObject<Camera>()->getViewMatrix();
		//m_constantBufferData.projection = m_hMainCamera->getObject<Camera>()->getProjectionMatrix();
		for (unsigned int i = 0; i < levelLoader.get()->num_gameObjs; i++) {
			MeshCPU* mesh = levelLoader.get()->g_gameObjs[i].m_hMeshCPU.getObject<MeshCPU>();
			MaterialBufferCPU* material = mesh->m_hMaterialCPU.getObject<MaterialBufferCPU>();
			//Shader setting per mesh
			if (material->isDetailedMesh()) {
				strncpy(shaderName, "Detailed", 256);
			}
			else {
				strncpy(shaderName, "Simple", 256);
			}
			Handle h = Handle(sizeof(Effect));
			_EffectManager->getEffect(keyBase, shaderName, h);
			Effect* currEffect = h.getObject<Effect>();

			context->VSSetShader(
				currEffect->m_vertexShader,
				nullptr,
				0
			);

			context->PSSetShader(
				currEffect->m_pixelShader,
				nullptr,
				0
			);

			context->IASetInputLayout(currEffect->m_inputLayout);
			context->IASetPrimitiveTopology(
				D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST
			);
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

				UINT startIndexLocation = levelLoader.get()->m_GPUIndices.at(key).second;
				UINT startVertexLocation = levelLoader.get()->m_GPUIndices.at(key).first;
				UINT index_count = levelLoader.get()->g_gameObjs[i].m_hMeshCPU.getObject<MeshCPU>()->m_hIndexBufferCPU.getObject<IndexBufferCPU>()->getNumVerts();

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