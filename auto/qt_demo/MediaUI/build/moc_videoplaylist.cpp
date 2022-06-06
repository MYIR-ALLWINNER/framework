/****************************************************************************
** Meta object code from reading C++ file 'videoplaylist.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../videoplayer/Header/videoplaylist.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videoplaylist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ScanVideoFileThread_t {
    QByteArrayData data[4];
    char stringdata0[52];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScanVideoFileThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScanVideoFileThread_t qt_meta_stringdata_ScanVideoFileThread = {
    {
QT_MOC_LITERAL(0, 0, 19), // "ScanVideoFileThread"
QT_MOC_LITERAL(1, 20, 12), // "scanComplete"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 17) // "QList<QFileInfo>*"

    },
    "ScanVideoFileThread\0scanComplete\0\0"
    "QList<QFileInfo>*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScanVideoFileThread[] = {

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
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void ScanVideoFileThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ScanVideoFileThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->scanComplete((*reinterpret_cast< QList<QFileInfo>*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ScanVideoFileThread::*)(QList<QFileInfo> * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanVideoFileThread::scanComplete)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ScanVideoFileThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_ScanVideoFileThread.data,
    qt_meta_data_ScanVideoFileThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ScanVideoFileThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScanVideoFileThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScanVideoFileThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int ScanVideoFileThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void ScanVideoFileThread::scanComplete(QList<QFileInfo> * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_VideoPlayList_t {
    QByteArrayData data[19];
    char stringdata0[315];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoPlayList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoPlayList_t qt_meta_stringdata_VideoPlayList = {
    {
QT_MOC_LITERAL(0, 0, 13), // "VideoPlayList"
QT_MOC_LITERAL(1, 14, 9), // "stopMovie"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 23), // "notifyVideoPlayerToPlay"
QT_MOC_LITERAL(4, 49, 16), // "QList<QFileInfo>"
QT_MOC_LITERAL(5, 66, 9), // "playlists"
QT_MOC_LITERAL(6, 76, 3), // "cnt"
QT_MOC_LITERAL(7, 80, 28), // "notifyVideoPlayerListChanged"
QT_MOC_LITERAL(8, 109, 14), // "onScanComplete"
QT_MOC_LITERAL(9, 124, 17), // "QList<QFileInfo>*"
QT_MOC_LITERAL(10, 142, 12), // "fileInfoList"
QT_MOC_LITERAL(11, 155, 24), // "on_UsbListButton_clicked"
QT_MOC_LITERAL(12, 180, 29), // "on_favoriteListButton_clicked"
QT_MOC_LITERAL(13, 210, 24), // "on_refreshButton_clicked"
QT_MOC_LITERAL(14, 235, 12), // "onBtnClicked"
QT_MOC_LITERAL(15, 248, 22), // "on_clearButton_clicked"
QT_MOC_LITERAL(16, 271, 12), // "hidePlayList"
QT_MOC_LITERAL(17, 284, 12), // "showPlayList"
QT_MOC_LITERAL(18, 297, 17) // "updateStatusLabel"

    },
    "VideoPlayList\0stopMovie\0\0"
    "notifyVideoPlayerToPlay\0QList<QFileInfo>\0"
    "playlists\0cnt\0notifyVideoPlayerListChanged\0"
    "onScanComplete\0QList<QFileInfo>*\0"
    "fileInfoList\0on_UsbListButton_clicked\0"
    "on_favoriteListButton_clicked\0"
    "on_refreshButton_clicked\0onBtnClicked\0"
    "on_clearButton_clicked\0hidePlayList\0"
    "showPlayList\0updateStatusLabel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoPlayList[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    2,   75,    2, 0x06 /* Public */,
       7,    1,   80,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   83,    2, 0x08 /* Private */,
      11,    0,   86,    2, 0x08 /* Private */,
      12,    0,   87,    2, 0x08 /* Private */,
      13,    0,   88,    2, 0x08 /* Private */,
      14,    0,   89,    2, 0x08 /* Private */,
      15,    0,   90,    2, 0x08 /* Private */,
      16,    0,   91,    2, 0x0a /* Public */,
      17,    0,   92,    2, 0x0a /* Public */,
      18,    0,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int,    5,    6,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VideoPlayList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VideoPlayList *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stopMovie(); break;
        case 1: _t->notifyVideoPlayerToPlay((*reinterpret_cast< QList<QFileInfo>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->notifyVideoPlayerListChanged((*reinterpret_cast< QList<QFileInfo>(*)>(_a[1]))); break;
        case 3: _t->onScanComplete((*reinterpret_cast< QList<QFileInfo>*(*)>(_a[1]))); break;
        case 4: _t->on_UsbListButton_clicked(); break;
        case 5: _t->on_favoriteListButton_clicked(); break;
        case 6: _t->on_refreshButton_clicked(); break;
        case 7: _t->onBtnClicked(); break;
        case 8: _t->on_clearButton_clicked(); break;
        case 9: _t->hidePlayList(); break;
        case 10: _t->showPlayList(); break;
        case 11: _t->updateStatusLabel(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QFileInfo> >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QFileInfo> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VideoPlayList::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoPlayList::stopMovie)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VideoPlayList::*)(QList<QFileInfo> , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoPlayList::notifyVideoPlayerToPlay)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (VideoPlayList::*)(QList<QFileInfo> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoPlayList::notifyVideoPlayerListChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VideoPlayList::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_VideoPlayList.data,
    qt_meta_data_VideoPlayList,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VideoPlayList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoPlayList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VideoPlayList.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int VideoPlayList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void VideoPlayList::stopMovie()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void VideoPlayList::notifyVideoPlayerToPlay(QList<QFileInfo> _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VideoPlayList::notifyVideoPlayerListChanged(QList<QFileInfo> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
