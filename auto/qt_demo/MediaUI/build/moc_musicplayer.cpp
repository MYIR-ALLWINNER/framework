/****************************************************************************
** Meta object code from reading C++ file 'musicplayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../musicplayer/Header/musicplayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'musicplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MusicInfoThread_t {
    QByteArrayData data[3];
    char stringdata0[26];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MusicInfoThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MusicInfoThread_t qt_meta_stringdata_MusicInfoThread = {
    {
QT_MOC_LITERAL(0, 0, 15), // "MusicInfoThread"
QT_MOC_LITERAL(1, 16, 8), // "complete"
QT_MOC_LITERAL(2, 25, 0) // ""

    },
    "MusicInfoThread\0complete\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MusicInfoThread[] = {

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
       1,    4,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QPixmap,    2,    2,    2,    2,

       0        // eod
};

void MusicInfoThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MusicInfoThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->complete((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QPixmap(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MusicInfoThread::*)(QString , QString , QString , QPixmap );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MusicInfoThread::complete)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MusicInfoThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_MusicInfoThread.data,
    qt_meta_data_MusicInfoThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MusicInfoThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MusicInfoThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MusicInfoThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int MusicInfoThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void MusicInfoThread::complete(QString _t1, QString _t2, QString _t3, QPixmap _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_MusicPlayer_t {
    QByteArrayData data[31];
    char stringdata0[556];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MusicPlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MusicPlayer_t qt_meta_stringdata_MusicPlayer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MusicPlayer"
QT_MOC_LITERAL(1, 12, 9), // "msgSignal"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 7), // "msgType"
QT_MOC_LITERAL(4, 31, 4), // "user"
QT_MOC_LITERAL(5, 36, 4), // "data"
QT_MOC_LITERAL(6, 41, 3), // "len"
QT_MOC_LITERAL(7, 45, 12), // "hidePlayList"
QT_MOC_LITERAL(8, 58, 12), // "showPlayList"
QT_MOC_LITERAL(9, 71, 20), // "hideSearchFileDialog"
QT_MOC_LITERAL(10, 92, 20), // "showSearchFileDialog"
QT_MOC_LITERAL(11, 113, 21), // "on_return_btn_clicked"
QT_MOC_LITERAL(12, 135, 25), // "on_preMusicButton_clicked"
QT_MOC_LITERAL(13, 161, 21), // "on_playButton_clicked"
QT_MOC_LITERAL(14, 183, 26), // "on_nextMusicButton_clicked"
QT_MOC_LITERAL(15, 210, 23), // "on_searchButton_clicked"
QT_MOC_LITERAL(16, 234, 25), // "on_playListButton_clicked"
QT_MOC_LITERAL(17, 260, 26), // "on_playOrderButton_clicked"
QT_MOC_LITERAL(18, 287, 25), // "on_setttingButton_clicked"
QT_MOC_LITERAL(19, 313, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(20, 335, 26), // "on_notifyMusicPlayerToPlay"
QT_MOC_LITERAL(21, 362, 16), // "QList<QFileInfo>"
QT_MOC_LITERAL(22, 379, 8), // "listType"
QT_MOC_LITERAL(23, 388, 31), // "on_notifyMusicPlayerListChanged"
QT_MOC_LITERAL(24, 420, 11), // "timerUpdate"
QT_MOC_LITERAL(25, 432, 21), // "onProgressSliderMoved"
QT_MOC_LITERAL(26, 454, 24), // "onProgressSliderReleased"
QT_MOC_LITERAL(27, 479, 12), // "setMusicInfo"
QT_MOC_LITERAL(28, 492, 27), // "on_notifyMusicPlayerAddFile"
QT_MOC_LITERAL(29, 520, 26), // "on_notifyMusicCancelSearch"
QT_MOC_LITERAL(30, 547, 8) // "doMsgCmd"

    },
    "MusicPlayer\0msgSignal\0\0msgType\0user\0"
    "data\0len\0hidePlayList\0showPlayList\0"
    "hideSearchFileDialog\0showSearchFileDialog\0"
    "on_return_btn_clicked\0on_preMusicButton_clicked\0"
    "on_playButton_clicked\0on_nextMusicButton_clicked\0"
    "on_searchButton_clicked\0"
    "on_playListButton_clicked\0"
    "on_playOrderButton_clicked\0"
    "on_setttingButton_clicked\0"
    "on_pushButton_clicked\0on_notifyMusicPlayerToPlay\0"
    "QList<QFileInfo>\0listType\0"
    "on_notifyMusicPlayerListChanged\0"
    "timerUpdate\0onProgressSliderMoved\0"
    "onProgressSliderReleased\0setMusicInfo\0"
    "on_notifyMusicPlayerAddFile\0"
    "on_notifyMusicCancelSearch\0doMsgCmd"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MusicPlayer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,  129,    2, 0x06 /* Public */,
       7,    0,  138,    2, 0x06 /* Public */,
       8,    0,  139,    2, 0x06 /* Public */,
       9,    0,  140,    2, 0x06 /* Public */,
      10,    0,  141,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,  142,    2, 0x08 /* Private */,
      12,    0,  143,    2, 0x08 /* Private */,
      13,    0,  144,    2, 0x08 /* Private */,
      14,    0,  145,    2, 0x08 /* Private */,
      15,    0,  146,    2, 0x08 /* Private */,
      16,    0,  147,    2, 0x08 /* Private */,
      17,    0,  148,    2, 0x08 /* Private */,
      18,    0,  149,    2, 0x08 /* Private */,
      19,    0,  150,    2, 0x08 /* Private */,
      20,    3,  151,    2, 0x08 /* Private */,
      23,    2,  158,    2, 0x08 /* Private */,
      24,    0,  163,    2, 0x08 /* Private */,
      25,    1,  164,    2, 0x08 /* Private */,
      26,    0,  167,    2, 0x08 /* Private */,
      27,    4,  168,    2, 0x08 /* Private */,
      28,    1,  177,    2, 0x08 /* Private */,
      29,    0,  180,    2, 0x08 /* Private */,
      30,    4,  181,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::VoidStar, QMetaType::VoidStar, QMetaType::Int,    3,    4,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21, QMetaType::Int, QMetaType::Int,    2,    2,   22,
    QMetaType::Void, 0x80000000 | 21, QMetaType::Int,    2,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QPixmap,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::VoidStar, QMetaType::VoidStar, QMetaType::Int,    3,    4,    5,    6,

       0        // eod
};

void MusicPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MusicPlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->msgSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< void*(*)>(_a[2])),(*reinterpret_cast< void*(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: _t->hidePlayList(); break;
        case 2: _t->showPlayList(); break;
        case 3: _t->hideSearchFileDialog(); break;
        case 4: _t->showSearchFileDialog(); break;
        case 5: _t->on_return_btn_clicked(); break;
        case 6: _t->on_preMusicButton_clicked(); break;
        case 7: _t->on_playButton_clicked(); break;
        case 8: _t->on_nextMusicButton_clicked(); break;
        case 9: _t->on_searchButton_clicked(); break;
        case 10: _t->on_playListButton_clicked(); break;
        case 11: _t->on_playOrderButton_clicked(); break;
        case 12: _t->on_setttingButton_clicked(); break;
        case 13: _t->on_pushButton_clicked(); break;
        case 14: _t->on_notifyMusicPlayerToPlay((*reinterpret_cast< QList<QFileInfo>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 15: _t->on_notifyMusicPlayerListChanged((*reinterpret_cast< QList<QFileInfo>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 16: _t->timerUpdate(); break;
        case 17: _t->onProgressSliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->onProgressSliderReleased(); break;
        case 19: _t->setMusicInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QPixmap(*)>(_a[4]))); break;
        case 20: _t->on_notifyMusicPlayerAddFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: _t->on_notifyMusicCancelSearch(); break;
        case 22: _t->doMsgCmd((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< void*(*)>(_a[2])),(*reinterpret_cast< void*(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QFileInfo> >(); break;
            }
            break;
        case 15:
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
            using _t = void (MusicPlayer::*)(int , void * , void * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MusicPlayer::msgSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MusicPlayer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MusicPlayer::hidePlayList)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MusicPlayer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MusicPlayer::showPlayList)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MusicPlayer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MusicPlayer::hideSearchFileDialog)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MusicPlayer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MusicPlayer::showSearchFileDialog)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MusicPlayer::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_MusicPlayer.data,
    qt_meta_data_MusicPlayer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MusicPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MusicPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MusicPlayer.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MusicPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void MusicPlayer::msgSignal(int _t1, void * _t2, void * _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MusicPlayer::hidePlayList()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MusicPlayer::showPlayList()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MusicPlayer::hideSearchFileDialog()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MusicPlayer::showSearchFileDialog()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
