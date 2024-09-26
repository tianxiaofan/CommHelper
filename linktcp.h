/**************************************************************************
 *   文件名	：linktcp.h
 *   =======================================================================
 *   创 建 者	：田小帆
 *   创建日期	：2024-9-26
 *   邮   箱	：499131808@qq.com
 *   Q Q		：499131808
 *   公   司      ：西安英杰伟成航空科技有限公司
 *   功能描述      ：
 *   使用说明 ：任何人或机构要使用、修改、发布本源代码,都必须要获得西安英杰伟成航空科技有限公司的授权
 *   ======================================================================
 *   修改者	：
 *   修改日期	：
 *   修改内容	：
 *   ======================================================================
 *
 ***************************************************************************/
#pragma once

#include "linkinterface.h"

#include <QPointer>
#include <QTcpSocket>
#include <QTimer>
class LinkTcp : public LinkInterface
{
public:
    LinkTcp();

    // QRunnable interface
public:
    void run() override;

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
