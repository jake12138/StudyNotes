cmake_minimum_required(VERSION 3.10)
project(code)

set(CMAKE_CXX_STANDARD 14)

add_executable(code main.cpp WaylandWindow.cpp)

target_link_libraries(code
        wayland-server
        wayland-client
        wayland-cursor
        wayland-egl
        EGL
        GLESv2)