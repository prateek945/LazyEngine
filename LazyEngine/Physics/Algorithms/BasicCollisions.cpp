#include "BasicCollisons.h"

namespace LE {
	bool SphereVSphere(Colliders::Sphere* A, Colliders::Sphere* B) {
		PrimitiveShapes::Point centerA, centerB;
		centerA = A->getCenter();
		centerB = B->getCenter();
		LEVector3 AB(centerB.x - centerA.x, centerB.y - centerA.y, centerB.z - centerA.z);
		Primitives::Float32 dist = AB.lengthSqrd();
		return ((dist > (A->getRadius()*A->getRadius() + B->getRadius()*B->getRadius())*1.0001f) ? false : true);
	}
	bool SphereVCube(Colliders::Sphere* A, Colliders::Cube* B) {

		LEVector3 SphereCenter = A->metaData.objMat.getTranslation();
		LEVector3 OBBCenter = B->metaData.objMat.getTranslation();
		LEVector3 dir = SphereCenter - OBBCenter;
		dir.Normalize();
		LEVector3 axes[] = { B->getMetaData().objMat.getU(),B->getMetaData().objMat.getV(),B->getMetaData().objMat.getN() };

		LEVector3 extents((B->max.x - B->min.x) / 2.f, (B->max.y - B->min.y) / 2.f, (B->max.z - B->min.z) / 2.f);

		LEVector3 nearestPT = OBBCenter;
		for (int i = 0; i < 3; i++) {
			Primitives::Float32 dist = dir.dotProduct(axes[i]);
			if (dist > extents.m_values[i]) dist = extents.m_values[i];
			if (dist < -extents.m_values[i]) dist = -extents.m_values[i];
			nearestPT += dist*axes[i];
		}
		if ((SphereCenter - nearestPT).lengthSqrd() >(A->getRadius() * A->getRadius()))
			return false;
		return true;
	}
	bool CubeVCube(Colliders::Cube* A, Colliders::Cube* B) {
		LEVector3 OBBCenterA = LEVector3(A->min.AsVector3() + (A->max.AsVector3() - A->min.AsVector3()) / 2.f);
		LEVector3 OBBCenterB = LEVector3(B->min.AsVector3() + (B->max.AsVector3() - B->min.AsVector3()) / 2.f);

		return false;
	}
	bool isColliding(Colliders::Collider* A, Colliders::Collider* B) {
		Colliders::ColliderType typeA = A->getMetaData().type;
		Colliders::ColliderType typeB = B->getMetaData().type;
		if (typeA == Colliders::ColliderType::TypeSphere
			&& typeB == Colliders::ColliderType::TypeSphere) {
			Colliders::Sphere* AasSphere = static_cast<Colliders::Sphere*>(A);
			Colliders::Sphere* BasSphere = static_cast<Colliders::Sphere*>(B);
			return SphereVSphere(AasSphere, BasSphere);
		}
		else if (typeA == Colliders::ColliderType::TypeSphere
			&& typeB == Colliders::ColliderType::TypeCube) {
			Colliders::Sphere* AasSphere = static_cast<Colliders::Sphere*>(A);
			Colliders::Cube* BasCube = static_cast<Colliders::Cube*>(B);
			return SphereVCube(AasSphere, BasCube);
		}
		else if (typeA == Colliders::ColliderType::TypeCube
			&& typeB == Colliders::ColliderType::TypeSphere) {
			Colliders::Sphere* BasSphere = static_cast<Colliders::Sphere*>(B);
			Colliders::Cube* AasCube = static_cast<Colliders::Cube*>(A);
			return SphereVCube(BasSphere, AasCube);
		}
		else if (typeA == Colliders::ColliderType::TypeCube
			&& typeB == Colliders::ColliderType::TypeCube) {
			Colliders::Cube* AasCube = static_cast<Colliders::Cube*>(A);
			Colliders::Cube* BasCube = static_cast<Colliders::Cube*>(A);
			return CubeVCube(AasCube, BasCube);
		}
		return false;
	}
};