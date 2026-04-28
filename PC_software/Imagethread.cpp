#include "Imagethread.h"
#include <QBuffer>
#include <QPixmap>
Imagethread::Imagethread(const QStringList imagelist, QObject* parent):
	QObject(parent), QRunnable(), imagelist(imagelist)
{
	setAutoDelete(false);
}

Imagethread::~Imagethread()
{
	if (imagebase64list != nullptr) delete imagebase64list;
	qDebug() << "imagethread end";
}

QStringList* Imagethread::imageswitchbase64()
{
	imagebase64list = new QStringList();
	if (this->imagelist.size() > 0)
	{
		for (QString imageurl : this->imagelist)
		{
			QPixmap tpimage(imageurl);
			QByteArray byteArray;
			QBuffer buffer(&byteArray);
			buffer.open(QIODevice::WriteOnly);
			tpimage.save(&buffer, "JPG");
			QString base64Data = byteArray.toBase64();
			imagebase64list->append(base64Data);
			qDebug() <<"size:" << imagebase64list->size();
		}
		return imagebase64list;
	}
	return nullptr;
}

void Imagethread::run()
{
	qDebug() << "run";
	QStringList* imagebase64list=imageswitchbase64();
	if (imagebase64list != nullptr)
	{
		qDebug() << "size:" << imagebase64list->size();
	}
	if (_bstop)
	{
		delete imagebase64list;
		return;
	}
	emit SigFinishImageSwitchBase64(imagebase64list);
}
