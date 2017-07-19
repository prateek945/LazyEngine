#include "Frustrum.h"

namespace LE {
	namespace PrimitiveShapes {
		template<class T>
		Frustrum<T>::Frustrum(Point<T> origin,LEVector3<T> axis,Primitives::Float32 FOV, Primitives::Float32 nearDist, Primitives::Float32 farDist) {
			//Setup Near and Far clip planes first.
			Primitives::Float32 theta = DEGTORAD(FOV) / 2.f;
			//near plane
			axis.Normalize();
			near.setPoint(Point<T>(origin.x + axis.m_x * nearDist, origin.y + axis.m_y * nearDist, origin.z + axis.m_z * nearDist));
			near.setNormal(&LEVector3<T>((near.getPoint().x - origin.x),(near.getPoint().y - origin.y),(near.getPoint().z - origin.z)).Normalize());
			//far plane
			far.setPoint(&Point<T>(origin.x + axis.m_x * farDist, origin.y + axis.m_y * farDist, origin.z + axis.m_z * farDist);
			far.setNormal(&LEVector3<T>(near.getNormal()));
			far.getNormal().m_z -= far.getNormal().m_z;
			Primitives::Float32 tantheta = tanf(theta);
			Primitives::Float32 halfhightnear = tantheta * nearDist;
			Primitives::Float32 halfheightfar = tantheta * farDist;

			Point<T> A, B, C, D, E, F, G, H;
			//near plane points.
			A = Point<T>(near.getPoint().x + halfhightnear, near.getPoint().y - halfhightnear, near.getPoint().z);
			B = Point<T>(near.getPoint().x + halfhightnear, near.getPoint().y + halfhightnear, near.getPoint().z);
			C = Point<T>(near.getPoint().x - halfhightnear, near.getPoint().y + halfhightnear, near.getPoint().z);
			D = Point<T>(near.getPoint().x - halfhightnear, near.getPoint().y - halfhightnear, near.getPoint().z);
			//far plane points.

			E = Point<T>(far.getPoint().x - halfheightfar, far.getPoint().y - halfheightfar, far.getPoint().z);
			F = Point<T>(far.getPoint().x - halfheightfar, far.getPoint().y + halfheightfar, far.getPoint().z);
			G = Point<T>(far.getPoint().x + halfheightfar, far.getPoint().y + halfheightfar, far.getPoint().z);
			H = Point<T>(far.getPoint().x + halfheightfar, far.getPoint().y - halfheightfar, far.getPoint().z);

			//top plane
			top.setPoint(&Point<T>(near.getPoint().x, near.getPoint().y + halfhightnear, near.getPoint().z);
			top.setNormal(&(normalGivenPoints(C, B, G)));
			//Bottom plane
			bottom.setPoint(&Point<T>(near.getPoint().x, near.getPoint().y - halfhightnear, near.getPoint().z);
			bottom.setNormal(&(normalGivenPoints(E, H, A)));
			//left plane.
			left.setPoint(&Point<T>(near.getPoint().x - halfhightnear, near.getPoint().y , near.getPoint().z);
			left.setNormal(&(normalGivenPoints(E, D, C)));
			//right plane.
			right.setPoint(&Point<T>(near.getPoint().x + halfhightnear, near.getPoint().y, near.getPoint().z);
			right.setNormal(&(normalGivenPoints(A, H, G)));
		}

		template <class T>
		Frustrum<T>::Frustrum(Point<T> A, Point<T> B, Point<T> C, Point<T> D, Point<T> E, Point<T> F, Point<T> G, Point<T> H) {
			//near plane
			near.setPoint(&A);
			near.setNormal(&(normalGivenPoints(A, B, C)));
			//top plane
			top.setPoint(&B);
			top.setNormal(&(normalGivenPoints(C, B, G)));
			//Bottom plane
			bottom.setPoint(&A);
			bottom.setNormal(&(normalGivenPoints(E, H, A)));
			//left plane.
			left.setPoint(&C);
			left.setNormal(&(normalGivenPoints(E, D, C)));
			//right plane.
			right.setPoint(&A);
			right.setNormal(&(normalGivenPoints(A, H, G)));
			//far plane.
			far.setPoint(&G);
			near.setNormal(&(normalGivenPoints(F, G, H)));
		}

		template <class T>
		LEVector3<T> Frustrum<T>::normalGivenPoints(Point<T> A, Point<T> B, Point<T> C) {
			LEVector3<T> v1 = LEVector3<T>(B.x - A.x, B.y - A.y, B.z - A.z).Normalize();
			LEVector3<T> v2 = LEVector3<T>(C.x - B.x, C.y - B.y, C.z - B.z).Normalize();
			v1.crossProduct(v2);
			return v1;
		}
	};
};