#include "udpworker.h"

UDPworker::UDPworker(QObject *parent) : QObject(parent)
{



}


/*!
 * @brief Метод инициализирует UDP сервер
 */
void UDPworker::InitSocket()
{

    serviceUdpSocket = new QUdpSocket(this);
    /*
     * Соединяем присваиваем адрес и порт серверу и соединяем функцию
     * обраотчик принятых пакетов с сокетом
     */
    serviceUdpSocket->bind(QHostAddress::LocalHost, BIND_PORT);

    connect(serviceUdpSocket, &QUdpSocket::readyRead, this, &UDPworker::readPendingDatagrams);

}

/*!
 * @brief Метод осуществляет обработку принятой датаграммы
 */
void UDPworker::ReadDatagram(QNetworkDatagram datagram)
{
    QByteArray data;
    data = datagram.data();
    Data_Type dt_type = static_cast<Data_Type>(data[0]);

    data = data.remove(0, 1);
    QDataStream inStr(&data, QIODevice::ReadOnly);

    switch (dt_type)
    {
    case Data_Type::dt_time:
        {
            QDateTime dateTime;
            inStr >> dateTime;
            emit sig_sendTimeToGUI(dateTime);
            break;
        };
    case Data_Type::dt_text:
        {
            QString  dataStr;
            inStr >> dataStr;

            QString address = datagram.senderAddress().toString();
            int data_length = data.length();
            qDebug() << "rcvd length = " << data_length;
            emit sig_sendText(dataStr, address, data_length);
            break;
        };
    }
}


void UDPworker::SendData(Data_to_Send data)
{
   // QByteArray byte_array_to_send;
   // byte_array_to_send.append(static_cast<char>(data.dt_type));
   // byte_array_to_send.append(data.data);
   // SendDatagram(byte_array_to_send);

    data.data.prepend(static_cast<char>(data.dt_type));
    SendDatagram(data.data);
}
/*!
 * @brief Метод осуществляет опередачу датаграммы
 */
void UDPworker::SendDatagram(QByteArray data )
{
    /*
     *  Отправляем данные на localhost и задефайненный порт
     */
    serviceUdpSocket->writeDatagram(data, QHostAddress::LocalHost, BIND_PORT);
}

/*!
 * @brief Метод осуществляет чтение датаграм из сокета
 */
void UDPworker::readPendingDatagrams( void )
{
    /*
     *  Производим чтение принятых датаграмм
     */
    while(serviceUdpSocket->hasPendingDatagrams()){
            QNetworkDatagram datagram = serviceUdpSocket->receiveDatagram();
            ReadDatagram(datagram);
    }

}
