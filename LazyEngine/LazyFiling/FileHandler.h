#pragma once
#ifndef _FILE_HANDLER_H_
#define _FILE_HANDLER_H_


#include "../Includes/LazyIncludes.h"
#include "../LazyLogger/LogManager.h"
#include <fstream>
#include <string>

using namespace std;
namespace LE {
	class FileReader {
		FILE *fptr;
	
	public:
		
		FileReader(const string s);
		~FileReader();
		void readNextFloat(Primitives::Float32 &val);
		void readNextInt(Primitives::Int32 &val);
		void readNextUInt(Primitives::UInt32 &val);
		bool readNextNonEmptyLine(char* val, Primitives::UInt32 max);
		bool ReadDataToBuffer(int length, int offset, char* buffer);
		Primitives::UInt32 getFileLength();
	};
};
#endif
