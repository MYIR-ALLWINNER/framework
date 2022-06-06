/****************************************************************************
** Meta object code from reading C++ file 'playlist.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../musicplayer/Header/playlist.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playlist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ScanMusicFileThread_t {
    QByteArrayData data[4];
    char stringdata0[52];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScanMusicFileThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScanMusicFileThread_t qt_meta_stringdata_ScanMusicFileThread = {
    {
QT_MOC_LITERAL(0, 0, 19), // "ScanMusicFileThread"
QT_MOC_LITERAL(1, 20, 12), // "scanComplete"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 17) // "QList<QFileInfo>*"

    },
    "ScanMusicFileThread\0scanComplete\0\0"
    "QList<QFileInfo>*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScanMusicFileThread[] = {

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

void ScanMusicFileThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ScanMusicFileThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->scanComplete((*reinterpret_cast< QList<QFileInfo>*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ScanMusicFileThread::*)(QList<QFileInfo> * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanMusicFileThread::scanComplete)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ScanMusicFileThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_ScanMusicFileThread.data,
    qt_meta_data_ScanMusicFileThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ScanMusicFileThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScanMusicFileThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScanMusicFileThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int ScanMusicFileThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ScanMusicFileThread::scanComplete(QList<QFileInfo> * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_waittingWidgetThread_t {
    QByteArrayData data[1];
    char stringdata0[21];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_waittingWidgetThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_waittingWidgetThread_t qt_meta_stringdata_waittingWidgetThread = {
    {
QT_MOC_LITERAL(0, 0, 20) // "waittingWidgetThread"

    },
    "waittingWidgetThread"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_waittingWidgetThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void waittingWidgetThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject waittingWidgetThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_waittingWidgetThread.data,
    qt_meta_data_waittingWidgetThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *waittingWidgetThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *waittingWidgetThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_waittingWidgetThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int waittingWidgetThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_PlayList_t {
    QByteArrayData data[22];
    char stringdata0[370];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayList_t qt_meta_stringdata_PlayList = {
    {
QT_MOC_LITERAL(0, 0, 8), // "PlayList"
QT_MOC_LITERAL(1, 9, 9), // "stopMovie"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 23), // "notifyMusicPlayerToPlay"
QT_MOC_LITERAL(4, 44, 16), // "QList<QFileInfo>"
QT_MOC_LITERAL(5, 61, 9), // "playlists"
QT_MOC_LITERAL(6, 71, 3), // "cnt"
QT_MOC_LITERAL(7, 75, 8), // "listType"
QT_MOC_LITERAL(8, 84, 28), // "notifyMusicPlayerListChanged"
QT_MOC_LITERAL(9, 113, 12), // "hidePlayList"
QT_MOC_LITERAL(10, 126, 12), // "showPlayList"
QT_MOC_LITERAL(11, 139, 17), // "updateStatusLabel"
QT_MOC_LITERAL(12, 157, 24), // "on_UsbListButton_clicked"
QT_MOC_LITERAL(13, 182, 29), // "on_favoriteListButton_clicked"
QT_MOC_LITERAL(14, 212, 14), // "onScanComplete"
QT_MOC_LITERAL(15, 227, 17), // "QList<QFileInfo>*"
QT_MOC_LITERAL(16, 245, 12), // "fileInfoList"
QT_MOC_LITERAL(17, 258, 12), // "onBtnClicked"
QT_MOC_LITERAL(18, 271, 24), // "on_refreshButton_clicked"
QT_MOC_LITERAL(19, 296, 22), // "on_clearButton_clicked"
QT_MOC_LITERAL(20, 319, 24), // "on_prePageButton_clicked"
QT_MOC_LITERAL(21, 344, 25) // "on_notifyMusicListAddFile"

    },
    "PlayList\0stopMovie\0\0notifyMusicPlayerToPlay\0"
    "QList<QFileInfo>\0playlists\0cnt\0listType\0"
    "notifyMusicPlayerListChanged\0hidePlayList\0"
    "showPlayList\0updateStatusLabel\0"
    "on_UsbListButton_clicked\0"
    "on_favoriteListButton_clicked\0"
    "onScanComplete\0QList<QFileInfo>*\0"
    "fileInfoList\0onBtnClicked\0"
    "on_refreshButton_clicked\0"
    "on_clearButton_clicked\0on_prePageButton_clicked\0"
    "on_notifyMusicListAddFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayList[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    3,   85,    2, 0x06 /* Public */,
       8,    2,   92,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   97,    2, 0x0a /* Public */,
      10,    0,   98,    2, 0x0a /* Public */,
      11,    0,   99,    2, 0x0a /* Public */,
      12,    0,  100,    2, 0x08 /* Private */,
      13,    0,  101,    2, 0x08 /* Private */,
      14,    1,  102,    2, 0x08 /* Private */,
      17,    0,  105,    2, 0x08 /* Private */,
      18,    0,  106,    2, 0x08 /* Private */,
      19,    0,  107,    2, 0x08 /* Private */,
      20,    0,  108,    2, 0x08 /* Private */,
      21,    1,  109,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int, QMetaType::Int,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int,    5,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void PlayList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PlayList *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stopMovie(); break;
        case 1: _t->notifyMusicPlayerToPlay((*reinterpret_cast< QList<QFileInfo>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->notifyMusicPlayerListChanged((*reinterpret_cast< QList<QFileInfo>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->hidePlayList(); break;
        case 4: _t->showPlayList(); break;
        case 5: _t->updateStatusLabel(); break;
        case 6: _t->on_UsbListButton_clicked(); break;
        case 7: _t->on_favoriteListButton_clicked(); break;
        case 8: _t->onScanComplete((*reinterpret_cast< QList<QFileInfo>*(*)>(_a[1]))); break;
        case 9: _t->onBtnClicked(); break;
        case 10: _t->on_refreshButton_clicked(); break;
        case 11: _t->on_clearButton_clicked(); break;
        case 12: _t->on_prePageButton_clicked(); break;
        case 13: _t->on_notifyMusicListAddFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
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
            using _t = void (PlayList::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayList::stopMovie)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PlayList::*)(QList<QFileInfo> , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayList::notifyMusicPlayerToPlay)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PlayList::*)(QList<QFileInfo> , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayList::notifyMusicPlayerListChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PlayList::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_PlayList.data,
    qt_meta_data_PlayList,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PlayList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlayList.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PlayList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void PlayList::stopMovie()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PlayList::notifyMusicPlayerToPlay(QList<QFileInfo> _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PlayList::notifyMusicPlayerListChanged(QList<QFileInfo> _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
