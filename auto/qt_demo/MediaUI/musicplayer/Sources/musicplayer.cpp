/*!
 * @file musicplayer.cpp
 * Copyright (c) 2018
 * @brief des
 * detailed des
 *
 * @date 2018
 * @author lee
 */
#include "musicplayer/Header/musicplayer.h"
#include "ui_musicplayer.h"
#include "common/Header/frmmessagebox.h"
#include "common/Header/mediahome.h"

#include <QMutex>
#include <QMutexLocker>
#include <QDebug>
#include <QDateTime>
#include <QPropertyAnimation>



MusicPlayer *MusicPlayer::self = NULL;
/**************************************
Function:
Description:
***************************************/
MusicPlayer *MusicPlayer::Instance(QWidget *parent)
{
    if (self == NULL) {
        QMutex mutex;
        QMutexLocker locker(&mutex);
        if (self == NULL) {
            self = new MusicPlayer(parent);
        }
    }
    return self;
}

/**************************************
Function:
Description:
***************************************/
MusicPlayer::MusicPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicPlayer),
    ap(NULL),
    m_totalDuration(0),
    m_curDuration(0),
    m_bPlayState(STOPPED),
    m_bMusicListOpen(false),
    m_bSearchDialogOpen(false),
    m_pPlayList(NULL),
    m_curMusicFilePath(""),
    m_curMusicFileCount(-1),
    m_curPlayOrderState(0),
    m_pSearchDialog(NULL),
    m_nextPlayOrderState(1)

{
    pStaticMusicPlayer = this;

    ui->setupUi(this);
    setWindowFlags(this->windowFlags()|Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);//the ~CameraSetting will be call when func close() run

    m_commonFunction = new CommonFunction ;

    ui->posterLabel->setPixmap(QPixmap(":/images/playerIcons/MusicPoster.png"));

    m_pPlayList = PlayList::Instance(this);
    m_pPlayList->move(1024,50);
    connect(this, SIGNAL(hidePlayList()), m_pPlayList, SLOT(hidePlayList()));
    connect(this,SIGNAL(showPlayList()),m_pPlayList,SLOT(showPlayList()));

    connect(m_pPlayList,SIGNAL(notifyMusicPlayerToPlay(QList<QFileInfo>,int,int)),\
            this,SLOT(on_notifyMusicPlayerToPlay(QList<QFileInfo>,int,int)));
    connect(m_pPlayList,SIGNAL(notifyMusicPlayerListChanged(QList<QFileInfo>,int)),\
            this,SLOT(on_notifyMusicPlayerListChanged(QList<QFileInfo>,int)));

    progressSliderTimer = new QTimer(this);
    connect(progressSliderTimer,SIGNAL(timeout()),this,SLOT(timerUpdate()));

    connect(ui->progressSlider,SIGNAL(sliderMoved(int)),this,SLOT(onProgressSliderMoved(int)));
    connect(ui->progressSlider,SIGNAL(sliderReleased()),this,SLOT(onProgressSliderReleased()));
    
    connect(ui->return_btn,SIGNAL(clicked()),this,SLOT(on_return_btn_clicked()));

    connect(this, SIGNAL(msgSignal(int,void*,void*,int)),
            this, SLOT(doMsgCmd(int,void*,void*,int)));
}


/**************************************
Function:
Description:
***************************************/
MusicPlayer::~MusicPlayer()
{
    delete ui;
    delete m_commonFunction;
    m_commonFunction = NULL;
    self = NULL;
    if(ap != NULL){
        delete ap;
        ap = NULL;
    }
}

/**************************************
Function:
Description:
***************************************/
void MusicPlayer::initAutPlayer()
{
    if(m_curMusicFilePath.isEmpty())
    {
        qDebug()<<"file path is emtpy";
    }
    if(ap != NULL){
        delete ap;
        ap = NULL;
    }
    ap = new AUTPlayer();
    if(ap == NULL){
        qDebug()<<"new AutPlayer error";
        return ;
    }
    m_bPlayState = STOPPED;

    int ret = ap->setUrl((char*)m_curMusicFilePath.toLatin1().data());
    if(ret != 0){
        qDebug()<<"this video set url errror";
        return;
    }
    ap->setUserCb(autMusicCb_func, this);

    m_totalDuration = ap->getDuration() / 1000;
    ui->progressSlider->setRange(0,m_totalDuration * 1000);
    m_curDuration=0;

    ui->totalTimeLabel->setText(getTimeStr(m_totalDuration,m_totalDuration));
        ui->curTimeLabel->setText(getTimeStr(m_curDuration,m_totalDuration));
    ret = ap->play();
    if(ret != 0)
        qDebug()<<"play bug";

    ui->playButton->setIcon(QIcon(":/images/playerIcons/Pause.png"));
    ui->playButton->setIconSize(QSize(50,50));
    m_bPlayState = PLAYING;

    progressSliderTimer->start(1000);
}

/**************************************
Function:
Description:
***************************************/
void MusicPlayer::timerUpdate()
{
    if (ap == NULL)
        return ;
    m_curDuration = ap->getCurrentPosition();
    ui->progressSlider->setValue(m_curDuration);
    updateDurationInfo(m_curDuration / 1000);
}

/**************************************
Function:
Description:
***************************************/
void MusicPlayer::updateDurationInfo(qint64 currentInfo)
{
    qDebug()<<"update the time label";
    QString tStr;

    if (ap == NULL)
        return ;
    if(currentInfo >= m_totalDuration)
    {
        currentInfo = 0;
        ui->progressSlider->setValue(0);
        m_bPlayState = STOPPED;
        ui->playButton->setIcon(QIcon(":/images/playerIcons/Play.png"));
        ui->playButton->setIconSize(QSize(50,50));
        progressSliderTimer->stop();
    }

    tStr=getTimeStr(currentInfo,m_totalDuration);
    ui->curTimeLabel->setText(tStr);

    qDebug()<<"update the time label" << tStr << " " << tStr.compare("") << " " <<tStr.size();
}

/**************************************
Function:
Description:
***************************************/
void MusicPlayer::onProgressSliderMoved(int value)
{
    qDebug()<<"slider is moved"<<value;
    progressSliderTimer->stop();
    if (!ui->progressSlider->isSliderDown()) {
        ui->progressSlider->setValue(value);
    }
    ui->progressSlider->setValue(value);
    updateDurationInfo(value / 1000);
    progressSliderTimer->start(1000);
}

/**************************************
Function:
Description:
***************************************/
void MusicPlayer::onProgressSliderReleased()
{
    qDebug()<<"slider is released";
    if(m_bPlayState == PAUSEED)
        on_playButton_clicked();
    progressSliderTimer->stop();
    m_bPlayState = SEEKING;
    if(ap != NULL){
        ap->seekto(ui->progressSlider->value() / 1000);
    }
    progressSliderTimer->start(1000);

    m_bPlayState = PLAYING;

}

/**************************************
Function:
Description:
***************************************/
void MusicPlayer::startPlay()
{
    bool isExist = m_commonFunction->fileExistOrNot(m_curMusicFilePath);
    if(!isExist){
        qDebug()<<"file exist";
        frmMessageBox *msg = new frmMessageBox(this);
        msg->SetMessage(QString("文件不存在！"),0);
        msg->exec();
        return;
    }
    if(!m_commonFunction->video_support_or_not(this,m_curMusicFilePath)){
        qDebug()<<"format not support";
        return ;
    }
    initAutPlayer();
    getMusicInfo(m_curMusicFilePath);
}

/**************************************
Function:
Description:
***************************************/
void MusicPlayer::stopPlay()
{
    if(ap != NULL){
        ap->stop();
    }
}
/**************************************
Function:
Description:
***************************************/
void MusicPlayer::on_notifyMusicPlayerToPlay(QList<QFileInfo> playList,int row,int listType)
{
    //hide the playlist
    emit hidePlayList();
    m_bMusicListOpen = false;

    if(listType == 0){
        if(m_playList_udisk != playList){
            qDebug()<<"on_notifyMusicPlayerToPlay set list wrong";
        }else{
            m_playList_udisk = playList;
        }
        m_playList = m_playList_udisk;
    }else if(listType == 1){
        if(m_playList_favorite != playList){
            qDebug()<<"on_notifyMusicPlayerToPlay set list wrong";
        }else{
            m_playList_favorite = playList;
        }
        m_playList = m_playList_favorite;
    }

    m_playList = playList;
    if(m_playList.count() < row){
        qDebug()<<"playlist is wrong";
        return;
    }
    m_curMusicFilePath = m_playList.at(row).absoluteFilePath();
    m_curMusicFileCount = row;

    startPlay();
}

/**************************************
Function:
Description:
***************************************/
void MusicPlayer::on_notifyMusicPlayerListChanged(QList<QFileInfo> playList,int listType)
{

    if(listType == 0){
        qDebug()<<"m_playList_udisk has been update";
        m_playList_udisk = playList;
    }else if(listType == 1){
        qDebug()<<"m_playList_favorite has been update";
        m_playList_favorite = playList;
    }
}

/**************************************
Function:
Description:
***************************************/
void MusicPlayer::on_playButton_clicked()
{
    qDebug()<<"MusicPlayer::on_playButton_clicked()";
    int ret=0;
    if(ap != NULL){
        ret = ap->pause();
        if(ret != 0)
            qDebug()<<"pause bug";
        if (m_bPlayState == PAUSEED){
            m_bPlayState = PLAYING;
            ui->playButton->setIcon(QIcon(":/images/playerIcons/Pause.png"));
        }
        else if(m_bPlayState == PLAYING){
            m_bPlayState = PAUSEED;
            ui->playButton->setIcon(QIcon(":/images/playerIcons/Play.png"));
        }
        else if(m_bPlayState == STOPPED){
            initAutPlayer();
        }
    }
}

/**************************************
Function:
Description:
***************************************/
void MusicPlayer::on_preMusicButton_clicked()
{
    qDebug()<<"on_preMusicButton_clicked,here";
    if(m_curMusicFileCount -1 >= 0){
        m_curMusicFileCount--;
        m_curMusicFilePath = m_playList.at(m_curMusicFileCount).absoluteFilePath();
        progressSliderTimer->stop();
        stopPlay();
        startPlay();
    }else{
        return ;
    }
}

/**************************************
Function:
Description:
***************************************/
void MusicPlayer::on_nextMusicButton_clicked()
{
    qDebug()<<"on_nextMusicButton_clicked,here";
    if(m_curMusicFileCount + 1 < m_playList.count()){
        m_curMusicFileCount++;
        m_curMusicFilePath = m_playList.at(m_curMusicFileCount).absoluteFilePath();\
        progressSliderTimer->stop();
        stopPlay();
        startPlay();
    }else{
        return ;
    }
}

/**************************************
Function:
Description:
***************************************/
void MusicPlayer::on_searchButton_clicked()
{
    qDebug()<<"on_searchButton_clicked";


    if(m_pSearchDialog  == NULL){
        m_pSearchDialog = new searchFileDialog(0,this);

        connect(m_pSearchDialog,SIGNAL(notifyMusicPlayerAddFile(QString)),\
                this,SLOT(on_notifyMusicPlayerAddFile(QString)));

        connect(m_pSearchDialog,SIGNAL(notifyMusicCancelSearch()),\
                this,SLOT(on_notifyMusicCancelSearch()));
    }

    if(m_bSearchDialogOpen == false){
        m_bSearchDialogOpen = true;
        m_pSearchDialog->showD();
    } else {
        m_bSearchDialogOpen = false;
        m_pSearchDialog->hide();
    }
}

/**************************************
Function:
Description:
***************************************/
void MusicPlayer::on_playListButton_clicked()
{
    qDebug()<<"on_playListButton_clicked";

    if(m_pPlayList == NULL){
        qDebug()<<"new";
        m_pPlayList = PlayList::Instance(this);
        m_pPlayList->move(1024,50);
    }
    qDebug()<<"already exisit";
    if(!m_bMusicListOpen){
        qDebug()<<"show!!!!";
        emit showPlayList();
        m_bMusicListOpen = true;
    } else {
        qDebug()<<"hide!!!";
        emit hidePlayList();
        m_bMusicListOpen = false;
    }
}


/**************************************
Function:
Description:
//some operation when MusicPlayer get focus
//通过焦点实现的方法还需要进一步测试，存在bug
***************************************/

void MusicPlayer::focusInEvent(QFocusEvent*)
{
    qDebug()<<"Musicplayer get focus";
    if(m_bMusicListOpen == true){
        emit hidePlayList();
        m_bMusicListOpen = false;
    }
}


/**************************************
Function:
Description:
***************************************/
void MusicPlayer::on_playOrderButton_clicked()
{
    switch(m_nextPlayOrderState){
    case 0:
        qDebug()<<"now is random play";
        ui->playOrderButton->setIcon(QIcon(":/images/playerIcons/randomPlay.png"));
        m_curPlayOrderState = 0;
        m_nextPlayOrderState = 1;
        break;
    case 1:
        qDebug()<<"now is sequence play";
        ui->playOrderButton->setIcon(QIcon(":/images/playerIcons/playlist2.png"));
        m_curPlayOrderState = 1;
        m_nextPlayOrderState = 2;
        break;
    case 2:
        qDebug()<<"now is circle play";
        ui->playOrderButton->setIcon(QIcon(":/images/playerIcons/playlistRepeat.png"));
        m_curPlayOrderState = 2;
        m_nextPlayOrderState = 0;
        break;
    }
}

/**************************************
Function:
Description:
***************************************/
void MusicPlayer::on_setttingButton_clicked()
{

}

/**************************************
Function:
Description:
***************************************/
void MusicPlayer::on_pushButton_clicked()
{
    if(ap!=NULL){
       ap->stop();
    }
    this->close();
    system("fbinit");
}

/**************************************
Function:
Description:
***************************************/
void MusicPlayer::getMusicInfo(QString path)
{
    MusicInfoThread* thread = new MusicInfoThread(path, this);
    connect(thread,SIGNAL(complete(QString,QString,QString,QPixmap)),\
            this,SLOT(setMusicInfo(QString ,QString ,QString ,QPixmap )));
    thread->start();
}

/**************************************
Function:
Description:
***************************************/
void MusicPlayer::setMusicInfo(QString albumName,QString musicName,QString singerName,QPixmap poster)
{
    m_albumName = albumName;
    m_musicName = musicName;
    m_singerName = singerName;
    m_poster = poster;
    if(!m_albumName.isEmpty()){
        ui->albumTextLabel->setText(m_albumName);
    }else{
        ui->albumTextLabel->setText("未知专辑");
    }
    if(!m_musicName.isEmpty()){
        ui->MusicTextLabel->setText(m_musicName);
    }else{
        ui->MusicTextLabel->setText("未知音乐名");
    }
    if(!m_singerName.isEmpty()){
        ui->artistTextLabel->setText(m_singerName);
    }else{
        ui->artistTextLabel->setText("未知艺术家");
    }
    if(!m_poster.isNull()){
        ui->posterLabel->clear();
        ui->posterLabel->setPixmap(m_poster);
    }else{
        ui->posterLabel->clear();
        ui->posterLabel->setPixmap(QPixmap(":/images/playerIcons/MusicPoster.png"));
    }
}


/**************************************
Function:
Description:
***************************************/
void MusicPlayer::on_return_btn_clicked()
{
    if(m_bSearchDialogOpen == true){
        m_bSearchDialogOpen = false;
        m_pSearchDialog->hide();
    }

    this->close();
	pGlobalMediaHome->distype=0;	
    pGlobalMediaHome->setHidden(false);
}


/**************************************
Function:
Description:
***************************************/
void MusicPlayer::on_notifyMusicPlayerAddFile(QString strpath)
{
    qDebug()<<"on_notifyMusicPlayerAddFile ";
    m_curMusicFilePath = strpath;
    if(m_bSearchDialogOpen == true){
        m_bSearchDialogOpen = false;
        m_pSearchDialog->hide();
    }
	startPlay();

}


/**************************************
Function:
Description:
***************************************/
void MusicPlayer::on_notifyMusicCancelSearch()
{
    qDebug()<<"on_notifyMusicCancelSearch ";

    if(m_bSearchDialogOpen == true){
        m_bSearchDialogOpen = false;
        m_pSearchDialog->hide();
    }

}


/**************************************
Function:
Description:
***************************************/
void MusicPlayer::doMsgCmd(int msgType, void* user,void* data,int len)
{

    switch(msgType)
    {
        case 128:
        	break;
        case SUBCTRL_SUBTITLE_AVAILABLE:
            break;
        case SUBCTRL_SUBTITLE_EXPIRED:
            break;
        case AWPLAYER_MEDIA_PREPARED:
            break;
        case AWPLAYER_MEDIA_PLAYBACK_COMPLETE:
            on_nextMusicButton_clicked();
            break;
        case AWPLAYER_MEDIA_SEEK_COMPLETE:

            break;
        case AWPLAYER_MEDIA_STARTED:
            break;
        case AWPLAYER_MEDIA_LOG_RECORDER:
            break;
        case AWPLAYER_MEDIA_BUFFERING_UPDATE:
            break;
        case AWPLAYER_MEDIA_ERROR:
            break;
        case AWPLAYER_MEDIA_INFO:
            break;
        case AWPLAYER_MEDIA_SET_VIDEO_SIZE:
            break;
        default:
            break;
    }
}

/**************************************
Function:
Description:
***************************************/
int MusicPlayer::autMusicCb_func(int msgType, void* user,void* data,int len)
{
    emit pStaticMusicPlayer->msgSignal(msgType,user,data,len);
}


/**************************************
Function:
Description:
***************************************/
MusicInfoThread::MusicInfoThread(QString path,QObject *parent)
    : m_filepath(path),
      QThread(parent)
{
    qDebug() << "MusicInfoThread Thread : " << QThread::currentThreadId();
    commonfunc = new CommonFunction;
    m_albumName = QString("");
    m_musicName = QString("");
    m_singerName = QString("");
    m_poster = QPixmap();
}

/**************************************
Function:
Description:
***************************************/
MusicInfoThread::~MusicInfoThread()
{
    qDebug()<<"~MusicInfoThread";
}

/**************************************
Function:
Description:
***************************************/
void MusicInfoThread::run()
{
    qDebug() << "MusicInfoThread run in  Thread : " << QThread::currentThreadId();
    qDebug()<<"the file's absoluteFilePath is"<<m_filepath;

    XRetriever *demoRetriver = XRetrieverCreate();
    if(NULL == demoRetriver){
        printf("XRetrieverCreate failed\n");
    }
    int ret = XRetrieverSetDataSource(demoRetriver, (char*)m_filepath.toLatin1().data(), NULL);
    if(ret < 0){
         printf("set datasource failed\n");
    }
    printf("XRetrieverSetDataSource end\n");
    CdxMediaInfoT mi;
    XRetrieverGetMetaData(demoRetriver, METADATA_MEDIAINFO, &mi);
    printf("the video information:titile[64]=[%.02x %.02x %.02x %.02x %.02x]\n",mi.title[0],mi.title[1],mi.title[2],mi.title[3],mi.title[4]);
    printf("the video information:album[64]=[%s] ,albumsz=%d,genre[64]=%s,genresz=%d,title[64]=%s,titlesz=%d,year[64]=%s,yearsz=%d,composer[64]=%s,date[64]=%s\n",
           mi.album,mi.albumsz,mi.genre,mi.genresz,mi.title,mi.titlesz,mi.year,mi.yearsz,mi.composer,mi.date);

    if(mi.albumsz!=0){
        m_albumName = commonfunc->print_info(mi.album,mi.albumsz);
        qDebug()<<"album is"<<m_albumName;
    }
    if(mi.titlesz!=0){
        m_musicName = commonfunc->print_info(mi.title,mi.titlesz);
        qDebug()<<"title is"<<m_musicName;
    }
    if(mi.authorsz!=0){
        m_singerName = commonfunc->print_info(mi.author,mi.authorsz);
        qDebug()<<"author is"<< m_singerName;
    }
    if(mi.nAlbumArtBufSize != 0){
        qDebug()<<"this music has poster";
        QImage img = QImage::fromData((const uchar*)mi.pAlbumArtBuf,mi.nAlbumArtBufSize);
        QImage imgScaled = img.scaled(320,260,Qt::KeepAspectRatio);
        m_poster.convertFromImage(imgScaled);
    }

    emit complete(m_albumName,m_musicName,m_singerName,m_poster);

    XRetrieverDestory(demoRetriver);
    demoRetriver = NULL;
    return ;
}
