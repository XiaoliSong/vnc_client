/****************************************************************************
** Meta object code from reading C++ file 'vnc_app.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../vnc_app.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vnc_app.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Vnc_app_t {
    QByteArrayData data[11];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Vnc_app_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Vnc_app_t qt_meta_stringdata_Vnc_app = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Vnc_app"
QT_MOC_LITERAL(1, 8, 6), // "to_app"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 3), // "msg"
QT_MOC_LITERAL(4, 20, 9), // "onRunStop"
QT_MOC_LITERAL(5, 30, 6), // "is_run"
QT_MOC_LITERAL(6, 37, 8), // "onClosed"
QT_MOC_LITERAL(7, 46, 11), // "onConnected"
QT_MOC_LITERAL(8, 58, 21), // "onTextMessageReceived"
QT_MOC_LITERAL(9, 80, 7), // "message"
QT_MOC_LITERAL(10, 88, 23) // "onBinaryMessageReceived"

    },
    "Vnc_app\0to_app\0\0msg\0onRunStop\0is_run\0"
    "onClosed\0onConnected\0onTextMessageReceived\0"
    "message\0onBinaryMessageReceived"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Vnc_app[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   47,    2, 0x0a /* Public */,
       6,    0,   50,    2, 0x08 /* Private */,
       7,    0,   51,    2, 0x08 /* Private */,
       8,    1,   52,    2, 0x08 /* Private */,
      10,    1,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QByteArray,    9,

       0        // eod
};

void Vnc_app::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Vnc_app *_t = static_cast<Vnc_app *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->to_app((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->onRunStop((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->onClosed(); break;
        case 3: _t->onConnected(); break;
        case 4: _t->onTextMessageReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->onBinaryMessageReceived((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Vnc_app::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Vnc_app::to_app)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Vnc_app::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Vnc_app.data,
      qt_meta_data_Vnc_app,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Vnc_app::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Vnc_app::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Vnc_app.stringdata0))
        return static_cast<void*>(const_cast< Vnc_app*>(this));
    return QObject::qt_metacast(_clname);
}

int Vnc_app::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Vnc_app::to_app(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
