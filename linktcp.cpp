/**************************************************************************
 *   文件名	：linktcp.cpp
 *   =======================================================================
 *   创 建 者	：田小帆
 *   创建日期	：2024-9-26
 *   邮   箱	：499131808@qq.com
 *   Q Q		：499131808
 *   公   司      ：
 *   功能描述      ：
 *   使用说明 ：
 *   ======================================================================
 *   修改者	：
 *   修改日期	：
 *   修改内容	：
 *   ======================================================================
 *
 ***************************************************************************/
#include "linktcp.h"

LinkTcp::LinkTcp() {}

bool LinkTcp::connectLink()
{
    asyncConnect();
    return true;
}

void LinkTcp::disconnectLink()
{
    if (m_tcpSocket) {
        m_tcpSocket->abort();
        m_tcpSocket->close();
        m_tcpSocket->deleteLater();
    }
}

bool LinkTcp::isConnected() const
{
    if (m_tcpSocket) {
        return m_tcpSocket->state() == QAbstractSocket::ConnectedState;
    }
    return false;
}

quint64 LinkTcp::writeData(const QByteArray &data)
{
    if (isConnected()) {
        return m_tcpSocket->write(data);
    }
    return -1;
}

QString tcptile = QObject::tr("TCP Link Error");
void LinkTcp::asyncConnect()
{
    QString noset = tr("no config");
    if (getConfig().isNull()) {
        emit linkError(tcptile, noset);
        return;
    }

    auto tcpConfig = qobject_cast<LinkTcpConfig *>(getConfig().data());
    if (tcpConfig == nullptr) {
        emit linkError(tcptile, noset);
        return;
    }

    //定时器，用于断线重连
    m_reTime.reset(new QTimer());
    connect(m_reTime.data(), &QTimer::timeout, this, [=]() {
        m_tcpSocket->abort();
        m_tcpSocket->close();
        auto str = QString("%1:%2 ").arg(tcpConfig->address().toString()).arg(tcpConfig->port());
        str = str + tr("connect timeout!");
        emit linkError(tcptile, str);

        m_tcpSocket->connectToHost(tcpConfig->address(), tcpConfig->port());
    });

    m_tcpSocket.reset(new QTcpSocket());
    connect(m_tcpSocket.data(), &QTcpSocket::readyRead, this, [this]() {
        auto byte_size = m_tcpSocket->bytesAvailable();
        if (byte_size > 0) {
            QByteArray buffer;
            buffer.resize(byte_size);
            m_tcpSocket->read(buffer.data(), buffer.size());
            emit receiveData(this, buffer);
        }
    });

    connect(m_tcpSocket.data(),
            &QTcpSocket::errorOccurred,
            this,
            [=](QAbstractSocket::SocketError error) {
                if (!m_reTime->isActive() && tcpConfig->autoConnect()) {
                    m_reTime->start(tcpConfig->interval());
                }

                if (m_tcpSocket) {
                    emit linkError(tcptile, m_tcpSocket->errorString());
                }
            });

    connect(m_tcpSocket.data(), &QTcpSocket::connected, this, [=]() {
        emit connected();
        if (m_reTime->isActive()) {
            m_reTime->stop();
        }
    });

    connect(m_tcpSocket.data(), &QTcpSocket::disconnected, this, &LinkTcp::disconnected);
    m_tcpSocket->connectToHost(tcpConfig->address(), tcpConfig->port());
}

QString LinkTcpConfig::ip() const
{
    return m_address.toString();
}

void LinkTcpConfig::setIp(const QString &newIp)
{
    QHostAddress test;
    if (test.setAddress(newIp)) {
        setAddrerss(test);
    }
    emit ipChanged();
}

quint32 LinkTcpConfig::port() const
{
    return m_port;
}

void LinkTcpConfig::setPort(quint32 newPort)
{
    if (m_port == newPort) {
        return;
    }
    m_port = newPort;
    emit portChanged();
}

const QHostAddress LinkTcpConfig::address() const
{
    return m_address;
}

void LinkTcpConfig::setAddrerss(const QHostAddress &address)
{
    if (m_address != address) {
        m_address = address;
    }
}

