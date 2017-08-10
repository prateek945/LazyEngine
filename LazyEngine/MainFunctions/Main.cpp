#include "Main.h"

#include "../Physics/Algorithms/BasicCollisons.h"
#include <time.h>
#include <chrono>
#include <thread>
#include <mutex>
using namespace std;
namespace LE {
	int MainWrapper() {
		cout << "Hello\n";

		LogManager *gLogManager = LogManager::getInstance();
		gLogManager->startUp();
		LAZYASSERT(gLogManager->get(), "Log Manager Not Set")
			
		MemoryManager *gMemoryManager = MemoryManager::getInstance();
		gMemoryManager->startUp();
		LAZYASSERT(gMemoryManager->get(), "Memory Manager Not Set")

		PhysicsManager *gPhysicsManager = PhysicsManager::getInstance();
		gPhysicsManager->startUp((Primitives::Int16) 100);
		LAZYASSERT(gPhysicsManager->get(), "Physics Manager Not Set")
		Colliders::ColliderMeta meta = {};
		meta.type = Colliders::ColliderType::TypeFrustrum;
		
//		Colliders::Cube cube = Colliders::Cube(1.f,1.f,1.f,meta);
		Colliders::Frustrum viewFrust = Colliders::Frustrum();
		viewFrust.getFurthestInDir(new LEVector3(1,0,0));
		Matrix4X4 m(1,0,0,10
			,0,1,0,10
			,0,0,1,10,
			0,0,0,1);
		LEVector3 v(1, 2, 1);
		v.Normalize();
		//cout << v * m.inverse();
		//cout << m.m31 << '\n';
		meta.objMat = m;
		meta.type = Colliders::ColliderType::TypeSphere;
		Colliders::Sphere sphere(meta);
		
		Colliders::Collider *c = new Colliders::Sphere(PrimitiveShapes::Point(0,0,0),1.f,meta);
		Colliders::Collider *c1 = new Colliders::Sphere(PrimitiveShapes::Point(1, 0, 4), 1.f, meta);
		meta.type = Colliders::ColliderType::TypeCube;
		Colliders::Collider *c2 = new Colliders::Cube(PrimitiveShapes::Point(10, 10, 10), 1.f, 1.f, 1.f,meta);
		std::vector<std::unique_ptr<Colliders::Collider>> cv;
		cv.push_back(std::make_unique<Colliders::Cube>(PrimitiveShapes::Point(10, 10, 10), 1.f, 1.f, 1.f, meta));
		if (isColliding(c, c2))
			cout << "Collide!!\n";
		
		
		//cout << sphere.getFurthestInDir(&v);
		
		return 0;
	}
};
//
//using namespace std;
//int main(int argc, char* argv) {
//
//	LE::MainWrapper();
//	while (true) {
//
//	}
//}
