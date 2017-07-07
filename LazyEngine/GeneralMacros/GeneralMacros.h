#pragma once
#ifndef GENERAL_MACROS_H_
#define GENERAL_MACROS_H_

#define DebugPause _asm {int 3}

#define DEGTORAD(deg) (((Primitives::Constants::PI)*(deg))/(180.0f))
#define RADTODEG(rad) (((180.0f)*(rad))/(Primitives::Constants::PI))

#define LAZYASSERT(truth,format,...) {if(!(truth)){\
LogManager::getInstance()->get()->Log(format "\n",##__VA_ARGS__);\
DebugPause} }\

#define MAX_DEBUG_CHAR 1024

#define MB * (1048576)

#define ALLIGNMENT 16
// Class definition Macros


		
		
#endif
//#define IFNDEF(className) #ifndef classname/
							