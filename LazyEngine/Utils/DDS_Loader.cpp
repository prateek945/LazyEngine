#include "DDS_Loader.h"
#pragma warning(disable : 4996)
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
			Primitives::Int32 width, height, components,uncompressedFormat,GPUFormat;
			width = ddsh->dwWidth;
			height = ddsh->dwHeight;

			dds->width = width;
			dds->height = height;
			
			if (ddsh->ddspf.dwFlags == DDS_RGBA && ddsh->ddspf.dwRGBBitCount == 32)
			{
				uncompressedFormat = DDS_RGBA;
				components = 4;
				printf("decodeDDSFormat(): DDS format (was DDSF_RGBA with RGBBitCount = 32), components = 4\n");
			}
			else if (ddsh->ddspf.dwFlags == DDS_RGB  && ddsh->ddspf.dwRGBBitCount == 32)
			{
				uncompressedFormat = DDS_RGB;
				components = 4;
				printf("decodeDDSFormat(): DDS format (was DDSF_RGB with RGBBitCount = 32), components = 4\n");
			}

			else if (ddsh->ddspf.dwFlags == DDS_RGB  && ddsh->ddspf.dwRGBBitCount == 24)
			{
				uncompressedFormat = DDS_RGB;
				components = 3;
				printf("decodeDDSFormat(): DDS format (was DDSF_RGB with RGBBitCount = 24), components = 3\n");
			}

			else if (ddsh->ddspf.dwRGBBitCount == 8)
			{
				uncompressedFormat = DDS_LUMINANCE;
				components = 1;
				printf("decodeDDSFormat(): DDS format (was RGBBitCount = 8), components = 1\n");
			}
			else
			{
				printf("ERROR: Uses a texture of unsupported type");
				return false;
			}
			dds->buffer = buffer;
			 // compressed pixel format not yet defined.
			dds->uncompressedFormat = uncompressedFormat; // pixel format uncompressed
			dds->components = components;
			dds->height = height;
			dds->width = width;
			if (ddsh->dwMipMapCount == 0) ddsh->dwMipMapCount++;
			dds->mips = ddsh->dwMipMapCount;

			Primitives::UInt32 Surfaces = 1;
			for (Primitives::Int16 surf = 0; surf < Surfaces; surf++)
			{
				//Every surfaces stores its own height and width data.
				width = dds->width;
				height = dds->height;
				for (Primitives::Int16 mip = 0; mip < dds->mips; mip++) 
				{
					dds->image[surf].pixels[mip] = buffer;
					buffer += width*height*components;
					width /= 2;
					height /= 2;
				}
			}

			return true;
		}

		bool loadDataFromHeaderInFile(const char* fileName, DDSHeader *ddsh) {
			return true;
		}
	};
};