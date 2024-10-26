#pragma once

#include "KBInterface.h"

class KBManager
{
public:
    KBManager(KBInterface *intf);
    ~KBManager();

    void goWakeup();
    void goIdle();

    int onBrightness;

private:
    int targetBrightness;
    int currentBrightness;

    KBInterface *intf;
};
