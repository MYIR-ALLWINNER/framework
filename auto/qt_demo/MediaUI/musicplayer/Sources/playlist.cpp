/*!
 * @file playlist.cpp
 * Copyright (c) 2018
 * @brief des
 * detailed des
 *
 * @date 2018
 * @author lee
 */
#include "musicplayer/Header/playlist.h"
#include "ui_playlist.h"
#include "common/Header/frmmessagebox.h"
#include "common/Header/config.h"

#include <QMutex>
#include <QMutexLocker>
#include <QDebug>
#include <QPropertyAnimation>
#include <QFileInfo>
#include <QDir>
#include <QByteArray>
#include <QTextCodec>
#include <QThread>
#include <QTimer>

////////////////////////////////////////////////////////////////////////////////////
/// \brief PlayList::self
/// ensure this class only has one instance
PlayList *PlayList::self = NULL;
PlayList *PlayList::Instance(QWidget *parent)
{
    if (self == NULL) {
        QMutex mutex;
        QMutexLocker locker(&mutex);
        if (self == NULL) {
            self = new PlayList(parent);
        }
    }
    return self;
}
PlayList::PlayList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayList)
{
    ui->setupUi(this);
    setWindowFlags(this->windowFlags()|Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);//the ~CameraSetting will be call when func close() run

    m_scrollBarV = ui->tableWidget->verticalScrollBar();
    ui->tableWidget->viewport()->installEventFilter(this);

    m_scrollBarV_2 = ui->tableWidget_2->verticalScrollBar();
    ui->tableWidget_2->viewport()->installEventFilter(this);

    ui->stackedWidget->setCurrentWidget(ui->mediaFilePositionSelect);

    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setColumnWidth(0,251);
    ui->tableWidget->setColumnWidth(1,30);
    ui->tableWidget->setColumnWidth(2,30);

    ui->tableWidget_2->setAlternatingRowColors(true);
    ui->tableWidget_2->setColumnWidth(0,251);
    ui->tableWidget_2->setColumnWidth(1,30);
    ui->tableWidget_2->setColumnWidth(2,30);

    ui->clearButton->setEnabled(false);
    ui->refreshButton->setEnabled(false);

}

PlayList::~PlayList()
{
    delete ui;
    self = NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////
//hidePlayList && showPlayList
//these two func is animation for playlist hide and show
/*!
 * @function
 * @brief des: this func mainly for animation of ui hide;
 */
void PlayList::hidePlayList()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(800);
    animation->setEasingCurve(QEasingCurve::InQuad);
    animation->setStartValue(QRect(704, 55, 320, 450));
    animation->setEndValue(QRect(1024, 55, 320, 450));
    animation->start();
    //hide operation
    connect(animation, SIGNAL(finished()), this, SLOT(hide()));
}
void PlayList::showPlayList()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(300);
    animation->setEasingCurve(QEasingCurve::InQuad);
    animation->setStartValue(QRect(1024, 55, 320, 450));
    animation->setEndValue(QRect(704, 55, 320, 450));
    animation->start();
    //show operation
    connect(animation, SIGNAL(finished()), this, SLOT(show()));
}
//////////////////////////////////////////////////////////////////////////////////////////

/*!
 * @function
 * @brief des
 * this function is used for add the music file to tablewidget after scan thread is complete
 */
void PlayList::onScanComplete(QList<QFileInfo>* fileInfoList)
{
    qDebug()<<"onScanComplete's thread ID is "<<QThread::currentThreadId();
    qDebug()<<"PlayList::onScanComplete";
    m_PlayList_Udisk = *fileInfoList;
    if(fileInfoList == NULL){
        ui->tableWidget->setItem(0,0,new QTableWidgetItem("未找到音乐文件"));
    } else {
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(fileInfoList->count());
        qDebug()<<ui->tableWidget->rowCount();
        for(int i = 0; i < fileInfoList->count(); i++){
            QByteArray ba = fileInfoList->at(i).fileName().toLocal8Bit();
            QTextCodec *codec = QTextCodec::codecForName("GBK");
            QString str = codec->toUnicode(ba);
            qDebug()<<"filename:"<<str;

            QPushButton* playButton = new QPushButton(this);
            QPushButton* delButton = new QPushButton(this);
            playButton->setStyleSheet("QPushButton{\
                                         background-color: rgba(255, 255, 255, 0);\
                                         border-image: url(:/images/playerIcons/playlistplayNormal.png);\
                                    }\
                                    QPushButton:pressed{\
                                        border-image: url(:/images/playerIcons/playlistplayPress.png);\
                                    }"
            );
            delButton->setStyleSheet("QPushButton{\
                                          background-color: rgba(255, 255, 255, 0);\
                                          border-image: url(:/images/playerIcons/playlistdelete.png);\
                                    }\
                                    QPushButton:pressed{\
                                        border-image: url(:/images/playerIcons/playlistdeletePress.png);\
                                    }"
                );
            playButton->setFocusPolicy(Qt::NoFocus);
            delButton->setFocusPolicy(Qt::NoFocus);

            connect(playButton,SIGNAL(clicked()),this,SLOT(onBtnClicked()));
            connect(delButton,SIGNAL(clicked()),this,SLOT(onBtnClicked()));

            ui->tableWidget->setRowHeight(i,35);
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(str));
            ui->tableWidget->setCellWidget(i,1,playButton);
            ui->tableWidget->setCellWidget(i,2,delButton);

            ui->statusLabel->setText(QString("状态：添加文件%1").arg(fileInfoList->at(i).fileName()));
        }//for
        QTimer::singleShot(1000, this, SLOT(updateStatusLabel()));
        emit stopMovie();
        emit notifyMusicPlayerListChanged(m_PlayList_Udisk,0);
    }//if
}

void PlayList::onBtnClicked()
{
    int ListType;
    QList<QFileInfo> tmp_PlayList;
    if(ui->stackedWidget->currentWidget() == ui->udiskMusicList){
        tmp_PlayList = m_PlayList_Udisk;
        ListType = 0;
    }
    if(ui->stackedWidget->currentWidget() == ui->favoriteMusicList){
        tmp_PlayList = m_PlayList_Favorite;
        ListType = 1;
    }
    QPushButton* pBtn = dynamic_cast<QPushButton*>(this->sender());
    if(pBtn == NULL){
        return;
    }
    int x = pBtn->frameGeometry().x();
    int y = pBtn->frameGeometry().y();

    QModelIndex index = ui->tableWidget->indexAt(QPoint(x,y));
    int row = index.row();
    int colum = index.column();

    qDebug()<<(QObject::tr("onBtnClicked ,row: %1, colum: %2").arg(row).arg(colum));

    if(colum == 1){
        qDebug()<<QObject::tr("this is play button");
        emit notifyMusicPlayerToPlay(tmp_PlayList,row,ListType);
    }
    if(colum == 2){
        qDebug()<<QObject::tr("this is remove button");

        ui->statusLabel->setText(QString("状态：删除文件%1").arg(tmp_PlayList.at(row).fileName()));
        tmp_PlayList.removeAt(row);
        if(ListType == 1){
            ui->tableWidget_2->removeRow(row);
        }else if (ListType == 0){
            ui->tableWidget->removeRow(row);
        }

        QTimer::singleShot(1000, this, SLOT(updateStatusLabel()));

        emit notifyMusicPlayerListChanged(tmp_PlayList,ListType);
    }
}
void PlayList::updateStatusLabel()
{
    if(ui->stackedWidget->currentWidget() == ui->udiskMusicList){
        ui->statusLabel->setText(QString("状态：列表音乐数量--%1").arg(m_PlayList_Udisk.count()));
    }
    if(ui->stackedWidget->currentWidget() == ui->favoriteMusicList){
        ui->statusLabel->setText(QString("状态：列表音乐数量--%1").arg(m_PlayList_Favorite.count()));
    }
}
void PlayList::scanMusicFileFromUdisk()
{
    ScanMusicFileThread* scanThread = new ScanMusicFileThread(this);
    connect(scanThread,SIGNAL(scanComplete(QList<QFileInfo>*)),this,SLOT(onScanComplete(QList<QFileInfo>*)));
    scanThread->start();
}
void PlayList::on_refreshButton_clicked()
{
    on_clearButton_clicked();
    ScanMusicFileThread* scanThread = new ScanMusicFileThread(this);
    connect(scanThread,SIGNAL(scanComplete(QList<QFileInfo>*)),this,SLOT(onScanComplete(QList<QFileInfo>*)));
    scanThread->start();
}

void PlayList::on_clearButton_clicked()
{
    if(ui->stackedWidget->currentWidget() == ui->udiskMusicList){
        ui->tableWidget->clear();
        m_PlayList_Udisk.clear();
        QTimer::singleShot(1000, this, SLOT(updateStatusLabel()));
        emit notifyMusicPlayerListChanged(m_PlayList_Udisk,0);
    }
    if(ui->stackedWidget->currentWidget() == ui->favoriteMusicList){
        ui->tableWidget_2->clear();
        m_PlayList_Favorite.clear();
        QTimer::singleShot(1000, this, SLOT(updateStatusLabel()));
        emit notifyMusicPlayerListChanged(m_PlayList_Favorite,1);
    }
}
/*!
 * @function
 * @brief des
 * this function is designed for scan udisk music file
 */
void PlayList::on_UsbListButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->udiskMusicList);
    ui->statusLabel->setText("状态：扫描u盘文件");
    ui->clearButton->setEnabled(true);
    ui->refreshButton->setEnabled(true);
    ui->titleLabel->setText("u盘音乐文件");
//    showWaittingDialog();// a bug
    scanMusicFileFromUdisk();
}
/*!
 * @function
 * @brief des
 * this function is designed for read a user's favorite music list from ini or txt etc.
 */
void PlayList::on_favoriteListButton_clicked()
{
    ui->clearButton->setEnabled(false);
    ui->refreshButton->setEnabled(false);
    ui->stackedWidget->setCurrentWidget(ui->favoriteMusicList);
    ui->statusLabel->setText("状态：读取收藏文件");
    ui->titleLabel->setText("我喜欢的音乐");
}
void PlayList::on_prePageButton_clicked()
{
    ui->clearButton->setEnabled(false);
    ui->refreshButton->setEnabled(false);
    ui->stackedWidget->setCurrentWidget(ui->mediaFilePositionSelect);
    ui->titleLabel->setText("播放列表选择");
}

void PlayList::showWaittingDialog()
{
    waittingWidgetThread* waittingThread = new waittingWidgetThread(this);
    waittingThread->start();
}

///////////////////////////////////////////////////////////////////////////////////
///
void PlayList::on_notifyMusicListAddFile(QString filepath)
{
    QFileInfo fileInfo = QFileInfo(filepath);
    if(!fileInfo.isFile()){
        qDebug()<<"this is a dir,ignored";
        return;
    }
    m_PlayList_Favorite.push_back(fileInfo);
    int count = ui->tableWidget_2->rowCount();
    ui->tableWidget_2->insertRow(count);
    QByteArray ba = fileInfo.fileName().toLocal8Bit();
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QString str = codec->toUnicode(ba);
    qDebug()<<"filename:"<<str;

    QPushButton* playButton = new QPushButton(this);
    QPushButton* delButton = new QPushButton(this);
    playButton->setStyleSheet("QPushButton{\
                                 background-color: rgba(255, 255, 255, 0);\
                                 border-image: url(:/images/playerIcons/playlistplayNormal.png);\
                            }\
                            QPushButton:pressed{\
                                border-image: url(:/images/playerIcons/playlistplayPress.png);\
                            }"
    );
    delButton->setStyleSheet("QPushButton{\
                                  background-color: rgba(255, 255, 255, 0);\
                                  border-image: url(:/images/playerIcons/playlistdelete.png);\
                            }\
                            QPushButton:pressed{\
                                border-image: url(:/images/playerIcons/playlistdeletePress.png);\
                            }"
        );
    playButton->setFocusPolicy(Qt::NoFocus);
    delButton->setFocusPolicy(Qt::NoFocus);

    connect(playButton,SIGNAL(clicked()),this,SLOT(onBtnClicked()));
    connect(delButton,SIGNAL(clicked()),this,SLOT(onBtnClicked()));

    ui->tableWidget_2->setRowHeight(count,35);
    ui->tableWidget_2->setItem(count,0,new QTableWidgetItem(str));
    ui->tableWidget_2->setCellWidget(count,1,playButton);
    ui->tableWidget_2->setCellWidget(count,2,delButton);

    ui->statusLabel->setText(QString("状态：添加文件%1").arg(fileInfo.fileName()));

    emit notifyMusicPlayerListChanged(m_PlayList_Favorite,1);
}
/////////////////////////////////////////////////////////////////////////////////////////////
/// \brief ScanMusicFileThread::ScanMusicFileThread
/// this thread is used for scan music file from udisk and other path
ScanMusicFileThread::ScanMusicFileThread(QObject *parent)
    : QThread(parent)
{
    qDebug() << "ScanMusicFileThread Thread : " << QThread::currentThreadId();
}
ScanMusicFileThread::~ScanMusicFileThread()
{
    qDebug()<<"~ScanMusicFileThread";
}

void ScanMusicFileThread::run()
{
    qDebug() << "ScanMusicFileThread Run Thread : " << QThread::currentThreadId() ;

    QDir* dir = new QDir(AUDIO_PATH);
    QStringList filter;
    filter<<"*.mp3";
    dir->setNameFilters(filter);
    fileInfoList = new QList<QFileInfo>(dir->entryInfoList(filter));
    qDebug()<<"this dir have"<<fileInfoList->count()<<"files";
    emit scanComplete(fileInfoList);
    return ;

}

////////////////////////////////////////////////////////////////////////////////////
/// \brief waittingWidgetThread::waittingWidgetThread
/// this is a loading ui for waitting scan music file and other
/// this ui is a model window

waittingWidgetThread::waittingWidgetThread(QObject *parent)
{
    qDebug() << "waittingWidgetThread Thread : " << QThread::currentThreadId();
}

waittingWidgetThread::~waittingWidgetThread()
{
    qDebug()<<"~waittingWidgetThread";
}

void waittingWidgetThread::waittingWidgetThread::run()
{
    qDebug()<<"showWaittingDialog's thread ID is "<<QThread::currentThreadId();
    m_pWaittingWidget = new WaittingWidget;
    connect(this, SIGNAL(stopMovie()),m_pWaittingWidget,SLOT(onStopMovie()));
    m_pWaittingWidget->user_setGeometry(QRect(704, 75, 320, 450));
#if 0
    QThread* waittingwidgetThread = new QThread;
    m_pWaittingWidget->moveToThread(waittingwidgetThread);
#endif
    m_pWaittingWidget->show();
    m_pWaittingWidget->startMovie();
}

//////////////////////////////////////////////////////////////////////////////
/// \brief Gallery::eventFilter
///scrollarea with flow
bool PlayList::eventFilter(QObject *obj, QEvent *event)
{
    static int press_y   = 0;
    static int move_y    = -1;
    static int release_y = 0;
    static QDateTime pressDateTime;
    static QPropertyAnimation *animation = new QPropertyAnimation();

    if("qt_scrollarea_viewport" != obj->objectName()){
        return false;
    }

    int scrollV_max = m_scrollBarV->maximum ();
    int scrollV_min = m_scrollBarV->minimum ();

    //根据鼠标的动作——按下、放开、拖动，执行相应的操作
    if(event->type() == QEvent::MouseButtonPress){
        //记录按下的时间、坐标
        pressDateTime = QDateTime::currentDateTime();
        move_y  = QCursor::pos().y();
        press_y = move_y;

        animation->stop();
    }
    else if(event->type() == QEvent::MouseButtonRelease){
        //鼠标放开，根据鼠标拖动的垂直距离和持续时间，设置窗口滚动快慢程度和距离
        if(animation->targetObject() != m_scrollBarV){
            animation->setTargetObject(m_scrollBarV);
            animation->setPropertyName("value");
        }
        move_y = -1;
        release_y = QCursor::pos().y();
        QObject *parent_obj = obj->parent();
        if(parent_obj != 0 || parent_obj->inherits("QAbstractItemView")){
            QTimer::singleShot(150, (QAbstractItemView *)parent_obj
                               , SLOT(clearSelection()));
        }
        int endValue;
        int pageStep;
        if(release_y - press_y != 0 && qAbs(release_y - press_y) > 45){
            //qDebug()<<"obj->objectName()="<<obj->objectName();
            int mseconds = pressDateTime.msecsTo(QDateTime::currentDateTime());
//            qDebug()<<"mseconds="<<mseconds;

            int limit = 440;
            pageStep = 220;//scrollBarV->pageStep();
//            qDebug()<<"pageStep="<<pageStep;
            if(mseconds > limit){
                //滑动的时间大于某个值的时候，不再滚动(通过增加分母)
                mseconds = mseconds + (mseconds - limit) * 20;
            }

            if(release_y - press_y > 0){
                endValue = m_scrollBarV->value()
                        - pageStep * (200.0 / mseconds);//.0避免避免强制转换为整形
                if(scrollV_min > endValue){
                    endValue = scrollV_min;
                }
            }
            else if(release_y - press_y < 0){
                    endValue = m_scrollBarV->value() + pageStep * (200.0 / mseconds);
                    if(endValue > scrollV_max){
                        endValue = scrollV_max;
                    }
            }
            if(mseconds > limit){
                mseconds = 0;//滑动的时间大于某个值的时候，滚动距离变小，减小滑动的时间
            }
            animation->setDuration(mseconds+550);
            animation->setEndValue(endValue);
            animation->setEasingCurve(QEasingCurve::OutQuad);
            animation->start();
            return true;
        }
    }
    else if(event->type() == QEvent::MouseMove && move_y >= 0)
    {
        //窗口跟着鼠标移动
        int move_distance = QCursor::pos().y() - move_y;
        int endValue = m_scrollBarV->value() - move_distance;
        if(scrollV_min > endValue){
            endValue = scrollV_min;
        }

        if(endValue > scrollV_max){
            endValue = scrollV_max;
        }
        m_scrollBarV->setValue(endValue);
        move_y = QCursor::pos().y();
    }
    return false;
}




