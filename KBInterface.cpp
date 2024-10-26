#include "KBInterface.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RAW_HID_BUFFER_SIZE 32

#define CHANNEL_BACKLIGHT 1
#define CHANNEL_RGB_LIGHT 2
#define CHANNEL_RGB_MATRIX 3

#define BACKLIGHT_VALUE_BRIGHTNESS 1
#define BACKLIGHT_VALUE_EFFECT 2

#define RGB_MATRIX_VALUE_BRIGHTNESS 1
#define RGB_MATRIX_VALUE_EFFECT 2
#define RGB_MATRIX_VALUE_EFFECT_SPEED 3
#define RGB_MATRIX_VALUE_COLOR 4

#define CUSTOM_SET_VALUE 0x07
#define CUSTOM_GET_VALUE 0x08

KBInterface::KBInterface(hid_device* handle) {
    this->handle = handle;
}

int KBInterface::getRGBBrightness() {
    return this->getRGBU8(RGB_MATRIX_VALUE_BRIGHTNESS);
}

void KBInterface::setRGBBrightness(const int brightness) {
    if (brightness < 0) {
        return;
    }

    this->setRGBU8(RGB_MATRIX_VALUE_BRIGHTNESS, brightness);
}

int KBInterface::getRGBU8(const unsigned char key) {
    unsigned char msg[] = { CHANNEL_RGB_MATRIX, key };
    unsigned char data[4] = { };
    int res = this->sendMessage(CUSTOM_GET_VALUE, msg, sizeof(msg), data, sizeof(data));
    if (res < 4) {
        printf("Error on getRGBU8(%d): %ls\n", res, hid_error(this->handle));
        return -1;
    }
    if (data[0] == 0xFF) {
        return -1;
    }
    return data[3];
}

int KBInterface::setRGBU8(const unsigned char key, const unsigned char value) {
    unsigned char msg[] = { CHANNEL_RGB_MATRIX, key, value };
    return this->sendMessage(CUSTOM_SET_VALUE, msg, sizeof(msg), NULL, 0);
}

int KBInterface::sendMessage(const unsigned char messageId, const unsigned char* msg, const int msgLen, unsigned char* outBuf, const int outBufLen) {
    unsigned char data[RAW_HID_BUFFER_SIZE];
    data[0] = 0x00; // report ID
    data[1] = messageId;
    if (msgLen > 0 && msgLen <= (RAW_HID_BUFFER_SIZE - 2)) {
        memcpy(data + 2, msg, msgLen);
    }

    int res = hid_write(this->handle, data, RAW_HID_BUFFER_SIZE);
    if (res < RAW_HID_BUFFER_SIZE) {
        printf("Error on hid_write: %ls\n", res, hid_error(this->handle));
        return -1;
    }

    res = hid_read_timeout(this->handle, data, RAW_HID_BUFFER_SIZE, 1000);
    if (res < RAW_HID_BUFFER_SIZE) {
        printf("Error on hid_read_timeout: %ls\n", res, hid_error(this->handle));
        return -1;
    }
        

    if (outBufLen < 1 || outBuf == NULL) {
        return 0;
    }

    if (res > outBufLen) {
        res = outBufLen;
    }
    memcpy(outBuf, data, res);
    return res;
}
