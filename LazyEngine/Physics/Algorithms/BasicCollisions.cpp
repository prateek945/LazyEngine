#include "BasicCollisons.h"

namespace LE {
	LEVector3 SphereVSphere(Colliders::Sphere* A, Colliders::Sphere* B) {
		LEVector3 retNormal(0, 0, 0);
		PrimitiveShapes::Point centerA, centerB;
		Primitives::Float32 scaleR = A->metaData.objMat.getScale().m_x;
		centerA = A->metaData.objMat.getTranslation();
		centerB = B->metaData.objMat.getTranslation();
		LEVector3 AB(centerB.x - centerA.x, centerB.y - centerA.y, centerB.z - centerA.z);
		//AB.Normalize();
		Primitives::Float32 dist = AB.lengthSqrd();
		Primitives::Float32 radiiSqrd = A->getRadius()*A->getRadius()*scaleR*scaleR + B->getRadius()*B->getRadius()*scaleR*scaleR;
		if ((dist <= (radiiSqrd))) {
			retNormal = -AB;
			retNormal.Normalize();
			if(dist < radiiSqrd) {
				Primitives::Float32 moveBackDist = radiiSqrd - dist;
				LEVector3 newCenter = centerA.AsVector3() + moveBackDist*retNormal;
				A->metaData.objMat.setTranslation(newCenter);
			}
			
			return retNormal;
		}
		return  LEVector3(0, 0, 0);
	}
	LEVector3 SphereVCube(Colliders::Sphere* A, Colliders::Cube* B) {
		LEVector3 retNormal(0, 0, 0);
		LEVector3 SphereCenter = A->metaData.objMat.getTranslation();
		Primitives::Float32 scaleR = A->metaData.objMat.getScale().m_x;
		LEVector3 OBBCenter = B->metaData.objMat.getTranslation();
		LEVector3 dir = SphereCenter - OBBCenter;
		//dir.Normalize();
		LEVector3 axes[] = { B->getMetaData().objMat.getU(),B->getMetaData().objMat.getV(),B->getMetaData().objMat.getN() };
		LEVector3 scale = B->getMetaData().objMat.getScale();
		LEVector3 extents(((B->max.x - B->min.x) / 2.f)*scale.m_x, ((B->max.y - B->min.y) / 2.f)*scale.m_y,
			((B->max.z - B->min.z) / 2.f)*scale.m_z);

		LEVector3 nearestPT = OBBCenter;
		for (int i = 0; i < 3; i++) {
			axes[i].Normalize();
			Primitives::Float32 dist = dir.dotProduct(axes[i]);
			if (dist > extents.m_values[i]) dist = extents.m_values[i];
			if (dist < -extents.m_values[i]) dist = -extents.m_values[i];
			nearestPT += dist*axes[i];
		}
		//nearestPT = OBBCenter - nearestPT;
		float v = (SphereCenter - nearestPT).lengthSqrd();
		if ((SphereCenter - nearestPT).lengthSqrd() *0.85 <= (A->getRadius()*scaleR * A->getRadius()*scaleR)) {
			
			nearestPT = nearestPT - OBBCenter;
			//retNormal = nearestPT.dotProduct(axes[0])*axes[0];
   			for (unsigned int i = 0; i < 3; i++) {
				if (fabs(nearestPT.m_values[i]) == extents.m_values[i]) {
					retNormal += nearestPT.dotProduct(axes[i])*axes[i];
				}
				
			}
			retNormal.Normalize();
			nearestPT += OBBCenter;
			if ((SphereCenter - nearestPT).lengthSqrd() < (A->getRadius()*scaleR * A->getRadius()*scaleR)) {
				LEVector3 invRet = LEVector3(0, 0, 0);
				for (int i = 0; i < 3; i++) {
					if (retNormal.m_values[i] < 0) invRet.m_values[i] = -1;
					else if (retNormal.m_values[i] > 0) invRet.m_values[i] = 1;
					else invRet.m_values[i] = 0;
				}

				LEVector3 newCenter = LEVector3(0,0,0);
				
				newCenter += OBBCenter + invRet*extents + (A->getRadius()*scaleR)*invRet;
				//Push back center to avoid intersection.
				for (int i = 0; i < 3; i++) {
					if (newCenter.m_values[i] - OBBCenter.m_values[i] == 0)
						newCenter.m_values[i] += SphereCenter.m_values[i] - OBBCenter.m_values[i];
				}
				A->metaData.objMat.setTranslation(newCenter);
			}
			return retNormal;
		}
		return LEVector3(0,0,0);
	}
	LEVector3 CubeVSphere(Colliders::Cube* B, Colliders::Sphere* A) {
		LEVector3 retNormal(0, 0, 0);
		LEVector3 SphereCenter = A->metaData.objMat.getTranslation();
		LEVector3 OBBCenter = B->metaData.objMat.getTranslation();
		LEVector3 dir = SphereCenter - OBBCenter;
		dir.Normalize();
		LEVector3 axes[] = { B->getMetaData().objMat.getU(),B->getMetaData().objMat.getV(),B->getMetaData().objMat.getN() };
		LEVector3 scale = B->getMetaData().objMat.getScale();
		LEVector3 extents(((B->max.x - B->min.x) / 2.f)*scale.m_x, ((B->max.y - B->min.y) / 2.f)*scale.m_y,
			((B->max.z - B->min.z) / 2.f)*scale.m_z);

		LEVector3 nearestPT = OBBCenter;
		for (int i = 0; i < 3; i++) {
			Primitives::Float32 dist = dir.dotProduct(axes[i]);
			if (dist > extents.m_values[i]) dist = extents.m_values[i];
			if (dist < -extents.m_values[i]) dist = -extents.m_values[i];
			nearestPT += dist*axes[i];
		}
		//nearestPT = OBBCenter - nearestPT;
		if ((SphereCenter - nearestPT).lengthSqrd() * 0.9999f <= (A->getRadius() * A->getRadius())) {

			retNormal = nearestPT - SphereCenter;
			retNormal.Normalize();
			return retNormal;
		}
		return LEVector3(0, 0, 0);
	}
	LEVector3 CubeVCube(Colliders::Cube* A, Colliders::Cube* B) {
		LEVector3 retNormal(0, 0, 0);
		LEVector3 OBBCenterA = LEVector3(A->min.AsVector3() + (A->max.AsVector3() - A->min.AsVector3()) / 2.f);
		LEVector3 OBBCenterB = LEVector3(B->min.AsVector3() + (B->max.AsVector3() - B->min.AsVector3()) / 2.f);

		return LEVector3(0, 0, 0);
	}
	LEVector3 isColliding(Colliders::Collider* A, Colliders::Collider* B) {
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
			return CubeVSphere(AasCube, BasSphere);
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
		return LEVector3(0, 0, 0);
	}
};