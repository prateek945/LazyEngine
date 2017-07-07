#pragma once
#ifndef STACK_ALLOCATOR_H_
#define STACK_ALLOCATOR_H_
#include "../Includes/LazyIncludes.h"
#include "../LazyLogger/LogManager.h"
namespace LE {
	class StackAllocator {
	public:
		StackAllocator();
		StackAllocator(void* ptr, Primitives::UInt32 space);
		void* Alloc(Primitives::UInt32 size);
		void free();
		void* getCurrentPtr() { return currentPtr; }
	private:
		void *currentPtr,*startPtr;
		Primitives::UInt32 StackSize;
		Primitives::Int32 spaceLeft;

	};
}; // LE
#endif // !STACK_ALLOCATOR_H
