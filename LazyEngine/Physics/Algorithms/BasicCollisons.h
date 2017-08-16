#pragma once
#ifndef BASICCOLLISIONS_H_
#define BASICCOLLISIONS_H_

#include "../Colliders/Cube.h"
#include "../Colliders/Sphere.h"
namespace LE {
	LEVector3 SphereVSphere(Colliders::Sphere* A, Colliders::Sphere* B);
	LEVector3 SphereVCube(Colliders::Sphere* A, Colliders::Cube* B);
	LEVector3 CubeVSphere(Colliders::Cube* A, Colliders::Sphere* B);
	LEVector3 CubeVCube(Colliders::Cube* A, Colliders::Cube* B);
	LEVector3 isColliding(Colliders::Collider* A, Colliders::Collider* B);
	
};
#endif 
