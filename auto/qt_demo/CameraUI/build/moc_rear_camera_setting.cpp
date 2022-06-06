/****************************************************************************
** Meta object code from reading C++ file 'rear_camera_setting.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/rear_camera_setting.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rear_camera_setting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Rear_Camera_Setting_t {
    QByteArrayData data[6];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Rear_Camera_Setting_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Rear_Camera_Setting_t qt_meta_stringdata_Rear_Camera_Setting = {
    {
QT_MOC_LITERAL(0, 0, 19), // "Rear_Camera_Setting"
QT_MOC_LITERAL(1, 20, 23), // "on_returnButton_clicked"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 21), // "on_sureButton_clicked"
QT_MOC_LITERAL(4, 67, 22), // "on_upperButton_clicked"
QT_MOC_LITERAL(5, 90, 21) // "on_downButton_clicked"

    },
    "Rear_Camera_Setting\0on_returnButton_clicked\0"
    "\0on_sureButton_clicked\0on_upperButton_clicked\0"
    "on_downButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Rear_Camera_Setting[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       3,    1,   37,    2, 0x0a /* Public */,
       4,    1,   40,    2, 0x0a /* Public */,
       5,    1,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void Rear_Camera_Setting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Rear_Camera_Setting *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_returnButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_sureButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_upperButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_downButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Rear_Camera_Setting::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_Rear_Camera_Setting.data,
    qt_meta_data_Rear_Camera_Setting,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Rear_Camera_Setting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Rear_Camera_Setting::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Rear_Camera_Setting.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Rear_Camera_Setting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
