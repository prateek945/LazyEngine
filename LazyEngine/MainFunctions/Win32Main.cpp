
#include "Win32Main.h"
global_variable const CHAR CLASS_NAME[] = "LazyEngineClass";

global_variable BITMAPINFO bminfo;
global_variable void *BitMapMemory;
global_variable LE::Primitives::Int32 BitmapWidth;
global_variable LE::Primitives::Int32 BitmapHeight;

global_variable LE::Primitives::Int32 BytesPerPixel = 4;

internal_function void
RenderWeirdGradient(int BlueOffset, int GreenOffset)
{
	int Width = BitmapWidth;
	int Height = BitmapHeight;

	int Pitch = Width*BytesPerPixel;
	UCHAR *Row = (UCHAR *)BitMapMemory;
	for (int Y = 0;
		Y < BitmapHeight;
		++Y)
	{
		LE::Primitives::UInt32 *Pixel = (LE::Primitives::UInt32 *)Row;
		for (int X = 0;
			X < BitmapWidth;
			++X)
		{
			UCHAR Blue = (X + BlueOffset);
			UCHAR Green = (Y + GreenOffset);

			*Pixel++ = ((Green << 8) | Blue);
		}

		Row += Pitch;
	}
}
	internal_function void
	ResizeDIBSection(LE::Primitives::Int32 Width,
		LE::Primitives::Int32 Height) {
		
		if (BitMapMemory) {
			VirtualFree(&BitMapMemory, 0, MEM_RELEASE);
		}
		BitmapWidth = Width;
		BitmapHeight = Height;
		

		//BITMAPINFO bminfo = {};
		bminfo.bmiHeader.biSize = sizeof(bminfo.bmiHeader);
		bminfo.bmiHeader.biPlanes = 1;
		bminfo.bmiHeader.biWidth = BitmapWidth;
		bminfo.bmiHeader.biHeight = -BitmapHeight;
		bminfo.bmiHeader.biBitCount = 32;
		bminfo.bmiHeader.biCompression = BI_RGB;

	
		LE::Primitives::Int32 BitmapMemSize = (BitmapWidth*BitmapHeight)*BytesPerPixel;
		BitMapMemory = VirtualAlloc(0, BitmapMemSize, MEM_COMMIT, PAGE_READWRITE);
		
		
	}

	internal_function void
	Win32UpdateWindow(HDC DeviceContext,RECT* ClientRect, LE::Primitives::Int32 X,
		LE::Primitives::Int32 Y, LE::Primitives::Int32 Width,
		LE::Primitives::Int32 Height) {
		int WindowHeight = ClientRect->bottom - ClientRect->top;
		int WindowWidth = ClientRect->right - ClientRect->left;
			StretchDIBits(DeviceContext, 0, 0, BitmapWidth, BitmapHeight,
				0, 0, WindowWidth, WindowHeight, BitMapMemory, &bminfo, DIB_RGB_COLORS, SRCCOPY);
	}
	LRESULT CALLBACK
		clientWindowProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{

		switch (Message) {
		case WM_SIZE: {
			RECT clientRect;
			GetClientRect(hwnd, &clientRect);
			LE::Primitives::Int32 Width, Height;
			Width = clientRect.right - clientRect.left;
			Height = clientRect.bottom - clientRect.top;
			int WindowWidth = Width;
			int WindowHeight = Height;
			ResizeDIBSection(Width,Height);
			return 0;
		}break;

		case WM_PAINT: {
			
			PAINTSTRUCT Paint;
			HDC DeviceContext = BeginPaint(hwnd, &Paint);
			int X = Paint.rcPaint.left;
			int Y = Paint.rcPaint.top;
			int Width = Paint.rcPaint.right - Paint.rcPaint.left;
			int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
			bool erase = Paint.fErase;
			RECT ClientRect;
			GetClientRect(hwnd, &ClientRect);
			
			Win32UpdateWindow(DeviceContext,&ClientRect, X, Y, Width, Height);
			EndPaint(hwnd, &Paint);
			
		}break;

		case WM_CLOSE: {
			PostQuitMessage(0);
			return 0;
		}break;
		case WM_ACTIVATEAPP:
		{
			OutputDebugStringA("WM_ACTIVATEAPP\n");
		} break;

		case WM_DESTROY: {
			PostQuitMessage(0);
			return 0;
		}break;

		default: {
			return DefWindowProcA(hwnd, Message, wParam, lParam);
		}break;
		}
		return 0;
	}
	int WINAPI
		WinMain(HINSTANCE Instance, HINSTANCE PrevInstance,
			PSTR commandLine, INT commandShow)
	{
		LE::MainWrapper();
		WNDCLASS clientWindowClass = {};
		clientWindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		clientWindowClass.hbrBackground = NULL;
		clientWindowClass.lpfnWndProc = clientWindowProc;
		clientWindowClass.hInstance = Instance;
		clientWindowClass.lpszClassName = "LazyEngineClass";



		LAZYASSERT(RegisterClass(&clientWindowClass),"Class Registration Failed");
		HWND clientWindowHandle = CreateWindowEx(0, clientWindowClass.lpszClassName,"LAZY ENGINE",WS_OVERLAPPEDWINDOW|WS_VISIBLE,
			CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,0,0,Instance,0);
		LAZYASSERT(clientWindowHandle,"Create Window Failed.") 
		//ShowWindow(clientWindowHandle, SW_SHOWMINIMIZED);
		MSG msg;
		LE::Primitives::Bool Running = true;
		LE::Primitives::Int32 Xoffset = 0, Yoffset = 0;
		while (Running)
		{
			while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{

				if (msg.message == WM_QUIT) Running = false;
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
			RenderWeirdGradient(Xoffset,Yoffset);
			Xoffset++; Yoffset++;
			HDC DeviceContext = GetDC(clientWindowHandle);
			RECT ClientRect;
			GetClientRect(clientWindowHandle, &ClientRect);
			 int WindowWidth = ClientRect.right - ClientRect.left;
			 int WindowHeight = ClientRect.bottom - ClientRect.top;
			Win32UpdateWindow(DeviceContext,&ClientRect, 0, 0, WindowWidth, WindowHeight);
			ReleaseDC(clientWindowHandle, DeviceContext);
		
		}

		return 0;
	}

