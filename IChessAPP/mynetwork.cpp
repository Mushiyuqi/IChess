#include "mynetwork.h"
#include <QBitArray>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include "MsgNode.h"
MyNetWork::MyNetWork(QObject *parent)
    : QObject(parent)
{

    // 初始化TCP客户端
    m_tcpSocket = new QTcpSocket(this);

    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &MyNetWork::readMessage);
    qDebug() << "初始化TCP服务器";
}
MyNetWork::~MyNetWork()
{
    if (m_tcpSocket) {
        m_tcpSocket->disconnectFromHost();
        if (m_tcpSocket->state() != QAbstractSocket::UnconnectedState) {
            m_tcpSocket->waitForDisconnected();
        }
        delete m_tcpSocket;
    }
}

QString MyNetWork::getMyip4() const
{
    m_tcpSocket->connectToHost(m_ip4, 10086);
    qDebug() << "getMyip4" << m_ip4;

    return m_ip4;
}
void MyNetWork::setMyip4(const QString &value)
{
    qDebug() << "setMyip4";
    if (m_ip4 == value)
        return;
    m_ip4 = value;

    emit myip4Changed();
    qDebug() << " emit myip4Changed()" << m_ip4;
}
QString MyNetWork::getSend() const
{
    qDebug() << "getSend";
    return m_send;
}
void MyNetWork::setSend(const QString &value)
{
    if (m_send == value)
        return;
    m_send = value;
    emit sendChanged();
    //sendMessage();
    qDebug() << "setSend";
}
QString MyNetWork::getreceive() const
{
    return m_receive;
}
void MyNetWork::setreceive(const QString &value)
{
    if (m_receive == value)
        return;
    m_receive = value;
    emit receiveChanged();
}

// 发送消息
void MyNetWork::sendMessage()
{
    qDebug() << "发送消息 ";

    if (m_tcpSocket)
        qDebug() << "m_tcpSocket";
    if (m_tcpSocket->state() == QAbstractSocket::ConnectedState)
        qDebug() << "m_tcpSocket->state() OK";
    QStringList sendData = m_send.split(' ', Qt::SkipEmptyParts); // 使用空格分割字符串

    if (sendData.size() != 7) {
        qDebug() << "Error: The string does not contain exactly 7 numbers.";
        return;
    }

    // 将字符串转换为整数 and to Json
    QJsonObject json;
    short id = sendData[4].toInt();
    json["xFrom"] = sendData[0].toInt();
    json["yFrom"] = sendData[1].toInt();
    json["xTo"] = sendData[2].toInt();
    json["yTo"] = sendData[3].toInt();
    json["id"] = sendData[4].toInt();
    json["color"] = sendData[5].toInt();
    json["roomID"] = sendData[6].toInt();
    // Json to String
    QByteArray data = QJsonDocument(json).toJson();
    qDebug() << data;
    short size = data.size();
    SendNode sendNode{data.data(), size, id};
    // send massage
    // qint64 bytesWritten = m_tcpSocket->write(sendNode.m_data, sendNode.m_total_len);
    QByteArray sendArray(sendNode.m_data, sendNode.m_total_len);
    qint64 bytesWritten = m_tcpSocket->write(sendArray);
    qDebug() << "sendMessage()" << m_send;
}
// 读取消息
void MyNetWork::readMessage()
{
    qDebug() << "读取消息";
    QByteArray data = m_tcpSocket->readAll();
    if (!data.isEmpty()) {
        short msgID;
        short msgLen;
        memcpy(&msgID, data.data(), HEAD_ID_LEN);
        memcpy(&msgLen, data.data() + HEAD_ID_LEN, HEAD_DATA_LEN);
        RecvNode recvNode(msgLen, msgID);
        memcpy(recvNode.m_data, data.data() + HEAD_TOTAL_LEN, msgLen);

        QString jsonStr(recvNode.m_data);
        QJsonObject json = QJsonDocument::fromJson(jsonStr.toUtf8()).object();
        QString xFrom = QString::number(json["xFrom"].toInt());
        QString yFrom = QString::number(json["yFrom"].toInt());
        QString xTo = QString::number(json["xTo"].toInt());
        QString yTo = QString::number(json["yTo"].toInt());
        QString id = QString::number(json["id"].toInt());
        QString color = QString::number(json["color"].toInt());
        QString roomID = QString::number(json["roomID"].toInt());
        m_receive = xFrom + " " + yFrom + " " + xTo + " " + yTo + " " + id + " " + color + " "
                    + roomID;
        qDebug() << "m_receive : " << m_receive;
        emit receiveChanged();
        qDebug() << "Message received:" << m_receive;
    } else
        qDebug() << "Message NO received:" << m_receive;
}
