#pragma once
#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include "../Physics/Colliders/ColliderMeta.h"
#include "../MeshDataCPU/MeshCPU.h"
#include "../Memory/Handle.h"
#include <vector>
#include <string>
using namespace std;
namespace LE {
	class GameObject {
		Primitives::UInt16 objId;
	public:
		
		Matrix4X4 objMatrix;
		char objectName[256];
		Primitives::Bool hasCollider;
		Colliders::ColliderMeta colliderMetaData;
		Primitives::Bool isPhysicsEnabled;
		Primitives::Bool isVisible;
		Handle m_hMeshCPU;
		LEVector3 diffuseColor;
		Primitives::Float32 alpha;
		GameObject() = default;
		GameObject(GameObject&&) = default;
		GameObject(GameObject const& g) {

			objId = g.getObjId();
			objMatrix = g.objMatrix;
			strcpy(objectName, g.objectName);
			hasCollider = g.hasCollider;
			colliderMetaData = g.colliderMetaData;
			isPhysicsEnabled = g.isPhysicsEnabled;
			isVisible = g.isVisible;
			m_hMeshCPU = g.m_hMeshCPU;
		};
		void setObjId(Primitives::UInt16 id) { objId = id; }
		Primitives::UInt16 getObjId()const { return objId; }
	};

	class GPUBuffers {
	public:
		vector<Primitives::Float32> m_vertices;
		vector<Primitives::UInt32> m_indices;
	};
};

#endif