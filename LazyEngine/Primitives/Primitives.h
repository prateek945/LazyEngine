#pragma once
#ifndef  PRIMITIVES_H_
#define PRIMITIVES_H_
#include <stdint.h>
namespace LE {
	namespace Primitives {
		typedef uint32_t UInt32;
		typedef int32_t Int32 ;
		typedef int16_t Int16;
		typedef uint16_t UInt16;
		typedef float Float32;
		typedef double Float64;
		typedef double Double;

		typedef char Char;
		typedef unsigned char Byte;
		typedef char * String;
		typedef bool Bool;

		namespace Constants {
			const Float32 c_Pi_F32 = 3.1415926535897932384626433832795f;
			const Float64 c_Pi_F64 = 3.1415926535897932384626433832795;
			const Float32 c_Epsilon_F32 = 0.00001f;

			const Float32 c_MaxFloat32 = 1000000000.0f;

			const Float32 c_LargeFloat32 = 1000000000.0f;

			const UInt32 c_MaxUInt32 = 0xFFFFFFFF;
			const Int32 c_MaxInt32 = 0x7FFFFFFF;
			const Int32 c_MinInt32 = 0x80000000;
			const UInt32 c_MaxUInt16 = 0xFFFF;
			const Int16 c_MaxInt16 = 0x7FFF;
			const Int16 c_MinInt16 = 0x8000;
		}
	};
};
#endif // ! PRIMITIVES_H_
