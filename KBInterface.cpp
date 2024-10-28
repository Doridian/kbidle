#include "KBInterface.h"

KBInterface::KBInterface() : client("kbidle") {
}

int KBInterface::ensureClient() {
    if (this->client.isConnected()) {
        return 0;
    }

    printf("OpenRGB Client connecting...\n");

    orgb::ConnectStatus status = this->client.connect("127.0.0.1");
    if (status != orgb::ConnectStatus::Success)
    {
        printf("Failed to connect to OpenRGB: %s (error code: %d)\n",
            enumString(status), int(this->client.getLastSystemError()));
        return -1;
    }

    this->list = std::move(this->client.requestDeviceListX());
    this->device = &this->list.findX(orgb::DeviceType::Keyboard);

    printf("OpenRGB Client connected!\n");

    return 0;
}

int KBInterface::getRGBBrightness() {
    return 255;
}

void KBInterface::setRGBBrightness(const int brightness) {
    if (brightness < 0) {
        return;
    }

    if (this->ensureClient() < 0) {
        return;
    }

    orgb::Color ourColor(brightness, 0, brightness);
    this->client.setDeviceColor(*this->device, ourColor);
}
