/****************************************************************************
** Meta object code from reading C++ file 'YmodemFileTransmit.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../YmodemFileTransmit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'YmodemFileTransmit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_YmodemFileTransmit_t {
    uint offsetsAndSizes[18];
    char stringdata0[19];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[15];
    char stringdata5[27];
    char stringdata6[7];
    char stringdata7[12];
    char stringdata8[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_YmodemFileTransmit_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_YmodemFileTransmit_t qt_meta_stringdata_YmodemFileTransmit = {
    {
        QT_MOC_LITERAL(0, 18),  // "YmodemFileTransmit"
        QT_MOC_LITERAL(19, 16),  // "transmitProgress"
        QT_MOC_LITERAL(36, 0),  // ""
        QT_MOC_LITERAL(37, 8),  // "progress"
        QT_MOC_LITERAL(46, 14),  // "transmitStatus"
        QT_MOC_LITERAL(61, 26),  // "YmodemFileTransmit::Status"
        QT_MOC_LITERAL(88, 6),  // "status"
        QT_MOC_LITERAL(95, 11),  // "readTimeOut"
        QT_MOC_LITERAL(107, 12)   // "writeTimeOut"
    },
    "YmodemFileTransmit",
    "transmitProgress",
    "",
    "progress",
    "transmitStatus",
    "YmodemFileTransmit::Status",
    "status",
    "readTimeOut",
    "writeTimeOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_YmodemFileTransmit[] = {

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

void YmodemFileTransmit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<YmodemFileTransmit *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->transmitProgress((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->transmitStatus((*reinterpret_cast< std::add_pointer_t<YmodemFileTransmit::Status>>(_a[1]))); break;
        case 2: _t->readTimeOut(); break;
        case 3: _t->writeTimeOut(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (YmodemFileTransmit::*)(int );
            if (_t _q_method = &YmodemFileTransmit::transmitProgress; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (YmodemFileTransmit::*)(YmodemFileTransmit::Status );
            if (_t _q_method = &YmodemFileTransmit::transmitStatus; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject YmodemFileTransmit::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_YmodemFileTransmit.offsetsAndSizes,
    qt_meta_data_YmodemFileTransmit,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_YmodemFileTransmit_t
, QtPrivate::TypeAndForceComplete<YmodemFileTransmit, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<YmodemFileTransmit::Status, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *YmodemFileTransmit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *YmodemFileTransmit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_YmodemFileTransmit.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Ymodem"))
        return static_cast< Ymodem*>(this);
    return QObject::qt_metacast(_clname);
}

int YmodemFileTransmit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void YmodemFileTransmit::transmitProgress(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void YmodemFileTransmit::transmitStatus(YmodemFileTransmit::Status _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
