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
			else if (currLayout == ShaderID::LightPass) {
				D3D11_INPUT_ELEMENT_DESC simpleShaderIL[] =
				{
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
					0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },

					{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,
					0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },

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
			
		}
		return hr;
	}
	HRESULT Renderer::CreateGPUBuffers(std::shared_ptr<LevelLoader> levelLoader)
	{
		HRESULT hr = S_OK;

		// Use the Direct3D device to load resources into graphics memory.
		ID3D11Device* device = m_deviceResources->GetDevice();
		ID3D11DeviceContext* context = m_deviceResources->GetDeviceContext();
		vector<VertexPositionNormalTangent> allVerts ;
		// Create cube geometry.
		int numgpuverts = (levelLoader.get()->gpubuffer.m_vertices.size());
		int vertsize = numgpuverts / (sizeof(VertexPositionNormalTangent) / 4);
		for (unsigned int i = 0; i < numgpuverts; i += (sizeof(VertexPositionNormalTangent) / 4)) {
			VertexPositionNormalTangent vert;
			vert.pos = LEVector3(levelLoader.get()->gpubuffer.m_vertices[i], levelLoader.get()->gpubuffer.m_vertices[i + 1], levelLoader.get()->gpubuffer.m_vertices[i + 2]);
			vert.textCoords[0] = levelLoader.get()->gpubuffer.m_vertices[i + 3];
			vert.textCoords[1] = levelLoader.get()->gpubuffer.m_vertices[i + 4];
			vert.normal = LEVector3(levelLoader.get()->gpubuffer.m_vertices[i + 5], levelLoader.get()->gpubuffer.m_vertices[i + 6], levelLoader.get()->gpubuffer.m_vertices[i + 7]);
			vert.tangent = LEVector3(levelLoader.get()->gpubuffer.m_vertices[i + 8], levelLoader.get()->gpubuffer.m_vertices[i + 9], levelLoader.get()->gpubuffer.m_vertices[i + 10]);
			allVerts.push_back(vert);
		}

		// Create vertex buffer:
		
		CD3D11_BUFFER_DESC vDesc(
			allVerts.size() * sizeof(VertexPositionNormalTangent),
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
		//Vertex and Index buffers for light pass
		VertexPositionTexCoord quadverts[] =
		{
			VertexPositionTexCoord{ LEVector3(-1,0,0),0.0,0.0 },
			VertexPositionTexCoord{ LEVector3(1,1,0),1.0,0.0 },
			VertexPositionTexCoord{ LEVector3(1,-1,0),1.0,1.0 },
			VertexPositionTexCoord{ LEVector3(-1,-1,0),0.0,1.0 }
		};

		CD3D11_BUFFER_DESC vQDesc(
			4 * sizeof(VertexPositionTexCoord),
			D3D11_BIND_VERTEX_BUFFER
		);
		vDesc.ByteWidth;
		
		ZeroMemory(&vData, sizeof(D3D11_SUBRESOURCE_DATA));
		vData.pSysMem = &(quadverts[0]);
		vData.SysMemPitch = 0;
		vData.SysMemSlicePitch = 0;


		hr = device->CreateBuffer(
			&vQDesc,
			&vData,
			&m_pVertrexBufferQuad
		);

		Primitives::UInt16 quadIndices[] = { 3,1,0,3,2,1 };
		CD3D11_BUFFER_DESC iQDesc(
			6* sizeof(Primitives::UInt16),
			D3D11_BIND_INDEX_BUFFER
		);

		
		ZeroMemory(&iData, sizeof(D3D11_SUBRESOURCE_DATA));
		iData.pSysMem = &quadIndices[0];
		iData.SysMemPitch = 0;
		iData.SysMemSlicePitch = 0;

		hr = device->CreateBuffer(
			&iQDesc,
			&iData,
			&m_pIndexBufferQuad
		);
		//

		D3D11_TEXTURE2D_DESC desc;
		desc.Width = m_deviceResources->GetViewPort().Width;
		desc.Height = m_deviceResources->GetViewPort().Height;
		desc.MipLevels = 0;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
		renderTargetViewDesc.Format = desc.Format;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;

		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
		shaderResourceViewDesc.Format = desc.Format;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;
		//Diffuse
		hr = device->CreateTexture2D(&desc, NULL, &m_pGBufferDiffuse);
		if (!SUCCEEDED(hr)) return false;
		hr = device->CreateRenderTargetView(m_pGBufferDiffuse.Get(), &renderTargetViewDesc, &m_pRTGBufferDiffuse);
		hr = device->CreateShaderResourceView(m_pGBufferDiffuse.Get(),&shaderResourceViewDesc, &m_pSRVGBufferDiffuse);
		//Normal
		hr = device->CreateTexture2D(&desc, NULL, &m_pGBufferNormal);
		if (!SUCCEEDED(hr)) return false;
		hr = device->CreateRenderTargetView(m_pGBufferNormal.Get(), &renderTargetViewDesc, &m_pRTGBufferNormal);
		hr = device->CreateShaderResourceView(m_pGBufferNormal.Get(), &shaderResourceViewDesc, &m_pSRVGBufferNormal);
		//Specular
		hr = device->CreateTexture2D(&desc, NULL, &m_pGBufferSpecular);
		if (!SUCCEEDED(hr)) return false;
		hr = device->CreateRenderTargetView(m_pGBufferSpecular.Get(), &renderTargetViewDesc, &m_pRTGBufferSpecular);
		hr = device->CreateShaderResourceView(m_pGBufferSpecular.Get(), &shaderResourceViewDesc, &m_pSRVGBufferSpecular);
		
		//Add SRVs to array

		m_SRVArray[0] = m_pSRVGBufferDiffuse.Get();
		m_SRVArray[1] = m_pSRVGBufferNormal.Get();
		m_SRVArray[2] = m_pSRVGBufferSpecular.Get();
	//	hr = device->CreateShaderResourceView(m_deviceResources->GetDepthStencil(),NULL, &m_pSRVGBufferDiffuse);
		//LightPass
		m_pRTLightPass = m_deviceResources->GetRenderTargets();


		m_renderTargetViewArray[0] = m_pRTGBufferDiffuse.Get();
		m_renderTargetViewArray[1] = m_pRTGBufferNormal.Get();
		m_renderTargetViewArray[2] = m_pRTGBufferSpecular.Get();
		m_renderTargetViewArray[3] = m_pRTLightPass.Get();



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
		Camera *MainCamera = new(m_hMainCamera->getAddress()) Camera(eye, at, up, 45.0f, aspectRatio, 0.01f, 1000.0f);
		m_constantBufferData.view = MainCamera->getViewMatrix().getTranspose();
		m_constantBufferData.projection = MainCamera->getProjectionMatrix().getTranspose();
	}

	//-----------------------------------------------------------------------------
	// Create device-dependent resources for rendering.
	//-----------------------------------------------------------------------------
	void Renderer::CreateDeviceDependentResources(std::shared_ptr<LevelLoader> levelLoader)
	{
		// Compile shaders using the Effects library.
		m_keyboard = make_unique<DirectX::Keyboard>();
		m_mouse = make_unique<DirectX::Mouse>();
		tracker = make_unique<DirectX::Keyboard::KeyboardStateTracker>();
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
		
		tracker->Update(DirectX::Keyboard::Get().GetState());
		//All buffers lit
		if(tracker->IsKeyReleased(DirectX::Keyboard::Get().Z))
		{
			toggleBuffers_ADNS[0] = true;
			toggleBuffers_ADNS[1] = false;
			toggleBuffers_ADNS[2] = false;
			toggleBuffers_ADNS[3] = false;
		}
		//Diffuse unlit
		if (tracker->IsKeyReleased(DirectX::Keyboard::Get().X))
		{
			toggleBuffers_ADNS[0] = false;
			toggleBuffers_ADNS[1] = true;
			toggleBuffers_ADNS[2] = false;
			toggleBuffers_ADNS[3] = false;
		}
		//Normals
		if (tracker->IsKeyReleased(DirectX::Keyboard::Get().C))
		{
			toggleBuffers_ADNS[0] = false;
			toggleBuffers_ADNS[1] = false;
			toggleBuffers_ADNS[2] = true;
			toggleBuffers_ADNS[3] = false;
		}
		//Specular
		if (tracker->IsKeyReleased(DirectX::Keyboard::Get().V))
		{
			toggleBuffers_ADNS[0] = false;
			toggleBuffers_ADNS[1] = false;
			toggleBuffers_ADNS[2] = false;
			toggleBuffers_ADNS[3] = true;
		}
		if (kb.NumPad4) {
			int prevFrame = !(g_frameCount % 2);
			PhysicsManager::getInstance()->get()->objects[prevFrame].at(0)->metaData.Velocity.m_x = -1.0f;
		}
		if (kb.NumPad6) {
			int prevFrame = !(g_frameCount % 2);
			PhysicsManager::getInstance()->get()->objects[prevFrame].at(0)->metaData.Velocity.m_x = 1.0f;
		}
		if (tracker->IsKeyReleased(DirectX::Keyboard::Get().P)) {
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
			
			mainCam->MoveUp(0.5f);

		}
		if (kb.S) {
			
			mainCam->MoveDown(0.5f);

		}
		if (kb.A) {
			
			mainCam->MoveLeft(0.5f);

		}
		if (kb.D) {
			
			mainCam->MoveRight(0.5f);

		}
		if (kb.R) {
			mainCam->Reset();
		}
		UINT size = levelLoader->g_gameObjs.size();
		if (g_frameCount == MAXINT32) g_frameCount = 0;
		LEVector3 eye = mainCam->getWorldMatrix().getTranslation();
		LEVector3 lookAt = eye + mainCam->getWorldMatrix().getN();
		LEVector3 up = mainCam->getWorldMatrix().getV();
		
		
		//mainCam->TurnLeft(0.01f);
		mainCam->ReCalculateView(eye,lookAt,up);
		//mainCam->ReCalculateProjection();
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
		ID3D11Device* device = m_deviceResources->GetDevice();
		ID3D11DeviceContext* context = m_deviceResources->GetDeviceContext();
		ID3D11RenderTargetView* renderTarget = m_deviceResources->GetRenderTargets();
		ID3D11DepthStencilView* depthStencil = m_deviceResources->GetDepthStencil();
				
		const float background[] = { 0.69f, 0.69f, 0.69f, 1.000f };
		for (int i = 0; i < 4;i++)
		{
			context->ClearRenderTargetView(
				m_renderTargetViewArray[i],
				background
			);
		}
		
		context->ClearDepthStencilView(
			depthStencil,
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
			1.0f,
			0);

		
		UINT stride = sizeof(VertexPositionNormalTangent);
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
		m_constantBufferData.view = m_hMainCamera->getObject<Camera>()->getViewMatrix().getTranspose();
		m_constantBufferData.projection = m_hMainCamera->getObject<Camera>()->getProjectionMatrix().getTranspose();
		m_hMainCamera->getObject<Camera>()->GetEyePosition(&m_constantBufferData.eyePos[0]);

		context->OMSetRenderTargets(
				4,
				m_renderTargetViewArray,
				depthStencil
		);
		//GBuffer Pass
		for (int i = 0; i < 4; i++)
		{
			if (toggleBuffers_ADNS[i])
				m_constantBufferData.toggles[i] = 1.0f;
			else
				m_constantBufferData.toggles[i] = 0.0f;
		}
		for (unsigned int i = 0; i < levelLoader.get()->num_gameObjs; i++) {
			MeshCPU* mesh = levelLoader.get()->g_gameObjs[i].m_hMeshCPU.getObject<MeshCPU>();
			MaterialBufferCPU* material = mesh->m_hMaterialCPU.getObject<MaterialBufferCPU>();
			//Shader setting per mesh
			if (material->isDetailedMesh()) {
				strncpy(shaderName, "Detailed", 256);
				m_constantBufferData.detailedMesh[0] = 1.0f;
				m_constantBufferData.detailedMesh[1] = 1.0f;
				m_constantBufferData.detailedMesh[2] = 0.0f;
				m_constantBufferData.detailedMesh[3] = 0.0f;
			}
			else {
				strncpy(shaderName, "Simple", 256);
				m_constantBufferData.detailedMesh[0] = 0.0f;
				m_constantBufferData.detailedMesh[1] = 0.0f;
				m_constantBufferData.detailedMesh[2] = 0.0f;
				m_constantBufferData.detailedMesh[3] = 0.0f;
			}
			

			Handle h = Handle(sizeof(Effect));
			_EffectManager->getEffect(keyBase, shaderName, h);
			Effect* currEffect = h.getObject<Effect>();
			// GBuffer Pass Start
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
			
			if (levelLoader.get()->g_gameObjs[i].isVisible) {
				
				m_constantBufferData.world = levelLoader.get()->g_gameObjs[i].objMatrix.getTranspose();
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
				context->PSSetConstantBuffers(
					0,
					1,
					m_pConstantBuffer.GetAddressOf()
				);
				for (int i = 0; i < material->m_hTextures.getSize(); i++) {
					Texture* currTexture = material->m_hTextures.getElement(i).getObject<Texture>();
					ID3D11ShaderResourceView* currResource = currTexture->GetTexture();
					context->VSSetShaderResources(i, 1,&currResource);
					context->PSSetShaderResources(i, 1, &currResource);
					SamplerState currSampler = SamplerStateManager::getInstance()->getSamplerState(ESamplerState::Sampler_State_Min_Mag_Mip_Linear_U_V_W_Wrap);
					

				}
				SamplerState currSampler = SamplerStateManager::getInstance()->getSamplerState(ESamplerState::Sampler_State_Min_Mag_Mip_Linear_U_V_W_Wrap);
				context->PSSetSamplers(0, 1, &currSampler.m_pSamplerState);
				context->VSSetSamplers(0, 1, &currSampler.m_pSamplerState);
				string key = levelLoader.get()->g_gameObjs[i].objectName;

				UINT startIndexLocation = levelLoader.get()->m_GPUIndices.at(key).second ;
				UINT startVertexLocation = (levelLoader.get()->m_GPUIndices.at(key).first /(stride*0.25));
				UINT index_count = levelLoader.get()->g_gameObjs[i].m_hMeshCPU.getObject<MeshCPU>()->m_hIndexBufferCPU.getObject<IndexBufferCPU>()->getNumVerts()*3;

				// Calling Draw tells Direct3D to start sending commands to the graphics device.
				context->DrawIndexed(
					index_count,
					startIndexLocation,
					startVertexLocation
				);


			}
			
		}

		//Light Pass
		context->VSSetConstantBuffers(
			0,
			1,
			m_pConstantBuffer.GetAddressOf()
		);
		context->PSSetConstantBuffers(
			0,
			1,
			m_pConstantBuffer.GetAddressOf()
		);
		Handle h = Handle(sizeof(Effect));
		_EffectManager->getEffect(keyBase, "Detailed_LightPass", h);
		Effect* LightPassEffect = h.getObject<Effect>();

		context->IASetInputLayout(LightPassEffect->getInputLayout());
		context->VSSetShader(LightPassEffect->getVertexShader(), NULL, 0);
		context->PSSetShader(LightPassEffect->getPixelShader(), NULL, 0);
		m_renderTargetViewArray[0] = NULL;
		m_renderTargetViewArray[1] = NULL;
		m_renderTargetViewArray[2] = NULL;
		//ID3D11RenderTargetView* rTargets[4] = {NULL,NULL,NULL, m_pRTLightPass.Get() };
		context->OMSetRenderTargets(4, m_renderTargetViewArray, depthStencil);
		
		for (int i = 0; i < 3; i++)
		{
			//context->PSSetShaderResources(i, 1, nullptr);
			context->PSSetShaderResources(i, 1, &m_SRVArray[i]);
		}
		stride = sizeof(VertexPositionTexCoord);
		offset = 0;

		context->IASetVertexBuffers(
			0,
			1,
			m_pVertrexBufferQuad.GetAddressOf(),
			&stride,
			&offset
		);
		// Set the vertex and pixel shaders that will be used to render.
		
		context->IASetIndexBuffer(
			m_pIndexBufferQuad.Get(),
			DXGI_FORMAT_R16_UINT,
			0
		);
		SamplerState currSampler = SamplerStateManager::getInstance()->getSamplerState(ESamplerState::Sampler_State_Min_Mag_Mip_Linear_U_V_W_Wrap );
		context->PSSetSamplers(0, 1, &currSampler.m_pSamplerState);
		context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		context->Draw(4,0);
		m_renderTargetViewArray[0] = m_pRTGBufferDiffuse.Get();
		m_renderTargetViewArray[1] = m_pRTGBufferNormal.Get();
		m_renderTargetViewArray[2] = m_pRTGBufferSpecular.Get();
		ID3D11ShaderResourceView* SRV[3] = { NULL,NULL,NULL };
		for (int i = 0; i < 3; i++)
		{
			//context->PSSetShaderResources(i, 1, nullptr);
			context->PSSetShaderResources(i, 1,&SRV[i]);
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