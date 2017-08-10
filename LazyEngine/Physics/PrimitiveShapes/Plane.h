#pragma once
#ifndef PLANE_H_



#include "Point.h"
namespace LE {
	namespace PrimitiveShapes {
		
		class Plane {	
		public:
			Point point;
			LEVector3 normal;
			//Normal is perpendicular to world space X axis.
			Plane();

			Plane& operator=(Plane rhs) {
				Plane ret();
				setNormal(rhs.getNormal());
				setPoint(rhs.getPoint());
				return *this;
			}
			Plane( Point point,  LEVector3 norm);
			Plane(Plane&&) = default;
			//Plane(Plane) = default;

			Point getPoint(void);
			LEVector3 getNormal(void);

			void setPoint(Point point);
			void setNormal(LEVector3 normal);


		};

		
		
		
	};
};
#endif