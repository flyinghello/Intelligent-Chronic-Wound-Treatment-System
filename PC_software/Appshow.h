#pragma once

#include "ElaWindow.h"
#include "ui_Appshow.h"
#include "ElaApplication.h"
#include "ElaTheme.h"
#include "T_Addfdc.h"
#include "T_Tablefdc.h"
#include "global.h"
QT_BEGIN_NAMESPACE
namespace Ui { class AppshowClass; };
QT_END_NAMESPACE
class T_Home;
class T_Icon;
class T_ElaScreen;
class T_BaseComponents;
class T_Graphics;
class T_Navigation;
class T_Popup;
class T_Card;
class T_ListView;
class T_TableView;
class T_TreeView;
class T_About;
class T_Setting;
class ElaContentDialog;

class T_Tablefdc;
class T_Addfdc;
class PatientShow;
class PatientTabView;
#pragma execution_character_set("utf-8")
#ifdef Q_OS_WIN
#pragma execution_character_set("utf-8") //解决 VS编译器下中文乱码
#endif
class Appshow : public ElaWindow
{
    Q_OBJECT

public:
    Appshow(QWidget* parent = nullptr);
    ~Appshow();
    void initWindow();
    void initEdgeLayout();
    void initContent();

private:
    Ui::AppshowClass* ui;
    ElaContentDialog* _closeDialog{ nullptr };
    T_Addfdc* _addfdc{ nullptr };
    T_Tablefdc* _tablefdc { nullptr };


    T_Home* _homePage{ nullptr };
#ifdef Q_OS_WIN
    T_ElaScreen* _elaScreenPage{ nullptr };
#endif
    T_Icon* _iconPage{ nullptr };
    T_BaseComponents* _baseComponentsPage{ nullptr };
    T_Graphics* _graphicsPage{ nullptr };
    T_Navigation* _navigationPage{ nullptr };
    T_Popup* _popupPage{ nullptr };
    T_Card* _cardPage{ nullptr };
    T_ListView* _listViewPage{ nullptr };
    T_TableView* _tableViewPage{ nullptr };
    T_TreeView* _treeViewPage{ nullptr };
    T_About* _aboutPage{ nullptr };
    T_Setting* _settingPage{ nullptr };
    PatientShow* _patientshow{ nullptr };
    PatientTabView* _patienttabview{nullptr};
    QString _elaDxgiKey{ "" };
    QString _viewKey{ "" };
    QString _aboutKey{ "" };
    QString _settingKey{ "" };
};
