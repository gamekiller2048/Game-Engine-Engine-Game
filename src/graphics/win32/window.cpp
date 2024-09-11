#include <graphics/win32/window.hpp>
#include <Windows.h>
#include <graphics/win32/glcontext.hpp>
#include "windowimpl.hpp"
#include "errorcheck.hpp"
#include "devicecontextimpl.hpp"

namespace mgl
{
	namespace win32
	{
		static std::string CLASS_NAME;

		static LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			Window* window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if(!window)
				return DefWindowProcA(hWnd, uMsg, wParam, lParam);

			switch(uMsg)
			{
			case WM_DESTROY:
				break;
			case WM_CLOSE:
				window->destroy();
				break;
			default:
				return DefWindowProcA((HWND)hWnd, uMsg, wParam, lParam);
			}

			return 0;
		}

		Window::Window(const std::string& title, uint width, uint height, RenderApi api) :
			mgl::Window(title, width, height, api), impl(CreateOwned<WindowImpl>())
		{
			HINSTANCE hInstance = WIN_CALLV(GetModuleHandle, NULL);

			if(CLASS_NAME.empty()) {
				CLASS_NAME = "MGL_WINDOW";

				WNDCLASSA wc = {};
				wc.lpfnWndProc = (WNDPROC)WindowProc;
				wc.hInstance = hInstance;

				// CS_OWNDC creates a private DC in memory for this window
				// DC is released automatically with the window and GetDC retrieves the same DC each time
				if(api == RenderApi::OPENGL)
					wc.style = CS_OWNDC;
					
				wc.lpszClassName = CLASS_NAME.c_str();
				WIN_CALLV(RegisterClassA, &wc);
			}

			impl->hWnd = WIN_CALLV(CreateWindowExA,
				0,                               // Optional window styles.
				CLASS_NAME.c_str(),
				title.c_str(),
				WS_OVERLAPPEDWINDOW,             // Window style

				// position and size 
				CW_USEDEFAULT, CW_USEDEFAULT, width, height,

				NULL,        // Parent window    
				NULL,        // Menu
				hInstance,   // Instance handle
				this
			);

			// TODO: this function returns 0 so make fix to wrap with WIN_CALL*
			SetWindowLongPtr(impl->hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

			if(api == RenderApi::OPENGL) {
				HDC hDC = WIN_CALLV(GetDC, impl->hWnd);
				PIXELFORMATDESCRIPTOR pfd = {};
				pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
				pfd.nVersion = 1;
				pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
				pfd.iPixelType = PFD_TYPE_RGBA;
				pfd.cColorBits = 32;
				pfd.cDepthBits = 24;
				pfd.cStencilBits = 8;
				int pixelFormat = WIN_CALLV(ChoosePixelFormat, hDC, &pfd);
				WIN_CALLV(SetPixelFormat, hDC, pixelFormat, &pfd);
			}

			show();
		}

		Window::~Window()
		{
			if(!destroyed)
				destroy();
		}

		WindowImpl* Window::getImpl() const
		{
			return impl.get();
		}

		void Window::destroy()
		{
			MLL_DEBUG(mll::Info("", "Destroying Window"));
			WIN_CALLV(DestroyWindow, impl->hWnd);
			destroyed = true;
		}

		void Window::show()
		{
			WIN_CALL(ShowWindow, impl->hWnd, SW_SHOW);
		}

		void Window::hide()
		{
			WIN_CALL(ShowWindow, impl->hWnd, SW_HIDE);
		}

		void Window::setTitle(const std::string& title)
		{
			this->title = title;
			WIN_CALLV(SetWindowTextA, impl->hWnd, title.c_str());
		}

		void Window::setX(int x)
		{
			this->pos.x = x;
			WIN_CALLV(MoveWindow, impl->hWnd, pos.x, pos.y, size.x, size.y, true);
		}

		void Window::setY(int y)
		{
			this->pos.y = y;
			WIN_CALLV(MoveWindow, impl->hWnd, pos.x, pos.y, size.x, size.y, true);
		}

		void Window::setPos(const mml::ivec2& pos)
		{
			this->pos = pos;
			WIN_CALLV(MoveWindow, impl->hWnd, pos.x, pos.y, size.x, size.y, true);
		}

		void Window::setWidth(uint width)
		{
			this->size.x = width;
			WIN_CALLV(MoveWindow, impl->hWnd, pos.x, pos.y, size.x, size.y, true);
		}

		void Window::setHeight(uint height)
		{
			this->size.y = height;
			WIN_CALLV(MoveWindow, impl->hWnd, pos.x, pos.y, size.x, size.y, true);
		}

		void Window::setSize(const mml::uvec2& size)
		{
			this->size = size;
			WIN_CALLV(MoveWindow, impl->hWnd, pos.x, pos.y, size.x, size.y, true);
		}
	}
}