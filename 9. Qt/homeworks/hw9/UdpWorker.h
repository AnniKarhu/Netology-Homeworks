#ifndef UDPWORKER_H
#define UDPWORKER_H

#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDateTime>


#define BIND_PORT 12345

enum class Data_Type
{
    dt_time = 0,
    dt_text = 1
};

struct Data_to_Send
{
    Data_Type dt_type;
    QByteArray data;
};



class UDPworker : public QObject
{
    Q_OBJECT


public:
    explicit UDPworker(QObject *parent = nullptr);
    void InitSocket( void );
    void ReadDatagram( QNetworkDatagram datagram);
    void SendData(Data_to_Send data);
    //void SendDatagram(QByteArray data );

private slots:
    void readPendingDatagrams(void);

private:
    QUdpSocket* serviceUdpSocket;
    void SendDatagram(QByteArray data );


signals:
    void sig_sendTimeToGUI(QDateTime data);
    void sig_sendText(QString TextData, QString address, int data_length);

};

#endif // UDPWORKER_H
