#include <stdio.h>
#include "WindowSurface.h"

int main(){
    printf("hello word\n");
    std::shared_ptr<WindowSurface> window = WindowSurface::getWindowSurface(400, 300);
    return 0;
}