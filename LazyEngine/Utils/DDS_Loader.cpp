#include "DDS_Loader.h"

namespace LE {
	namespace DDS {
		bool loadDDSFromFile(const char* fileName, DDSTextureInSystemMemory* dds) {
			unsigned char* buffer;
			FileReader fr = FileReader(fileName);
			Primitives::UInt32 FileSize = fr.getFileLength();
			buffer = static_cast<unsigned char*>(malloc(FileSize));
			fr.ReadDataToBuffer(buffer);
			string ddstag;
			ddstag.copy((char*)buffer, 4);
			
			LAZYASSERT(ddstag.compare("DDS "), "%s is not a dds texture", fileName);
			buffer += 4;
			DDSHeader* ddsh = (DDSHeader*)buffer;
			buffer += sizeof(DDSHeader);




		}

		bool loadDataFromHeaderInFile(const char* fileName, DDSHeader *ddsh) {

		}
	};
};