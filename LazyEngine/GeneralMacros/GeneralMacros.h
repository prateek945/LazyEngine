#pragma once
#ifndef GENERAL_MACROS_H_
#define GENERAL_MACROS_H_
#define DebugPause _asm {int 3}
#define LAZYASSERT(truth) {if(!truth) {DebugPause} }
#endif
//#define IFNDEF(className) #ifndef classname/
							