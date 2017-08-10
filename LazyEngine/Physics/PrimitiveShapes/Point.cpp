#include "Point.h"
namespace LE {
	namespace PrimitiveShapes {
		Point::Point() {
			x = (Primitives::Float32)0;
			y = (Primitives::Float32)0;
			z = (Primitives::Float32)0;
		}

		Point::Point(Primitives::Float32 xC, Primitives::Float32 yC, Primitives::Float32 zC) {
			x = xC;
			y = yC;
			z = zC;
		}

		Point::Point(Primitives::Float32 *coords) {
			memcpy(coords, &coordinates, 3 * sizeof(Primitives::Float32));
		}

		Point::Point(LEVector3 coords) {
			memcpy(&coordinates, &(coords.m_values), 3 * sizeof(Primitives::Float32));
		}


		Point::Point(const Point *point) {
			x = point->x;
			y = point->y;
			z = point->z;
		}


		void Point::copyCoordinates(Primitives::Float32 *loc) {
			memcpy(loc, &coordinates, 3 * sizeof(Primitives::Float32));
		}

		LEVector3 Point::AsVector3()
		{
			return LEVector3(x, y, z);
		}
	};
};