#pragma once

#include <hidapi/hidapi.h>

class KBInterface
{
public:
    KBInterface(hid_device *handle);
    ~KBInterface();

    int getRGBBrightness();
    void setRGBBrightness(const int brightness);

    void goWakeup();
    void goIdle();

private:
    int onBrightness;
    void loadOnBrightness();

    int sendMessage(const unsigned char messageId, const unsigned char* msg, const int msgLen, unsigned char* outBuf, const int outLen);

    int setRGBU8(const unsigned char key, const unsigned char value);
    int getRGBU8(const unsigned char key);

    hid_device *handle;
};
