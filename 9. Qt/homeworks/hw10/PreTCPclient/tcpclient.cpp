#include "tcpclient.h"

/* ServiceHeader
 * Для работы с потоками наши данные необходимо сериализовать.
 * Поскольку типы данных не стандартные перегрузим оператор << Для работы с ServiceHeader
*/
QDataStream &operator >>(QDataStream &out, ServiceHeader &data){

    out >> data.id;
    out >> data.idData;
    out >> data.status;
    out >> data.len;
    return out;
};
QDataStream &operator <<(QDataStream &in, ServiceHeader &data){

    in << data.id;
    in << data.idData;
    in << data.status;
    in << data.len;

    return in;
};



/*
 * Поскольку мы являемся клиентом, инициализацию сокета
 * проведем в конструкторе. Также необходимо соединить
 * сокет со всеми необходимыми нам сигналами.
*/
TCPclient::TCPclient(QObject *parent) : QObject(parent)
{
   socket = new QTcpSocket(this);

   connect(socket, &QTcpSocket::readyRead, this, &TCPclient::ReadyReed); //входное сообщение

   connect(socket, &QTcpSocket::connected, this, [&]{
        emit sig_connectStatus(STATUS_SUCCES);
    });

   connect(socket, &QTcpSocket::errorOccurred, this, [&]{
         emit sig_connectStatus(ERR_CONNECT_TO_HOST);
     });

   connect(socket, &QTcpSocket::disconnected, this, &TCPclient::sig_Disconnected);
}

/* write
 * Метод отправляет запрос на сервер. Сериализировать будем
 * при помощи QDataStream
*/
void TCPclient::SendRequest(ServiceHeader head)
{
    qDebug() << "SendRequest 1";
    QByteArray array_to_send;
    QDataStream outStream(&array_to_send, QIODevice::WriteOnly);

    outStream << head;
    socket->write(array_to_send);
    qDebug() << "SendRequest 2";
}

/* write
 * Такой же метод только передаем еще данные.
*/
void TCPclient::SendData(ServiceHeader head, QString str)
{
    qDebug() << "SendData 1";
    QByteArray array_to_send;
    QDataStream outStream(&array_to_send, QIODevice::WriteOnly);

    outStream << head;
    outStream << str;
    socket->write(array_to_send);
     qDebug() << "SendData 2";
     qDebug() << array_to_send;

}

/*
 * \brief Метод подключения к серверу
 */
void TCPclient::ConnectToHost(QHostAddress host, uint16_t port)
{
    socket->connectToHost(host, port);
}
/*
 * \brief Метод отключения от сервера
 */
void TCPclient::DisconnectFromHost()
{
    socket->disconnectFromHost();
}


void TCPclient::ReadyReed()
{
    qDebug() << "ReadyReed 1";
    QDataStream incStream(socket);

    if(incStream.status() != QDataStream::Ok){
        qDebug() << "ReadyReed 2";
        QMessageBox msg;
        msg.setIcon(QMessageBox::Warning);
        msg.setText("Ошибка открытия входящего потока для чтения данных!");
        msg.exec();
    }


    //Читаем до конца потока
    while(incStream.atEnd() == false){
        //Если мы обработали предыдущий пакет, мы скинули значение idData в 0
        if(servHeader.idData == 0){
            qDebug() << "ReadyReed 3";
            //Проверяем количество полученных байт. Если доступных байт меньше чем
            //заголовок, то выходим из обработчика и ждем новую посылку. Каждая новая
            //посылка дописывает данные в конец буфера
            if(socket->bytesAvailable() < sizeof(ServiceHeader)){
                return;
            }
            else{
                qDebug() << "ReadyReed 4";
                //Читаем заголовок
                incStream >> servHeader;
                //Проверяем на корректность данных. Принимаем решение по заранее известному ID
                //пакета. Если он "битый" отбрасываем все данные в поисках нового ID.
                if(servHeader.id != ID){
                    qDebug() << "ReadyReed 5";
                    uint16_t hdr = 0;
                    while(incStream.atEnd()){
                        incStream >> hdr;
                        if(hdr == ID){
                            incStream >> servHeader.idData;
                            incStream >> servHeader.status;
                            incStream >> servHeader.len;
                            break;
                        }
                    }
                }
            }
        }

        //Если получены не все данные, то выходим из обработчика. Ждем новую посылку
        if(socket->bytesAvailable() < servHeader.len){
            qDebug() << "ReadyReed 6";
            return;
        }
        else{
            //Обработка данных
            qDebug() << "ReadyReed 7";
            qDebug() << "data len = " <<  servHeader.len;
            ProcessingData(servHeader, incStream);
            servHeader.idData = 0;
            servHeader.status = 0;
            servHeader.len = 0;
        }
    }
}


/*
 * Остался метод обработки полученных данных. Согласно протоколу
 * мы должны прочитать данные из сообщения и вывести их в ПИ.
 * Поскольку все типы сообщений нам известны реализуем выбор через
 * switch. Реализуем получение времени.
*/

void TCPclient::ProcessingData(ServiceHeader header, QDataStream &stream)
{
    qDebug() << "ProcessingData 1";
    switch (header.idData){

        case GET_TIME:
        {
            QDateTime time;
            stream >> time;
            qDebug() << "emit sig_sendTime";
            emit sig_sendTime(time);
            break;
        }
        case GET_SIZE:
        {
            uint32_t free_size;
            stream >> free_size;
           qDebug() << "sig_sendFreeSize";
            emit sig_sendFreeSize(free_size);
            break;
        }
        case GET_STAT:
        {
            StatServer stat;

           // stream >> stat;
            stream >> stat.incBytes;  //принято байт
            stream >> stat.sendBytes;
            stream >> stat.revPck;
            stream >> stat.sendPck;
            stream >> stat.workTime;
            stream >> stat.clients;

            qDebug() << "sig_sendStat";
             emit sig_sendStat(stat);
             break;
        }
        case SET_DATA:
        {
            QString data_str;
            stream >> data_str;
            qDebug() << "sig_SendReplyForSetData";
            qDebug() << "data_str = " + data_str;
            emit  sig_SendReplyForSetData(data_str);
            break;
        }
        case CLEAR_DATA:
        {

            qDebug() << "case CLEAR_DATA:";
            ServiceHeader hdr;
            stream >> hdr;
            qDebug() << "hdr.status = " << hdr.status;
            if (hdr.status == STATUS_SUCCES)
            {
                qDebug() << "sig_Success";
                emit  sig_Success(CLEAR_DATA);
            }

            break;

        }
        default:
            return;

        }

}
