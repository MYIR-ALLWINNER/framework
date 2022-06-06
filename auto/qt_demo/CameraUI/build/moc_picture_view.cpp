/****************************************************************************
** Meta object code from reading C++ file 'picture_view.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/picture_view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'picture_view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Picture_view_t {
    QByteArrayData data[9];
    char stringdata0[183];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Picture_view_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Picture_view_t qt_meta_stringdata_Picture_view = {
    {
QT_MOC_LITERAL(0, 0, 12), // "Picture_view"
QT_MOC_LITERAL(1, 13, 22), // "on_btnMenu_Min_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 22), // "on_btnMenu_Max_clicked"
QT_MOC_LITERAL(4, 60, 24), // "on_btnMenu_Close_clicked"
QT_MOC_LITERAL(5, 85, 23), // "on_prePicButton_clicked"
QT_MOC_LITERAL(6, 109, 24), // "on_nextPicButton_clicked"
QT_MOC_LITERAL(7, 134, 23), // "on_largerButton_clicked"
QT_MOC_LITERAL(8, 158, 24) // "on_smallerButton_clicked"

    },
    "Picture_view\0on_btnMenu_Min_clicked\0"
    "\0on_btnMenu_Max_clicked\0"
    "on_btnMenu_Close_clicked\0"
    "on_prePicButton_clicked\0"
    "on_nextPicButton_clicked\0"
    "on_largerButton_clicked\0"
    "on_smallerButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Picture_view[] = {

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
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

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

void Picture_view::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Picture_view *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnMenu_Min_clicked(); break;
        case 1: _t->on_btnMenu_Max_clicked(); break;
        case 2: _t->on_btnMenu_Close_clicked(); break;
        case 3: _t->on_prePicButton_clicked(); break;
        case 4: _t->on_nextPicButton_clicked(); break;
        case 5: _t->on_largerButton_clicked(); break;
        case 6: _t->on_smallerButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Picture_view::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_Picture_view.data,
    qt_meta_data_Picture_view,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Picture_view::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Picture_view::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Picture_view.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Picture_view::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
