#pragma once

#include "T_BasePage.h"
#include "ui_PatientShow.h"
#include <QJsonObject>
#include <QJsonDocument>
#include "global.h"
class ElaMenu;
class ElaFlowLayout;
QT_BEGIN_NAMESPACE
namespace Ui { class PatientShowClass; };
QT_END_NAMESPACE

class PatientShow : public T_BasePage, public std::enable_shared_from_this<PatientShow>
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit PatientShow(QWidget* parent = nullptr);
    ~PatientShow();
    void insertpatient(std::shared_ptr<PatientData> userdata);
Q_SIGNALS:
    Q_SIGNAL void elaScreenNavigation();
    Q_SIGNAL void elaBaseComponentNavigation();
    Q_SIGNAL void elaSceneNavigation();
    Q_SIGNAL void elaCardNavigation();
    Q_SIGNAL void elaIconNavigation();
signals:
    void elaTabViewNavigation(std::shared_ptr<PatientData> patientdata);

public slots:
    void slot_insert_patientdata(ReqId id, QString res, ErrorCodes err);
protected:
    virtual void mouseReleaseEvent(QMouseEvent* event);

private:
    Ui::PatientShowClass* ui;
    ElaMenu* _homeMenu{ nullptr };
    ElaFlowLayout* _flowLayout{ nullptr };
    QMap<QString, QList<std::shared_ptr<PatientData>>> _patientdatemap;
};
