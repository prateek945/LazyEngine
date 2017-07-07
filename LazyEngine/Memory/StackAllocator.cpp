#include "StackAllocator.h"

namespace LE {
	StackAllocator::StackAllocator(): startPtr(nullptr), currentPtr(nullptr), StackSize(0) {}

	StackAllocator::StackAllocator(void* ptr,Primitives::UInt32 size) : startPtr(ptr), currentPtr(ptr), StackSize((Primitives::Int32)size),spaceLeft(size) {
		LogManager* gLogManager = LogManager::getInstance();
		gLogManager->get()->Log("Stack of size %u assigned at %x\n",StackSize,startPtr);
	}

	void* StackAllocator::Alloc(Primitives::UInt32 size) {
		void* returnPtr = currentPtr;
		currentPtr = (void*)((Primitives::UInt32)currentPtr + size);
		Primitives::UInt32 currentptr_int = (Primitives::UInt32)currentPtr;
		spaceLeft -= size;
		LogManager::getInstance()->get()->Log("Space Left : %u \n", spaceLeft);
		LAZYASSERT(spaceLeft >= 0, "%u",spaceLeft )
		return returnPtr;	
	}

	void StackAllocator::free() {
		currentPtr = startPtr;   
		memset(startPtr, 0, StackSize); 
	}
};