#pragma once

#include <stdint.h>

class KBInterface
{
public:
    KBInterface();

    int getRGBBrightness();
    void setRGBBrightness(const int brightness);
};
