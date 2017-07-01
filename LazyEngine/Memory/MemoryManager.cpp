#include "MemoryManager.h"
namespace LE {
		MemoryManager *MemoryManager::gMemoryManager = new MemoryManager();
		MemoryManager::MemoryManager() {}
		MemoryManager::~MemoryManager() {}
		MemoryPool* MemoryManager::get() const { return m_singletonReference; }
		void MemoryManager::startUp() { 
			MemoryManager::gMemoryManager = new MemoryManager();
			m_singletonReference = new MemoryPool(); }
		void MemoryManager::shutDown() {}
		MemoryManager* MemoryManager::getInstance() { return MemoryManager::gMemoryManager; }

};