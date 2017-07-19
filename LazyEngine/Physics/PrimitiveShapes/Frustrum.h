#pragma once
#ifndef FRUSTRUM_H_
#define FRUSTRUM_H_
#include "../../Includes//LazyIncludes.h"
#include "Plane.h"
namespace LE {
	namespace PrimitiveShapes {
		template <typename T = Primitives::Float32>
		class Frustrum {
			Plane near, far, left, right, top, bottom;

		public:
			//NOTE : Plane normales are defined to be inwards for all 6 planes.
			//NOTE : Z Axis is forward axis WOrld space or otherwise.

			//Generating planes from FOV (in degrees), origin, near and far clip distances.
			Frustrum<T>(Point<T> origin,LEVector3<T> ForwardAxis,Primitives::Float32 FOV,Primitives::Float32 nearDist,Primitives::Float32 farDist);
			//eight world space points in counter clockwise order
			Frustrum<T>(Point<T> A, Point<T> B, Point<T> C, Point<T> D, Point<T> E, Point<T> F, Point<T> G, Point<T> H);
			//Points are counterclockwise (Left hand system).
			LEVector3<T> normalGivenPoints(Point<T> A, Point<T> B, Point<T> C);
			
		};
	};
};

#endif // !FRUSTRUM_H_

