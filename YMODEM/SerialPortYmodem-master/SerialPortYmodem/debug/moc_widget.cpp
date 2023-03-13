/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    uint offsetsAndSizes[30];
    char stringdata0[7];
    char stringdata1[21];
    char stringdata2[1];
    char stringdata3[26];
    char stringdata4[25];
    char stringdata5[26];
    char stringdata6[25];
    char stringdata7[17];
    char stringdata8[9];
    char stringdata9[16];
    char stringdata10[15];
    char stringdata11[27];
    char stringdata12[7];
    char stringdata13[14];
    char stringdata14[26];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_Widget_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
        QT_MOC_LITERAL(0, 6),  // "Widget"
        QT_MOC_LITERAL(7, 20),  // "on_comButton_clicked"
        QT_MOC_LITERAL(28, 0),  // ""
        QT_MOC_LITERAL(29, 25),  // "on_transmitBrowse_clicked"
        QT_MOC_LITERAL(55, 24),  // "on_receiveBrowse_clicked"
        QT_MOC_LITERAL(80, 25),  // "on_transmitButton_clicked"
        QT_MOC_LITERAL(106, 24),  // "on_receiveButton_clicked"
        QT_MOC_LITERAL(131, 16),  // "transmitProgress"
        QT_MOC_LITERAL(148, 8),  // "progress"
        QT_MOC_LITERAL(157, 15),  // "receiveProgress"
        QT_MOC_LITERAL(173, 14),  // "transmitStatus"
        QT_MOC_LITERAL(188, 26),  // "YmodemFileTransmit::Status"
        QT_MOC_LITERAL(215, 6),  // "status"
        QT_MOC_LITERAL(222, 13),  // "receiveStatus"
        QT_MOC_LITERAL(236, 25)   // "YmodemFileReceive::Status"
    },
    "Widget",
    "on_comButton_clicked",
    "",
    "on_transmitBrowse_clicked",
    "on_receiveBrowse_clicked",
    "on_transmitButton_clicked",
    "on_receiveButton_clicked",
    "transmitProgress",
    "progress",
    "receiveProgress",
    "transmitStatus",
    "YmodemFileTransmit::Status",
    "status",
    "receiveStatus",
    "YmodemFileReceive::Status"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x08,    1 /* Private */,
       3,    0,   69,    2, 0x08,    2 /* Private */,
       4,    0,   70,    2, 0x08,    3 /* Private */,
       5,    0,   71,    2, 0x08,    4 /* Private */,
       6,    0,   72,    2, 0x08,    5 /* Private */,
       7,    1,   73,    2, 0x08,    6 /* Private */,
       9,    1,   76,    2, 0x08,    8 /* Private */,
      10,    1,   79,    2, 0x08,   10 /* Private */,
      13,    1,   82,    2, 0x08,   12 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14,   12,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_comButton_clicked(); break;
        case 1: _t->on_transmitBrowse_clicked(); break;
        case 2: _t->on_receiveBrowse_clicked(); break;
        case 3: _t->on_transmitButton_clicked(); break;
        case 4: _t->on_receiveButton_clicked(); break;
        case 5: _t->transmitProgress((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->receiveProgress((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->transmitStatus((*reinterpret_cast< std::add_pointer_t<YmodemFileTransmit::Status>>(_a[1]))); break;
        case 8: _t->receiveStatus((*reinterpret_cast< std::add_pointer_t<YmodemFileReceive::Status>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Widget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Widget.offsetsAndSizes,
    qt_meta_data_Widget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Widget_t
, QtPrivate::TypeAndForceComplete<Widget, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<YmodemFileTransmit::Status, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<YmodemFileReceive::Status, std::false_type>


>,
    nullptr
} };


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
