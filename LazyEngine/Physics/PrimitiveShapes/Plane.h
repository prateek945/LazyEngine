#pragma once
#ifndef PLANE_H_
#define PLANE_H_
#include "../../Includes/LazyIncludes.h"
#include "../../Math/LEVector.h"
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
			Plane<T>( Point<T> point,  LEVector3<T> norm);
			Plane<T>(const Plane<T>* copyPlane);

			Point<T> getPoint(void);
			LEVector3<T> getNormal(void);

			void setPoint(Point<T> point);
			void setNormal(LEVector3<T> normal);


		};
		template <class T = Primitives::Float32>
		Plane<T>::Plane() {
			point = Point<T>();
			normal = LEVector3<T>();

		}
		template <class T = Primitives::Float32>
		Plane<T>::Plane( Point<T> point,  LEVector3<T> norm) {
			this->point = point;
			this->normal = norm;
		}
		template <class T = Primitives::Float32>
		Plane<T>::Plane(const Plane<T>* copyPlane) {
			this->normal = copyPlane->getNormal();
			this->point = copyPlane->getPoint();
		}

		template <class T = Primitives::Float32>
		Point<T> Plane<T>::getPoint() {
			return point;
		}

		template <class T = Primitives::Float32>
		LEVector3<T> Plane<T>::getNormal() {
			return normal;
		}

		template <class T = Primitives::Float32>
		void Plane<T>::setPoint(Point<T> p) {
			this->point = p;
		}
		template <class T = Primitives::Float32>
		void Plane<T>::setNormal(LEVector3<T> norm) {
			this->normal = norm;
		}
	};
};
#endif