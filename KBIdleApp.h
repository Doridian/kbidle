#pragma once

#include <QObject>

class KBIdleApp : public QObject
{
    Q_OBJECT

public:
    KBIdleApp(const int timeout);
    ~KBIdleApp() override;

public Q_SLOTS:
    void timeoutReached(int id, int timeout);
    void resumeEvent();
};
