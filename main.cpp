#include "KBIdleApp.h"
#include <QGuiApplication>

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

    QGuiApplication app(argc, argv);
    KBIdleApp t(timeout);
    return app.exec();
}
