#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <mutex>

#include "KBManager.h"

#define INC_STEP 5
#define INC_US 2000
#define WAIT_US 50000

KBManager::KBManager(KBInterface* intf) {
    this->running = false;
    this->intf = intf;

    this->onBrightness = 0xFF;
    this->targetBrightness = this->onBrightness;
    this->setBrightness = this->intf->getRGBBrightness();
}

KBManager::~KBManager() {
    this->wait();
}

#define GET_TIME_US(var) { \
    gettimeofday(&time, NULL); \
    var = ((uint64_t)time.tv_sec * 1000000) + (uint64_t)time.tv_usec; \
}

void KBManager::run() {
    struct timeval time;
    uint64_t time_us;
    uint64_t time_us2;

    while (this->setBrightness != this->targetBrightness && this->running) {
        if (this->setBrightness > this->targetBrightness) {
            this->setBrightness -= INC_STEP;
            if (this->setBrightness < this->targetBrightness) {
                this->setBrightness = this->targetBrightness;
            }
        } else {
            this->setBrightness += INC_STEP;
            if (this->setBrightness > this->targetBrightness) {
                this->setBrightness = this->targetBrightness;
            }
        }

        GET_TIME_US(time_us);
        this->intf->setRGBBrightness(this->setBrightness);
        GET_TIME_US(time_us2);
        if (time_us2 > time_us) {
            usleep(INC_US - (time_us2 - time_us));
            continue;
        }
        usleep(INC_US);
    }
}

void KBManager::setTargetBrightness(const int target) {
    std::lock_guard<std::mutex> guard(this->setTargerBrightnessMutex);

    this->running = false;
    this->wait();
    this->targetBrightness = target;
    this->running = true;
    this->start();
}

void KBManager::goWakeup() {
    this->setTargetBrightness(this->onBrightness);
}

void KBManager::goIdle() {
    this->setTargetBrightness(0);
}
