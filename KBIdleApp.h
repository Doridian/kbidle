#pragma once

#include <QObject>

#include "KBInterface.h"

class KBIdleApp : public QObject
{
    Q_OBJECT

public:
    KBIdleApp(const int timeout, KBInterface *kb);
    ~KBIdleApp() override;

public Q_SLOTS:
    void timeoutReached(int id, int timeout);
    void resumingFromIdle();

protected:
    KBInterface* kb;
};
