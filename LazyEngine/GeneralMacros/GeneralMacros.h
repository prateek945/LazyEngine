#pragma once
#ifndef GENERAL_MACROS_H_
#define GENERAL_MACROS_H_
#define DebugPause _asm {int 3}
#define LAZYASSERT(truth) {if(!truth) {DebugPause} }
#define MAX_DEBUG_CHAR 1024
// Class definition Macros

#define CLASS_SINGLETON(managerclass_,class_) \
		class managerclass_{ \
			public:\
			managerclass_() {} \
			~managerclass_() {} \
			class_* get() {return m_singletonReference;} \
			void startUp() { m_singletonReference = new class_(); }\
			void shutDown();\
			\
			class_ *m_singletonReference; \
		};\
		managerclass_ g##managerclass_;\
		
#endif
//#define IFNDEF(className) #ifndef classname/
							