#pragma once
#include <QNetworkReply>
#include <QNetworkRequest>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <QJsonArray>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
enum ReqId
{
	ReqTEST = 0,
	AddSqlData = 1,
	GetPatientData = 2,
	GetPatientViewWoundImage=3,
	GetPatientNowData=4,
};
enum Modules
{
	ModTEST = 0,
	ReqAddfdc = 1,
	ReqPatientData = 2,
	ReqPatientViewWoundImage = 3,
};
enum  ErrorCodes
{
	SUCCESS = 0,
	ERR_NETWORK=1,
	ERR_JSON=3
};

class  PatientData{
public:
	PatientData()
		: _id(0), _imageurl(""), _introduceurl(""), _introduce(""), _woundimageurl(""), _name(""), _temperaturearray() {}

	PatientData(int id,QString imageurl, QString introduceurl, QString introduce, QString woundimageurl,QString name, QJsonArray temperaturearray,QJsonArray voltagearray)
		:_id(id),_imageurl(imageurl), _introduceurl(introduceurl), 
		_introduce(introduce), _woundimageurl(woundimageurl), 
		_name(name), _temperaturearray(temperaturearray),
		_voltagearray(voltagearray) {};

	int _id;
	QString _imageurl;
	 QString _introduceurl;
	 QString _introduce;
	 QString _woundimageurl;
	 QString _name;
	 QJsonArray _temperaturearray;
	 QJsonArray _voltagearray;
private:

};