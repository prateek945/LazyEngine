#pragma once
#ifndef LOG_MANAGER_H_
#define LOG_MANAGER_H_
#include "../GeneralMacros/GeneralMacros.h"
#include "Logger.h"
namespace LE {
	
		class LogManager {

		public:
			LogManager();
			~LogManager();
			Logger* get() const;
			void startUp();
			void shutDown();
			static LogManager* getInstance();
		private:
			static LogManager *gLogManager;
			Logger *m_singletonReference;
		};
};
#endif