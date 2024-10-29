#pragma once

#include "OpenRGB/Client.hpp"

#include <stdint.h>

class KBInterface
{
public:
    KBInterface();

    int getRGBBrightness();
    void setRGBBrightness(const int brightness);
    void prepareStandby();
    void handleWakeup();

private:
    int ensureClient();
    orgb::Client client;

    orgb::DeviceList list;
    const orgb::Device* device;

    void configureDevice();
};
