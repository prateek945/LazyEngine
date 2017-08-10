#pragma once
#ifndef WIN32MAIN_H_
#define WIN32MAIN_H_

#include "Main.h"
#include "../DX11/MainWindow.h"
#include <Xinput.h>
struct win32_buffer_info {
	BITMAPINFO bminfo;
	void *BitMapMemory;
	LE::Primitives::Int32 BitmapWidth;
	LE::Primitives::Int32 BitmapHeight;
	LE::Primitives::Int32 BytesPerPixel = 4;
};
#endif
