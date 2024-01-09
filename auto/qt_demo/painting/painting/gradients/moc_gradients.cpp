/****************************************************************************
** Meta object code from reading C++ file 'gradients.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gradients.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gradients.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ShadeWidget_t {
    QByteArrayData data[3];
    char stringdata0[27];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ShadeWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ShadeWidget_t qt_meta_stringdata_ShadeWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ShadeWidget"
QT_MOC_LITERAL(1, 12, 13), // "colorsChanged"
QT_MOC_LITERAL(2, 26, 0) // ""

    },
    "ShadeWidget\0colorsChanged\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ShadeWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void ShadeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ShadeWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->colorsChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ShadeWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ShadeWidget::colorsChanged)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ShadeWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ShadeWidget.data,
    qt_meta_data_ShadeWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ShadeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShadeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ShadeWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ShadeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void ShadeWidget::colorsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_GradientEditor_t {
    QByteArrayData data[6];
    char stringdata0[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GradientEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GradientEditor_t qt_meta_stringdata_GradientEditor = {
    {
QT_MOC_LITERAL(0, 0, 14), // "GradientEditor"
QT_MOC_LITERAL(1, 15, 20), // "gradientStopsChanged"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 14), // "QGradientStops"
QT_MOC_LITERAL(4, 52, 5), // "stops"
QT_MOC_LITERAL(5, 58, 13) // "pointsUpdated"

    },
    "GradientEditor\0gradientStopsChanged\0"
    "\0QGradientStops\0stops\0pointsUpdated"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GradientEditor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void GradientEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GradientEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->gradientStopsChanged((*reinterpret_cast< const QGradientStops(*)>(_a[1]))); break;
        case 1: _t->pointsUpdated(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GradientEditor::*)(const QGradientStops & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GradientEditor::gradientStopsChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GradientEditor::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_GradientEditor.data,
    qt_meta_data_GradientEditor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GradientEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GradientEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GradientEditor.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GradientEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void GradientEditor::gradientStopsChanged(const QGradientStops & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_GradientRenderer_t {
    QByteArrayData data[11];
    char stringdata0[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GradientRenderer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GradientRenderer_t qt_meta_stringdata_GradientRenderer = {
    {
QT_MOC_LITERAL(0, 0, 16), // "GradientRenderer"
QT_MOC_LITERAL(1, 17, 16), // "setGradientStops"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 14), // "QGradientStops"
QT_MOC_LITERAL(4, 50, 5), // "stops"
QT_MOC_LITERAL(5, 56, 12), // "setPadSpread"
QT_MOC_LITERAL(6, 69, 15), // "setRepeatSpread"
QT_MOC_LITERAL(7, 85, 16), // "setReflectSpread"
QT_MOC_LITERAL(8, 102, 17), // "setLinearGradient"
QT_MOC_LITERAL(9, 120, 17), // "setRadialGradient"
QT_MOC_LITERAL(10, 138, 18) // "setConicalGradient"

    },
    "GradientRenderer\0setGradientStops\0\0"
    "QGradientStops\0stops\0setPadSpread\0"
    "setRepeatSpread\0setReflectSpread\0"
    "setLinearGradient\0setRadialGradient\0"
    "setConicalGradient"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GradientRenderer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x0a /* Public */,
       9,    0,   56,    2, 0x0a /* Public */,
      10,    0,   57,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GradientRenderer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GradientRenderer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setGradientStops((*reinterpret_cast< const QGradientStops(*)>(_a[1]))); break;
        case 1: _t->setPadSpread(); break;
        case 2: _t->setRepeatSpread(); break;
        case 3: _t->setReflectSpread(); break;
        case 4: _t->setLinearGradient(); break;
        case 5: _t->setRadialGradient(); break;
        case 6: _t->setConicalGradient(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GradientRenderer::staticMetaObject = { {
    &ArthurFrame::staticMetaObject,
    qt_meta_stringdata_GradientRenderer.data,
    qt_meta_data_GradientRenderer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GradientRenderer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GradientRenderer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GradientRenderer.stringdata0))
        return static_cast<void*>(this);
    return ArthurFrame::qt_metacast(_clname);
}

int GradientRenderer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ArthurFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
struct qt_meta_stringdata_GradientWidget_t {
    QByteArrayData data[9];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GradientWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GradientWidget_t qt_meta_stringdata_GradientWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "GradientWidget"
QT_MOC_LITERAL(1, 15, 11), // "setDefault1"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 11), // "setDefault2"
QT_MOC_LITERAL(4, 40, 11), // "setDefault3"
QT_MOC_LITERAL(5, 52, 11), // "setDefault4"
QT_MOC_LITERAL(6, 64, 9), // "setPreset"
QT_MOC_LITERAL(7, 74, 13), // "setPrevPreset"
QT_MOC_LITERAL(8, 88, 13) // "setNextPreset"

    },
    "GradientWidget\0setDefault1\0\0setDefault2\0"
    "setDefault3\0setDefault4\0setPreset\0"
    "setPrevPreset\0setNextPreset"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GradientWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GradientWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GradientWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setDefault1(); break;
        case 1: _t->setDefault2(); break;
        case 2: _t->setDefault3(); break;
        case 3: _t->setDefault4(); break;
        case 4: _t->setPreset(); break;
        case 5: _t->setPrevPreset(); break;
        case 6: _t->setNextPreset(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject GradientWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_GradientWidget.data,
    qt_meta_data_GradientWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GradientWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GradientWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GradientWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GradientWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
