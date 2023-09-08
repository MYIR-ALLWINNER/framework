#include "music_player.h"
#include "ui_music_player.h"
#include <QFontDatabase>
#include <QDesktopWidget>
#include "main_desktop.h"
#include <QPalette>
#include <QDebug>
#include <QMessageBox>
#include "frmmessagebox.h"
#include "moviedesk1.h"
#include "setfirst.h"
#include "midwindow.h"
#include <QImage>
#include <QTextCodec>

extern movieDesk1* pStaticMovieDesk;
extern QFileInfo fileInfo_music_to_play;
extern main_desktop* pStaticMaindesktop;
extern MidWindow* midwindow;
extern int now_voice_value;
extern SetFirst* pStaticSetfirst;
#if defined(Q_OS_LINUX)
extern int is_dir_exist(const char *dir_path);
extern int autCb_func(int32_t msgType, void *user,void* data,int len);
#endif
extern QString print_info(unsigned char tmp[],int tmp2);
extern QString get_utf8_string(QString str);
Music_Player* pStaticMusicPlayer=NULL;
Music_Player::Music_Player(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Music_Player)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    qDebug()<<"the filename will play is"<<fileInfo_music_to_play.completeBaseName();
    ui->playButton->setIcon(QIcon(":/icon/Pause.png"));
    ui->playButton->setIconSize(QSize(51,51));
    ui->muteButton->setIcon(QIcon(":/icon/voice.png"));
    ui->muteButton->setIconSize(QSize(51,51));
    ui->voiceSlider->setRange(0,100);
    ui->voiceSlider->setValue(now_voice_value);
#if defined(Q_OS_LINUX)
    qDebug()<<"video player first set voice";
    QString cmd="tinymix 2 "+ QString::number(now_voice_value*2,10);
    //system((char*)cmd.toStdString().c_str());
#endif
    isOpen=false;//for other information
    show_title();
    FormInCenter();
    tablewidget = NULL;
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    current_path=fileInfo_music_to_play.absolutePath();
    qDebug()<<"current path is:"<<current_path;
#if defined(Q_OS_LINUX)
    if(!is_dir_exist((char*)current_path.toStdString().c_str()))
    {
        dir.setPath(current_path);
        file_list=GetFileList(dir);
        for(int i=0;i<file_list.size();i++)
        {
            qDebug()<<"----------here";
            qDebug()<<"compare:"<<file_list[i].completeBaseName()<<"==?=="<<fileInfo_music_to_play.completeBaseName();

            char* temp_1=(char*)file_list[i].absoluteFilePath().toLatin1().data();
            char* temp_2=(char*)fileInfo_music_to_play.absoluteFilePath().toLatin1().data();
//            printf("print file temp_1:\n");
//            for(int K=0;K<strlen(temp_1);K++)
//            {
//                printf("=======[%x] ",temp_1[K]);
//            }
//            printf("\n");
//            printf("print file temp_2:\n");
//            for(int K=0;K<strlen(temp_2);K++)
//            {
//                printf("=======[%x] ",temp_2[K]);
//            }
//            printf("\n");
            if(file_list[i]==fileInfo_music_to_play){
                current_video=i;
                qDebug()<<"find the correct video"<<current_video;
                break;
            }
        }
    }else{
        qDebug()<<"path is not exist";
    }
#else
    if(current_path==""){
        qDebug()<<"the wrong path";
    }else{
        dir.setPath(current_path);
        file_list=GetFileList(dir);
        for(int i=0;i<file_list.size();i++)
        {
            if(file_list[i]==fileInfo_music_to_play){
                current_video=i;
                break;
            }
        }
    }

#endif
    isMuted=false;
    isPlaying=true;
    seekto_is_ok=1;
    ui->widget->setVisible(true);
    setMouseTracking(true);
    mouseMoveTime = new QTimer();
    connect(mouseMoveTime,SIGNAL(timeout()),this,SLOT(on_timeout_mouserMoveTime()));
//    mouseMoveTime->start(100000);
    pStaticMusicPlayer=this;

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::white);

#if defined(Q_OS_LINUX)
    ui->progressSlider->setEnabled(false);
    #if 0
    char * snd_devname="hw:1";    //hdmi output
    ap = new AUTPlayer(44100,2,snd_devname);
    #else
    ap = new AUTPlayer();
    #endif
    if(ap == NULL){
        qDebug()<<"new AutPlayer error";
        return ;
    }
    astatus = ASTATUS_STOPPED;
    QFileInfo file_path_to_play=file_list.at(current_video);
    QString ab_file_path=file_path_to_play.absoluteFilePath();
    qDebug()<<"the file's absoluteFilePath is"<<ab_file_path;
    QString file_name=file_path_to_play.fileName();
    qDebug()<<"the video name: "<<file_name<<"while play";
    int ret = ap->setUrl((char*)ab_file_path.toLatin1().data());
    if (ret < 0)
    {
        qDebug()<<"setUrl is error-------------------";
         ui->label->setText("");
        frmMessageBox *msg=new frmMessageBox(this);
        msg->SetMessage(QString(tr("video not support!")),0);
        msg->exec();
    }else{
        ap->setUserCb(autCb_func, this);
        ap->setViewWindow(0, 0, 800, 480);
        int linux_duration=ap->getDuration()/1000;
        setMusicInfo(file_path_to_play);
        ui->progressSlider->setRange(0,linux_duration);
        printf("----------------------the video totaltime is %d\n",linux_duration);
        QString totalTime=QDateTime::fromTime_t(linux_duration).toString("mm:ss");
        printf("----------------------the video totaltime is %s\n",(char*)totalTime.toStdString().c_str());
        ret=ap->play();
		timer->start(100);
        if(ret!=0)
            qDebug()<<"play bug";
        astatus = ASTATUS_PLAYING;
        this->duration=linux_duration;
        qDebug()<<"total time is"<<duration;
        //can't catch
        //method 1

        QByteArray ba=file_name.toLocal8Bit();
        QTextCodec *codec = QTextCodec::codecForName("GBK");
        QString str = codec->toUnicode(ba);
        ui->label->setText(QString(tr("now play:"))+QString(str));
		
        connect(ui->voiceSlider,SIGNAL(valueChanged(int)),this,SLOT(setVolume(int)));
        connect(ui->progressSlider,SIGNAL(sliderMoved(int)),this,SLOT(seek(int)));
        connect(midwindow,SIGNAL(video_complete()),this,SLOT(on_video_complete()));
    }
#else
    QFileInfo file_path_to_play=file_list.at(current_video);
    QString ab_file_path=file_path_to_play.absoluteFilePath();
    QString file_name=file_path_to_play.fileName();

    player = new QMediaPlayer(0,QMediaPlayer::VideoSurface);
    my_video_widget=new QVideoWidget(this);
    player->setVideoOutput(my_video_widget);
    my_video_widget->show();

    player->setMedia(QMediaContent(QUrl::fromLocalFile(ab_file_path)));
    player->play();

    ui->label->setText(QString(tr("now playing:"))+file_name);
    ui->progressSlider->setRange(0,player->duration()/1000);
    connect(ui->voiceSlider,SIGNAL(valueChanged(int)),player,SLOT(setVolume(int)));
    connect(ui->progressSlider,SIGNAL(sliderMoved(int)),this,SLOT(seek(int)));
    connect(player, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));

#endif
    connect(this,SIGNAL(main_desktop_visible()),pStaticMaindesktop,SLOT(on_main_desktop_visible()));
    connect(ui->voiceSlider,SIGNAL(valueChanged(int)),pStaticSetfirst,SLOT(update_voice(int)));
}
/***********
 * this func is read the music info
 * all: fileSizecdx_uint32 bitrate;
 * bSeekable : this music support seek or not;
 * album[64];albumsz;albumCharEncode: this music's album data;
 * author[64];authorsz;authorCharEncode: this music's author data;
 * genre[64];genresz;genreCharEncode : this music's genre data;
 * title[64];titlesz;titleCharEncode: this music's title data;
 * year[64];yearsz;yearCharEncode:this music's year data;
 * pAlbumArtBuf;nAlbumArtBufSize: this music's poster data,this data can show image directly
 * composer[64];
 * date[64];artist[64];writer[64];albumArtist[64];compilation[64];
 * other unknow data:location[64];rotate[4];
   discNumber;programNum, programIndex;program[PROGRAM_LIMIT];privData;
 ************/
void Music_Player::setMusicInfo(QFileInfo file_path_to_play)
{
#if defined(Q_OS_LINUX)
    QString ab_file_path=file_path_to_play.absoluteFilePath();
    qDebug()<<"the file's absoluteFilePath is"<<ab_file_path;
    QString file_name=file_path_to_play.fileName();
    qDebug()<<"-----------setMusicInfo::"<<ab_file_path;
    demoRetriver = XRetrieverCreate();
    if(NULL == demoRetriver)
    {
        printf("XRetrieverCreate failed\n");
    }
    int ret = XRetrieverSetDataSource(demoRetriver, (char*)ab_file_path.toLatin1().data(), NULL);
    if(ret < 0)
    {
         printf("set datasource failed\n");
    }
    printf("XRetrieverSetDataSource end\n");
    CdxMediaInfoT mi;
    XRetrieverGetMetaData(demoRetriver, METADATA_MEDIAINFO, &mi);
    printf("the video information:titile[64]=[%.02x %.02x %.02x %.02x %.02x]\n",mi.title[0],mi.title[1],mi.title[2],mi.title[3],mi.title[4]);
    printf("the video information:album[64]=[%s] ,albumsz=%d,genre[64]=%s,genresz=%d,title[64]=%s,titlesz=%d,year[64]=%s,yearsz=%d,composer[64]=%s,date[64]=%s\n",
           mi.album,mi.albumsz,mi.genre,mi.genresz,mi.title,mi.titlesz,mi.year,mi.yearsz,mi.composer,mi.date);
    QString album_str="";
    if(mi.albumsz!=0)
    {
        album_str=print_info(mi.album,mi.albumsz);
        qDebug()<<"album is"<<album_str;
        ui->AlbumLabel->setText(album_str);
    }else{
        ui->AlbumLabel->setText(tr("未知专辑 "));
    }
    QString title_str="";
    if(mi.titlesz!=0)
    {
        title_str=print_info(mi.title,mi.titlesz);
        qDebug()<<"title is"<<title_str;
        ui->musicNameLabel->setText(title_str);
    }else{
        ui->musicNameLabel->setText(tr("未知曲目 "));
    }
    QString author_str="";
    if(mi.authorsz!=0)
    {
        author_str=print_info(mi.author,mi.authorsz);
        qDebug()<<"author is"<<author_str;
        ui->authorNameLabel->setText(author_str);
    }else{
        ui->authorNameLabel->setText(tr("佚名 "));
    }
    QString year_str="";
    if(mi.yearsz!=0)
    {
        year_str=print_info(mi.year,mi.yearsz);
        qDebug()<<"year is"<<year_str;
        ui->yearLabel->setText(year_str);
    }else{
        ui->yearLabel->setText(tr("未知年份 "));
    }
    QString compser_str="";
    if(strlen((char*)mi.composer)!=0)
    {
        compser_str=print_info(mi.composer,strlen((char*)mi.composer)+1);
        qDebug()<<"composer is"<<compser_str;
        mediaInfo.compser_str = compser_str;
    }else{
        mediaInfo.compser_str="";
    }
    QString artist_str="";
    if(strlen((char*)mi.artist)!=0)
    {
        artist_str=print_info(mi.artist,strlen((char*)mi.artist)+1);
        qDebug()<<"artist is"<<artist_str;
        mediaInfo.artist_str = artist_str;
    }else{
        mediaInfo.artist_str = "";
    }
    QString writer_str="";
    if(strlen((char*)mi.writer)!=0)
    {
        writer_str=print_info(mi.writer,strlen((char*)mi.writer)+1);
        qDebug()<<"writer is"<<writer_str;
        mediaInfo.writer_str = writer_str;
    }else{
        mediaInfo.writer_str = writer_str;
    }
    QString albumArtist_str="";
    if(strlen((char*)mi.albumArtist)!=0)
    {
        albumArtist_str=print_info(mi.albumArtist,strlen((char*)mi.albumArtist)+1);
        qDebug()<<"albumArtist is"<<albumArtist_str;
        mediaInfo.albumArtist_str = albumArtist_str;
    }else{
        mediaInfo.albumArtist_str = "";
    }
    int filesize=0;
//    filesize=mi.fileSize;
    mediaInfo.filesize=filesize;
    int bitrate=0;
    bitrate=mi.bitrate;
    mediaInfo.bitrate=bitrate;
    int isSeekable=mi.bSeekable;
    if(isSeekable==0){
        mediaInfo.bSeekable=true;
    }else{
        mediaInfo.bSeekable=false;
    }
    if(mi.nAlbumArtBufSize != 0){
        qDebug()<<"this music has poster";
        QImage img=QImage::fromData((const uchar*)mi.pAlbumArtBuf,mi.nAlbumArtBufSize);
        qDebug()<<"posterlabel size"<<ui->posterLabel->size();
        QImage imgScaled=img.scaled(300,300,Qt::KeepAspectRatio);
        QPixmap pix=QPixmap();
        pix.convertFromImage(imgScaled);
        ui->posterLabel->setPixmap(pix);

    }else{
        printf("get videoFrame faild\n");
        QImage img=QImage(":/icon/poster.png");
        QPixmap pix=QPixmap();
        pix.convertFromImage(img.scaled(300,300,Qt::KeepAspectRatio));
        ui->posterLabel->setPixmap(pix);
    }

    XRetrieverDestory(demoRetriver);
    demoRetriver=NULL;
#endif
}

Music_Player::~Music_Player()
{
    delete ui;
#if defined(Q_OS_LINUX)

#endif
}
void Music_Player::on_btnMenu_Min_clicked()
{
    ui->AlbumLabel->setText(tr("辑专:"));
}
void Music_Player::setVolume(int n_value)
{
    qDebug()<<"the voice value is"<<n_value;
    now_voice_value=n_value;
#if defined(Q_OS_LINUX)
    qDebug()<<"player ready to change the voice";
    QString cmd="tinymix 2 "+ QString::number(n_value*2,10);
    system((char*)cmd.toStdString().c_str());
#endif
}
void Music_Player::timerUpdate()
{
#if defined(Q_OS_LINUX)
    int currentTime=ap->getCurrentPosition()/1000;
//    qDebug()<<"current video time is"<<currentTime;
    ui->progressSlider->setValue(currentTime);
    updateDurationInfo(currentTime);
#endif
}

void Music_Player::durationChanged(qint64 duration)
{
    qDebug()<<"------durationchanged";
    this->duration = duration/1000;
    ui->progressSlider->setMaximum(duration / 1000);
}

void Music_Player::positionChanged(qint64 progress)
{
    qDebug()<<"----------positionchanged";
    if (!ui->progressSlider->isSliderDown()) {
        ui->progressSlider->setValue(progress / 1000);
    }
    updateDurationInfo(progress / 1000);
}
void Music_Player::updateDurationInfo(qint64 currentInfo)
{
//    qDebug()<<"update the time label";
    QString tStr;

#if defined(Q_OS_LINUX)
    int linux_duration=ap->getDuration()/1000;
    if(linux_duration==(int)currentInfo)
    {
        currentInfo=0;
        ui->progressSlider->setValue(0);
        astatus = ASTATUS_PAUSED;
        ui->playButton->setIcon(QIcon(":/icon/play.png"));
    }
#endif
    if (currentInfo || duration) {
        QTime currentTime((currentInfo/3600)%60, (currentInfo/60)%60, currentInfo%60, (currentInfo*1000)%1000);
        QTime totalTime((duration/3600)%60, (duration/60)%60, duration%60, (duration*1000)%1000);
        QString format = "mm:ss";
        if (duration > 3600)
            format = "hh:mm:ss";
        tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
    }
    ui->nowTimeLabel->setText(tStr);
}
void Music_Player::play_video(QFileInfo file_path_to_play)
{
#if defined(Q_OS_LINUX)
    QString ab_file_path=file_path_to_play.absoluteFilePath();
    qDebug()<<"the file's absoluteFilePath is"<<ab_file_path;
    QString file_name=file_path_to_play.fileName();
    qDebug()<<"the music name: "<<file_name<<"while play";
    int ret=0;
    if(ap!=NULL){
        delete ap;
    }
    ap = new AUTPlayer();
    if(ap == NULL){
        qDebug()<<"new AutPlayer error";
        return ;
    }
    astatus = ASTATUS_STOPPED;
    if(ab_file_path.isEmpty())
    {
        qDebug()<<"file path is error";
    }
    qDebug()<<"here------------0";
    ret = ap->setUrl((char*)ab_file_path.toLatin1().data());
    if (ret < 0)
    {
        qDebug()<<"setUrl is error-------------------";
         ui->label->setText("");
        frmMessageBox *msg=new frmMessageBox(this);
        msg->SetMessage(QString(tr("video not support!")),0);
        msg->exec();
        return ;
    }
    qDebug()<<"here------------1";
    ap->setUserCb(autCb_func, this);
    ap->setViewWindow(0, 0, 800, 480);
    qDebug()<<"here------------2";
    int linux_duration=ap->getDuration()/1000;
    ui->progressSlider->setRange(0,linux_duration);
    printf("----------------------the video totaltime is %d\n",linux_duration);
    QString totalTime=QDateTime::fromTime_t(linux_duration).toString("mm:ss");
    printf("----------------------the video totaltime is %s\n",(char*)totalTime.toStdString().c_str());
    ret=ap->play();
    qDebug()<<"here------------3";
    if(ret!=0)
        qDebug()<<"play bug";
    this->duration=linux_duration;
    qDebug()<<"total time is"<<duration;
    QByteArray ba=file_name.toLocal8Bit();
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QString str = codec->toUnicode(ba);
    ui->label->setText(QString(tr("now play:"))+QString(str));
    astatus = ASTATUS_PLAYING;
    timer->start(100);
    ui->playButton->setIcon(QIcon(":/icon/Pause.png"));
#endif
}
void Music_Player::seek(int seconds)
{
#if defined(Q_OS_LINUX)
    int ret=0;
    qDebug()<<"ready to seekto"<<seconds<<"s";
    timer->stop();
    int currentTime=ap->getCurrentPosition()/1000;
    astatus = ASTATUS_SEEKING;
    ret=ap->seekto(seconds);
    if(ret!=0)
        qDebug()<<"seekto bug";
    if (!ui->progressSlider->isSliderDown()) {
        ui->progressSlider->setValue(currentTime);
    }
    updateDurationInfo(seconds);
    timer->start(100);
#else
    player->setPosition(seconds * 1000);
#endif
}

void Music_Player::on_btnMenu_Max_clicked()
{
    #if defined(Q_OS_LINUX)
    timer->stop();
        #if defined(USE_AUTPLAYER)
    if(ap!=NULL){
        ap->stop();
        delete ap;
        ap=NULL;
    }
        #endif
        astatus = ASTATUS_STOPPED;
    #else
        player->stop();
    #endif
    this->close();
//        pStaticMaindesktop->setHidden(false);
    pStaticMaindesktop->on_main_desktop_visible();
     pStaticMovieDesk->setHidden(false);
}

void Music_Player::on_btnMenu_Close_clicked()
{
#if defined(Q_OS_LINUX)
    #if defined(USE_AUTPLAYER)
    timer->stop();
    if(ap!=NULL){
        ap->stop();
        delete ap;
        ap=NULL;
    }

    #endif
    astatus = ASTATUS_STOPPED;

#else
    player->stop();
#endif
    this->close();
    pStaticMaindesktop->on_main_desktop_visible();
    pStaticMovieDesk->setHidden(false);

}

void Music_Player::on_playButton_clicked()
{
//    qDebug()<<"start video";
#if defined(Q_OS_LINUX)
    if(ap==NULL&&astatus == ASTATUS_STOPPED)
    {
        QFileInfo file_path_to_play=file_list.at(current_video);
        play_video(file_path_to_play);
        astatus = ASTATUS_PLAYING;
        ui->playButton->setIcon(QIcon(":/icon/Pause.png"));
    }
    else{
        int ret=0;
        ret=ap->pause();
        if(ret!=0)
            qDebug()<<"pause bug";
        if (astatus == ASTATUS_PAUSED)
        {
          astatus = ASTATUS_PLAYING;
          ui->playButton->setIcon(QIcon(":/icon/Pause.png"));
        }
        else
        {
          astatus = ASTATUS_PAUSED;
          ui->playButton->setIcon(QIcon(":/icon/play.png"));
        }
    }
#else
    if(isPlaying){
        qDebug()<<"pause video";
        player->pause();
        ui->playButton->setIcon(QIcon(":/icon/play.png"));
        isPlaying=false;
    }else{
        qDebug()<<"start video";
        player->play();
        ui->playButton->setIcon(QIcon(":/icon/Pause.png"));
        isPlaying=true;
    }

#endif
}

void Music_Player::on_muteButton_clicked()
{
#if !defined(Q_OS_LINUX)
    qDebug()<<"set muted";
    if(!isMuted){
        qDebug()<<"now is not muted";
        player->setMuted(true);
        ui->muteButton->setIcon(QIcon(":/icon/mute.png"));
        ui->voiceSlider->setValue(0);
        isMuted=true;
    }else{
        qDebug()<<"now is muted";
        player->setMuted(false);
        ui->voiceSlider->setValue(now_voice_value);
        ui->muteButton->setIcon(QIcon(":/icon/voice.png"));
        isMuted=false;
    }
#else
    qDebug()<<"set muted";
    if(!isMuted){
        qDebug()<<"now is not muted";
        ui->muteButton->setIcon(QIcon(":/icon/mute.png"));
        ui->voiceSlider->setValue(0);
        isMuted=true;
    }else{
        qDebug()<<"now is muted";
        ui->voiceSlider->setValue(now_voice_value);
        ui->muteButton->setIcon(QIcon(":/icon/voice.png"));
        isMuted=false;
    }
#endif
}

void Music_Player::show_title()
{
    int fontId = QFontDatabase::addApplicationFont(":/font/fontawesome-webfont.ttf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont iconFont = QFont(fontName);
    iconFont.setPointSize(10);
    ui->btnMenu_Close->setFont(iconFont);
    ui->btnMenu_Close->setText(QChar(0xf00d));
    ui->btnMenu_Max->setFont(iconFont);
    ui->btnMenu_Max->setText( QChar(0xf096));
    ui->btnMenu_Min->setFont(iconFont);
    ui->btnMenu_Min->setText( QChar(0xf068));
    iconFont.setPointSize(12);
    ui->lab_Ico->setFont(iconFont);
    ui->lab_Ico->setText( QChar(0xf015));
#if !defined(Q_OS_LINUX)
    ui->label->setFont(iconFont);
    ui->nowTimeLabel->setFont(iconFont);
#endif
}
void Music_Player::FormInCenter()
{
    QDesktopWidget w;
    int deskWidth = w.width();
    int deskHeight = w.height();
    this->resize(deskWidth,deskHeight);
}
//clean up the ui for sync
void Music_Player::clean_window_for_other_music()
{
    if(tablewidget != NULL){
        tablewidget->setHidden(true);
        delete tablewidget;
        tablewidget = NULL;
    }
    ui->musicNameLabel->setText("");
    ui->authorNameLabel->setText("");
    ui->AlbumLabel->setText("");
    ui->yearLabel->setText("");
    ui->label->setText("");
    ui->nowTimeLabel->setText("00:00/00:00");
}

void Music_Player::on_preMovieButton_clicked()
{
    qDebug()<<"-----------------on_preMovieButton_clicked,here";
#if defined(Q_OS_LINUX)
    if(current_video-1>=0){
        clean_window_for_other_music();
        timer->stop();
        if(!is_dir_exist((char*)current_path.toStdString().c_str()))
        {

            QFileInfo file_path_to_play=file_list.at(--current_video);
            setMusicInfo(file_path_to_play);
            play_video(file_path_to_play);
        }
    }else{
        qDebug()<<"this is the first music"<<current_video<<file_list.size();
        frmMessageBox *msg=new frmMessageBox(this);
        msg->SetMessage(QString(tr("this is first music!")),0);
        QTimer::singleShot(8000, msg, SLOT(close()));
        msg->show();
        qDebug()<<"pre next is ok";
    }
#else
    if(current_video-1>=0){
        file_list=GetFileList(dir);
        QFileInfo file_path_to_play=file_list.at(--current_video);
        QString ab_file_path=file_path_to_play.absoluteFilePath();
        QString file_name=file_path_to_play.fileName();
        player->setMedia(QMediaContent(QUrl::fromLocalFile(ab_file_path)));
        player->play();

        ui->label->setText(QString(tr("now playing:"))+file_name);
        ui->progressSlider->setRange(0,player->duration()/1000);
    }else{
        qDebug()<<"this is the first music"<<current_video<<file_list.size();
        frmMessageBox *msg=new frmMessageBox(this);
        msg->SetMessage(QString(tr("this is first music!")),0);
        QTimer::singleShot(8000, msg, SLOT(close()));
        msg->show();
        qDebug()<<"pre next is ok";

    }

#endif
}

void Music_Player::on_nextMovieButton_clicked()
{
    qDebug()<<"-----------------on_nextMovieButton_clicked,here";
#if defined(Q_OS_LINUX)
    if(current_video+1<file_list.size()){
        clean_window_for_other_music();
        qDebug()<<"----------------now is:"<<current_video<<"\n-----------------------total is"<<file_list.size();
        timer->stop();
        if(!is_dir_exist((char*)current_path.toStdString().c_str()))
        {
            QFileInfo file_path_to_play=file_list.at(++current_video);
            setMusicInfo(file_path_to_play);
            play_video(file_path_to_play);
        }
    }else{
        qDebug()<<"this is the last music"<<current_video<<file_list.size();
        frmMessageBox *msg=new frmMessageBox(this);
        msg->SetMessage(QString(tr("this is last music!")),0);
        QTimer::singleShot(8000, msg, SLOT(close()));
        msg->show();
//        QMessageBox::information(this,tr("information"),tr("this is last music!"));
        qDebug()<<"pre next is ok";
    }
#else
    if(current_video+1<file_list.size()){
        file_list=GetFileList(dir);
        QFileInfo file_path_to_play=file_list.at(++current_video);
        QString ab_file_path=file_path_to_play.absoluteFilePath();
        QString file_name=file_path_to_play.fileName();
        player->setMedia(QMediaContent(QUrl::fromLocalFile(ab_file_path)));
        player->play();
        ui->label->setText(QString(tr("now playing"))+file_name);
        ui->progressSlider->setRange(0,player->duration()/1000);
    }else{
        qDebug()<<"this is the last music"<<current_video<<file_list.size();
        frmMessageBox *msg=new frmMessageBox(this);
        msg->SetMessage(QString(tr("this is last music!")),0);
        QTimer::singleShot(8000, msg, SLOT(close()));
        msg->show();
//        QMessageBox::information(this,tr("information"),tr("this is last music!"));
        qDebug()<<"pre next is ok";
    }

#endif
}
QFileInfoList Music_Player::GetFileList(QDir dir)
{
    qDebug()<<"get all music file name";
    QStringList filters;
    filters <<"*.mp3"<<"*.wav"<<"*.aac"<<"*.flac"<<"*.ape"<<"*.pcm";
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setNameFilters(filters);
    dir.setSorting(QDir::Name);
    QFileInfoList file_list=dir.entryInfoList();
    for(int i=0;i<file_list.size();i++)
    {
        QFileInfo fileInfo=file_list.at(i);
        fileInfo.absoluteFilePath();
//        qDebug()<<fileInfo.fileName();
    }
    return file_list;
}

void Music_Player::mouseDoubleClickEvent(QMouseEvent *)
{
    on_mouse_active();
}
void Music_Player::mouseMoveEvent(QMouseEvent *)
{
    on_mouse_active();
}
void Music_Player::mousePressEvent(QMouseEvent *)
{
    on_mouse_active();
}
void Music_Player::mouseReleaseEvent(QMouseEvent *)
{
    on_mouse_active();
}

void Music_Player::on_mouse_active()
{
//    mouseMoveTime->stop();
//    mouseMoveTime->start(100000);

    ui->widget->setVisible(true);
    ui->titlewidget->setVisible(true);
}
void Music_Player::on_timeout_mouserMoveTime()
{
    ui->widget->setVisible(false);
    ui->titlewidget->setVisible(false);
}

void Music_Player::on_otherInfo_clicked()
{
    if(!isOpen){
        int w,h;
        tablewidget = new QTableWidget(this);
        tablewidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        tablewidget->setColumnCount(2);
        tablewidget->setRowCount(7);
        tablewidget->setItem(0,0,new QTableWidgetItem(tr("文件大小")));
        tablewidget->setItem(1,0,new QTableWidgetItem(tr("比特率")));
        tablewidget->setItem(2,0,new QTableWidgetItem(tr("快进")));
        tablewidget->setItem(3,0,new QTableWidgetItem(tr("compser")));
        tablewidget->setItem(4,0,new QTableWidgetItem(tr("artist")));
        tablewidget->setItem(5,0,new QTableWidgetItem(tr("writer")));
        tablewidget->setItem(6,0,new QTableWidgetItem(tr("albumArtist")));
        //QString compser_str;QString artist_str;QString writer_str;QString albumArtist_str;
        // tablewidget->setItem(1,1,new QTableWidgetItem(tr("我是测试1")));
        if(mediaInfo.filesize != 0){
            tablewidget->setItem(0,1,new QTableWidgetItem(mediaInfo.filesize));
        }else{
            tablewidget->setItem(0,1,new QTableWidgetItem(tr("未获取到")));
        }
        if(mediaInfo.bitrate != 0){
             tablewidget->setItem(1,1,new QTableWidgetItem(mediaInfo.bitrate));
        }else{
            tablewidget->setItem(1,1,new QTableWidgetItem(tr("未获取到")));
        }
        if(mediaInfo.bSeekable){
            tablewidget->setItem(2,1,new QTableWidgetItem(tr("是")));
        }else{
            tablewidget->setItem(2,1,new QTableWidgetItem(tr("否")));
        }
        if(mediaInfo.compser_str.isEmpty()){
            tablewidget->setItem(3,1,new QTableWidgetItem(tr("无")));
        }else{
            tablewidget->setItem(3,1,new QTableWidgetItem(mediaInfo.compser_str));
        }
        if(mediaInfo.artist_str.isEmpty()){
            tablewidget->setItem(4,1,new QTableWidgetItem(tr("无")));
        }else{
            tablewidget->setItem(4,1,new QTableWidgetItem(mediaInfo.artist_str));
        }
        if(mediaInfo.writer_str.isEmpty()){
            tablewidget->setItem(5,1,new QTableWidgetItem(tr("无")));
        }else{
            tablewidget->setItem(5,1,new QTableWidgetItem(mediaInfo.writer_str));
        }
        if(mediaInfo.albumArtist_str.isEmpty()){
            tablewidget->setItem(6,1,new QTableWidgetItem(tr("无")));
        }else{
            tablewidget->setItem(6,1,new QTableWidgetItem(mediaInfo.albumArtist_str));
        }
        tablewidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tablewidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
        QHeaderView* headerView = tablewidget->verticalHeader();
        headerView->setHidden(true);
        tablewidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tablewidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tablewidget->setRowHeight(0,30);
        tablewidget->setColumnWidth(0,100);
        tablewidget->resize(423,440);
        qDebug()<<"pushbutton"<<ui->otherInfo->size();
        qDebug()<<"pushbutton"<<ui->otherInfo->x()<<ui->otherInfo->y();
        w = ui->otherInfo->x() + ui->otherInfo->width() - tablewidget->width();
        h = ui->widget->y() - tablewidget->height();
        qDebug()<<w<<h<<tablewidget->size();
        tablewidget->move(w,33);
        QStringList headers;
        headers<<"名  称"<<"详细信息";
        tablewidget->setHorizontalHeaderLabels(headers);
        tablewidget->show();

        isOpen = true;
    }else{
        tablewidget->setHidden(true);
        delete tablewidget;
        isOpen = false;
    }
}

void Music_Player::on_video_complete()
{
    qDebug()<<"music player get video complete signal";
    astatus = ASTATUS_STOPPED;
    ui->progressSlider->setValue(0);
    ui->playButton->setIcon(QIcon(":/icon/play.png"));
    #ifdef AGEING_TEST_MUSIC //ageing test
    qDebug()<<"start forever play mode";
    if(current_video+1<file_list.size()){
        on_nextMovieButton_clicked();
    }else{
        current_video=0;
        on_nextMovieButton_clicked();
    }
    #else
    on_stopButton_clicked();
    #endif
}

