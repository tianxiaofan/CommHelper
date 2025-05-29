/**************************************************************************
 *   文件名	：linktcp.h
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
#pragma once

#include "linkconfig.h"
#include "linkinterface.h"

#include <QPointer>
#include <QTcpSocket>
#include <QTimer>

class LinkTcpConfig : public LinkConfig
{
    Q_OBJECT
public:
    LinkTcpConfig() {};
    Q_PROPERTY(QString ip READ ip WRITE setIp NOTIFY ipChanged FINAL)
    Q_PROPERTY(quint32 port READ port WRITE setPort NOTIFY portChanged FINAL)
    QString ip() const;
    void setIp(const QString &newIp);
    quint32 port() const;
    void setPort(quint32 newPort);
    const QHostAddress address() const;
    void setAddrerss(const QHostAddress &address);

signals:
    void ipChanged();

    void portChanged();

private:
    QHostAddress m_address; // 目标地址
    quint32 m_port;
};

class LinkTcp : public LinkInterface
{
public:
    LinkTcp();

    // LinkInterface interface
public:
    bool connectLink() override;
    void disconnectLink() override;
    bool isConnected() const override;

protected:
    quint64 writeData(const QByteArray &data) override;

    void asyncConnect();

private:
    QScopedPointer<QTcpSocket> m_tcpSocket;
    QScopedPointer<QTimer> m_reTime;
};
