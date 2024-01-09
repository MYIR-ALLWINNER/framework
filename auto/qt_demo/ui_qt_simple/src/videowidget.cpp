#include "videowidget.h"
#include "ui_videowidget.h"
#include <QDesktopWidget>
#include "main_desktop.h"
#include "midwindow.h"
#include "frmmessagebox.h"
#include "moviedesk1.h"
#include <sys/time.h>
#include <QTime>
#include <QModelIndex>
#include <QTextCodec>
extern movieDesk1* pStaticMovieDesk;
extern main_desktop* pStaticMaindesktop;
// This is available in all editors.
extern QFileInfo fileInfo_to_play;
const QString win_path="E:/tech_practise/DvrUI/DvrUI/video/";
//const QString linux_path="/mnt/sdcard/mmcblk1p1/frontVideo/";//sdcard
extern QString linux_usb_path;//U
extern QString linux_sdcard_path;//sd

extern MidWindow* midwindow;
extern QString get_utf8_string(QString str);
extern int video_support_or_not(QWidget* tmp_widget,QFileInfo file_to_play);
extern QString prase_path(QString linux_path);
videoWidget::videoWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::videoWidget)
{
    ui->setupUi(this);
//    ui->listWidget_file=new QListWidget(this);
    show_model=true;
    ui->listWidget_file->clear();

#if defined(Q_OS_LINUX)

#endif
    show_file();

    connect(ui->listWidget_file,SIGNAL(clicked(QModelIndex)),this,SLOT(play_video(QModelIndex)));

    connect(this,SIGNAL(main_desktop_disvisible()),pStaticMaindesktop,SLOT(on_main_desktop_disvisible()));

    connect(midwindow,SIGNAL(usb_insert()),this,SLOT(on_usb_mount()));
    connect(midwindow,SIGNAL(usb_delete()),this,SLOT(on_usb_umount()));

}
void videoWidget::show_file()
{
    qDebug()<<"video widget is showing file";
    #if defined(Q_OS_LINUX)
    qDebug()<<"now path is "<<linux_usb_path;
    file_list=GetFileList(prase_path(linux_usb_path));
    #else
    file_list=GetFileList(win_path);
    #endif
    ui->listWidget_file->setObjectName(QString::fromUtf8("listWidget_file"));
    ui->listWidget_file->setMovement(QListView::Static);

    ui->listWidget_file->setSelectionMode(QAbstractItemView::ExtendedSelection);
    //ui->listWidget_file->selectAll();
    ui->listWidget_file->setSpacing(10);
    ui->listWidget_file->setResizeMode(QListView::Adjust);
    if(show_model){

        ui->listWidget_file->setViewMode(QListView::IconMode);
        ui->listWidget_file->setIconSize(QSize(100,100));

        ui->listWidget_file->setDragEnabled(false);
        show_file_by_iconview(file_list);
    }else{

        ui->listWidget_file->setViewMode(QListView::ListMode);
        ui->listWidget_file->setDragEnabled(false);
        ui->listWidget_file->setIconSize(QSize(22,22));
        show_file_by_listview(file_list);
    }
}
void videoWidget::on_usb_mount()
{
    qDebug()<<"videowidget get the signal usb insert";

    show_file();
}
void videoWidget::on_usb_umount()
{
    qDebug()<<"videowidget get the signal usb delete";

    ui->listWidget_file->clear();
}

QFileInfoList videoWidget::GetFileList(QString dir_str)
{
    QDir dir(dir_str);
    qDebug()<<"-----------------------------------------------"<<dir.exists()<<dir.isReadable();
    qDebug()<<"GetFileList:"<<"now path is :"<<dir.path();
    qDebug()<<"get all file name";
    QStringList filters;
    filters << "*.mp4" << "*.avi"<<"*.mkv"<<"*.vob"<<"*.flv"<<"*.wmv"<<"*.h264"
            <<"*.h263"<<"*.mpeg2"<<"*.mpeg4"<<"*.ts";
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);
    dir.setNameFilters(filters);
    QFileInfoList file_list=dir.entryInfoList();

    for(int i=0;i<file_list.size();i++)
    {
        QFileInfo fileInfo=file_list.at(i);
        fileInfo.absoluteFilePath();
        QTextCodec *codec = QTextCodec::codecForName("GB2312");
        QString str = codec->toUnicode(fileInfo.fileName().toLatin1().data());
        qDebug()<<"before code filename:"<<fileInfo.absoluteFilePath();
//        qDebug()<<"after code filename:"<<str.toUtf8().toHex().toUpper()<<str;
//        pStaticMovieDesk->ui->viceButton->setText(str);
//        qDebug()<<fileInfo.fileName();
    }
    qDebug()<<"this path has"<<file_list.size()<<"files";
    return file_list;
 }
void videoWidget::show_file_by_iconview(QFileInfoList file_list)
{
    qDebug()<<"show_file_by_iconview";
    qDebug()<<"file_list has "<<file_list.size()<<" files";
    ui->listWidget_file->setIconSize(QSize(100,100));
    for(int i=0;i<file_list.size();i++)
    {
        QFileInfo file_info=file_list.at(i);
        qDebug()<<"show_file_by_iconview:::"<<file_info.absoluteFilePath();
        QString tempFilePath=file_info.absoluteFilePath();
        int filename_index=tempFilePath.lastIndexOf("/");
        QString tempFileName=tempFilePath.right(tempFilePath.size()-filename_index-1);
//        qDebug()<<"file name:"<<tempFileName;
        QString tempFileName_NoSuffix=tempFileName;
        int suffix_index=tempFileName_NoSuffix.lastIndexOf(".");
        tempFileName_NoSuffix.truncate(suffix_index);
        QString temp = tempFileName.toUtf8().toHex().toUpper();
        qDebug()<<"filename:"<<tempFileName<<"'s"<<" UTF-8 code is:"<<temp;
        QTextCodec *codec = QTextCodec::codecForName("GB2312");
        QString str = codec->toUnicode(tempFileName.toLatin1().data());
        qDebug()<<"in show_file_by_icon:"<<str;
        QString icon_file_path="";
        QPixmap pix("");

        QListWidgetItem *pItem;
        QPixmap objPixmap1(":/icon/no_shotvideo.png");
        pItem=new QListWidgetItem(QIcon(objPixmap1.scaled(QSize(120,90))),str);

        pItem->setSizeHint(QSize(120,100));
        ui->listWidget_file->addItem(pItem);
//        QModelIndex pos=ui->listWidget_file->currentIndex();
//        int pos=ui->listWidget_file->currentRow();
//        qDebug()<<"show_file_by_iconview:"<<pos;
        gen_shot_picture(tempFileName_NoSuffix,icon_file_path,tempFileName,tempFilePath,pix,i);
    }
}
void videoWidget::show_file_by_listview(QFileInfoList file_list)
{
    ui->listWidget_file->setIconSize(QSize(22,22));
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

        QTextCodec *codec = QTextCodec::codecForName("GB2312");
        QString str = codec->toUnicode(tempFileName.toLatin1().data());
        qDebug()<<"the no_suffix filename:"<<tempFileName_NoSuffix;
        QString icon_file_path="";
        QPixmap pix("");

        QListWidgetItem *pItem;
        QPixmap objPixmap1(":/icon/no_shotvideo.png");
        pItem=new QListWidgetItem(QIcon(objPixmap1.scaled(QSize(120,90))),str);

        pItem->setSizeHint(QSize(20,20));
        ui->listWidget_file->addItem(pItem);
        int pos=ui->listWidget_file->currentRow();

        gen_shot_picture(tempFileName_NoSuffix,icon_file_path,tempFileName,tempFilePath,pix,pos);
    }

}
void videoWidget::gen_shot_picture(QString tempFileName_NoSuffix,QString file_path,QString tempFileName,QString ab_file_path,QPixmap pix,int pos)
{
    qDebug() <<"gen_shot_picture:" <<tempFileName_NoSuffix;
    qDebug()<<"gen_shot_picture:"<<pos;
    QThread* thread = new ThumbnailThread(tempFileName_NoSuffix,file_path,tempFileName, ab_file_path, pix,pos);
    connect(thread, SIGNAL(thumbnailFinished(QPixmap,QString,int)), this, SLOT(add_shot_pic(QPixmap,QString,int)));
    connect(thread, SIGNAL(thumbnailFailed(const QString)), this, SLOT(showError(const QString)));
    connect(thread, SIGNAL(finished()), this, SLOT(deleteThread()));
    thread->start();
}

void videoWidget::deleteThread()
{
    QObject* obj = sender();
    obj->deleteLater();
}
void videoWidget::showError(QString filename)
{
    qDebug()<<"can't get shot_pic for"<<filename;
}
void videoWidget::add_shot_pic(QPixmap pix,QString file_path,int pos)
{
    qDebug()<<"add_shot_pic"<<"------------------------here1";
    qDebug()<<"add_shot_pic::"<<pos;
    QListWidgetItem* pItem=ui->listWidget_file->takeItem(pos);
    qDebug()<<"add_shot_pic test:"<<pos<<"is"<<pItem->text();
    if(file_path==""&&pix.isNull()){
        qDebug()<<"can't get shot_pic";
        return;
    }else{
        QPixmap objPixmap;
        if(file_path!="")
        {
        #if defined(Q_OS_LINUX)
            objPixmap=QPixmap(":/icon/no_shotvideo.png");
        #else
            objPixmap=QPixmap(file_path);
        #endif
        }else{
             objPixmap=pix;
        }
       objPixmap=objPixmap.scaled(QSize(120,90));
       if(objPixmap.save(QString("/mnt/usb/sda4/pic/%1.png").arg(pos))){
           qDebug()<<"shot_pic save successful";
       }
       pItem->setIcon(objPixmap);
    }
    ui->listWidget_file->insertItem(pos,pItem);
}
videoWidget::~videoWidget()
{
    delete ui;
#if defined(Q_OS_LINUX)

#endif
}
void videoWidget::play_video(QModelIndex pos)
{
    QListWidgetItem* item=ui->listWidget_file->currentItem();
    qDebug()<<"filename"<<item->text();
    qDebug()<<"which file:"<<pos.row();

    fileInfo_to_play=file_list.at(pos.row());
    int ret=0;
    ret=video_support_or_not(this,fileInfo_to_play);
    if(!ret){
//        if(video_players!=NULL){
//            delete video_players;
//            video_players=NULL;
//        }
        video_players=new Video_Player(this);
        pStaticMovieDesk->setHidden(true);//hide moviedesk
        pStaticMaindesktop->on_main_desktop_disvisible();//close camera priview
        video_players->showNormal();
    }
}


ThumbnailThread::ThumbnailThread(QString tempFileName_NoSuffix_arg,QString file_path_arg,QString tempFileName_arg,QString ab_file_path_arg,QPixmap pix_arg,int pos_arg)
{
    tempFileName_NoSuffix=tempFileName_NoSuffix_arg;
    file_path=file_path_arg;
    tempFileName=tempFileName_arg;
    ab_file_path=ab_file_path_arg;
    shot_pic=pix_arg;
    pos=pos_arg;
}
void ThumbnailThread::run()
{
#if defined(Q_OS_LINUX)
    file_path="";
    XRetriever* demoRetriver;
    qDebug()<<"getting"<<ab_file_path<<"'s shot_pic";
    demoRetriver = XRetrieverCreate();
    if(NULL == demoRetriver)
    {
        printf("XRetrieverCreate failed,%s\n",(char*)ab_file_path.toLatin1().data());
    }
    int ret = XRetrieverSetDataSource(demoRetriver, (char*)ab_file_path.toLatin1().data(), NULL);
    if(ret < 0)
    {
         printf("set datasource failed,%s\n",(char*)ab_file_path.toLatin1().data());
    }
    printf("XRetrieverSetDataSource end\n");

    XVideoFrame* videoFrame = NULL;
    videoFrame = XRetrieverGetFrameAtTime(demoRetriver, 5, 0);

    if(NULL == videoFrame){
        qDebug()<<"this video don't have any shot pic can use"<<ab_file_path;

        emit thumbnailFailed(tempFileName);

        printf("get videoFrame faild,%s\n",(char*)ab_file_path.toLatin1().data());
    }else{
        qDebug()<<"this video has shot pic";
        printf("mWidth=%d,h=%d,dispW=%d,dispH=%d,size=%d,%s\n",videoFrame->mWidth,videoFrame->mHeight,
                                videoFrame->mDisplayWidth,videoFrame->mDisplayHeight,videoFrame->mSize,
                                (char*)ab_file_path.toLatin1().data());
        int w,h;
        w=videoFrame->mDisplayWidth;
        h=videoFrame->mDisplayHeight;
        QImage* img=new QImage((const uchar*)videoFrame->mData,w,h,QImage::Format_RGB16);
        QImage imgScaled=img->scaled(120,90,Qt::KeepAspectRatio);

        shot_pic.convertFromImage(imgScaled);

        emit thumbnailFinished(shot_pic,file_path,pos);

        qDebug()<<"shot pic has got"<<ab_file_path;
        XRetrieverDestory(demoRetriver);
        demoRetriver=NULL;
    }
#else
    const QString cmd="E:\\tech_practise\\T3_linux\\T3_linux\\T3_linux\\shared\\bin\\ffmpeg.exe";
    QStringList arg;
    file_path="";
    arg.append("-i");
    arg.append("E:\\tech_practise\\DvrUI\\DvrUI\\video\\"+tempFileName);
    arg.append("-y");
    arg.append("-r");
    arg.append("1");
    arg.append("-f");
    arg.append("image2");
    arg.append("-ss");
    arg.append("00:00:10");
    arg.append("-t");
    arg.append("00:00:01");
    arg.append(tempFileName_NoSuffix+".jpg");
    qDebug()<<"arg:"<<arg;
    const QString now_dir="E:\\tech_practise\\DvrUI\\DvrUI\\";
    QProcess::startDetached(cmd,arg,now_dir);
    file_path="E:/tech_practise/DvrUI/DvrUI/"+tempFileName_NoSuffix+".jpg";
    if(file_path.isEmpty())
    {
        emit thumbnailFailed(tempFileName);
    }else{
        emit thumbnailFinished(QPixmap(""),file_path,pos);
    }
    qDebug()<<file_path;
#endif
}
