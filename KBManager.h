#pragma once

#include <QThread>
#include "KBInterface.h"

class KBManager : public QThread
{
    Q_OBJECT

public:
    KBManager(KBInterface *intf);
    ~KBManager();

    void goWakeup(void);
    void goIdle(void);

    void run(void);

private:
    volatile int targetBrightness;
    volatile int setBrightness;
    
    volatile int onBrightness;
    void loadOnBrightness(void);

    KBInterface *intf;
    volatile bool running;
};
