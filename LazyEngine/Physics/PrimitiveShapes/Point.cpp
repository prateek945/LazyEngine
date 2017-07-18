#include "Point.h"

namespace LE {
	namespace PrimitiveShapes {
		
		template <class T = Primitives::Float32>
		Point<T>::Point() {
			x = (T)0;
			y = (T)0;
			z = (T)0;
		}
		template <class T = Primitives::Float32>
		Point<T>::Point(const T *x, const T *y, const T *z) {
			*this.x = x;
			*this.y = y;
			*this.z = z;
		}
		template <class T = Primitives::Float32>
		Point<T>::Point(const T *coords) {
			memcpy(coords, &coordinates, 3 * sizeof(T));
		}
		template <class T = Primitives::Float32>
		Point<T>::Point(const LEVector3<T> *coords) {
			memcpy(&coordinates,&(coords->m_values), 3 * sizeof(T));
		}

		template <class T = Primitives::Float32>
		Point<T>::Point(const Point* point) {
			point->copyCoordinates(&coordinates);
		}

		template <class T = Primitives::Float32>
		void Point<T>::copyCoordinates(T *loc){
			memcpy(loc, &coordinates, 3 * sizeof(T));
		}

	};
};