#pragma once
#ifndef BASICCOLLISIONS_H_
#define BASICCOLLISIONS_H_

#include "../Colliders/Cube.h"
#include "../Colliders/Sphere.h"
namespace LE {
	bool SphereVSphere(Colliders::Sphere* A, Colliders::Sphere* B);
	bool SphereVCube(Colliders::Sphere* A, Colliders::Cube* B);
	bool CubeVCube(Colliders::Cube* A, Colliders::Cube* B);
	bool isColliding(Colliders::Collider* A, Colliders::Collider* B);
	
};
#endif 
