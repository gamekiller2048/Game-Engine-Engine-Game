#include <graphics/win32/app.hpp>
#include <Windows.h>
#include <glad/gl.h>
#include "errorcheck.hpp"

namespace mgl
{
	namespace win32
	{
        App::App(RenderApi api) :
            mgl::App(api) {}

		void App::run()
		{
            bool running = true;
            MSG msg;

            while(running) {
                // TODO: window that is deleted still has unprocessed msgs (Invalid Window Handle)
                if(WIN_CALLR(PeekMessage, &msg, NULL, 0, 0, PM_REMOVE)) {
                    if(msg.message == WM_QUIT) {
                        running = false;
                        break;
                    }

                    WIN_CALL(TranslateMessage, &msg);
                    WIN_CALL(DispatchMessage, &msg);
                }
                else {
                    if(!windows.size())
                        break;

                    for(auto it = windows.begin(); it != windows.end();) {
                        Ref<Window> window = (*it);

                        if(window->isDestroyed()) {
                            it = windows.erase(it);
                            continue;
                        }

                        window->getContext()->useWindow(window.get());
                        window->getContext()->makeCurrent();
                        window->getScene()->update();
                        window->getContext()->swapBuffers();

                        it++;
                    }
                }
            }
		}

        void App::destroy()
        {
            WIN_CALL(PostQuitMessage, 0);
        }
	}
}