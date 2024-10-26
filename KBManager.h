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
    int targetBrightness;
    int setBrightness;
    void setTargetBrightness(const int target);
    
    int onBrightness;
    void loadOnBrightness(void);

    KBInterface *intf;
    volatile bool running;
};
