#pragma once
#ifndef RAY_H_
#define RAY_H_


#include "../../Math/Quaternion.h"
#include "Point.h"
namespace LE {
	namespace PrimitiveShapes {
		
		class Ray {
		private:
			Point startPoint;
			LEVector3 direction;

		public:
			//Default Direction is world space X axis
			Ray();
			Ray(const Point *point, const LEVector3 *dir);
			Ray(const Ray* ray);
			Point getStartPoint() const;
			LEVector3 getDirection() const;
			void setStartPoint(Point *startpoint);
			void setDirection(LEVector3 *direction);
		};
		
		Ray::Ray() {
			startPoint = Point();
			direction =  LEVector3(1, 0, 0);
		}
		
		Ray::Ray(const Point *point, const LEVector3 *dir)
		{
			startPoint = *point;
			direction = *dir;
		}
		
		Ray::Ray(const Ray* ray) {
			setStartPoint(&ray->getStartPoint());
			setDirection(&ray->getDirection());
		}

		Point Ray::getStartPoint() const{
			return startPoint;
		}

		
		LEVector3 Ray::getDirection() const {
			return direction;
		}

		
		void Ray::setStartPoint(Point *point) {
			startPoint.x = point->x;
			startPoint.y = point->y;
			startPoint.z = point->z;
		}

		
		void Ray::setDirection(LEVector3 *dir) {
			this->direction = *dir;
		}
	};
};

#endif // !RAY_H_
