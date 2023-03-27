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

class WindowSurface
{
private:
    // wayland窗口
    struct wl_display* mWlDisplay = nullptr;
    struct wl_registry* mWlRegistry = nullptr;

    uint mWidth = 0; // 窗口的宽
    uint mHight = 0; // 窗口的高

public:
    static std::shared_ptr<WindowSurface> mWindowSurface;
    static std::shared_ptr<WindowSurface> getWindowSurface(uint windowWidth, uint windowHight);
    WindowSurface();
    ~WindowSurface();
private:
    bool initEGL();
    bool initWayland();
};




#endif