#include "HttpMgr.h"
#ifdef WIN64  
#pragma execution_character_set("utf-8")  
#endif
HttpMgr::~HttpMgr()
{
}
HttpMgr::HttpMgr()
{
	connect(this, &HttpMgr::sig_http_finish, this, &HttpMgr::slot_http_finish);
	connect(this, &HttpMgr::sig_http_get_image_finish, this, &HttpMgr::slot_http_get_image_finish);
}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)
{
	QByteArray data = QJsonDocument(json).toJson();
	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));

	auto self = shared_from_this();

	QNetworkReply* reply = _manager.post(request,data);
	QObject::connect(reply, &QNetworkReply::finished, [self, reply, req_id, mod]() {
		if (reply->error() != QNetworkReply::NoError)
		{
			qDebug() << reply->errorString();
			emit self->sig_http_finish(req_id, "", ErrorCodes::ERR_NETWORK, mod);
			reply->deleteLater();
			return;
		}
		QString res = reply->readAll();
		emit self->sig_http_finish(req_id, res, ErrorCodes::SUCCESS, mod);
		reply->deleteLater();
		return;
	});
}

void HttpMgr::GetImageHttpReq(QUrl url, ReqId req_id, Modules mod)
{
	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

	auto self = shared_from_this();

	QNetworkReply* reply = _manager.get(request);
	QObject::connect(reply, &QNetworkReply::finished, [self, reply, req_id, mod]() {
		if (reply->error() != QNetworkReply::NoError)
		{
			qDebug() << reply->errorString();
			emit self->sig_http_get_image_finish(req_id, "", ErrorCodes::ERR_NETWORK, mod);
			reply->deleteLater();
			return;
		}
		QByteArray res = reply->readAll();
		emit self->sig_http_get_image_finish(req_id, res, ErrorCodes::SUCCESS, mod);
		reply->deleteLater();
		return;
		});
}

void HttpMgr::slot_http_get_image_finish(ReqId id, QByteArray res, ErrorCodes err, Modules mod)
{
	qDebug() << "http_get_image_finish";
	switch (mod)
	{
	case Modules::ReqPatientViewWoundImage:
	{
		qDebug() << "ReqPatientViewWoundImage";
		emit sig_getPatientViewWoundImage_mod_finish(id, res, err);
		if(!_que.empty())_que.pop();
		if (_que.size() > 0)
		{
			auto tq = _que.front();
			GetImageHttpReq(tq.url,tq.req_id,tq.mod);
		}
	}
	default:
		break;
	}
	return;
}


void HttpMgr::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod)
{
	qDebug() << "http finish";
	switch (mod)
	{
		case Modules::ModTEST:
		{
			qDebug() << "TEST success" << "err solve by other widget ";
			qDebug() << res;
			QJsonDocument json = QJsonDocument::fromJson(res.toUtf8());
			qDebug() << json;
			emit sig_test_mod_finish(id, res, err);
			break;
		}
		case Modules::ReqAddfdc:
		{
			qDebug() << "AddSqlData";
			qDebug() << res;
			emit sig_addfdc_mod_finish(id, res, err);
			break;
		}
		case Modules::ReqPatientData:
		{
			qDebug() << "GetUserdata";
			//qDebug() << res;
			emit sig_getpatientdata_mod_finish(id, res, err);
		}
		default:
			break;
	}
	return;
}
