/****************************************************************************
** Meta object code from reading C++ file 'videos.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/videos.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videos.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Videos_t {
    QByteArrayData data[6];
    char stringdata0[56];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Videos_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Videos_t qt_meta_stringdata_Videos = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Videos"
QT_MOC_LITERAL(1, 7, 8), // "newVideo"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 15), // "newCurrentVideo"
QT_MOC_LITERAL(4, 33, 6), // "Video*"
QT_MOC_LITERAL(5, 40, 15) // "setCurrentVideo"

    },
    "Videos\0newVideo\0\0newCurrentVideo\0"
    "Video*\0setCurrentVideo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Videos[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       3,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void Videos::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Videos *_t = static_cast<Videos *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newVideo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->newCurrentVideo((*reinterpret_cast< Video*(*)>(_a[1]))); break;
        case 2: _t->setCurrentVideo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Videos::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Videos::newVideo)) {
                *result = 0;
            }
        }
        {
            typedef void (Videos::*_t)(Video * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Videos::newCurrentVideo)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject Videos::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Videos.data,
      qt_meta_data_Videos,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Videos::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Videos::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Videos.stringdata0))
        return static_cast<void*>(const_cast< Videos*>(this));
    return QObject::qt_metacast(_clname);
}

int Videos::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Videos::newVideo(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Videos::newCurrentVideo(Video * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
