#include "MainWindow.h"
#include "../LazyLogger/LogManager.h"

namespace LE {
	Handle *MainWindow::m_hMainCamera = 0;
	MainWindow::MainWindow() : m_windowname("LAZYENGINE"), m_WHND(NULL), m_Instance((HINSTANCE)GetModuleHandleA(NULL)) { m_hMainCamera = 0; }
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

		
		int nDefaultWidth = 640;
		int nDefaultHeight = 480;
		SetRect(&m_rc, 0, 0, nDefaultWidth, nDefaultHeight);

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

		UINT con = WM_KEYDOWN;
		switch (uMsg) {

		case WM_CLOSE: {
			OutputDebugStringA("WM_CLOSE\n");
			PostQuitMessage(0);
			return 0;
		}break;
		case WM_ACTIVATEAPP:
		{
			DirectX::Keyboard::ProcessMessage(uMsg, wParam, lParam);
			DirectX::Mouse::ProcessMessage(uMsg, wParam, lParam);
			OutputDebugStringA("WM_ACTIVATEAPP\n");
		} break;

		case WM_DESTROY: {
			PostQuitMessage(0);
			return 0;
		}break;
		case WM_KEYDOWN:
			DirectX::Keyboard::ProcessMessage(uMsg, wParam, lParam);
			break;
		case WM_KEYUP:
			DirectX::Keyboard::ProcessMessage(uMsg, wParam, lParam);
			break;
		case WM_SYSKEYUP:
			DirectX::Keyboard::ProcessMessage(uMsg, wParam, lParam);
			break;
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
		m_hMainCamera = (renderer->m_hMainCamera);
		while (Running)
		{
			//Press and hold 'P' in order to run physics simulations (Only good for debugging can be removed later).
			
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