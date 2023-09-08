/****************************************************************************
** Meta object code from reading C++ file 'renderarea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "renderarea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'renderarea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RenderArea_t {
    QByteArrayData data[14];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RenderArea_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RenderArea_t qt_meta_stringdata_RenderArea = {
    {
QT_MOC_LITERAL(0, 0, 10), // "RenderArea"
QT_MOC_LITERAL(1, 11, 11), // "setFillRule"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 12), // "Qt::FillRule"
QT_MOC_LITERAL(4, 37, 4), // "rule"
QT_MOC_LITERAL(5, 42, 15), // "setFillGradient"
QT_MOC_LITERAL(6, 58, 6), // "color1"
QT_MOC_LITERAL(7, 65, 6), // "color2"
QT_MOC_LITERAL(8, 72, 11), // "setPenWidth"
QT_MOC_LITERAL(9, 84, 5), // "width"
QT_MOC_LITERAL(10, 90, 11), // "setPenColor"
QT_MOC_LITERAL(11, 102, 5), // "color"
QT_MOC_LITERAL(12, 108, 16), // "setRotationAngle"
QT_MOC_LITERAL(13, 125, 7) // "degrees"

    },
    "RenderArea\0setFillRule\0\0Qt::FillRule\0"
    "rule\0setFillGradient\0color1\0color2\0"
    "setPenWidth\0width\0setPenColor\0color\0"
    "setRotationAngle\0degrees"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RenderArea[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       5,    2,   42,    2, 0x0a /* Public */,
       8,    1,   47,    2, 0x0a /* Public */,
      10,    1,   50,    2, 0x0a /* Public */,
      12,    1,   53,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QColor, QMetaType::QColor,    6,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::QColor,   11,
    QMetaType::Void, QMetaType::Int,   13,

       0        // eod
};

void RenderArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RenderArea *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setFillRule((*reinterpret_cast< Qt::FillRule(*)>(_a[1]))); break;
        case 1: _t->setFillGradient((*reinterpret_cast< const QColor(*)>(_a[1])),(*reinterpret_cast< const QColor(*)>(_a[2]))); break;
        case 2: _t->setPenWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setPenColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 4: _t->setRotationAngle((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RenderArea::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_RenderArea.data,
    qt_meta_data_RenderArea,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RenderArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RenderArea::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RenderArea.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RenderArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
