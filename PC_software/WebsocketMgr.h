#pragma once
#include <QObject>
#include <QWebsocket>
#include "singleton.h"
#include "global.h"

class WebsocketMgr  : public QObject,public Singleton<WebsocketMgr>,
	public std::enable_shared_from_this<WebsocketMgr>
{
	Q_OBJECT

public:
	void slot_websocket_connect();
	~WebsocketMgr();
private:
	friend class Singleton<WebsocketMgr>;
	WebsocketMgr();
	void initHandlers();
	void handleMsg(ReqId id, QJsonDocument data);
	QWebSocket _socket;
	QString _host;
	QString _port;
	bool _b_recv_pending;
	QMap<ReqId, std::function<void(ReqId id, QJsonDocument data)>> _handlers;

public slots:
	void slot_send_data(ReqId reqId, QString data);
signals:
	void sig_con_success(bool bsuccess);
	void sig_send_data(ReqId reqId, QString data);
	void sig_switch_chatdlg();
	void sig_login_failed(int);
	void sig_change_patient_data(QJsonObject obj);

};
