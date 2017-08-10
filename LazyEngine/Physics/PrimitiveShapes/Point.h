#pragma once
#ifndef POINT_H_
#define POINT_H_

#include "../../Math/LEVector.h"
namespace LE {
	namespace PrimitiveShapes {
		
		class Point {
		public:
			union {
				struct {
					Primitives::Float32 x, y, z;
				};
				Primitives::Float32 coordinates[3];
			};
			//initialize to 0
			Point();
			Point( Primitives::Float32 x,  Primitives::Float32 y,  Primitives::Float32 z);
			Point( Primitives::Float32 *coords);
			Point( LEVector3 coords);
			Point( const Point *point);

			void copyCoordinates(Primitives::Float32 *loc);
			friend ostream &operator << (ostream &out, const Point &p) {
				out << "Point : "  << p.x << " " << p.y << " " << p.z << '\n';
				return out;
			}
			LEVector3 AsVector3();
		};

		
		

		
	};
};
#endif