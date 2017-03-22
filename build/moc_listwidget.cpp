/****************************************************************************
** Meta object code from reading C++ file 'listwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/listwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'listwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ListWidget_t {
    QByteArrayData data[14];
    char stringdata0[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ListWidget_t qt_meta_stringdata_ListWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ListWidget"
QT_MOC_LITERAL(1, 11, 9), // "openFiles"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 9), // "dropEvent"
QT_MOC_LITERAL(4, 32, 11), // "QDropEvent*"
QT_MOC_LITERAL(5, 44, 2), // "ev"
QT_MOC_LITERAL(6, 47, 14), // "dragEnterEvent"
QT_MOC_LITERAL(7, 62, 16), // "QDragEnterEvent*"
QT_MOC_LITERAL(8, 79, 13), // "dragMoveEvent"
QT_MOC_LITERAL(9, 93, 15), // "QDragMoveEvent*"
QT_MOC_LITERAL(10, 109, 5), // "event"
QT_MOC_LITERAL(11, 115, 14), // "dragLeaveEvent"
QT_MOC_LITERAL(12, 130, 16), // "QDragLeaveEvent*"
QT_MOC_LITERAL(13, 147, 8) // "_addItem"

    },
    "ListWidget\0openFiles\0\0dropEvent\0"
    "QDropEvent*\0ev\0dragEnterEvent\0"
    "QDragEnterEvent*\0dragMoveEvent\0"
    "QDragMoveEvent*\0event\0dragLeaveEvent\0"
    "QDragLeaveEvent*\0_addItem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ListWidget[] = {

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
       3,    1,   47,    2, 0x0a /* Public */,
       6,    1,   50,    2, 0x0a /* Public */,
       8,    1,   53,    2, 0x0a /* Public */,
      11,    1,   56,    2, 0x0a /* Public */,
      13,    1,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QStringList,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    5,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,   10,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void ListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ListWidget *_t = static_cast<ListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openFiles((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 1: _t->dropEvent((*reinterpret_cast< QDropEvent*(*)>(_a[1]))); break;
        case 2: _t->dragEnterEvent((*reinterpret_cast< QDragEnterEvent*(*)>(_a[1]))); break;
        case 3: _t->dragMoveEvent((*reinterpret_cast< QDragMoveEvent*(*)>(_a[1]))); break;
        case 4: _t->dragLeaveEvent((*reinterpret_cast< QDragLeaveEvent*(*)>(_a[1]))); break;
        case 5: _t->_addItem((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ListWidget::*_t)(QStringList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ListWidget::openFiles)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject ListWidget::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata_ListWidget.data,
      qt_meta_data_ListWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ListWidget.stringdata0))
        return static_cast<void*>(const_cast< ListWidget*>(this));
    return QListWidget::qt_metacast(_clname);
}

int ListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
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
void ListWidget::openFiles(QStringList _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
