#include "Ray.h"

namespace LE {
	namespace PrimitiveShapes {
		template<class T>
		Ray<T>::Ray() {
			*this.startPoint = new Point<T>();
			*this.direction = new LEVector3<T>(1, 0, 0);
		}
		template<class T>
		Ray<T>::Ray(const Point<T> *point, const LEVector3<T> *dir)
		{
			*this.startPoint(*point);
			*this.direction = *dir;
		}
		template<class T>
		Ray<T>::Ray(const Ray* ray) {
			setStartPoint(ray->getStartPoint());
			setDirection(ray->getDirection());
		}

		template <class T>
		Point<T> Ray<T>::getStartPoint() {
			return startPoint;
		}

		template <class T>
		LEVector3<T> Ray<T>::getDirection() {
			return direction;
		}

		template <class T>
		void Ray<T>::setStartPoint(Point<T> *point) {
			point->copyCoordinates(&(*this.startPoint));
		}

		template <class T>
		void Ray<T>::setDirection(LEVector3<T> *dir) {
			*this.direction = *dir;
		}
	};
};