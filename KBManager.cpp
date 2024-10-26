#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "KBManager.h"

#define INC_STEP 5
#define INC_US 2000
#define WAIT_US 50000

KBManager::KBManager(KBInterface* intf) {
    this->running = true;
    this->intf = intf;

    this->onBrightness = 0xFF;
    this->targetBrightness = this->onBrightness;
    this->setBrightness = this->intf->getRGBBrightness();

    this->start();
}

KBManager::~KBManager() {
    this->running = false;
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

    while (true) {
        while (this->setBrightness != this->targetBrightness) {
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

        usleep(WAIT_US);
    }
}

void KBManager::goWakeup() {
    this->targetBrightness = this->onBrightness;
}

void KBManager::goIdle() {
    if (this->targetBrightness == this->setBrightness &&
        this->setBrightness == this->onBrightness) {
        int newOnBrightness = this->intf->getRGBBrightness();
        if (abs(newOnBrightness - this->onBrightness) > 2) {
            // This stops the off-by-one errors in the control...
            this->onBrightness = newOnBrightness;
            printf("Adjusting onBrightness to %d\n", newOnBrightness);
        }
    }

    this->targetBrightness = 0;
}
