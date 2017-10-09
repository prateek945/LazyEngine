#pragma once
#ifndef MEMORY_MANAGER_H_
#define MEMORY_MANAGER_H_
#include "../GeneralMacros/GeneralMacros.h"
#include "MemoryPool.h"
//16B alignment
#define ALLIGNMENT 16
//Increase when number of pools is increased.
#define NUM_MEM_POOLS 9
#define INVALID_UINT 0xFFFFFFFF

namespace LE {
	const unsigned int g_memPool[][2]{
		//increase memory by adding more pools or more blocks in existing pools here.
		{16,1024},
		{32,1024},
		{64,1024},
		{128,1024},
		{512,1024},
		{1024,16},
		{2048,16},
		{32 MB,16},
		
	};
	//CLASS_SINGLETON_DECL(MemoryManager, MemoryPool)
	class MemoryManager{
private:
	static MemoryManager *m_globalInstance;
public:
	MemoryPool* m_MemoryPools[NUM_MEM_POOLS];
	MemoryManager() {};
	~MemoryManager() {};
	static MemoryManager* getInstance();
	//Setup function for the global class instance as well as the memory block.
	//Call this once in main method.
	void startUp();
	void* allocateBlock(unsigned int size, unsigned int &poolIndex, unsigned int &blockIndex);
	void freeBlock(unsigned int poolIndex, unsigned int blockIndex);
	
	};
};
#endif // !MEMORY_MANAGER_H_

