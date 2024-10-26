#pragma once

#include <hidapi/hidapi.h>

class KBInterface
{
public:
    KBInterface(hid_device *handle);

    int getRGBBrightness();
    void setRGBBrightness(const int brightness);

private:

    int sendMessage(const unsigned char messageId, const unsigned char* msg, const int msgLen, unsigned char* outBuf, const int outLen);

    int setRGBU8(const unsigned char key, const unsigned char value);
    int getRGBU8(const unsigned char key);

    hid_device *handle;
};
