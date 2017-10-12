#pragma once
#include "../Includes/LazyIncludes.h"
#include "../LazyFiling/FileHandler.h"
namespace LE {
	namespace DDS {
		struct DDS_PIXELFORMAT
		{
			uint32_t dwSize;
			uint32_t dwFlags;
			uint32_t dwFourCC;
			uint32_t dwRGBBitCount;
			uint32_t dwRBitMask;
			uint32_t dwGBitMask;
			uint32_t dwBBitMask;
			uint32_t dwABitMask;
		};
		struct DDSHeader {

			uint32_t           dwSize;
			uint32_t           dwFlags;
			uint32_t           dwHeight;
			uint32_t           dwWidth;
			uint32_t           dwPitchOrLinearSize;
			uint32_t           dwDepth;
			uint32_t           dwMipMapCount;
			uint32_t           dwReserved1[11];
			DDS_PIXELFORMAT ddspf;
			uint32_t           dwCaps;
			uint32_t           dwCaps2;
			uint32_t           dwCaps3;
			uint32_t           dwCaps4;
			uint32_t           dwReserved2;
		};
		typedef struct _DDS_IMAGE
		{
			unsigned char *pixels[DDSF_MAX_MIPMAPS];		//the mip map images 
		}_DDS_IMAGE;

		struct DDSTextureInSystemMemory
		{
			unsigned char		*buffer;	//pointer to loaded dds file
			uint32_t			compressedFormat; // format of compressed texels, 0 if not compressed (in which case use format)
			uint32_t			uncompressedFormat;	//format of the texels if not compressed, 0 if compressed
			uint32_t			components; //number of channels 
			uint32_t			width;		//width of base image in pixels
			uint32_t			height;		//height of based image in pixels
			uint32_t			mips;		//number of mip levels
			uint32_t			surfaces;	//number of surfaces ( 1 = a texture 6 = a cube map)

			_DDS_IMAGE image[6];
		};


		bool loadDDSFromFile(const char* fileName, DDSTextureInSystemMemory *dds);
		bool loadDataFromHeaderInFile(const char* fileName, DDSHeader *ddsh);
	};
};