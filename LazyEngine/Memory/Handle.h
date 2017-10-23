#pragma once

#include "../Includes/LazyIncludes.h"
#include "../LazyLogger/LogManager.h"
#include "MemoryManager.h"
namespace LE {
	struct Handle {
	
		void* m_objPtr;
		unsigned int m_poolIndex, m_blockIndex, objectSize;
		bool valid;
	public:
		Handle(){}
		Handle(unsigned int size) : m_objPtr(0), m_poolIndex(INVALID_UINT), m_blockIndex(INVALID_UINT), objectSize(0) {

			if (size > 0) {
				objectSize = size;
				MemoryManager::getInstance()->allocateBlock(size, m_poolIndex, m_blockIndex);
				m_objPtr = MemoryManager::getInstance()->getBlockStart(m_poolIndex, m_blockIndex);
				LAZYASSERT(m_objPtr, "No free Memory for this block size");
			}
		}
		template<typename T>
		T* getObject() {
			if (sizeof(T) > objectSize) {
				std::cout << "Object Size is larger than this memory block";
				return nullptr;
			}
			else
				return (T*)m_objPtr;
		}
		void* getAddress() {
			return m_objPtr;
		}
		void Release() {
			MemoryManager::getInstance()->freeBlock(m_poolIndex, m_blockIndex);
		}

		bool operator==(const Handle &b)
		{
			return (m_objPtr == b.m_objPtr);
		}
	};
};