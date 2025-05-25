#include "WebsocketMgr.h"
#include "UserMgr.h"
WebsocketMgr::~WebsocketMgr()
{}

void WebsocketMgr::slot_send_data(ReqId reqId, QString data)
{
    qDebug() << "websocker login send" << data;
    _socket.sendTextMessage(data);
}

void WebsocketMgr::slot_websocket_connect()
{
    qDebug() << "receive websocket connect signal";
    _socket.open(QUrl("ws://127.0.0.1:8000"));
}

WebsocketMgr::WebsocketMgr():_host(""),_port(""), _b_recv_pending(false)
{
	QObject::connect(&_socket,&QWebSocket::connected,[&]() {
		qDebug() << "connect to server";
		emit sig_con_success(true);
	});

	QObject::connect(&_socket, &QWebSocket::textMessageReceived, [&](const QString& message) {
		QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
		//qDebug() << doc;
        QJsonObject obj = doc.object();
        handleMsg(ReqId(obj["id"].toInt()), doc);
	});

	QObject::connect(&_socket, &QWebSocket::errorOccurred, [&](QAbstractSocket::SocketError err) {
		qDebug() << err;
        switch (err) {
        case QAbstractSocket::HostNotFoundError:
            qDebug() << "Host not found!";
            break;
        case QAbstractSocket::ConnectionRefusedError:
            qDebug() << "Connection refused!";
            break;
        case QAbstractSocket::RemoteHostClosedError:
            qDebug() << "Remote host closed the connection!";
            break;
        case QAbstractSocket::SocketTimeoutError:
            qDebug() << "Socket timeout!";
            break;
        default:
            qDebug() << "Other error:" << err;
            break;
        }
	});

    QObject::connect(&_socket, &QWebSocket::disconnected, [&]() {
        qDebug() << "disconnect from server";
    });

    QObject::connect(this, &WebsocketMgr::sig_send_data, this, &WebsocketMgr::slot_send_data);
    initHandlers();
}

void WebsocketMgr::initHandlers()
{
    _handlers.insert(ReqId::GetPatientNowData, [this](ReqId id, QJsonDocument data) {
        if (data.isNull())
        {
            qDebug() << "data=null";
            return;
        }

        
        //qDebug() << "get now data success";
        emit sig_change_patient_data(data.object());
    });
}

void WebsocketMgr::handleMsg(ReqId id, QJsonDocument data)
{
    auto find_it = _handlers.find(id);
    if (find_it == _handlers.end())
    {
        qDebug() << "not found id [" << id << "] to handle";
        return;
    }
    find_it.value()(id, data);
}
