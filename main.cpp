#include <QGuiApplication>

#include "KBInterface.h"
#include "KBManager.h"
#include "KBIdleApp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s TIMEOUT_MS\n", argv[0]);
        return 1;
    }

    KBInterface kb;
    if (strcmp(argv[1], "standby") == 0) {
        printf("Going standby...\n");
        kb.prepareStandby();
        return 0;
    } else if(strcmp(argv[1], "wakeup") == 0) {
        printf("Going wakeup...\n");
        kb.handleWakeup();
        return 0;
    }

    const int timeout = atoi(argv[1]);
    if (timeout < 1) {
        printf("Timeout must be at least 1 millisecond\n");
        return 1;
    }

    KBManager mgr(&kb);

    QGuiApplication app(argc, argv);
    KBIdleApp t(timeout, &mgr);
    return app.exec();
}
