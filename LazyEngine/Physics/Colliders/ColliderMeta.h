#pragma once
#ifndef COLLIDER_META_H_
#define COLLIDER_META_H_
#include "../../Math/Matrix4X4.h"
namespace LE {
	namespace Colliders {
		enum ColliderType {
			TypeCube = 1,
			TypeSphere,
			TypeFrustrum,
			TypeCollisionVolume,
			TypeInvalid
		};
		struct ColliderMeta {
			Primitives::Int16 ObjId;
			ColliderType type;
			Primitives::Bool bisMovable;
			Matrix4X4 objMat;
			Primitives::Bool Gravity;
			Primitives::Float32 mass;
			LEVector3 velocityDir;
			Primitives::Float32 velocityMagnitude;
		};
	};
};

#endif
