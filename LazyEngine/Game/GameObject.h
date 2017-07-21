#pragma once
#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include "../Includes/LazyIncludes.h"
#include "../GeneralMacros/GeneralMacros.h"
#include "../Physics/Colliders/ColliderMeta.h"
#include "../Math/Matrix4X4.h"

namespace LE {
	class GameObject {

		Primitives::Int16 objId;
		Matrix4X4<> objMatrix;
		Primitives::Bool hasCollider;
		Colliders::ColliderMeta colliderMetaData;

	public:

		GameObject(){}

		GameObject(Primitives::Int16 Id,Matrix4X4<> modelspace,
			Primitives::Bool hasCollider,Colliders::ColliderMeta collidermd):objId(Id),
			objMatrix(modelspace),hasCollider(hasCollider),colliderMetaData(collidermd){}


		

	};
};
#endif