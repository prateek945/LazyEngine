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
		Primitives::UInt32 num_verts;
		Primitives::UInt32 num_indices;
		Primitives::Bool isVisible;
		Handle* m_hMeshCPU;

		vector<Primitives::Float32> m_vertices;
		vector<Primitives::Float32> m_color;
		vector<Primitives::Float32> m_normals;
		vector<Primitives::UInt32> m_indices;
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
			num_verts = g.num_verts;
			num_indices = g.num_indices;
			isPhysicsEnabled = g.isPhysicsEnabled;
			isVisible = g.isVisible;
			m_vertices = g.m_vertices;
			m_color = g.m_color;
			m_normals = g.m_normals;
			m_indices = g.m_indices;
			diffuseColor = g.diffuseColor;
			alpha = g.alpha;
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