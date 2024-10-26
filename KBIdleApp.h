#pragma once

#include <QObject>

#include "KBManager.h"

class KBIdleApp : public QObject
{
    Q_OBJECT

public:
    KBIdleApp(const int timeout, KBManager *mgr);
    ~KBIdleApp() override;

public Q_SLOTS:
    void timeoutReached(int id, int timeout);
    void resumingFromIdle();

protected:
    KBManager* mgr;
};
