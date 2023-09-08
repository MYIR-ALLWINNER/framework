/****************************************************************************
** Meta object code from reading C++ file 'pathdeform.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "pathdeform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pathdeform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PathDeformRenderer_t {
    QByteArrayData data[13];
    char stringdata0[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PathDeformRenderer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PathDeformRenderer_t qt_meta_stringdata_PathDeformRenderer = {
    {
QT_MOC_LITERAL(0, 0, 18), // "PathDeformRenderer"
QT_MOC_LITERAL(1, 19, 7), // "clicked"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 9), // "setRadius"
QT_MOC_LITERAL(4, 38, 6), // "radius"
QT_MOC_LITERAL(5, 45, 11), // "setFontSize"
QT_MOC_LITERAL(6, 57, 8), // "fontSize"
QT_MOC_LITERAL(7, 66, 7), // "setText"
QT_MOC_LITERAL(8, 74, 4), // "text"
QT_MOC_LITERAL(9, 79, 12), // "setIntensity"
QT_MOC_LITERAL(10, 92, 9), // "intensity"
QT_MOC_LITERAL(11, 102, 11), // "setAnimated"
QT_MOC_LITERAL(12, 114, 8) // "animated"

    },
    "PathDeformRenderer\0clicked\0\0setRadius\0"
    "radius\0setFontSize\0fontSize\0setText\0"
    "text\0setIntensity\0intensity\0setAnimated\0"
    "animated"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PathDeformRenderer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       5,   60, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   45,    2, 0x0a /* Public */,
       5,    1,   48,    2, 0x0a /* Public */,
       7,    1,   51,    2, 0x0a /* Public */,
       9,    1,   54,    2, 0x0a /* Public */,
      11,    1,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Bool,   12,

 // properties: name, type, flags
      12, QMetaType::Bool, 0x00095103,
       4, QMetaType::Int, 0x00095103,
       6, QMetaType::Int, 0x00095103,
      10, QMetaType::Int, 0x00095103,
       8, QMetaType::QString, 0x00095103,

       0        // eod
};

void PathDeformRenderer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PathDeformRenderer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clicked(); break;
        case 1: _t->setRadius((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setFontSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->setIntensity((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setAnimated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PathDeformRenderer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathDeformRenderer::clicked)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<PathDeformRenderer *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->animated(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->radius(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->fontSize(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->intensity(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->text(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<PathDeformRenderer *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setAnimated(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->setRadius(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setFontSize(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setIntensity(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setText(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject PathDeformRenderer::staticMetaObject = { {
    &ArthurFrame::staticMetaObject,
    qt_meta_stringdata_PathDeformRenderer.data,
    qt_meta_data_PathDeformRenderer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PathDeformRenderer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PathDeformRenderer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PathDeformRenderer.stringdata0))
        return static_cast<void*>(this);
    return ArthurFrame::qt_metacast(_clname);
}

int PathDeformRenderer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ArthurFrame::qt_metacall(_c, _id, _a);
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
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void PathDeformRenderer::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_PathDeformControls_t {
    QByteArrayData data[4];
    char stringdata0[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PathDeformControls_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PathDeformControls_t qt_meta_stringdata_PathDeformControls = {
    {
QT_MOC_LITERAL(0, 0, 18), // "PathDeformControls"
QT_MOC_LITERAL(1, 19, 9), // "okPressed"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 11) // "quitPressed"

    },
    "PathDeformControls\0okPressed\0\0quitPressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PathDeformControls[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PathDeformControls::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PathDeformControls *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->okPressed(); break;
        case 1: _t->quitPressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PathDeformControls::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathDeformControls::okPressed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PathDeformControls::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PathDeformControls::quitPressed)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject PathDeformControls::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_PathDeformControls.data,
    qt_meta_data_PathDeformControls,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PathDeformControls::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PathDeformControls::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PathDeformControls.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PathDeformControls::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void PathDeformControls::okPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PathDeformControls::quitPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_PathDeformWidget_t {
    QByteArrayData data[4];
    char stringdata0[44];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PathDeformWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PathDeformWidget_t qt_meta_stringdata_PathDeformWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "PathDeformWidget"
QT_MOC_LITERAL(1, 17, 12), // "showControls"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 12) // "hideControls"

    },
    "PathDeformWidget\0showControls\0\0"
    "hideControls"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PathDeformWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x08 /* Private */,
       3,    0,   25,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PathDeformWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PathDeformWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showControls(); break;
        case 1: _t->hideControls(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject PathDeformWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_PathDeformWidget.data,
    qt_meta_data_PathDeformWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PathDeformWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PathDeformWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PathDeformWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PathDeformWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
