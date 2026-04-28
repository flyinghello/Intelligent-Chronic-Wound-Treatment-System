#ifndef T_HOME_H
#define T_HOME_H
#pragma once
#include "T_BasePage.h"
#include <QJsonObject>
#include <QJsonDocument>
#include "global.h"
class ElaMenu;
class ElaFlowLayout;
class T_Home : public T_BasePage
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit T_Home(QWidget* parent = nullptr);
    ~T_Home();
    void insertpatient(PatientData userdata);
Q_SIGNALS:
    Q_SIGNAL void elaScreenNavigation();
    Q_SIGNAL void elaBaseComponentNavigation();
    Q_SIGNAL void elaSceneNavigation();
    Q_SIGNAL void elaCardNavigation();
    Q_SIGNAL void elaIconNavigation();

public slots:
    void slot_insert_patientdata(ReqId id, QString res, ErrorCodes err);
protected:
    virtual void mouseReleaseEvent(QMouseEvent* event);

private:
    ElaMenu* _homeMenu{nullptr};
    ElaFlowLayout* _flowLayout{ nullptr };
};

#endif // T_HOME_H
