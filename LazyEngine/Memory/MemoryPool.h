#pragma once
#ifndef MEMORY_POOL_H_
#define MEMORY_POOL_H_
#include "../Includes/LazyIncludes.h"
#include "../Primitives/Primitives.h"

namespace LE {
	class MemoryPool {
	private:

		struct PoolHeader {
			void* startPtr;
			unsigned int m_poolSize, m_nBlocks, m_nBlocksFree;
		};
		PoolHeader m_header;
		unsigned int m_freeBlocks[];
	public:
		MemoryPool() {

		}
		~MemoryPool() {

		}
		static MemoryPool* startUp(unsigned int poolSize, unsigned int numBlocks, void *Ptr) {

			MemoryPool* ptr = (MemoryPool *)Ptr;

			ptr->m_header.startPtr = (void*)((uintptr_t)sizeof(PoolHeader) + numBlocks * sizeof(unsigned int) + (uintptr_t)Ptr);
			ptr->m_header.m_poolSize = poolSize;
			ptr->m_header.m_nBlocks = numBlocks;
			ptr->m_header.m_nBlocksFree = numBlocks;

			for (unsigned int i = 0; i < numBlocks; i++) {
				ptr->m_freeBlocks[i] = i;

			}
			return ptr;
		}
		void* allocateBlock(unsigned int &blockIndex) {
			void *ptr;
			blockIndex = m_freeBlocks[--m_header.m_nBlocksFree];
			return (void*)((uintptr_t)m_header.startPtr + blockIndex*m_header.m_poolSize);
		}
		void freeBlock(unsigned int blockIndex) {
			m_freeBlocks[m_header.m_nBlocksFree++] = blockIndex;
			memset((void*)((uintptr_t)m_header.startPtr + blockIndex*m_header.m_poolSize), 0, m_header.m_poolSize);
		}
		static unsigned int sizeRequired(unsigned int blockSize, unsigned int numBlocks) {
			return ((uintptr_t)sizeof(PoolHeader) + numBlocks * sizeof(unsigned int) + blockSize*numBlocks);
		}
	};
};
#endif