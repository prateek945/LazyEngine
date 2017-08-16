#include "ColliderBase.h"

namespace LE {
	namespace Colliders {
		Collider::Collider() :metaData(), collisionCount(0){}
		Collider::Collider(ColliderMeta m) :metaData(m) {}
		Collider::Collider(Collider const&col) {
			collisionCount = col.getCollisionCount();
			collidedObjs = col.getCollidedObjs();
			metaData = col.metaData;
		}
		//virtual PrimitiveShapes::Point Collider::getFurthestInDir(LEVector3 *Dir) = 0;
		ColliderMeta Collider::getMetaData() { return metaData; }
		void Collider::setColliderType(ColliderType type) { metaData.type = type; }
		void Collider::setCollisionCount(Primitives::Int16 count) { collisionCount = count; }
		void Collider::incrementCollisionCount() {
			collisionCount++;
		}
		void Collider::addColliderIdNormal(Primitives::Int16 id,LEVector3 normal) {
			collidedObjs.push_back(std::make_pair(id,normal));
		}
		std::pair<Primitives::Int16, LEVector3> Collider::getColliderId(Primitives::Int16 index)const {
			return collidedObjs.at(index);
		}
		 Primitives::Int16 Collider::getCollisionCount() const {
			return collisionCount;
		}
		 std::vector<std::pair<Primitives::Int16,LEVector3>> Collider::getCollidedObjs() const {
			return collidedObjs;
		}
		
		
	}
}