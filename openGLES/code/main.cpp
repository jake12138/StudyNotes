#include <stdio.h>
#include "WaylandWindow.h"

int main(){
    printf("hello word\n");
    std::shared_ptr<WaylandWindow> window = WaylandWindow::getWindowSurface(400, 300);
    return 0;
}