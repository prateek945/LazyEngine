#include "MemoryManager.h"

namespace LE {
	MemoryManager* MemoryManager::m_globalInstance = 0;
	MemoryManager* MemoryManager::getInstance() {
		return m_globalInstance;
	}
	void *allignPtr(void* ptr) {
		void* allignPtr = ptr;
		unsigned int offset = (uintptr_t)allignPtr % ALLIGNMENT;
		if (offset)
			allignPtr = (void*)((uintptr_t)allignPtr + ALLIGNMENT - offset);
		return allignPtr;
	}
	//Setup function for the global class instance as well as the memory block.
	//Call this once in main method.
	void MemoryManager::startUp() {

		unsigned int size = 0;
		for (unsigned int i = 0; i < NUM_MEM_POOLS; i++) {
			size += MemoryPool::sizeRequired(g_memPool[i][0], g_memPool[i][1]);
			size += ALLIGNMENT;
		}
		void *ptr = malloc(size + ALLIGNMENT);

		printf("Allocated memory %d Bytes at location 0x%x", size + ALLIGNMENT, ptr);
		void* allignedPtr = allignPtr(ptr);
		m_globalInstance = new MemoryManager();
		//Now create the actual pools over the complete memory block
		for (unsigned int i = 0; i < NUM_MEM_POOLS; i++) {
			m_globalInstance->m_MemoryPools[i] = MemoryPool::startUp(g_memPool[i][0], g_memPool[i][1], allignedPtr);
		}

	}
	void* MemoryManager::allocateBlock(unsigned int size, unsigned int &poolIndex, unsigned int &blockIndex)
	{
		void* ptr = 0;
		for (unsigned int i = 0; i < NUM_MEM_POOLS; i++) {
			if (g_memPool[i][0] >= size) {
				poolIndex = i;
				ptr = m_globalInstance->m_MemoryPools[i]->allocateBlock(blockIndex);
				break;
			}
		}
		return ptr;
	}
	void MemoryManager::freeBlock(unsigned int poolIndex, unsigned int blockIndex) {
		m_globalInstance->m_MemoryPools[poolIndex]->freeBlock(blockIndex);
	}
	
};

