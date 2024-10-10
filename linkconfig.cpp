#include "linkconfig.h"

LinkConfig::LinkConfig(QObject *parent)
    : QObject{parent}
{}

bool LinkConfig::autoConnect() const
{
    return m_autoConnect;
}

void LinkConfig::setAutoConnect(bool newAutoConnect)
{
    if (m_autoConnect == newAutoConnect) {
        return;
    }
    m_autoConnect = newAutoConnect;
    emit autoConnectChanged();
}

quint32 LinkConfig::interval() const
{
    return m_interval;
}

void LinkConfig::setInterval(quint32 newInterval)
{
    if (m_interval == newInterval) {
        return;
    }
    m_interval = newInterval;
    emit intervalChanged();
}
