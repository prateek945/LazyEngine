
#include "Win32Main.h"

//#include "../Physics/Colliders/Frustrum.h"
global_variable const CHAR CLASS_NAME[] = "LazyEngineClass";
//Input defines

global_variable win32_buffer_info BackBuffer;

internal_function void
RenderWeirdGradient(win32_buffer_info Buffer, int BlueOffset, int GreenOffset, int RedOffset)
{
	int Width = Buffer.BitmapWidth;
	int Height = Buffer.BitmapHeight;

	int Pitch = Width*Buffer.BytesPerPixel;
	UCHAR *Row = (UCHAR *)Buffer.BitMapMemory;
	for (int Y = 0;
		Y < Buffer.BitmapHeight;
		++Y)
	{
		LE::Primitives::UInt32 *Pixel = (LE::Primitives::UInt32 *)Row;
		for (int X = 0;
			X < Buffer.BitmapWidth;
			++X)
		{
			UCHAR Blue = sin(Y + BlueOffset) * 255;
			UCHAR Green = cos(X + GreenOffset) * 255 ;
			UCHAR Red = sin(X+RedOffset)*255;
			*Pixel++ = ((Red << 16)|(Green << 8) | Blue);
		}

		Row += Pitch;
	}
}
	internal_function void
	ResizeDIBSection(win32_buffer_info *Buffer,LE::Primitives::Int32 Width,
		LE::Primitives::Int32 Height) {
		
		if (Buffer->BitMapMemory) {
			VirtualFree(&Buffer->BitMapMemory, 0, MEM_RELEASE);
		}
		Buffer->BitmapWidth = Width;
		Buffer->BitmapHeight = Height;
		

		//BITMAPINFO bminfo = {};
		Buffer->bminfo.bmiHeader.biSize = sizeof(Buffer->bminfo.bmiHeader);
		Buffer->bminfo.bmiHeader.biPlanes = 1;
		Buffer->bminfo.bmiHeader.biWidth = Buffer->BitmapWidth;
		Buffer->bminfo.bmiHeader.biHeight = -(Buffer->BitmapHeight);
		Buffer->bminfo.bmiHeader.biBitCount = 32;
		Buffer->bminfo.bmiHeader.biCompression = BI_RGB;

	
		LE::Primitives::Int32 BitmapMemSize = (Buffer->BitmapWidth*Buffer->BitmapHeight)*Buffer->BytesPerPixel;
		Buffer->BitMapMemory = VirtualAlloc(0, BitmapMemSize, MEM_COMMIT, PAGE_READWRITE);
		
		
	}

	internal_function void
	Win32UpdateWindow(win32_buffer_info Buffer,HDC DeviceContext,RECT* ClientRect, LE::Primitives::Int32 X,
		LE::Primitives::Int32 Y, LE::Primitives::Int32 Width,
		LE::Primitives::Int32 Height) {
		int WindowHeight = ClientRect->bottom - ClientRect->top;
		int WindowWidth = ClientRect->right - ClientRect->left;
			StretchDIBits(DeviceContext, 0, 0, Buffer.BitmapWidth, Buffer.BitmapHeight,
				0, 0, WindowWidth, WindowHeight, Buffer.BitMapMemory, &Buffer.bminfo, DIB_RGB_COLORS, SRCCOPY);
	}
	LRESULT CALLBACK
		clientWindowProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{

		return 0;
	}
	int WINAPI
		WinMain(HINSTANCE Instance, HINSTANCE PrevInstance,
			PSTR commandLine, INT commandShow)
	{
		LE::MainWrapper();
		std::shared_ptr<LE::LevelLoader> levelLoader = std::shared_ptr<LE::LevelLoader>(new LE::LevelLoader("testLevel1.lvl"));
		levelLoader->loadLevelGameObjs();
		std::string windowName = "LazyEngine";
		std::shared_ptr<LE::MainWindow> winMain = std::shared_ptr<LE::MainWindow>(new LE::MainWindow(windowName,Instance));
		HRESULT hr = S_OK;
		std::string windowClassName = "LazyEngineClass";
		hr = winMain->CreateDesktopWindow(windowClassName);
		if (SUCCEEDED(hr)) {
			std::shared_ptr<LE::DeviceResources> deviceResources = std::shared_ptr<LE::DeviceResources>(new LE::DeviceResources());
			// Create device resources.
			deviceResources->CreateDeviceResources();

			// Instantiate the renderer.
			std::shared_ptr<LE::Renderer> renderer = std::shared_ptr<LE::Renderer>(new LE::Renderer(deviceResources));
			renderer->CreateDeviceDependentResources(levelLoader);

			// We have a window, so initialize window size-dependent resources.
			deviceResources->CreateWindowResources(winMain->getWindowHandle());
			renderer->CreateWindowSizeDependentResources();

			// Go full-screen.
			//deviceResources->GoFullScreen();

			// Whoops! We resized the "window" when we went full-screen. Better
			// tell the renderer.
			//renderer->CreateWindowSizeDependentResources();

			// Run the program.
			renderer->Update(levelLoader);
			hr = winMain->RUN(deviceResources, renderer,levelLoader);

		}
	
		return 0;
	}

