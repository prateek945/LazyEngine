#include "FileHandler.h"
namespace LE {

	FileReader::FileReader(const string filename) {
		fptr = fopen(filename.c_str(), "r");
		LAZYASSERT(fptr, "File %s could not be opened for reading", filename)
	}
	FileReader::~FileReader() {
		fclose(fptr);
	}
	void FileReader::readNextFloat(Primitives::Float32 &val) {
		fscanf(fptr, "%f", &val);
	}
	void FileReader::readNextInt(Primitives::Int32 &val) {
		fscanf(fptr, "%d", &val);
	}
	void FileReader::readNextUInt(Primitives::UInt32 &val) {
		fscanf(fptr, "%u", &val);
	}
	bool FileReader::readNextNonEmptyLine(char* val, Primitives::UInt32 max) {

		if (fgets(val, max, fptr) == NULL)
			return false;
		int len = strlen(val);

		while (len && (val[len - 1] == '\x0D' || val[len - 1] == '\x0A'))
		{
			val[len - 1] = '\0';
			len--;
		}

		if (len == 0 || (strcmp(val, " ") == 0)) // read until get non empty line
		{
			return readNextNonEmptyLine(val, max); // search deeper
		}
		else
		{
			return true; // good line
		}
	}

	bool FileReader::ReadDataToBuffer(unsigned char* buffer) {
		if (fptr == nullptr)
			return false;
		
		fseek(fptr, 0, SEEK_END);
		int size = ftell(fptr);
		fseek(fptr, 0, SEEK_SET);
		fread(buffer, 1, size, fptr);
		
		return true;
	}

	Primitives::UInt32 FileReader::getFileLength() {

		fseek(fptr, 0, SEEK_END);
		Primitives::UInt32 size = ftell(fptr);
		return size;

	}
};