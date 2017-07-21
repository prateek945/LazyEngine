#pragma once
#ifndef COLLIDER_META_H_
#define COLLIDER_META_H_
#include "../../Includes/LazyIncludes.h"
#include "../../Math/Matrix4X4.h"
namespace LE {
	namespace Colliders {
		enum ColliderType {
			Cube = 1,
			Sphere,
			Frustrum,
			CollisionVolume,
			Invalid
		};
		struct ColliderMeta {
			Primitives::Int16 ObjId;
			ColliderType type;
			Primitives::Bool bisMovable;
			Matrix4X4<> objMat;
		};
	};
};

#endif
