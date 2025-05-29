#include "linkudp.h"
#include <QUdpSocket>
#include <QThread>
#include <QMutexLocker>

LinkUdp::LinkUdp() : m_thread(nullptr),
                     m_isConnected(false),
                     m_shouldExit(false)
{
}

LinkUdp::~LinkUdp()
{
}


bool LinkUdp::isConnected() const
{
    return true;
}


void LinkUdp::run()
{
}
