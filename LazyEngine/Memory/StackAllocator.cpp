#include "StackAllocator.h"

namespace LE {
	StackAllocator::StackAllocator(): startPtr(nullptr), currentPtr(nullptr), StackSize(0) {}

	StackAllocator::StackAllocator(void* ptr,Primitives::UInt32 size) : startPtr(ptr), currentPtr(ptr), StackSize(size),spaceLeft(size) {
		LogManager* gLogManager = LogManager::getInstance();
		gLogManager->get()->Log("Stack of size %u assigned at %x\n",StackSize,startPtr);
	}

	void* StackAllocator::Alloc(Primitives::UInt32 size) {
		currentPtr = (void*)((Primitives::UInt32)currentPtr + size);
		
		
		Primitives::UInt32 currentptr_int = (Primitives::UInt32)currentPtr;
		spaceLeft -= size;
		LAZYASSERT(spaceLeft >= 0, "%u",spaceLeft )
		
		return currentPtr;
		
		
	}
};