#include "KBManager.h"

KBManager::KBManager(KBInterface* intf) {
    this->intf = intf;
    this->currentBrightness = 0xFF;
    this->onBrightness = this->currentBrightness;
    this->targetBrightness = this->currentBrightness;
}

KBManager::~KBManager() {
}

void KBManager::goWakeup() {
    this->intf->setRGBBrightness(this->onBrightness);
}

void KBManager::goIdle() {
    this->intf->setRGBBrightness(0);
}
