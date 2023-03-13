/****************************************************************************
** Meta object code from reading C++ file 'YmodemFileReceive.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../YmodemFileReceive.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'YmodemFileReceive.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_YmodemFileReceive_t {
    uint offsetsAndSizes[18];
    char stringdata0[18];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[14];
    char stringdata5[26];
    char stringdata6[7];
    char stringdata7[12];
    char stringdata8[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_YmodemFileReceive_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_YmodemFileReceive_t qt_meta_stringdata_YmodemFileReceive = {
    {
        QT_MOC_LITERAL(0, 17),  // "YmodemFileReceive"
        QT_MOC_LITERAL(18, 15),  // "receiveProgress"
        QT_MOC_LITERAL(34, 0),  // ""
        QT_MOC_LITERAL(35, 8),  // "progress"
        QT_MOC_LITERAL(44, 13),  // "receiveStatus"
        QT_MOC_LITERAL(58, 25),  // "YmodemFileReceive::Status"
        QT_MOC_LITERAL(84, 6),  // "status"
        QT_MOC_LITERAL(91, 11),  // "readTimeOut"
        QT_MOC_LITERAL(103, 12)   // "writeTimeOut"
    },
    "YmodemFileReceive",
    "receiveProgress",
    "",
    "progress",
    "receiveStatus",
    "YmodemFileReceive::Status",
    "status",
    "readTimeOut",
    "writeTimeOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_YmodemFileReceive[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    1 /* Public */,
       4,    1,   41,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,   44,    2, 0x08,    5 /* Private */,
       8,    0,   45,    2, 0x08,    6 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void YmodemFileReceive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<YmodemFileReceive *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->receiveProgress((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->receiveStatus((*reinterpret_cast< std::add_pointer_t<YmodemFileReceive::Status>>(_a[1]))); break;
        case 2: _t->readTimeOut(); break;
        case 3: _t->writeTimeOut(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (YmodemFileReceive::*)(int );
            if (_t _q_method = &YmodemFileReceive::receiveProgress; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (YmodemFileReceive::*)(YmodemFileReceive::Status );
            if (_t _q_method = &YmodemFileReceive::receiveStatus; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject YmodemFileReceive::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_YmodemFileReceive.offsetsAndSizes,
    qt_meta_data_YmodemFileReceive,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_YmodemFileReceive_t
, QtPrivate::TypeAndForceComplete<YmodemFileReceive, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<YmodemFileReceive::Status, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *YmodemFileReceive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *YmodemFileReceive::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_YmodemFileReceive.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Ymodem"))
        return static_cast< Ymodem*>(this);
    return QObject::qt_metacast(_clname);
}

int YmodemFileReceive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void YmodemFileReceive::receiveProgress(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void YmodemFileReceive::receiveStatus(YmodemFileReceive::Status _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
