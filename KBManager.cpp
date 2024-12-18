#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <mutex>

#include "KBManager.h"

#define INC_STEP 40
#define INC_US 16000

KBManager::KBManager(KBInterface* intf) {
    this->running = false;
    this->intf = intf;

    this->onBrightness = 0xFF;
    this->setBrightness = this->intf->getRGBBrightness();
    this->goWakeup();
}

KBManager::~KBManager() {
    this->wait();
}

#define GET_TIME_US(var) { \
    clock_gettime(CLOCK_MONOTONIC, &time); \
    var = ((uint64_t)time.tv_sec * 1000000) + (uint64_t)(time.tv_nsec / 1000); \
}

void KBManager::run() {
    struct timespec time;
    uint64_t time_us;
    uint64_t time_us2;
    uint64_t time_delta;

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

        if (time_us2 <= time_us) {
            usleep(INC_US);
            continue;
        }

        time_delta = time_us2 - time_us;
        if (time_delta >= INC_US) {
            continue;
        }
        usleep(INC_US - time_delta);
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

void KBManager::loadCurBrightness() {
    std::lock_guard<std::mutex> guard(this->setTargerBrightnessMutex);

    if (this->targetBrightness != this->onBrightness || \
        this->setBrightness != this->onBrightness) {
        return;
    }

    if (this->isRunning()) {
        return;
    }

    const int curBrightness = this->intf->getRGBBrightness();
    if (curBrightness < 0) {
        return;
    }

    this->setBrightness = curBrightness;
    this->onBrightness = curBrightness;
}

void KBManager::goWakeup() {
    this->setTargetBrightness(this->onBrightness);
}

void KBManager::goIdle() {
    this->loadCurBrightness();
    this->setTargetBrightness(0);
}
