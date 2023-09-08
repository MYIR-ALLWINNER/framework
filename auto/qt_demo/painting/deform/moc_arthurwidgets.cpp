/****************************************************************************
** Meta object code from reading C++ file 'arthurwidgets.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../shared/arthurwidgets.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'arthurwidgets.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ArthurFrame_t {
    QByteArrayData data[11];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ArthurFrame_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ArthurFrame_t qt_meta_stringdata_ArthurFrame = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ArthurFrame"
QT_MOC_LITERAL(1, 12, 25), // "descriptionEnabledChanged"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 14), // "setPreferImage"
QT_MOC_LITERAL(4, 54, 2), // "pi"
QT_MOC_LITERAL(5, 57, 21), // "setDescriptionEnabled"
QT_MOC_LITERAL(6, 79, 7), // "enabled"
QT_MOC_LITERAL(7, 87, 10), // "showSource"
QT_MOC_LITERAL(8, 98, 12), // "enableOpenGL"
QT_MOC_LITERAL(9, 111, 10), // "use_opengl"
QT_MOC_LITERAL(10, 122, 10) // "usesOpenGL"

    },
    "ArthurFrame\0descriptionEnabledChanged\0"
    "\0setPreferImage\0pi\0setDescriptionEnabled\0"
    "enabled\0showSource\0enableOpenGL\0"
    "use_opengl\0usesOpenGL"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ArthurFrame[] = {

 // content:
       8,       // revision
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
       5,    1,   50,    2, 0x0a /* Public */,
       7,    0,   53,    2, 0x0a /* Public */,
       8,    1,   54,    2, 0x0a /* Public */,
      10,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Bool,

       0        // eod
};

void ArthurFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ArthurFrame *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->descriptionEnabledChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setPreferImage((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->setDescriptionEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->showSource(); break;
        case 4: _t->enableOpenGL((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: { bool _r = _t->usesOpenGL();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ArthurFrame::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ArthurFrame::descriptionEnabledChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ArthurFrame::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ArthurFrame.data,
    qt_meta_data_ArthurFrame,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ArthurFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ArthurFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ArthurFrame.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ArthurFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void ArthurFrame::descriptionEnabledChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
