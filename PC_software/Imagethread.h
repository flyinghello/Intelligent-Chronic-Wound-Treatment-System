#pragma once
//#include <QThread>
#include <QRunnable>
#include <QObject>
#include "global.h"
class Imagethread:public QObject, public QRunnable,std::enable_shared_from_this<Imagethread>
{
	Q_OBJECT
public:
	Imagethread(const QStringList imagelist,QObject *parent=nullptr);
	~Imagethread();
	QStringList* imageswitchbase64();
protected:
	virtual void run();
private:
	QStringList* imagebase64list=nullptr;
	bool _bstop=false;
	QStringList imagelist;
signals:
	void SigFinishImageSwitchBase64(QStringList* imagebase64list);
};

