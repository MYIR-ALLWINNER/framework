/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[261];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 24), // "on_clearAction_triggered"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 23), // "on_markAction_triggered"
QT_MOC_LITERAL(4, 61, 25), // "on_unmarkAction_triggered"
QT_MOC_LITERAL(5, 87, 24), // "on_printAction_triggered"
QT_MOC_LITERAL(6, 112, 31), // "on_printPreviewAction_triggered"
QT_MOC_LITERAL(7, 144, 13), // "printDocument"
QT_MOC_LITERAL(8, 158, 9), // "QPrinter*"
QT_MOC_LITERAL(9, 168, 7), // "printer"
QT_MOC_LITERAL(10, 176, 9), // "printPage"
QT_MOC_LITERAL(11, 186, 5), // "index"
QT_MOC_LITERAL(12, 192, 9), // "QPainter*"
QT_MOC_LITERAL(13, 202, 7), // "painter"
QT_MOC_LITERAL(14, 210, 8), // "showFont"
QT_MOC_LITERAL(15, 219, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(16, 236, 4), // "item"
QT_MOC_LITERAL(17, 241, 12), // "updateStyles"
QT_MOC_LITERAL(18, 254, 6) // "column"

    },
    "MainWindow\0on_clearAction_triggered\0"
    "\0on_markAction_triggered\0"
    "on_unmarkAction_triggered\0"
    "on_printAction_triggered\0"
    "on_printPreviewAction_triggered\0"
    "printDocument\0QPrinter*\0printer\0"
    "printPage\0index\0QPainter*\0painter\0"
    "showFont\0QTreeWidgetItem*\0item\0"
    "updateStyles\0column"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    0,   63,    2, 0x0a /* Public */,
       7,    1,   64,    2, 0x0a /* Public */,
      10,    3,   67,    2, 0x0a /* Public */,
      14,    1,   74,    2, 0x0a /* Public */,
      17,    2,   77,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 12, 0x80000000 | 8,   11,   13,    9,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 15, QMetaType::Int,   16,   18,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_clearAction_triggered(); break;
        case 1: _t->on_markAction_triggered(); break;
        case 2: _t->on_unmarkAction_triggered(); break;
        case 3: _t->on_printAction_triggered(); break;
        case 4: _t->on_printPreviewAction_triggered(); break;
        case 5: _t->printDocument((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        case 6: _t->printPage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QPainter*(*)>(_a[2])),(*reinterpret_cast< QPrinter*(*)>(_a[3]))); break;
        case 7: _t->showFont((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 8: _t->updateStyles((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
