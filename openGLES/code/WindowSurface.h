#ifndef WINDOW_SURFACE
#define WINDOW_SURFACE

#include <wayland-client.h>
#include <wayland-server.h>
#include <wayland-cursor.h>
#include <wayland-egl.h>
#include <EGL/egl.h>
#include <EGL/eglplatform.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2platform.h>
#include <memory>

#define LOGI printf
#define LOGE printf
#define LOGD printf

/*流程：
	1.通过wayland创建EGL所需的EGLNativeWindowType--initWayland
	2.构建EGL---initEGL
*/

class WindowSurface
{
private:
    // wayland窗口
    struct wl_display* mWlDisplay = nullptr;
    struct wl_registry* mWlRegistry = nullptr;
    struct wl_compositor* mWlCompositor = nullptr;
    struct wl_shell* mWlShell = nullptr;
    struct wl_surface* mWlSurface = nullptr;
    struct wl_shell_surface* mWlShellSurface = nullptr;
    struct wl_egl_window* mEGLWindow;

    uint mWidth = 0; // 窗口的宽
    uint mHigh = 0; // 窗口的高
    static std::shared_ptr<WindowSurface> mWindowSurface;
public:
    static std::shared_ptr<WindowSurface> getWindowSurface(uint windowWidth = 100, uint windowHigh=100);
    WindowSurface();
    ~WindowSurface();
    void globalHandle(void *data,
                      struct wl_registry *wl_registry,
                      uint32_t name,
                      const char *interface,
                      uint32_t version);
    void globalRemoveHandle(void *data,
                            struct wl_registry *wl_registry,
                            uint32_t name);
private:
    bool initEGL();
    bool initWayland();
};

#endif