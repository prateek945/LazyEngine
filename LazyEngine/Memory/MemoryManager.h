#pragma once
#ifndef MEMORY_MANAGER_H_
#define MEMORY_MANAGER_H_
#include "../GeneralMacros/GeneralMacros.h"
#include "MemoryPool.h"
namespace LE {
	//CLASS_SINGLETON_DECL(MemoryManager, MemoryPool)
	class MemoryManager {

	public:
		MemoryManager();
		~MemoryManager();
		MemoryPool* get() const;
		void startUp();
		void shutDown();
		static MemoryManager* getInstance();
	private:
		static MemoryManager* gMemoryManager;
		MemoryPool *m_singletonReference;
	};
};
#endif // !MEMORY_MANAGER_H_

