#include <QGuiApplication>

#include <hidapi/hidapi.h>
#include "KBInterface.h"
#include "KBIdleApp.h"

#define QMK_INTERFACE 0x01

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s TIMEOUT_MS\n", argv[0]);
        return 1;
    }

    const int timeout = atoi(argv[1]);
    if (timeout < 1) {
        printf("Timeout must be at least 1 millisecond\n");
        return 1;
    }

   (void)hid_init();

    hid_device_info* info = hid_enumerate(0x32ac, 0x0012);
    while (info != NULL && info->interface_number != QMK_INTERFACE) {
        info = info->next;
    }

    if (info == NULL) {
        printf("Could not find keyboard!\n");
        return 1;
    }

    hid_device* handle = hid_open_path(info->path);
    if (!handle) {
        printf("Could not open keyboard!\n");
        return 1;
    }

    KBInterface kb(handle);
    QGuiApplication app(argc, argv);
    KBIdleApp t(timeout, &kb);
    return app.exec();
}
