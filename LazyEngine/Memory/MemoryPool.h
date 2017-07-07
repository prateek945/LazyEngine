#pragma once
#ifndef MEMORY_POOL_H_
#define MEMORY_POOL_H_
#include "../Includes/LazyIncludes.h"
#include "../Primitives/Primitives.h"
#include "StackAllocator.h"

#include <malloc.h>

namespace LE {
	const Primitives::UInt32 Memory_pools[][2] = {
		{ 0,40 MB }, // Alligned Allocator General
		{ 1,200 MB }, // Stack Allocator for level loading and 
		{ 2,16 MB },
	};

	class MemoryPool {
		//Allocating 256 MB memory across various Allocators

	public: 
		MemoryPool() {
			Primitives::UInt32 totalSize = 0;
			for (int i = 0; i < 3; i++) {
				totalSize += Memory_pools[i][1] + ALLIGNMENT;
			}
			CurrentAllocPtr = malloc(totalSize + ALLIGNMENT);
			LAZYASSERT(CurrentAllocPtr,"Pointer Not Set");
			stackAllocatorRef =  new StackAllocator(CurrentAllocPtr, (Primitives::UInt32)(1 MB));
			
		}

		StackAllocator* getStackAllocator() { return stackAllocatorRef; }
		
	private:
		void* CurrentAllocPtr;
		StackAllocator* stackAllocatorRef;
		

	};
};
#endif