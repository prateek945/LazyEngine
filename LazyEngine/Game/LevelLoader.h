#pragma once
#ifndef LEVEL_LOADER_H_
#define LEVEL_LOADER_H_


#include "GameObject.h"
#include "../LazyFiling/FileHandler.h"
#include "../Physics/PhysicsManager.h"
#include "../DX11/ShaderIDEnum.h"
#include "LightObject.h"
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#include <cstring>
using namespace std;
namespace LE {

	class LevelLoader {
	public:
		string levelName;
		vector<GameObject> g_gameObjs;
		vector<LightObject> g_lights;
		Primitives::UInt32 num_gameObjs;
		map<std::string, Handle> m_instances;
		map<std::string, std::pair<Primitives::Int32, Primitives::Int32>> m_GPUIndices;
		vector<pair<ShaderID, string>> m_pixelShaders;
		vector<pair<ShaderID, string>> m_vertexShaders;
		
		GPUBuffers gpubuffer;
		
		LevelLoader(string levelname): levelName(levelname){}
		bool loadLevelGameObjs(ID3D11Device* device,ID3D11DeviceContext* context);
		void storeGPUVertDataForObj(Handle);

		const char* getLevelName() { return levelName.c_str(); }

	};
}
#endif // !LEVEL_LOADER_H_
