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
    LinkTcpConfig();
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
