/****************************************************************************
** Meta object code from reading C++ file 'front_adas_setting.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/front_adas_setting.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'front_adas_setting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_front_ADAS_setting_t {
    QByteArrayData data[7];
    char stringdata0[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_front_ADAS_setting_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_front_ADAS_setting_t qt_meta_stringdata_front_ADAS_setting = {
    {
QT_MOC_LITERAL(0, 0, 18), // "front_ADAS_setting"
QT_MOC_LITERAL(1, 19, 14), // "unHideSettings"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 21), // "on_nextButton_clicked"
QT_MOC_LITERAL(4, 57, 23), // "on_returnButton_clicked"
QT_MOC_LITERAL(5, 81, 17), // "change_line_value"
QT_MOC_LITERAL(6, 99, 5) // "value"

    },
    "front_ADAS_setting\0unHideSettings\0\0"
    "on_nextButton_clicked\0on_returnButton_clicked\0"
    "change_line_value\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_front_ADAS_setting[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   35,    2, 0x0a /* Public */,
       4,    0,   36,    2, 0x0a /* Public */,
       5,    1,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void front_ADAS_setting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<front_ADAS_setting *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->unHideSettings(); break;
        case 1: _t->on_nextButton_clicked(); break;
        case 2: _t->on_returnButton_clicked(); break;
        case 3: _t->change_line_value((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (front_ADAS_setting::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&front_ADAS_setting::unHideSettings)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject front_ADAS_setting::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_front_ADAS_setting.data,
    qt_meta_data_front_ADAS_setting,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *front_ADAS_setting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *front_ADAS_setting::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_front_ADAS_setting.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int front_ADAS_setting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void front_ADAS_setting::unHideSettings()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
