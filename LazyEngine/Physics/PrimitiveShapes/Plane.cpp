#include "Plane.h"

namespace LE {
	namespace PrimitiveShapes {
		template <class T = Primitives::Float32>
		Plane<T>::Plane() {
			point = Point<T>();
			normal = LEVector3<T>();

		}
		template <class T = Primitives::Float32>
		Plane<T>::Plane(const Point<T> *point, const LEVector<T> *norm) {
			*this.point = *point;
			*this.normal = *norm;
		}
		template <class T = Primitives::Float32>
		Plane<T>::Plane(const Plane<T>* copyPlane) {
			
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
		void Plane<T>::setPoint(Point<T> *p) {
			*this.point = *p;
		}
		template <class T = Primitives::Float32>
		void Plane<T>::setNormal(LEVector3<T> *norm) {
			*this.normal = norm;
		}

	};
};