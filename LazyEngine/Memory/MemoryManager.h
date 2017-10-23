#pragma once
#ifndef MEMORY_MANAGER_H_
#define MEMORY_MANAGER_H_
#include "../GeneralMacros/GeneralMacros.h"
#include "MemoryPool.h"
//16B alignment
#define ALLIGNMENT 16
//Increase when number of pools is increased.
#define NUM_MEM_POOLS 25
#define INVALID_UINT 0xFFFFFFFF

namespace LE {
	const unsigned int g_memPool[][2]{
		//increase memory by adding more pools or more blocks in existing pools here.
		{ 16,       65536 },  // we might increase 16 to 32 for 64 bit systems since Handle is 24B on 64 bit systems and we alin block sizes to 16
		{ 32,       4096 },  //
		{ 48,       4096 },  // need a lot of pieces of 40B to work with skin weights
		{ 64,       2048 },  //
		{ 80,       2048 },  //
		{ 96,       2048 },  //
		{ 112,      2048 },  //
		{ 128,      2048 },  //
		{ 256,      2048 },  //
		{ 512,      2048 },  //
		{ 1024,     2048 },  //
		{ 2048,     2048 },  //
		{ 4096,     512 },  //
		{ 8192,     512 },  //
		{ 16384,    1024 },  //
		{ 32768,    512 },   //
		{ 65536,    256 },   //
		{ 131072,   32 },   //
		{ 262144,   16 },    // 256KB ~ 256x256xRGBA              //256K * 
		{ 524288,   8 },    // 512KB
		{ 1048576,  4 },    // 1MB ~ 512x512xRGBA
		{ 2097152,  2 },     // 2MB
		{ 4194304,  1 },     // 4MB
		{ 4194304 * 2,  1 },      // 8MB ~ 1024x1024xRGBA texture // 8MB * 2  =  16MB   SUM
		{ 4194304 * 4,  1 },      // 16 MB                        // 16 * 1   =  16MB   SUM
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
	void allocateBlock(unsigned int size, unsigned int &poolIndex, unsigned int &blockIndex);
	void freeBlock(unsigned int poolIndex, unsigned int blockIndex);
	void *getBlockStart(unsigned int memoryPoolIndex, unsigned int blockIndex)
	{
		return m_MemoryPools[memoryPoolIndex]->getBlockStart(blockIndex);
	}
	
	};
};
#endif // !MEMORY_MANAGER_H_

