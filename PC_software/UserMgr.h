#pragma once
#include <QObject>
#include <memory>
#include "singleton.h"
#include "global.h"
class UserMgr :public QObject, public Singleton<UserMgr>,public std::enable_shared_from_this<UserMgr>
{
	Q_OBJECT
public:
	friend class Singleton<UserMgr>;
	~UserMgr() {};
	void SetName(QString name);
	void SetUid(int uid);
	void SetToken(QString token);
	QString GetName() { return this->_name; };
private:
	UserMgr(){};
	QString _name="zjb";
	QString _token;
	int _uid;
};