#include "Plane.h"

namespace LE {
	namespace PrimitiveShapes {
		Plane::Plane() {
			this->setNormal(LEVector3(1, 0, 0));
			this->setPoint(Point());
		}
		Plane::Plane(Point point, LEVector3 norm) {
			this->point = point;
			normal = norm;
		}


		Point Plane::getPoint() {
			return point;
		}


		LEVector3 Plane::getNormal() {
			return normal;
		}


		void Plane::setPoint(Point p) {
			point = p;
		}

		void Plane::setNormal(LEVector3 norm) {
			normal = norm;
		}
	};
};