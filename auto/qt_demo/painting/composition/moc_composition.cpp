/****************************************************************************
** Meta object code from reading C++ file 'composition.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "composition.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'composition.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CompositionWidget_t {
    QByteArrayData data[3];
    char stringdata0[28];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CompositionWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CompositionWidget_t qt_meta_stringdata_CompositionWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "CompositionWidget"
QT_MOC_LITERAL(1, 18, 8), // "nextMode"
QT_MOC_LITERAL(2, 27, 0) // ""

    },
    "CompositionWidget\0nextMode\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CompositionWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void CompositionWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CompositionWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->nextMode(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject CompositionWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_CompositionWidget.data,
    qt_meta_data_CompositionWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CompositionWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CompositionWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CompositionWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CompositionWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_CompositionRenderer_t {
    QByteArrayData data[35];
    char stringdata0[493];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CompositionRenderer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CompositionRenderer_t qt_meta_stringdata_CompositionRenderer = {
    {
QT_MOC_LITERAL(0, 0, 19), // "CompositionRenderer"
QT_MOC_LITERAL(1, 20, 12), // "setClearMode"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 13), // "setSourceMode"
QT_MOC_LITERAL(4, 48, 11), // "setDestMode"
QT_MOC_LITERAL(5, 60, 17), // "setSourceOverMode"
QT_MOC_LITERAL(6, 78, 15), // "setDestOverMode"
QT_MOC_LITERAL(7, 94, 15), // "setSourceInMode"
QT_MOC_LITERAL(8, 110, 13), // "setDestInMode"
QT_MOC_LITERAL(9, 124, 16), // "setSourceOutMode"
QT_MOC_LITERAL(10, 141, 14), // "setDestOutMode"
QT_MOC_LITERAL(11, 156, 17), // "setSourceAtopMode"
QT_MOC_LITERAL(12, 174, 15), // "setDestAtopMode"
QT_MOC_LITERAL(13, 190, 10), // "setXorMode"
QT_MOC_LITERAL(14, 201, 11), // "setPlusMode"
QT_MOC_LITERAL(15, 213, 15), // "setMultiplyMode"
QT_MOC_LITERAL(16, 229, 13), // "setScreenMode"
QT_MOC_LITERAL(17, 243, 14), // "setOverlayMode"
QT_MOC_LITERAL(18, 258, 13), // "setDarkenMode"
QT_MOC_LITERAL(19, 272, 14), // "setLightenMode"
QT_MOC_LITERAL(20, 287, 17), // "setColorDodgeMode"
QT_MOC_LITERAL(21, 305, 16), // "setColorBurnMode"
QT_MOC_LITERAL(22, 322, 16), // "setHardLightMode"
QT_MOC_LITERAL(23, 339, 16), // "setSoftLightMode"
QT_MOC_LITERAL(24, 356, 17), // "setDifferenceMode"
QT_MOC_LITERAL(25, 374, 16), // "setExclusionMode"
QT_MOC_LITERAL(26, 391, 14), // "setCircleAlpha"
QT_MOC_LITERAL(27, 406, 5), // "alpha"
QT_MOC_LITERAL(28, 412, 14), // "setCircleColor"
QT_MOC_LITERAL(29, 427, 3), // "hue"
QT_MOC_LITERAL(30, 431, 19), // "setAnimationEnabled"
QT_MOC_LITERAL(31, 451, 7), // "enabled"
QT_MOC_LITERAL(32, 459, 11), // "circleColor"
QT_MOC_LITERAL(33, 471, 11), // "circleAlpha"
QT_MOC_LITERAL(34, 483, 9) // "animation"

    },
    "CompositionRenderer\0setClearMode\0\0"
    "setSourceMode\0setDestMode\0setSourceOverMode\0"
    "setDestOverMode\0setSourceInMode\0"
    "setDestInMode\0setSourceOutMode\0"
    "setDestOutMode\0setSourceAtopMode\0"
    "setDestAtopMode\0setXorMode\0setPlusMode\0"
    "setMultiplyMode\0setScreenMode\0"
    "setOverlayMode\0setDarkenMode\0"
    "setLightenMode\0setColorDodgeMode\0"
    "setColorBurnMode\0setHardLightMode\0"
    "setSoftLightMode\0setDifferenceMode\0"
    "setExclusionMode\0setCircleAlpha\0alpha\0"
    "setCircleColor\0hue\0setAnimationEnabled\0"
    "enabled\0circleColor\0circleAlpha\0"
    "animation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CompositionRenderer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       3,  182, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  149,    2, 0x0a /* Public */,
       3,    0,  150,    2, 0x0a /* Public */,
       4,    0,  151,    2, 0x0a /* Public */,
       5,    0,  152,    2, 0x0a /* Public */,
       6,    0,  153,    2, 0x0a /* Public */,
       7,    0,  154,    2, 0x0a /* Public */,
       8,    0,  155,    2, 0x0a /* Public */,
       9,    0,  156,    2, 0x0a /* Public */,
      10,    0,  157,    2, 0x0a /* Public */,
      11,    0,  158,    2, 0x0a /* Public */,
      12,    0,  159,    2, 0x0a /* Public */,
      13,    0,  160,    2, 0x0a /* Public */,
      14,    0,  161,    2, 0x0a /* Public */,
      15,    0,  162,    2, 0x0a /* Public */,
      16,    0,  163,    2, 0x0a /* Public */,
      17,    0,  164,    2, 0x0a /* Public */,
      18,    0,  165,    2, 0x0a /* Public */,
      19,    0,  166,    2, 0x0a /* Public */,
      20,    0,  167,    2, 0x0a /* Public */,
      21,    0,  168,    2, 0x0a /* Public */,
      22,    0,  169,    2, 0x0a /* Public */,
      23,    0,  170,    2, 0x0a /* Public */,
      24,    0,  171,    2, 0x0a /* Public */,
      25,    0,  172,    2, 0x0a /* Public */,
      26,    1,  173,    2, 0x0a /* Public */,
      28,    1,  176,    2, 0x0a /* Public */,
      30,    1,  179,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, QMetaType::Bool,   31,

 // properties: name, type, flags
      32, QMetaType::Int, 0x00095103,
      33, QMetaType::Int, 0x00095103,
      34, QMetaType::Bool, 0x00095003,

       0        // eod
};

void CompositionRenderer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CompositionRenderer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setClearMode(); break;
        case 1: _t->setSourceMode(); break;
        case 2: _t->setDestMode(); break;
        case 3: _t->setSourceOverMode(); break;
        case 4: _t->setDestOverMode(); break;
        case 5: _t->setSourceInMode(); break;
        case 6: _t->setDestInMode(); break;
        case 7: _t->setSourceOutMode(); break;
        case 8: _t->setDestOutMode(); break;
        case 9: _t->setSourceAtopMode(); break;
        case 10: _t->setDestAtopMode(); break;
        case 11: _t->setXorMode(); break;
        case 12: _t->setPlusMode(); break;
        case 13: _t->setMultiplyMode(); break;
        case 14: _t->setScreenMode(); break;
        case 15: _t->setOverlayMode(); break;
        case 16: _t->setDarkenMode(); break;
        case 17: _t->setLightenMode(); break;
        case 18: _t->setColorDodgeMode(); break;
        case 19: _t->setColorBurnMode(); break;
        case 20: _t->setHardLightMode(); break;
        case 21: _t->setSoftLightMode(); break;
        case 22: _t->setDifferenceMode(); break;
        case 23: _t->setExclusionMode(); break;
        case 24: _t->setCircleAlpha((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->setCircleColor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->setAnimationEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<CompositionRenderer *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->circleColor(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->circleAlpha(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->animationEnabled(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<CompositionRenderer *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setCircleColor(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setCircleAlpha(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setAnimationEnabled(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject CompositionRenderer::staticMetaObject = { {
    &ArthurFrame::staticMetaObject,
    qt_meta_stringdata_CompositionRenderer.data,
    qt_meta_data_CompositionRenderer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CompositionRenderer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CompositionRenderer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CompositionRenderer.stringdata0))
        return static_cast<void*>(this);
    return ArthurFrame::qt_metacast(_clname);
}

int CompositionRenderer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ArthurFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 27)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 27;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
