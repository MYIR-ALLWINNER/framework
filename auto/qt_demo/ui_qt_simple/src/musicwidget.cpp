#include "musicwidget.h"
#include "ui_musicwidget.h"
#include <QDesktopWidget>
#include <QDir>
#include "main_desktop.h"
#include "midwindow.h"
#include "moviedesk1.h"
#include "frmmessagebox.h"
#include <QTextCodec>
extern main_desktop* pStaticMaindesktop;
extern movieDesk1* pStaticMovieDesk;
extern QFileInfo fileInfo_music_to_play;
const QString win_path="E:/tech_practise/DvrUI/DvrUI/video/";
extern QString linux_usb_path;//U
extern QString linux_sdcard_path;//sd
extern QString print_info(unsigned char tmp[],int tmp2);
extern MidWindow* midwindow;
extern int video_support_or_not(QWidget* tmp_widget,QFileInfo file_to_play);
extern QString prase_path(QString linux_path);
MusicWidget::MusicWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MusicWidget)
{
    ui->setupUi(this);
    show_model=true;
    ui->listWidget->clear();

    show_file();
#if defined(Q_OS_LINUX)
    demoRetriver=NULL;

#endif
    connect(midwindow,SIGNAL(usb_insert()),this,SLOT(on_usb_mount()));
    connect(midwindow,SIGNAL(usb_delete()),this,SLOT(on_usb_umount()));
}
void MusicWidget::show_file()
{
    qDebug()<<"music widget is showing file";
    #if defined(Q_OS_LINUX)
    qDebug()<<"now path is "<<linux_usb_path;
    file_list=GetFileList(prase_path(linux_usb_path));
    #else
    file_list=GetFileList(win_path);
    #endif
    ui->listWidget->setObjectName(QString::fromUtf8("listWidget"));
    ui->listWidget->setMovement(QListView::Static);

    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

    ui->listWidget->setSpacing(12);
    ui->listWidget->setResizeMode(QListView::Adjust);
    if(show_model){

        ui->listWidget->setViewMode(QListView::IconMode);
        ui->listWidget->setIconSize(QSize(100,100));

        ui->listWidget->setDragEnabled(false);
        show_file_by_iconview(file_list);
    }else{

        ui->listWidget->setViewMode(QListView::ListMode);
        ui->listWidget->setDragEnabled(false);
        ui->listWidget->setIconSize(QSize(22,22));
        show_file_by_listview(file_list);
    }
}
void MusicWidget::on_usb_mount()
{
    qDebug()<<"MusicWidget get the signal usb insert";

    show_file();
}
void MusicWidget::on_usb_umount()
{
    qDebug()<<"MusicWidget get the signal usb delete";

    ui->listWidget->clear();
}
MusicWidget::~MusicWidget()
{
    delete ui;
#if defined(Q_OS_LINUX)

#endif
}

void MusicWidget::on_listWidget_clicked(const QModelIndex &pos)
{
    QListWidgetItem* item=ui->listWidget->currentItem();
    qDebug()<<"filename"<<item->text();
    qDebug()<<"which file:"<<pos.row();
    fileInfo_music_to_play=file_list.at(pos.row());
    int ret=0;
    ret=video_support_or_not(this,fileInfo_music_to_play);
    if(!ret){
//        if(music_player!=NULL){
//            delete music_player;
//            music_player=NULL;
//        }
        music_player=new Music_Player(this);
        pStaticMovieDesk->setHidden(true);
        pStaticMaindesktop->on_main_desktop_disvisible();//close camera priview
        music_player->exec();
    }
}
void MusicWidget::getMusicInfo(QFileInfo file_path_to_play)
{
#if defined(Q_OS_LINUX)
    QString ab_file_path=file_path_to_play.absoluteFilePath();
    qDebug()<<"the file's absoluteFilePath is"<<ab_file_path;
    QString file_name=file_path_to_play.fileName();
    qDebug()<<"-----------getMusicInfo::"<<ab_file_path;
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

    QString album_str="";
    if(mi.albumsz!=0)
    {
        album_str=print_info(mi.album,mi.albumsz);
        qDebug()<<"album is"<<album_str;
    }else{
    }
    QString title_str="";
    if(mi.titlesz!=0)
    {
        title_str=print_info(mi.title,mi.titlesz);
        qDebug()<<"title is"<<title_str;
    }else{
    }
    QString author_str="";
    if(mi.authorsz!=0)
    {
        author_str=print_info(mi.author,mi.authorsz);
        qDebug()<<"author is"<<author_str;
    }else{
    }
    QString year_str="";
    if(mi.yearsz!=0)
    {
        year_str=print_info(mi.year,mi.yearsz);
        qDebug()<<"year is"<<year_str;
    }else{
    }
    XVideoFrame* videoFrame = NULL;
    videoFrame = XRetrieverGetFrameAtTime(demoRetriver, 1, 0);
    if(NULL == videoFrame){
        printf("get videoFrame faild\n");
        QPixmap pix=QPixmap(":/icon/poster.jpg");
    }else{
        printf("in musicwidget mWidth=%d,h=%d,dispW=%d,dispH=%d,size=%d\n",videoFrame->mWidth,videoFrame->mHeight,
                                videoFrame->mDisplayWidth,videoFrame->mDisplayHeight,videoFrame->mSize);
        int w,h;
        w=videoFrame->mDisplayWidth;
        h=videoFrame->mDisplayHeight;
        QImage* img=new QImage((const uchar*)videoFrame->mData,w,h,QImage::Format_RGB16);
        QImage imgScaled=img->scaled(120,90,Qt::KeepAspectRatio);
        QPixmap pix=QPixmap();
        pix.convertFromImage(imgScaled);
    }
    XRetrieverDestory(demoRetriver);
    demoRetriver=NULL;
#endif
}
QFileInfoList MusicWidget::GetFileList(QString dir_str)
{
    QDir dir(dir_str);
    qDebug()<<"-----------------------------------------------"<<dir.exists()<<dir.isReadable();
    qDebug()<<"GetFileList:"<<"now path is :"<<dir.path();
    qDebug()<<"get all file name";
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
        qDebug()<<fileInfo.fileName();
    }

    qDebug()<<"this path has"<<file_list.size()<<"files";
    return file_list;
}
void MusicWidget::show_file_by_iconview(QFileInfoList file_list)
{
    qDebug()<<"show_file_by_iconview";
    qDebug()<<"file_list has "<<file_list.size()<<" files";
    ui->listWidget->setIconSize(QSize(100,100));
    for(int i=0;i<file_list.size();i++)
    {
        QFileInfo file_info=file_list.at(i);
        QString tempFilePath=file_info.absoluteFilePath();
        int filename_index=tempFilePath.lastIndexOf("/");
        QString tempFileName=tempFilePath.right(tempFilePath.size()-filename_index-1);
//        qDebug()<<"file name:"<<tempFileName;
        QString tempFileName_NoSuffix=tempFileName;
        int suffix_index=tempFileName_NoSuffix.lastIndexOf(".");
        tempFileName_NoSuffix.truncate(suffix_index);
//        qDebug()<<"the no_suffix filename:"<<tempFileName_NoSuffix;
        QString icon_file_path="";

        QTextCodec *codec = QTextCodec::codecForName("GB2312");
        QString str = codec->toUnicode(tempFileName.toLatin1().data());
        QListWidgetItem *pItem;
        if(icon_file_path==""){
            QPixmap objPixmap1(":/icon/no_shotvideo.png");
            pItem=new QListWidgetItem(QIcon(objPixmap1.scaled(QSize(100,70))),str);
        }else{
            QPixmap objPixmap(icon_file_path);
            pItem = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,70))),str);
        }
        pItem->setSizeHint(QSize(100,90));
        ui->listWidget->addItem(pItem);
    }
}
void MusicWidget::show_file_by_listview(QFileInfoList file_list)
{
    ui->listWidget->setIconSize(QSize(22,22));
    for(int i=0;i<file_list.size();i++)
    {
        QFileInfo file_info=file_list.at(i);
        QString tempFilePath=file_info.absoluteFilePath();
        int filename_index=tempFilePath.lastIndexOf("/");
        QString tempFileName=tempFilePath.right(tempFilePath.size()-filename_index-1);

//        qDebug()<<"file name:"<<tempFileName;
        QString tempFileName_NoSuffix=tempFileName;
        int suffix_index=tempFileName_NoSuffix.lastIndexOf(".");
        tempFileName_NoSuffix.truncate(suffix_index);
//        qDebug()<<"the no_suffix filename:"<<tempFileName_NoSuffix;
        QString icon_file_path="";

        QListWidgetItem *pItem;
        if(icon_file_path==""){
            pItem=new QListWidgetItem(QIcon(":/icon/no_shotvideo.png"),tempFileName);
        }else{

            QPixmap objPixmap(icon_file_path);
            QListWidgetItem *pItem = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(20,20))),tempFileName);
            pItem->setSizeHint(QSize(22,22));
        }
        pItem->setSizeHint(QSize(90,90));
        ui->listWidget->addItem(pItem);
    }
}
