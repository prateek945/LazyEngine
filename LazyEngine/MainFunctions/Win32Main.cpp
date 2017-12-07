
#include "Win32Main.h"
//#include "../Physics/Colliders/Frustrum.h"
global_variable const CHAR CLASS_NAME[] = "LazyEngineClass";
//Input defines

global_variable win32_buffer_info BackBuffer;

	int WINAPI
		WinMain(HINSTANCE Instance, HINSTANCE PrevInstance,
			PSTR commandLine, INT commandShow)
	{
		LE::MainWrapper();
		
		std::shared_ptr<LE::LevelLoader> levelLoader = std::shared_ptr<LE::LevelLoader>(new LE::LevelLoader("testLevelImrod.lvl"));
		
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
			LE::TextureManager* gTextureManager = LE::TextureManager::getInstance();
			gTextureManager->startUp(deviceResources->GetDevice(), deviceResources->GetDeviceContext());

			levelLoader->loadLevelGameObjs(deviceResources->GetDevice(), deviceResources->GetDeviceContext());
			
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

