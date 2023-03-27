#include "WindowSurface.h"

std::shared_ptr<WindowSurface>  WindowSurface::mWindowSurface = nullptr;

std::shared_ptr<WindowSurface> WindowSurface::getWindowSurface(uint width, uint hight){
    if(mWindowSurface == nullptr){
        mWindowSurface = std::make_shared<WindowSurface>();
        mWindowSurface->mWidth = width;
        mWindowSurface->mHight = hight;
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

WindowSurface::WindowSurface(){}

WindowSurface::~WindowSurface()
{
    mWindowSurface = nullptr;
}

bool WindowSurface::initWayland(){
    return true;
}

bool WindowSurface::initEGL(){
    return true;
}