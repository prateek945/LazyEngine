#pragma once
#ifndef POINT_H_
#define POINT_H_
#include "../../Includes/LazyIncludes.h"
#include "../../Math/LEVector.h"
namespace LE {
	namespace PrimitiveShapes {
		template <class T = Primitives::Float32>
		class Point {
			union {
				struct {
					T x, y, z;
				};
				T coordinates[3];
			};

		public:
			//initialize to 0
			Point<T>();
			Point<T>(const T *x,const T *y,const T *z);
			Point<T>(const T *coords);
			Point<T>(const LEVector3<T> *coords);
			Point<T>(const Point* point);
			
			void copyCoordinates(T *loc);

		};

	};
};
#endif