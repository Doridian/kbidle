#include "KBIdleApp.h"

#include "kidletime.h"

KBIdleApp::KBIdleApp(const int timeout, KBManager *mgr) {
    this->mgr = mgr;

    connect(KIdleTime::instance(), &KIdleTime::resumingFromIdle, this, &KBIdleApp::resumingFromIdle);
    connect(KIdleTime::instance(), qOverload<int, int>(&KIdleTime::timeoutReached), this, &KBIdleApp::timeoutReached);

    KIdleTime::instance()->addIdleTimeout(timeout);
}

KBIdleApp::~KBIdleApp() {
}

void KBIdleApp::resumingFromIdle() {
    this->mgr->goWakeup();
}

void KBIdleApp::timeoutReached(int id, int timeout) {
    Q_UNUSED(id)
    Q_UNUSED(timeout)

    this->mgr->goIdle();

    KIdleTime::instance()->catchNextResumeEvent();
}

#include "moc_KBIdleApp.cpp"
