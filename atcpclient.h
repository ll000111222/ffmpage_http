#ifndef ATCPCLIENT_H
#define ATCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include <QTimer>

class ATcpClient : public QObject
{
    Q_OBJECT
public:
    ATcpClient(QString sServerIp, int nPort, QObject *parent = 0);
    virtual ~ATcpClient();

    int  sendData(QByteArray baData);
    void setReConnectInterval(int nMSec);
    void doReConnect();

protected:
    virtual void initInThread();
    virtual void deinitInThread();

    virtual void setConnectStatus(bool bIsConnect);

    virtual int doSendDataImp(QByteArray baData);
    virtual int doRecvDataImp(const QByteArray &baRecvData);

signals:
    void sigSendData(QByteArray baData);
    void sigOnDeinit();
    void sendReceiveMsg(QByteArray byteArray);

private slots:
    void sltSendData(QByteArray baData);
    void sltReadyRead();

    void sltOnConnected();
    void sltOnDisonnected();
    void sltOnError(QAbstractSocket::SocketError nErrCode);
    void sltOnStateChanged(QAbstractSocket::SocketState nSocketState);

private:
    QString m_sServerIp;
    int m_nPort;
    int m_nInterval;
    bool m_bConnected{false};

    QThread* m_pThread{nullptr};
    QTimer* m_pTimer{nullptr};
    QTcpSocket* m_pSocketClient{nullptr};
};

#endif // ATCPCLIENT_H
