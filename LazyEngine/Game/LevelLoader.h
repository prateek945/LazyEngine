#pragma once
#ifndef LEVEL_LOADER_H_
#define LEVEL_LOADER_H_


#include "GameObject.h"
#include "../LazyFiling/FileHandler.h"
#include "../Physics/PhysicsManager.h"
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <cstring>
using namespace std;
namespace LE {

	class LevelLoader {
	public:
		string levelName;
		vector<GameObject> g_gameObjs;
		
		Primitives::UInt32 num_gameObjs;
		map<string, pair<Primitives::UInt32,Primitives::UInt32>> m_instances;
		GPUBuffers gpubuffer;
		
		LevelLoader(string levelname): levelName(levelname){}
		bool loadLevelGameObjs();
		
		const char* getLevelName() { return levelName.c_str(); }

	};
}
#endif // !LEVEL_LOADER_H_
