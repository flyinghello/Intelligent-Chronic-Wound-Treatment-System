/****************************************************************************
** Meta object code from reading C++ file 'T_Addfdc.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../T_Addfdc.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'T_Addfdc.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASST_AddfdcENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASST_AddfdcENDCLASS = QtMocHelpers::stringData(
    "T_Addfdc",
    "addtablesqldata",
    "",
    "slot_addfdc_mod_finish",
    "ReqId",
    "id",
    "res",
    "ErrorCodes",
    "err",
    "getimage64list",
    "QStringList*",
    "imagebase64list",
    "addsqldata",
    "addimage"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASST_AddfdcENDCLASS_t {
    uint offsetsAndSizes[28];
    char stringdata0[9];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[23];
    char stringdata4[6];
    char stringdata5[3];
    char stringdata6[4];
    char stringdata7[11];
    char stringdata8[4];
    char stringdata9[15];
    char stringdata10[13];
    char stringdata11[16];
    char stringdata12[11];
    char stringdata13[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASST_AddfdcENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASST_AddfdcENDCLASS_t qt_meta_stringdata_CLASST_AddfdcENDCLASS = {
    {
        QT_MOC_LITERAL(0, 8),  // "T_Addfdc"
        QT_MOC_LITERAL(9, 15),  // "addtablesqldata"
        QT_MOC_LITERAL(25, 0),  // ""
        QT_MOC_LITERAL(26, 22),  // "slot_addfdc_mod_finish"
        QT_MOC_LITERAL(49, 5),  // "ReqId"
        QT_MOC_LITERAL(55, 2),  // "id"
        QT_MOC_LITERAL(58, 3),  // "res"
        QT_MOC_LITERAL(62, 10),  // "ErrorCodes"
        QT_MOC_LITERAL(73, 3),  // "err"
        QT_MOC_LITERAL(77, 14),  // "getimage64list"
        QT_MOC_LITERAL(92, 12),  // "QStringList*"
        QT_MOC_LITERAL(105, 15),  // "imagebase64list"
        QT_MOC_LITERAL(121, 10),  // "addsqldata"
        QT_MOC_LITERAL(132, 8)   // "addimage"
    },
    "T_Addfdc",
    "addtablesqldata",
    "",
    "slot_addfdc_mod_finish",
    "ReqId",
    "id",
    "res",
    "ErrorCodes",
    "err",
    "getimage64list",
    "QStringList*",
    "imagebase64list",
    "addsqldata",
    "addimage"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASST_AddfdcENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    3,   45,    2, 0x0a,    2 /* Public */,
       9,    1,   52,    2, 0x0a,    6 /* Public */,
      12,    0,   55,    2, 0x0a,    8 /* Public */,
      13,    0,   56,    2, 0x0a,    9 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4, QMetaType::QString, 0x80000000 | 7,    5,    6,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject T_Addfdc::staticMetaObject = { {
    QMetaObject::SuperData::link<T_BasePage::staticMetaObject>(),
    qt_meta_stringdata_CLASST_AddfdcENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASST_AddfdcENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASST_AddfdcENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<T_Addfdc, std::true_type>,
        // method 'addtablesqldata'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_addfdc_mod_finish'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<ReqId, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<ErrorCodes, std::false_type>,
        // method 'getimage64list'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QStringList *, std::false_type>,
        // method 'addsqldata'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addimage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void T_Addfdc::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<T_Addfdc *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addtablesqldata(); break;
        case 1: _t->slot_addfdc_mod_finish((*reinterpret_cast< std::add_pointer_t<ReqId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<ErrorCodes>>(_a[3]))); break;
        case 2: _t->getimage64list((*reinterpret_cast< std::add_pointer_t<QStringList*>>(_a[1]))); break;
        case 3: _t->addsqldata(); break;
        case 4: _t->addimage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (T_Addfdc::*)();
            if (_t _q_method = &T_Addfdc::addtablesqldata; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *T_Addfdc::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *T_Addfdc::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASST_AddfdcENDCLASS.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "std::enable_shared_from_this<T_Addfdc>"))
        return static_cast< std::enable_shared_from_this<T_Addfdc>*>(this);
    return T_BasePage::qt_metacast(_clname);
}

int T_Addfdc::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = T_BasePage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void T_Addfdc::addtablesqldata()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
