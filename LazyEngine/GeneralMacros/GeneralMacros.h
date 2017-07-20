#pragma once
#ifndef GENERAL_MACROS_H_
#define GENERAL_MACROS_H_

#define DebugPause _asm {int 3}
#define global_variable static
#define internal_function static
#define internal_variable static
#define DEGTORAD(deg) (((Primitives::Constants::c_Pi_F32)*(deg))/(180.0f))
#define RADTODEG(rad) (((180.0f)*(rad))/(Primitives::Constants::PI))

#define LAZYASSERT(truth,format,...) {if(!(truth)){\
LE::LogManager::getInstance()->get()->Log(format "\n",##__VA_ARGS__);\
DebugPause} }\

#define MAX_DEBUG_CHAR 1024

#define MB * (1048576)

#define ALLIGNMENT 16

#define CREATEOBJ(var,obj,...)/

#define DEBUGLOG(format,...) LE::LogManager::getInstance()->get()->Log(format,##__VA_ARGS__);
// Class definition Macros


		
		
#endif
//#define IFNDEF(className) #ifndef classname/
							