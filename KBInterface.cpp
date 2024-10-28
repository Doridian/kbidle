#include "KBInterface.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

KBInterface::KBInterface() {
}

int KBInterface::getRGBBrightness() {
    return 255;
}

void KBInterface::setRGBBrightness(const int brightness) {
    if (brightness < 0) {
        return;
    }

     if (brightness == 255) {
        system("openrgb -p Default");
     } else if (brightness == 0) {
        system("openrgb -p Off");
     }
}
