#ifndef T_BASEPAGE_H
#define T_BASEPAGE_H

#include <ElaScrollPage.h>
#include "ElaPromotionCard.h"
#include "ElaPromotionView.h"
#include "ElaPopularCard.h"
#include "ElaFlowLayout.h"
#include "PatientInfoWidget.h"
class QVBoxLayout;

class T_BasePage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit T_BasePage(QWidget* parent = nullptr);
    ~T_BasePage();
    void addtopbutton(QWidget* abutton);
    void addimageview(ElaPromotionView *imageview);
    void adduserview(ElaPopularCard* userCard);
    void addintroduce(PatientInfoWidget* patientinfowidget);
protected:
    void createCustomWidget(QString desText);
private:
    QHBoxLayout* _buttonLayout;
    QHBoxLayout* _imageviewLayout;
    ElaFlowLayout* _userLayout;
    QHBoxLayout* _introduceLayout;
};

#endif // T_BASEPAGE_H
