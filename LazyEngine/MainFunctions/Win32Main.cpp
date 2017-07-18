
#include "Win32Main.h"
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

		switch (Message) {
		case WM_SIZE: {
			RECT clientRect;
			GetClientRect(hwnd, &clientRect);
			LE::Primitives::Int32 Width, Height;
			Width = clientRect.right - clientRect.left;
			Height = clientRect.bottom - clientRect.top;
			int WindowWidth = Width;
			int WindowHeight = Height;
			ResizeDIBSection(&BackBuffer,Width,Height);
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
			
			Win32UpdateWindow(BackBuffer,DeviceContext,&ClientRect, X, Y, Width, Height);
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
			RenderWeirdGradient(BackBuffer,Xoffset,Yoffset,Xoffset);
			Xoffset++; Yoffset++;
			HDC DeviceContext = GetDC(clientWindowHandle);
			RECT ClientRect;
			GetClientRect(clientWindowHandle, &ClientRect);
			 int WindowWidth = ClientRect.right - ClientRect.left;
			 int WindowHeight = ClientRect.bottom - ClientRect.top;
			Win32UpdateWindow(BackBuffer,DeviceContext,&ClientRect, 0, 0, WindowWidth, WindowHeight);
			ReleaseDC(clientWindowHandle, DeviceContext);
		
		}

		return 0;
	}

