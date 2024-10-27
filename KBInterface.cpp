#include "KBInterface.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEVICE_PATH "/sys/class/leds/viauled::kbd_backlight/brightness"

KBInterface::KBInterface() {
}

int KBInterface::getRGBBrightness() {
    FILE *fd = fopen(DEVICE_PATH, "r");
    if (!fd) {
        perror("fopen(LED, r)");
        return -1;
    }
    char buf[256];
    if (fgets(buf, sizeof(buf), fd) == NULL) {
        fclose(fd);
        return -1;
    }
    fclose(fd);
    return atoi(buf);
}

void KBInterface::setRGBBrightness(const int brightness) {
    if (brightness < 0) {
        return;
    }

    char buf[256];
    snprintf(buf, sizeof(buf), "%d\n", brightness);

    FILE *fd = fopen(DEVICE_PATH, "w");
    if (!fd) {
        perror("fopen(LED, w)");
        return;
    }
    fputs(buf, fd);
    fclose(fd);
}
