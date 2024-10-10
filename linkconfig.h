#pragma once

#include <QObject>

class LinkConfig : public QObject
{
    Q_OBJECT
public:
    explicit LinkConfig(QObject *parent = nullptr);
    Q_PROPERTY(bool autoConnect READ autoConnect WRITE setAutoConnect NOTIFY autoConnectChanged FINAL)
    Q_PROPERTY(quint32 interval READ interval WRITE setInterval NOTIFY intervalChanged FINAL)

    bool autoConnect() const;
    void setAutoConnect(bool newAutoConnect);

    quint32 interval() const;
    void setInterval(quint32 newInterval);

signals:
    void autoConnectChanged();

    void intervalChanged();

private:
    bool m_autoConnect = false;
    quint32 m_interval = 3000;
};
