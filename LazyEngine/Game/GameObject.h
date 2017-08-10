#pragma once
#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include "../Physics/Colliders/ColliderMeta.h"

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
		Primitives::UInt32 num_verts;
		Primitives::UInt32 num_indices;
		
		GameObject() = default;
		GameObject(GameObject&&) = default;
		GameObject(GameObject const& g) {
			objMatrix = g.objMatrix;
			strcpy(objectName, g.objectName);
			hasCollider = g.hasCollider;
			colliderMetaData = g.colliderMetaData;
			num_verts = g.num_verts;
			num_indices = g.num_indices;
			isPhysicsEnabled = g.isPhysicsEnabled;
		};
		void setObjId(Primitives::UInt16 id) { objId = id; }
		Primitives::UInt16 getObjId() { return objId; }
	};

	class GPUBuffers {
	public:
		vector<Primitives::Float32> m_vertices;
		vector<Primitives::UInt32> m_indices;
	};
};

#endif