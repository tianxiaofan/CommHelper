#pragma once

#include "linkconfig.h"
#include "linkinterface.h"

class LinkUdpConfig : public LinkConfig
{
    Q_OBJECT
public:
    LinkUdpConfig() {}
};

class LinkUdp : public LinkInterface
{
    Q_OBJECT
public:
    LinkUdp();
    ~LinkUdp();

    virtual bool isConnected() const override;

private:
    void run(); // 线程运行函数

private:
    QThread *m_thread;
    bool m_isConnected;
    volatile bool m_shouldExit;
};
