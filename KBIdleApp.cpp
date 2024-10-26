#include "KBIdleApp.h"

#include "kidletime.h"

KBIdleApp::KBIdleApp(const int timeout)
{
    // connect to idle events
    connect(KIdleTime::instance(), &KIdleTime::resumingFromIdle, this, &KBIdleApp::resumeEvent);
    connect(KIdleTime::instance(), qOverload<int, int>(&KIdleTime::timeoutReached), this, &KBIdleApp::timeoutReached);

    KIdleTime::instance()->addIdleTimeout(timeout);
}

KBIdleApp::~KBIdleApp()
{
}

void KBIdleApp::resumeEvent()
{
    printf("RESUME\n");
}

void KBIdleApp::timeoutReached(int id, int timeout)
{
    Q_UNUSED(id)
    Q_UNUSED(timeout)

    printf("IDLE\n");
    KIdleTime::instance()->catchNextResumeEvent();
}

#include "moc_KBIdleApp.cpp"
