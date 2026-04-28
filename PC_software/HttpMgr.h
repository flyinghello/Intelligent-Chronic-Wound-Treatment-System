#pragma once
#include "singleton.h"
#include <QUrl>
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include "global.h"
#include <queue>

struct QueData
{

	QUrl url;
	ReqId req_id;
	Modules mod;
	QueData(const QUrl& u, ReqId id, Modules m)
		: url(u), req_id(id), mod(m)
	{}
}; 

class HttpMgr:public QObject,public Singleton<HttpMgr>,public std::enable_shared_from_this<HttpMgr>
{
	Q_OBJECT
public:
	~HttpMgr();
	void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);
	void GetImageHttpReq(QUrl url, ReqId req_id, Modules mod);
	void AddQueGetImageHttpReq(QUrl url, ReqId req_id, Modules mod)
	{
		_que.push(QueData(url,req_id,mod));
		if(_que.size()==1) GetImageHttpReq(url,req_id,mod);
	};
private:
	friend class Singleton<HttpMgr>;
	HttpMgr();
	QNetworkAccessManager _manager;
	std::queue<QueData> _que;

private slots:
	void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
	void slot_http_get_image_finish(ReqId id, QByteArray res, ErrorCodes err, Modules mod);
signals:
	void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
	void sig_http_get_image_finish(ReqId id, QByteArray res, ErrorCodes err, Modules mod);
	void sig_test_mod_finish(ReqId id, QString res, ErrorCodes err);
	void sig_addfdc_mod_finish(ReqId id, QString res, ErrorCodes err);
	void sig_getpatientdata_mod_finish(ReqId id, QString res, ErrorCodes err);
	void sig_getPatientViewWoundImage_mod_finish(ReqId id, QByteArray  res, ErrorCodes err);
};

