#pragma once
#include <QDebug>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QTcpSocket>
#include <QtNetwork>
class MyNetWork : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString myip4 READ getMyip4 WRITE setMyip4 NOTIFY myip4Changed)
    Q_PROPERTY(QString send READ getSend WRITE setSend NOTIFY sendChanged)
    Q_PROPERTY(QString receive READ getreceive WRITE setreceive NOTIFY receiveChanged)

public:
    explicit MyNetWork(QObject *parent = nullptr);
    ~MyNetWork();

    QString getMyip4() const;
    void setMyip4(const QString &value);
    QString getSend() const;
    void setSend(const QString &value);
    QString getreceive() const;
    void setreceive(const QString &value);

    Q_INVOKABLE void sendMessage();

signals:
    void myip4Changed();
    void sendChanged();
    void receiveChanged();

private:
    QString m_ip4;
    QString m_send;
    QString m_receive;
    QTcpSocket *m_tcpSocket;

private slots:
    void readMessage(); // 读取消息
};
