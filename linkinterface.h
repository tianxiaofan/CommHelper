/**************************************************************************
 *   文件名	：linkinterface.h
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
#include <QObject>

class LinkInterface : public QObject
{
    Q_OBJECT
public:
    LinkInterface();

    /// 打开连接，具备断线后自动重连功能， 直到close调用后停止重连
    virtual bool connectLink() = 0;
    /// 关闭连接
    virtual void disconnectLink() = 0;
    /// 返回连接状态
    virtual bool isConnected() const = 0;

    void writeBytesThreadSafe(const char *bytes, int len)
    {
        writeBytesThreadSafe(QByteArray(bytes, len));
    }
    void writeBytesThreadSafe(const QByteArray &byte);

protected:
    virtual quint64 writeData(const QByteArray &data) = 0;

signals:
    void receiveData(const LinkInterface *link, const QByteArray &data);
    void sendData(const QByteArray &data);

    /// 连接成功
    void connected();
    /// 断开
    void disconnected();
    /// 错误信息
    void linkError(const QString &title, const QString &error);
};
