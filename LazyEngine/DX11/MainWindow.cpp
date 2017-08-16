#include "MainWindow.h"
#include "../LazyLogger/LogManager.h"

namespace LE {
	MainWindow::MainWindow() : m_windowname("LAZYENGINE"), m_WHND(NULL), m_Instance((HINSTANCE)GetModuleHandleA(NULL)) {}
	MainWindow::MainWindow(std::string windowName, HINSTANCE instance) : m_windowname(windowName), m_WHND(NULL), m_Instance(instance) {}

	HRESULT MainWindow::CreateDesktopWindow(std::string m_windowClassName) {



		HICON hIcon = NULL;
		CHAR szExePath[MAX_PATH];
		GetModuleFileName(NULL, szExePath, MAX_PATH);

		// If the icon is NULL, then use the first one found in the exe
		

		// Register the windows class
		WNDCLASS wndClass;
		wndClass.style = CS_HREDRAW;
		wndClass.lpfnWndProc = MainWindow::StaticWindowProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = m_Instance;
		wndClass.hIcon = NULL;
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = m_windowClassName.c_str();

		if (!RegisterClass(&wndClass))
		{
			DWORD dwError = GetLastError();
			if (dwError != ERROR_CLASS_ALREADY_EXISTS)
				return HRESULT_FROM_WIN32(dwError);
		}


		int x = CW_USEDEFAULT;
		int y = CW_USEDEFAULT;

		// No menu in this example.

		// This example uses a non-resizable 640 by 480 viewport for simplicity.
		int nDefaultWidth = 640;
		int nDefaultHeight = 480;
		SetRect(&m_rc, 0, 0, nDefaultWidth, nDefaultHeight);

		//SetRect(&m_rc, 0, 0, nDefaultWidth, nDefaultHeight);
		AdjustWindowRect(
			&m_rc,
			WS_OVERLAPPEDWINDOW,
			false
		);

		// Create the window for our viewport.
		m_WHND = CreateWindowExA(0, wndClass.lpszClassName, m_windowname.c_str(), WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, m_Instance, 0);
		LAZYASSERT(m_WHND, "Window Creation Failed!")
			if (m_WHND == NULL)
			{
				DWORD dwError = GetLastError();
				return HRESULT_FROM_WIN32(dwError);
			}

		return S_OK;

	}

	LRESULT CALLBACK MainWindow::StaticWindowProc(
		HWND hWnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam) {

		switch (uMsg) {

		case WM_CLOSE: {
			OutputDebugStringA("WM_CLOSE\n");
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
		case WM_KEYDOWN: {
			switch (wParam) {
			case VK_LEFT: {
				int prevFrame = !(g_frameCount % 2);
				PhysicsManager::getInstance()->get()->objects[prevFrame].at(0)->metaData.Velocity.m_x =-1.0f;
				}break;
			case VK_RIGHT: {
				int prevFrame = !(g_frameCount % 2);
				PhysicsManager::getInstance()->get()->objects[prevFrame].at(0)->metaData.Velocity.m_x =1.0f;
				}break;
			case 'P': {
				g_runPhysics = true;
				}break;
			}
		}break;
		case WM_KEYUP: {
			switch (wParam) {
			case VK_LEFT: {
				int prevFrame = !(g_frameCount % 2);
				PhysicsManager::getInstance()->get()->objects[prevFrame].at(0)->metaData.Velocity.m_x = 0.0f;
				}break;
			case VK_RIGHT: {
				int prevFrame = !(g_frameCount % 2);
				PhysicsManager::getInstance()->get()->objects[prevFrame].at(0)->metaData.Velocity.m_x = 0.0f;
				}break;
			case 'P': {
				g_runPhysics = false;
				}break;
			}
		}break;
		default: {
			return DefWindowProcA(hWnd, uMsg, wParam, lParam);
		}break;
		}
		return 0;

	}

	HRESULT MainWindow::RUN(std::shared_ptr<DeviceResources> deviceResources, std::shared_ptr<Renderer> renderer,
		std::shared_ptr<LevelLoader> levelLoader) {
		MSG msg;
		LE::Primitives::Bool Running = true;
		LE::Primitives::Int32 Xoffset = 0, Yoffset = 0;
		while (Running)
		{
			if(g_runPhysics)
				g_frameCount++;
			while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
				
				if (msg.message == WM_QUIT) {
					Running = false;
					TranslateMessage(&msg);
					DispatchMessageA(&msg);
					
					DestroyWindow(getWindowHandle());
				}
				
				
			}
			renderer->Update(levelLoader);
			renderer->Render(levelLoader);
			deviceResources->Present();

		}
		return S_OK;
	}
};





//ShowWindow(clientWindowHandle, SW_SHOWMINIMIZED);