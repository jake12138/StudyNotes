#include "WaylandWindow.h"
#include <string.h>

/*回调函数，回调wl_registry嗅探到的所有可用组件*/
static void wl_global_cb(void *data, struct wl_registry *wl_registry, uint32_t name, const char *interface,
                         uint32_t version) {
    std::shared_ptr<WaylandWindow> window = WaylandWindow::getWindowSurface();
    window->globalHandle(data, wl_registry, name, interface, version);
}

static void wl_global_remove_cb(void *data, struct wl_registry *wl_registry, uint32_t name) {
    std::shared_ptr<WaylandWindow> window = WaylandWindow::getWindowSurface();
    window->globalRemoveHandle(data,wl_registry, name);
}

std::shared_ptr<WaylandWindow>  WaylandWindow::mWindowSurface = nullptr;

/*1.获取WindowSurface单例，第一次调用需要传入窗口的长宽，后续则不用.
 *2.如果第一次没有传入窗口的宽和高，默认使用100x100
 *3.获取失败返回nullptr*/
std::shared_ptr<WaylandWindow> WaylandWindow::getWindowSurface(uint width, uint high){
    if(mWindowSurface == nullptr){
        mWindowSurface = std::make_shared<WaylandWindow>();
        mWindowSurface->mWidth = width;
        mWindowSurface->mHigh = high;
        if(!mWindowSurface->initWayland()){
            LOGE("init wayland failed\n");
            mWindowSurface = nullptr;
            return nullptr;
        }
        if(!mWindowSurface->initEGL()){
            LOGE("init EGL failed\n");
            mWindowSurface = nullptr;
            return nullptr;
        }
    }
    return mWindowSurface;
}

WaylandWindow::WaylandWindow(){}

WaylandWindow::~WaylandWindow()
{
    mWindowSurface = nullptr;
}

bool WaylandWindow::initWayland(){
    // 获取wayland客户端,采用默认的"wayland-0"
    mWlDisplay = wl_display_connect(nullptr);

    /*申请创建registry，得到代理对象wl_registry。这个对象相当
     * 于Client在Server端放的一个用于嗅探资源的Observer。
     * Client通过它得到Server端有哪些Global对象的信息。*/
    mWlRegistry = wl_display_get_registry(mWlDisplay);

    // 注册监听函数
    struct wl_registry_listener listener{
            .global = wl_global_cb,
            .global_remove = wl_global_remove_cb,
    };
    wl_registry_add_listener(mWlRegistry, &listener, nullptr);

    wl_display_dispatch(mWlDisplay);
    wl_display_roundtrip(mWlDisplay);//在这里等待监听函数的执行完毕

    if(mWlCompositor== nullptr || mWlShell== nullptr){
        //如果获取compositor和shell失败，释放已持有资源
        LOGE("init wayland: can't get Compositor or Shell");
        wl_registry_destroy(mWlRegistry);
        wl_display_destroy(mWlDisplay);
        return false;
    }

    mWlSurface = wl_compositor_create_surface(mWlCompositor);
    if(!mWlSurface){
        LOGE("get wayland surface failed.");
        wl_shell_destroy(mWlShell);
        wl_compositor_destroy(mWlCompositor);
        wl_registry_destroy(mWlRegistry);
        wl_display_destroy(mWlDisplay);
        return false;
    }

    mWlShellSurface = wl_shell_get_shell_surface(mWlShell, mWlSurface);
    if(mWlShellSurface){
        wl_shell_surface_set_title(mWlShellSurface,"wayland_surface");
        wl_shell_surface_set_toplevel(mWlShellSurface);
    }else{
        LOGE("gel ShellSurface failed.");
    }

    mEGLWindow = wl_egl_window_create(mWlSurface, mWidth, mHigh);
    if(!mEGLWindow){
        LOGE("get egl window failed");
        wl_surface_destroy(mWlSurface);
        wl_shell_destroy(mWlShell);
        wl_compositor_destroy(mWlCompositor);
        wl_registry_destroy(mWlRegistry);
        wl_display_destroy(mWlDisplay);
        return false;
    }
    LOGI("wayland client init ok!\n");
    return true;
}

bool WaylandWindow::initEGL(){
    //todo
    mEGLDisplay = eglGetDisplay((EGLNativeDisplayType)mWlDisplay);
    if(mEGLDisplay == EGL_NO_DISPLAY){
        LOGE("get EGLDisplay failed: %d",eglGetError());
        return false;
    }

    // 获取EGL的版本
    EGLint eglVersion[2]={0};
    if(eglInitialize(mEGLDisplay, &eglVersion[0], &eglVersion[1])){
        LOGI("get EGL version: %d.%d\n",eglVersion[0],eglVersion[1]);
    }else{
        LOGE("EGL initialize failed:%d\n",eglGetError());
        return false;
    }

    // EGL config
    const EGLint egl_display_config_required[]={
            EGL_RED_SIZE,8,
            EGL_GREEN_SIZE,8,
            EGL_BLUE_SIZE,8,
            EGL_DEPTH_SIZE,8,
            EGL_STENCIL_SIZE,8,
            EGL_RENDERABLE_TYPE,EGL_OPENGL_ES2_BIT,
            EGL_NONE
    };
    EGLint num_config;
    EGLConfig* eglDisplayConfig = nullptr;
    eglGetConfigs(mEGLDisplay, nullptr, 0, &num_config);
    LOGD("EGL: get egl config num_config=%d\n",num_config);
    if((eglDisplayConfig = (EGLConfig*)calloc(num_config, sizeof(EGLConfig))) == nullptr){
        LOGE("calloc eglDisplayConfig failed\n");
        return false;
    }
    if(!eglChooseConfig(mEGLDisplay, egl_display_config_required, eglDisplayConfig,num_config, &num_config)){
        LOGE("EGL: eglChooseConfig failed with err: %d\n",eglGetError());
        free(eglDisplayConfig);
        return false;
    }
    EGLint context_config_required[]={
            EGL_CONTEXT_CLIENT_VERSION,2,
            EGL_NONE
    };
    mEGLContext = eglCreateContext(mEGLDisplay, *eglDisplayConfig, EGL_NO_CONTEXT, context_config_required);
    if(mEGLContext == EGL_NO_CONTEXT){
        LOGE("EGL: eglCreateContext failed with err: %d\n",eglGetError());
        free(eglDisplayConfig);
        return false;
    }

    mEGLSurface = eglCreateWindowSurface(mEGLDisplay, *eglDisplayConfig, (EGLNativeWindowType)mEGLWindow, nullptr);
    free(eglDisplayConfig);
    if(mEGLSurface == EGL_NO_SURFACE){
        LOGE("EGL:eglCreateWindowSurface failed with err: 0x%x\n",eglGetError());
        return false;
    }
    LOGD("EGL: egl init success!\n");
    return true;
}

void WaylandWindow::globalHandle(void *data, struct wl_registry *wl_registry, uint32_t name, const char *interface,
                                 uint32_t version) {
    //todo
    if(!strncmp(interface,"wl_compositor",sizeof("wl_compositor"))){
        mWlCompositor = (struct wl_compositor*)wl_registry_bind(mWlRegistry, name, &wl_compositor_interface, version);
    }else if(!strncmp(interface,"wl_shell",sizeof("wl_shell"))){
        mWlShell = (struct wl_shell*)wl_registry_bind(mWlRegistry,name,&wl_shell_interface,version);
    }
}

void WaylandWindow::globalRemoveHandle(void *data, struct wl_registry *wl_registry, uint32_t name) {
    //todo
}