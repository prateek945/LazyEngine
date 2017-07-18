#pragma once
#ifndef PLANE_H_
#define PLANE_H_
#include "../../Includes/LazyIncludes.h"
#include "../../Math/LEVector.h"
#include "../../Math/Matrix3X3.h"
#include "Point.h"
namespace LE {
	namespace PrimitiveShapes {
		template <class T = Primitives::Float32>
		class Plane {

			Point<T> point;
			LEVector3<T> normal;

		public:
			//Normal is perpendicular to world space X axis.
			Plane<T>();
			Plane<T>(const Point<T> *point, const LEVector<T> *norm);
			Plane<T>(const Plane<T>* copyPlane);

			Point<T> getPoint();
			LEVector3<T> getNormal();

			void setPoint(Point<T> *point);
			void setNormal(LEVector3<T> *normal);

		};
	};
};
#endif