#pragma once
#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include "Renderer.h"


namespace LE {
	class MainWindow {
		std::string m_windowname;
		HWND m_WHND;
		RECT m_rc;
		HINSTANCE m_Instance;
	public:
		MainWindow();
		MainWindow(std::string, HINSTANCE);
		~MainWindow() {};

		HWND getWindowHandle() const { return m_WHND; }
		RECT getWindowRect() const { return m_rc; }
		std::string getWindowName() const { return m_windowname; }

		HRESULT CreateDesktopWindow(std::string);
		static LRESULT CALLBACK StaticWindowProc(
			HWND hWnd,
			UINT uMsg,
			WPARAM wParam,
			LPARAM lParam
		);
		HRESULT RUN(std::shared_ptr<DeviceResources>,std::shared_ptr<Renderer>,std::shared_ptr<LevelLoader>);
	};
};

#endif
