/*!
 * @file videoplayer.cpp
 * Copyright (c) 2018
 * @brief des
 * detailed des
 *
 * @date 2018
 * @author lee
 */
#include "videoplayer/Header/videoplayer.h"
#include "ui_videoplayer.h"
#include "common/Header/frmmessagebox.h"
#include "common/Header/mediahome.h"

#include <QMutex>
#include <QMutexLocker>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QTextCodec>


VideoPlayer *VideoPlayer::self = NULL;


/**************************************
Function:
Description:
***************************************/
VideoPlayer *VideoPlayer::Instance(QWidget *parent)
{
    if (self == NULL) {
        QMutex mutex;
        QMutexLocker locker(&mutex);
        if (self == NULL) {
            self = new VideoPlayer(parent);
        }
    }
    return self;
}


/**************************************
Function:
Description:
***************************************/
VideoPlayer::VideoPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoPlayer),
    ap(NULL),
    m_totalDuration(0),
    m_curDuration(0),
    m_bPlayState(STOPPED),
    m_bVideoListOpen(false),
    m_curVideoFilePath(""),
    m_curVideoFileName(""),
    m_curVideoFileCount(-1),
    m_bSearchDialogOpen(false),
    m_pSearchDialog(NULL),
    m_subtitleNow(1),
    m_audioNow(1)
{
    qDebug()<<"VideoPlayer init";

    pStaticVideoPlayer=this;

    ui->setupUi(this);

    m_commonFunction = new CommonFunction ;

    ui->UnFullscreenButton->setVisible(false);

    m_pVideoPlayList = VideoPlayList::Instance(this);
    m_pVideoPlayList->move(1024,50);
    connect(this, SIGNAL(hidePlayList()), m_pVideoPlayList, SLOT(hidePlayList()));
    connect(this,SIGNAL(showPlayList()),m_pVideoPlayList,SLOT(showPlayList()));

    connect(m_pVideoPlayList,SIGNAL(notifyVideoPlayerToPlay(QList<QFileInfo>,int)),\
            this,SLOT(on_notifyVideoPlayerToPlay(QList<QFileInfo>,int)));
    connect(m_pVideoPlayList,SIGNAL(notifyVideoPlayerToPlay(QList<QFileInfo>)),\
            this,SLOT(on_notifyVideoPlayerListChanged(QList<QFileInfo>)));

    progressSliderTimer = new QTimer(this);
    connect(progressSliderTimer,SIGNAL(timeout()),this,SLOT(timerUpdate()));

    connect(ui->progressSlider,SIGNAL(sliderMoved(int)),this,SLOT(onProgressSliderMoved(int)));
    connect(ui->progressSlider,SIGNAL(sliderReleased()),this,SLOT(onProgressSliderReleased()));
    
    connect(ui->return_btn,SIGNAL(clicked()),this,SLOT(on_return_btn_clicked()));

    connect(ui->nextVideoButton,SIGNAL(clicked()),this,SLOT(on_nextVideoButton_clicked()));

    connect(this, SIGNAL(msgSignal(int,void*,void*,int)),
            this, SLOT(doMsgCmd(int,void*,void*,int)));

    setAttribute(Qt::WA_TranslucentBackground, true);

    setStyleSheet("background-color: transparent");
}


/**************************************
Function:
Description:
***************************************/
VideoPlayer::~VideoPlayer()
{
    delete ui;
    self = NULL;
}

/**************************************
Function:
Description:
***************************************/
void VideoPlayer::initAutPlayer()
{
    if(m_curVideoFilePath.isEmpty())
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

    int ret = ap->setUrl((char*)m_curVideoFilePath.toLatin1().data());
    if(ret != 0){
        qDebug()<<"this video set url errror";
        return;
    }
    ui->videoNameLabel->setText(m_curVideoFileName);

    ap->setUserCb(autVideoCb_func, this);

    m_totalDuration = ap->getDuration() / 1000;
    ui->progressSlider->setRange(0,m_totalDuration * 1000);
    m_pretime=0;
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
void VideoPlayer::startPlay()
{
    bool isExist = m_commonFunction->fileExistOrNot(m_curVideoFilePath);
    if(!isExist){
        qDebug()<<"file exist";
        frmMessageBox *msg = new frmMessageBox(this);
        msg->SetMessage(QString("文件不存在！"),0);
        msg->exec();
        return;
    }
    if(!m_commonFunction->video_support_or_not(this,m_curVideoFilePath)){
        qDebug()<<"format not support";
        return ;
    }
    initAutPlayer();
}

/**************************************
Function:
Description:
***************************************/
void VideoPlayer::onProgressSliderMoved(int value)
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
void VideoPlayer::onProgressSliderReleased()
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
void VideoPlayer::timerUpdate()
{
    if (ap == NULL)
        return ;
    m_curDuration = ap->getCurrentPosition();

    //qDebug()<<"timerUpdate "<<m_curDuration;

    ui->progressSlider->setValue(m_curDuration);
    updateDurationInfo(m_curDuration / 1000);
}



/**************************************
Function:
Description:
***************************************/
void VideoPlayer::updateDurationInfo(qint64 currentInfo)
{

    QString tStr;

    if (ap == NULL)
        return ;


    if(currentInfo >= m_totalDuration)
    {
        currentInfo = 0;
        m_bPlayState = STOPPED;
        ui->playButton->setIcon(QIcon(":/images/playerIcons/Play.png"));
        ui->playButton->setIconSize(QSize(50,50));
        progressSliderTimer->stop();

    }

    tStr=getTimeStr(currentInfo,m_totalDuration);
    ui->curTimeLabel->setText(tStr);

    //qDebug()<<"update the time label" << tStr << " " << tStr.compare("") << " " <<tStr.size();
}

/**************************************
Function:
Description:
***************************************/
void VideoPlayer::on_return_btn_clicked()
{
    QString tStr = "00:00";

    this->close();

    if(m_bPlayState == PLAYING){
       on_playButton_clicked();
    }

    if(ap != NULL){
        ap->stop();
        m_bPlayState = STOPPED;
        progressSliderTimer->stop();
        ui->progressSlider->setValue(0);
        ui->curTimeLabel->setText(tStr);
    }

    if(m_bSearchDialogOpen == true){
        m_bSearchDialogOpen = false;
        m_pSearchDialog->hide();
    }

    pGlobalMediaHome->setHidden(false);
}


/**************************************
Function:
Description:
***************************************/
void VideoPlayer::on_fullScreenButton_clicked()
{
    ui->UnFullscreenButton->setVisible(true);
    ui->controlButtonwidget->setVisible(false);
    ui->progressSlider->setVisible(false);
    ui->tilteWidget->setVisible(false);
    ui->sliderAndTimeLabelWidget->move(0,570);
    ui->subtitlewidget->move(0,510);
    ui->videoNameWidget->move(0,5);

}

/**************************************
Function:
Description:
***************************************/
void VideoPlayer::on_UnFullscreenButton_clicked()
{
    ui->UnFullscreenButton->setVisible(false);
    ui->controlButtonwidget->setVisible(true);
    ui->progressSlider->setVisible(true);
    ui->tilteWidget->setVisible(true);
    ui->sliderAndTimeLabelWidget->move(0,490);
    ui->subtitlewidget->move(0,430);
    ui->videoNameWidget->move(0,70);
}


/**************************************
Function:
Description:
***************************************/
void VideoPlayer::stopPlay()
{
    if(ap != NULL){
        ap->stop();
    }
}
/**************************************
Function:
Description:
***************************************/
void VideoPlayer::on_preVideoButton_clicked()
{
    if(m_curVideoFileCount -1 >= 0){
        m_curVideoFileCount--;
        m_curVideoFilePath = m_playList.at(m_curVideoFileCount).absoluteFilePath();
        m_curVideoFileName = m_playList.at(m_curVideoFileCount).completeBaseName();
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
void VideoPlayer::on_nextVideoButton_clicked()
{
    qDebug()<<"on_nextVideoButton_clicked ";

    if(m_curVideoFileCount + 1 < m_playList.count()){
        m_curVideoFileCount++;
        m_curVideoFilePath = m_playList.at(m_curVideoFileCount).absoluteFilePath();
        m_curVideoFileName = m_playList.at(m_curVideoFileCount).completeBaseName();
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
void VideoPlayer::on_playButton_clicked()
{
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
void VideoPlayer::on_subtitleListButton_clicked()
{

}
/**************************************
Function:
Description:
***************************************/
void VideoPlayer::on_playListButton_clicked()
{
   qDebug()<<"on_playListButton_clicked "<<m_bVideoListOpen;

    if(m_pVideoPlayList == NULL){
        m_pVideoPlayList = VideoPlayList::Instance(this);
        m_pVideoPlayList->move(1024,50);
    }
    if(m_bVideoListOpen == false){
        emit showPlayList();
        m_bVideoListOpen = true;
    } else {
        emit hidePlayList();
        m_bVideoListOpen = false;
    }

}
/**************************************
Function:
Description:
***************************************/
void VideoPlayer::on_searchButton_clicked()
{
    if(m_pSearchDialog  == NULL){
        m_pSearchDialog = new searchFileDialog(1,this);

        connect(m_pSearchDialog,SIGNAL(notifyVideoPlayerAddFile(QString)),\
                this,SLOT(on_notifyVideoPlayerAddFile(QString)));

        connect(m_pSearchDialog,SIGNAL(notifyVideoCancelSearch()),\
                this,SLOT(on_notifyVideoCancelSearch()));
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
void VideoPlayer::on_notifyVideoPlayerToPlay(QList<QFileInfo> playList,int row)
{
    //hide the playlist
    emit hidePlayList();
    m_bVideoListOpen = 0;

    m_playList = playList;
    if(m_playList.count() < row){
        qDebug()<<"playlist is wrong";
        return;
    }
    m_curVideoFileName = m_playList.at(row).completeBaseName();
    m_curVideoFilePath = m_playList.at(row).absoluteFilePath();
    m_curVideoFileCount = row;

    stopPlay();
    startPlay();
}


/**************************************
Function:
Description:
***************************************/
void VideoPlayer::on_notifyVideoPlayerListChanged(QList<QFileInfo> playList)
{
    m_playList = playList;
}


/**************************************
Function:
Description:
***************************************/
void VideoPlayer::getNumOfAudioAndSubtitle(int& subtitleNum,int& audioNum)
{
    if(ap != NULL){
        MediaInfo* mediaInfo = ap->getMediaInfo();
        subtitleNum = mediaInfo->nSubtitleStreamNum;
        audioNum = mediaInfo->nAudioStreamNum;
    }else{
        frmMessageBox* msg = new frmMessageBox();
        msg->SetMessage("播放器没有在运行！！",0);
        msg->show();
    }
}

/**************************************
Function:
Description:
***************************************/
void VideoPlayer::on_subtitleSelectButton_clicked()
{


    QFileDialog *fileDialog = new QFileDialog(this);

    fileDialog->setStyleSheet("font: bold; font-size:20px; color: rgb(0,0,0); background-color: rgb(170, 255, 255)");
    fileDialog->setFileMode(QFileDialog::Directory);
    fileDialog->setDirectory("/mnt/");

    if(fileDialog->exec() == QDialog::Accepted)
    {
        str_SelectPath = fileDialog->getExistingDirectory();
        qDebug()<<"the path is "<< str_SelectPath;

    }else{

    }
}


/**************************************
Function:
Description:
***************************************/
void VideoPlayer::setSubtitleNum(QAction* pAction)
{
    QString file = pAction->text();
    pAction->setCheckable(true);
    pAction->setChecked(true);
    qDebug()<<"triggered the "<<file;
    QString tmp;
    for(int i=0;i<file.size();i++){
        if(file[i].isDigit()){
            tmp += file[i];
        }
    }
    int num = tmp.toInt();
    m_subtitleNow = num;
    qDebug()<<"the subtitle "<<num<<" will be set";
    ap->switchSubtitle(num);

}

/**************************************
Function:
Description:
***************************************/
void VideoPlayer::setAudioNum(QAction* pAction)
{
    QString file = pAction->text();
    pAction->setCheckable(true);
    pAction->setChecked(true);
    qDebug()<<"triggered the "<<file;
    QString tmp;
    for(int i = 0;i < file.size();i++){
        if(file[i].isDigit()){
            tmp += file[i];
        }
    }
    int num = tmp.toInt();
    m_audioNow = num;
    qDebug()<<"the audio "<<num<<" will be set";
    ap->switchAudio(num);

}

/**************************************
Function:
Description:
***************************************/
void VideoPlayer::doMsgCmd(int msgType, void* user,void* data,int len)
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
            on_nextVideoButton_clicked();
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
int VideoPlayer::autVideoCb_func(int msgType, void* user,void* data,int len)
{
    emit pStaticVideoPlayer->msgSignal(msgType,user,data,len);
}


/**************************************
Function:
Description:
***************************************/
void VideoPlayer::on_notifyVideoPlayerAddFile(QString strpath)
{
    m_curVideoFilePath = strpath;
    QFileInfo fileInfo(strpath);
    m_curVideoFileName = fileInfo.fileName();

    if(m_bSearchDialogOpen == true){
        m_bSearchDialogOpen = false;
        m_pSearchDialog->hide();
    }

    qDebug()<<"on_notifyVideoPlayerAddFile "<< m_curVideoFilePath << " "<< m_curVideoFileName;

    stopPlay();
    startPlay();

}

/**************************************
Function:
Description:
***************************************/
void VideoPlayer::on_notifyVideoCancelSearch()
{

	qDebug()<<"on_notifyVideoCancelSearch ";

	if(m_bSearchDialogOpen == true){
		m_bSearchDialogOpen = false;
		m_pSearchDialog->hide();
	}
}

