#pragma once
#ifndef RAY_H_
#define RAY_H_
#include "../../Includes/LazyIncludes.h"
#include "../../Math/LEVector.h"
#include "../../Math/Quaternion.h"
#include "Point.h"
namespace LE {
	namespace PrimitiveShapes {
		template<class T = Primitives::Float32>
		class Ray {
			Point startPoint;
			LEVector3<T> direction;

		public:
			//Default Direction is world space X axis
			Ray<T>();
			Ray<T>(const Point<T> *point, const LEVector3<T> *dir);
			Ray<T>(const Ray* ray);
			Point getStartPoint();
			LEVector3<T> getDirection();
			void setStartPoint(Point<T> *startpoint);
			void setDirection(LEVector3<T> *direction);
		};
	};
};

#endif // !RAY_H_
