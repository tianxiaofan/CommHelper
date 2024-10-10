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
#include "tilogger.h"

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
    //定时器，用于断线重连
    m_reTime.reset(new QTimer());
    connect(m_reTime.data(), &QTimer::timeout, this, [this]() {
        m_tcpSocket->abort();
        m_tcpSocket->close();
        // LOG_DEBUG() << m_tcpConfig->address().toString() << m_tcpConfig->port();
        // auto str = QString("%1:%2 ").arg(m_tcpConfig->address().toString()).arg(m_tcpConfig->port());
        // str = str + tr("connect timeout!");
        // GlobalInfo::instance()->errorMessage(tr("Link"), str);

        // m_tcpSocket->connectToHost(m_tcpConfig->address(), m_tcpConfig->port());
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
            [this](QAbstractSocket::SocketError error) {
                emit linkError(tcptile, m_tcpSocket->errorString());
            });
    connect(m_tcpSocket.data(), &QTcpSocket::connected, this, &LinkTcp::connected);
    connect(m_tcpSocket.data(), &QTcpSocket::disconnected, this, &LinkTcp::disconnected);
    // m_tcpSocket->connectToHost(m_tcpConfig->address(), m_tcpConfig->port());
}
