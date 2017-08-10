#include "LogManager.h"
namespace LE {
	LogManager* LogManager::gLogManager = new LogManager();
	LogManager::LogManager() {}
	LogManager::~LogManager() {}
	Logger* LogManager::get() const { return m_singletonReference; }
	void LogManager::startUp() {
		
		m_singletonReference = new Logger(); 
	}
	void LogManager::shutDown() {}
	LogManager* LogManager::getInstance() { return LogManager::gLogManager; }
};
	
