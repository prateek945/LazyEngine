#pragma once
#ifndef POINT_H_
#define POINT_H_
#include "../../Includes/LazyIncludes.h"
#include "../../Math/LEVector.h"
namespace LE {
	namespace PrimitiveShapes {
		template <class T = Primitives::Float32>
		class Point {
			

		public:
			union {
				struct {
					T x, y, z;
				};
				T coordinates[3];
			};
			//initialize to 0
			Point<T>();
			Point<T>( T x,  T y,  T z);
			Point<T>( T *coords);
			Point<T>( LEVector3<T> coords);
			Point<T>( const Point *point);

			void copyCoordinates(T *loc);

		};

		template <class T = Primitives::Float32>
		Point<T>::Point() {
			x = (T)0;
			y = (T)0;
			z = (T)0;
		}
		template <class T = Primitives::Float32>
		Point<T>::Point( T x,  T y,  T z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}
		template <class T = Primitives::Float32>
		Point<T>::Point( T *coords) {
			memcpy(coords, &coordinates, 3 * sizeof(T));
		}
		template <class T = Primitives::Float32>
		Point<T>::Point( LEVector3<T> coords) {
			memcpy(&coordinates, &(coords.m_values), 3 * sizeof(T));
		}

		template <class T = Primitives::Float32>
		Point<T>::Point( const Point *point) {
			point->copyCoordinates(&coordinates);
		}

		template <class T = Primitives::Float32>
		void Point<T>::copyCoordinates(T *loc) {
			memcpy(loc, &coordinates, 3 * sizeof(T));
		}
	};
};
#endif