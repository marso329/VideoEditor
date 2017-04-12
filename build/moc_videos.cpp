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
    QByteArrayData data[9];
    char stringdata0[98];
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
QT_MOC_LITERAL(5, 40, 18), // "changeCurrentFrame"
QT_MOC_LITERAL(6, 59, 6), // "Frame*"
QT_MOC_LITERAL(7, 66, 15), // "setCurrentVideo"
QT_MOC_LITERAL(8, 82, 15) // "newCurrentFrame"

    },
    "Videos\0newVideo\0\0newCurrentVideo\0"
    "Video*\0changeCurrentFrame\0Frame*\0"
    "setCurrentVideo\0newCurrentFrame"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Videos[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    1,   42,    2, 0x06 /* Public */,
       5,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   48,    2, 0x0a /* Public */,
       8,    1,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 6,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Float,    2,

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
        case 2: _t->changeCurrentFrame((*reinterpret_cast< Frame*(*)>(_a[1]))); break;
        case 3: _t->setCurrentVideo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->newCurrentFrame((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Video* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Frame* >(); break;
            }
            break;
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
        {
            typedef void (Videos::*_t)(Frame * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Videos::changeCurrentFrame)) {
                *result = 2;
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
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
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

// SIGNAL 2
void Videos::changeCurrentFrame(Frame * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
