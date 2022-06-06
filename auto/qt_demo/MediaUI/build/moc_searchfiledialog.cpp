/****************************************************************************
** Meta object code from reading C++ file 'searchfiledialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../common/Header/searchfiledialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'searchfiledialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_searchFileDialog_t {
    QByteArrayData data[10];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_searchFileDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_searchFileDialog_t qt_meta_stringdata_searchFileDialog = {
    {
QT_MOC_LITERAL(0, 0, 16), // "searchFileDialog"
QT_MOC_LITERAL(1, 17, 24), // "notifyMusicPlayerAddFile"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 24), // "notifyVideoPlayerAddFile"
QT_MOC_LITERAL(4, 68, 20), // "notifyGalleryAddFile"
QT_MOC_LITERAL(5, 89, 23), // "notifyMusicCancelSearch"
QT_MOC_LITERAL(6, 113, 23), // "notifyVideoCancelSearch"
QT_MOC_LITERAL(7, 137, 25), // "notifyGalleryCancelSearch"
QT_MOC_LITERAL(8, 163, 13), // "onGetFileName"
QT_MOC_LITERAL(9, 177, 8) // "onCancel"

    },
    "searchFileDialog\0notifyMusicPlayerAddFile\0"
    "\0notifyVideoPlayerAddFile\0"
    "notifyGalleryAddFile\0notifyMusicCancelSearch\0"
    "notifyVideoCancelSearch\0"
    "notifyGalleryCancelSearch\0onGetFileName\0"
    "onCancel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_searchFileDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       3,    1,   57,    2, 0x06 /* Public */,
       4,    1,   60,    2, 0x06 /* Public */,
       5,    0,   63,    2, 0x06 /* Public */,
       6,    0,   64,    2, 0x06 /* Public */,
       7,    0,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   66,    2, 0x0a /* Public */,
       9,    0,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void searchFileDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<searchFileDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->notifyMusicPlayerAddFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->notifyVideoPlayerAddFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->notifyGalleryAddFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->notifyMusicCancelSearch(); break;
        case 4: _t->notifyVideoCancelSearch(); break;
        case 5: _t->notifyGalleryCancelSearch(); break;
        case 6: _t->onGetFileName(); break;
        case 7: _t->onCancel(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (searchFileDialog::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&searchFileDialog::notifyMusicPlayerAddFile)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (searchFileDialog::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&searchFileDialog::notifyVideoPlayerAddFile)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (searchFileDialog::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&searchFileDialog::notifyGalleryAddFile)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (searchFileDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&searchFileDialog::notifyMusicCancelSearch)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (searchFileDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&searchFileDialog::notifyVideoCancelSearch)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (searchFileDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&searchFileDialog::notifyGalleryCancelSearch)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject searchFileDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_searchFileDialog.data,
    qt_meta_data_searchFileDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *searchFileDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *searchFileDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_searchFileDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int searchFileDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void searchFileDialog::notifyMusicPlayerAddFile(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void searchFileDialog::notifyVideoPlayerAddFile(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void searchFileDialog::notifyGalleryAddFile(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void searchFileDialog::notifyMusicCancelSearch()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void searchFileDialog::notifyVideoCancelSearch()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void searchFileDialog::notifyGalleryCancelSearch()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
