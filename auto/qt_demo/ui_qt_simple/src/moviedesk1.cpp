#include "moviedesk1.h"
#include "ui_moviedesk1.h"
#include <QMessageBox>
#include "midwindow.h"
#include "frmmessagebox.h"
#include "main_desktop.h"
#include <QTextCodec>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QLineEdit>
#include <QImage>
#include <QPixmap>
#include "unicodeandutf8.h"
extern main_desktop* pStaticMaindesktop;
movieDesk1* pStaticMovieDesk=NULL;
#include <QButtonGroup>
extern QFileInfo fileInfo_to_play;
extern QFileInfo fileInfo_to_show;
extern QFileInfo fileInfo_music_to_play;
extern MidWindow* midwindow;
extern Video_Player* pStaticVideoPlayer;
#if defined(Q_OS_LINUX)
#define AUDIO_PCM_OUTPUT 128
#if  1
int autCb_func(int32_t msgType, void *user,void* data,int len)
{
#if defined(Q_OS_LINUX)
    SubtitleItem* pItem = (SubtitleItem*)data;
    switch(msgType)
    {
        case AUDIO_PCM_OUTPUT:
            break;

        case SUBCTRL_SUBTITLE_AVAILABLE:
        {

            if(pItem == NULL)
            {
                logw("error pItem == NULL");
                return -1;
            }
            if(pItem->bText!=0)
            {
                if(pItem->pText!=NULL){
                    QString str=QString(pItem->pText);
                    pStaticVideoPlayer->subtitle_label->setVisible(true);
                    pStaticVideoPlayer->subtitle_label->setAlignment(Qt::AlignCenter);

                    printf("-----now is text subtitle--------\n");
                    printf("subtitle show,text=%s\n",pItem->pText);
                    QString str_subtitle = QObject::trUtf8(pItem->pText);
                    //str.toUtf8().toHex().toUpper();
                    qDebug()<<"subtitle code:"<<QString(pItem->pText).toUtf8().toHex().toUpper();
                    qDebug()<<"the subtitle is:"<<str_subtitle;
                    pStaticVideoPlayer->subtitle_label->setText(str_subtitle);
                    qDebug()<<"subtitle show done";
                }
            }else{
                printf("-----now is bitmap subtitle--------\n");
                pStaticVideoPlayer->subtitle_label->setVisible(true);
                pStaticVideoPlayer->subtitle_label->setAlignment(Qt::AlignCenter);
                int w,h;
                w=pItem->nBitmapWidth;
                h=pItem->nBitmapHeight;
                QImage* img=new QImage((const uchar*)pItem->pBitmapData,w,h,QImage::Format_RGBA8888);
                QImage imgScaled=img->scaled(pStaticVideoPlayer->subtitle_label->width(),pStaticVideoPlayer->subtitle_label->height(),Qt::KeepAspectRatio);
                QPixmap pix=QPixmap();
                pix.convertFromImage(imgScaled);
                pStaticVideoPlayer->subtitle_label->setPixmap(pix);
            }
            break;
        }
        case SUBCTRL_SUBTITLE_EXPIRED:
        {
            printf("subtitle disable\n");
            if(pItem == NULL)
            {
                printf("error: pItem == NULL");
                return -1;
            }
            if(pItem->bText!=0)
            {
                printf("-----now is text subtitle--------\n");
                pStaticVideoPlayer->subtitle_label->setVisible(true);
                pStaticVideoPlayer->subtitle_label->setText(" ");
            }else{
                printf("-----now is bitmap subtitle--------\n");
                pStaticVideoPlayer->subtitle_label->setVisible(false);
            }
            break;
        }
        case AWPLAYER_MEDIA_PREPARED:
        case AWPLAYER_MEDIA_PLAYBACK_COMPLETE:
        {
            qDebug()<<"the video is complete";
            midwindow->on_video_complete();
        }
        break;
        case AWPLAYER_MEDIA_SEEK_COMPLETE:
        {
            qDebug()<<"call back seek to is complete ";
            pStaticVideoPlayer->seekto_is_ok=1;
            break;
        }
        case AWPLAYER_MEDIA_LOG_RECORDER:
        case AWPLAYER_MEDIA_BUFFERING_UPDATE:
        case AWPLAYER_MEDIA_ERROR:
        case AWPLAYER_MEDIA_INFO:
        case AWPLAYER_MEDIA_SET_VIDEO_SIZE:
            break;
        default:
        {
            //logw("message 0x%x not handled.", messageId);
            break;
        }
    }
#endif
    return 0;
}
#endif
#endif
QString print_info(unsigned char tmp[],int tmp2)
{
    //tmp
    QString str="";
    for(int i=0;i<tmp2;i++)
    {
        if(tmp[i]==0)
            continue;
        str+=tmp[i];
    }
//    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//    QString desStr = codec->fromUnicode(str);
    return QObject::trUtf8(str.toLatin1().data());
}
QString get_utf8_string(QString strs)
{
//    const char *s=(char*)strs.toStdString().c_str();
    qDebug()<<"......."<<strs.toUtf8();



    //中文测试
//    qDebug()<<"in get_utf8_string fun"<<str;
//    //the string's codec is "2F6D6E742F7573622F736461342FE59388E59388E593882E617669"
//    unsigned char input[]={0xE5,0x93,0x88};
//    unsigned long output;
//    enc_utf8_to_unicode_one(input,&output);
//    qDebug()<<"hello:"<<output;
//    QString hello=QString::number(output,16);
//    qDebug()<<hello;
//    hello="\\u"+hello;
//    const char* halo="\u54C8\u54C8";
//    const char* halo1=(const char*) hello.toLocal8Bit();
//    qDebug()<<hello<<QString::fromLocal8Bit(halo1)<<QString::fromLocal8Bit(halo);
//    //qDebug()<<"test:::"<<QString::fromLocal8Bit("\uE59388\uE59388\uE59388");
//    qDebug()<<"test:::你好:"<<QString::fromLocal8Bit("\u4F60\u597D");
//    qDebug()<<"test::::"<<QString::fromLocal8Bit("\u54C8\u54C8");
//    QString tmp=QString::fromLocal8Bit("\u54C8\u54C8");
//    qDebug()<<"test::::"<<tmp;
//    qDebug()<<"teset:::"<<tmp+"123adb";

//    QTextCodec *codec = QTextCodec::codecForName("utf-8");
//    char utf8[] = {0xE4 ,0xBD, 0xA0, 0xE5, 0xA5, 0xBD, 0};
//    QString str2 = QString::fromUtf8(utf8);
//    qDebug()<<str2;

//    char utf82[] = {0xE5 ,0x93, 0x88, 0xE5, 0x93, 0x88, 0};
//    QString str3 = QString::fromUtf8(utf82);
//    qDebug()<<str3;

//    QString result="";
//    QString temp = str.toUtf8().toHex().toUpper();
//    qDebug()<<"the string's codec is"<<temp<<temp.size();
////    QTextCodec *codec = QTextCodec::codecForName("GBK");
////    QString desStr = codec->toUnicode(str.toLatin1());
////    QString::fromLatin1(codec->fromUnicode(InputStr));

////    QByteArray ba=str.toLatin1();
////    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
////    QString result1 = codec->toUnicode(ba);
////    qDebug()<<result1;
////    qDebug()<<QString::fromUtf8(ba.data());
//    QTextCodec *codec = QTextCodec::codecForName("utf-8");
//    int j=0;
//    for(int i=0;i<str.size();i++)
//    {
//        QString tmp;
//        QString mid_string;
//        qDebug()<<"single char"<<str.at(i);
//        if(str.at(i).isLetterOrNumber()||str.at(i)=='/'){
//            qDebug()<<"code:"<<temp.mid(j,2);
//            mid_string=temp.mid(j,2);
//            mid_string.toUShort(0,16);
//            j=j+2;
//        }else{
//            qDebug()<<"code:"<<temp.mid(j,6);
//            mid_string=temp.mid(j,6);
//            mid_string.toUShort(0,16);
//            j=j+6;
//        }
//        QString re=codec->fromUnicode(mid_string);
//        qDebug()<<"after change code:"<<QObject::trUtf8(re.toLatin1().data());
//    }
//    return result;


//    QTextCodec *codec = QTextCodec::codecForName("utf-8");
//    QString str = "0891683108500145F1240D91685143256178F0000831214281659423044F60597D";
//    QString t = str.mid(58);
//    QStringList s;

//    for(int i = 0;i < t.length();i += 4) {
//    s.append(t.mid(i,4));
//    }
//    QString t1;

//    foreach (const QString &t, s) {
//    t1.append(t.toUShort(0,16));
//    }

//    QString re = codec->fromUnicode(t1);
//    qDebug() << QObject::trUtf8(re.toLatin1().data());

//    const QString str = "汉字";
//    qDebug()<<str.size()<<str;
//    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//    QString unicode_str = codec->toUnicode(str.toLatin1().data());

//    for(int i = 0;i <unicode_str.length();++i) {
//        qDebug() << QString::number(unicode_str[i].unicode(),16);
//    }

}
QString prase_path(QString linux_path)
{
    QString dir_path="";
    for(int i=0;i<linux_path.size();i++)
    {
//        qDebug()<<"path prase:"<<linux_path.at(i);
        dir_path+=linux_path.at(i);
    }
    return dir_path;
}
int video_support_or_not(QWidget* tmp_widget,QFileInfo file_to_play)
{
#if defined(Q_OS_LINUX)
    AUTPlayer *ap = NULL;
    if(ap==NULL)
    {
        qDebug()<<"video_support_or_not";
        QString ab_file_path=file_to_play.absoluteFilePath();
        qDebug()<<ab_file_path;
        ap = new AUTPlayer();
        int ret = ap->setUrl((char*)ab_file_path.toLatin1().data());
        if (ret < 0)
        {
            qDebug()<<"setUrl is error-------------------";
            frmMessageBox *msg=new frmMessageBox(tmp_widget);
            msg->SetMessage(QString("video not support!"),0);
            msg->exec();
            if(ap!=NULL){
                delete ap;
                 ap=NULL;
            }
            return -1;
        }else{
            return 0;
        }
    }
#endif
    return 0;
}
movieDesk1::movieDesk1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::movieDesk1),cur_index(0)
{
    ui->setupUi(this);
    pStaticMovieDesk=this;


    ui->mainCameraButton->setCheckable(true);
    ui->viceButton->setCheckable(true);
    ui->videoButton->setCheckable(true);
    ui->picButton->setCheckable(true);
    ui->scanButton->setCheckable(true);
    ui->musicButton->setCheckable(true);

    ui->videoButton->setChecked(true);
    ui->mainCameraButton->setChecked(true);
    ui->mainCameraButton->setStyleSheet("background-color:red");
    ui->scanButton->setStyleSheet("background-color:red");
    slave_picturewidget=new slave_PictureWidget();
    slave_videowidget=new slave_VideoWidget();
    musicwidget=new MusicWidget();
    videowidget=new videoWidget();
    fileDialog=new QFileDialog(ui->stackedWidget,Qt::SubWindow);
    fileDialog->setStyleSheet("border:1px solid white;");
    foreach (QObject *obj, fileDialog->children()){
//        qDebug()<<obj->objectName();
        if (obj->objectName() == "fileNameLabel"){
               QLabel *label = qobject_cast<QLabel *>(obj);
               label->setText("hello");
           }
    }
    if (QLabel *label = fileDialog->findChild<QLabel *>("fileNameLabel")){
        label->setText(tr("文件名:"));
        label->setStyleSheet("color:rgb(255,255,255);");
    }
    if (QLabel *label = fileDialog->findChild<QLabel *>("fileTypeLabel")){
        label->setText(tr("文件类型:"));
        label->setStyleSheet("color:rgb(255,255,255);");
    }
    if (QLabel *label = fileDialog->findChild<QLabel *>("lookInLabel")){
        label->setText(tr("路径:"));
        label->setStyleSheet("color:rgb(255,255,255);");
    }
    if (QDialogButtonBox *buttonbox = fileDialog->findChild<QDialogButtonBox *>("buttonBox")){
        buttonbox->button(QDialogButtonBox::Open)->setText(tr("打开"));
        buttonbox->button(QDialogButtonBox::Cancel)->setHidden(true);
        buttonbox->button(QDialogButtonBox::Open)->setStyleSheet("border-style: none;border: 0px;color: rgb(255,255,255);padding: 5px;border-radius:5px;background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    }
    if (QComboBox *combox = fileDialog->findChild<QComboBox *>("lookInCombo")){

        combox->setStyleSheet("color:rgb(255,255,255);");
    }
    if (QComboBox *combox = fileDialog->findChild<QComboBox *>("fileTypeCombo")){

        combox->setStyleSheet("color:rgb(255,255,255);");
    }
    if (QLineEdit *lineEdit = fileDialog->findChild<QLineEdit *>("fileNameEdit")){

        lineEdit->setStyleSheet("color:rgb(255,255,255);");
    }
    picturewidget=new pictureWidget();

    QButtonGroup* btnGroup1=new QButtonGroup();
    btnGroup1->addButton(ui->mainCameraButton);
    btnGroup1->addButton(ui->viceButton);
    btnGroup1->setExclusive(true);
    QButtonGroup* btnGroup2=new QButtonGroup();
    btnGroup2->addButton(ui->videoButton);
    btnGroup2->addButton(ui->picButton);
    btnGroup2->addButton(ui->scanButton);
    btnGroup2->addButton(ui->musicButton);
    btnGroup2->setExclusive(true);

    ui->stackedWidget->addWidget(slave_picturewidget);
    ui->stackedWidget->addWidget(slave_videowidget);
    ui->stackedWidget->addWidget(videowidget);
    ui->stackedWidget->addWidget(fileDialog);
    ui->stackedWidget->addWidget(picturewidget);
    ui->stackedWidget->addWidget(musicwidget);
    ui->stackedWidget->setCurrentWidget(fileDialog);


#if defined(Q_OS_LINUX)
    fileDialog->setDirectory("/mnt/usb");
#else
    fileDialog->setDirectory("E:");
#endif

    fileDialog->setStyleSheet("border-radius:1px;background-color:rgb(255,255,255,0);");
    //"QFileDialog::pushButton{border-style: none;border: 0px;color: #F0F0F0;padding: 5px;border-radius:5px;background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3); }"
    connect(fileDialog,SIGNAL(fileSelected(QString)),this,SLOT(open_file(QString)));
    connect(ui->returnButton,SIGNAL(clicked()),SLOT(on_returnButton_clicked()));

    connect(fileDialog,SIGNAL(finished(int)),this,SLOT(deal_fileDialog(int)));
    connect(fileDialog,SIGNAL(accepted()),this,SLOT(deal_fileDialog1()));

    connect(midwindow,SIGNAL(usb_insert()),this,SLOT(on_usb_mount()));
    connect(midwindow,SIGNAL(usb_delete()),this,SLOT(on_usb_umount()));
}

movieDesk1::~movieDesk1()
{
    delete ui;
}
void movieDesk1::on_usb_mount()
{
    qDebug()<<"filedialog get the signal usb insert";
    fileDialog->update();
}
void movieDesk1::on_usb_umount()
{
    qDebug()<<"filedialog get the signal usb delete";
    fileDialog->update();
}

void movieDesk1::deal_fileDialog(int a)
{
    qDebug()<<"cancel is done"<<a;

    QFile file("/tmp/out.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    out << "begin getting file name: " << "\n";
    if (QLineEdit *lineEdit = fileDialog->findChild<QLineEdit *>("fileNameEdit")){

        out<<lineEdit->text()<<"\n";
    }
    fileDialog->show();
}
void movieDesk1::deal_fileDialog1()
{
    qDebug()<<"accept is done";
    fileDialog->show();
}
void movieDesk1::open_file(QString fileName)
{
//    QMessageBox::information(NULL, tr("Path"), tr("You selected ") + fileName);
    QFileInfo fileInfo(fileName);
     QString file_suffix=fileName.right(fileName.size()-fileName.lastIndexOf(".")-1);
    QString no_suffix_fileName=fileInfo.completeBaseName();
    QString file_path=fileInfo.absolutePath();

    if(file_suffix=="mp4"||file_suffix=="avi"||file_suffix=="mkv"||file_suffix=="FLV"||file_suffix=="flv"||file_suffix=="WMV"||
            file_suffix=="MKV"||file_suffix=="MP4"||file_suffix=="AVI"||file_suffix=="H264"||file_suffix=="H263"||file_suffix=="MPEG4"||file_suffix=="MPEG2"||file_suffix=="ts"||file_suffix=="TS"||file_suffix=="VOB"||file_suffix=="vob"||file_suffix=="wmv")
    {
        fileInfo_to_play=fileInfo;
        qDebug()<<"video play";
//        qDebug()<<"the path is"<<fileInfo.absolutePath();
        int ret=0;
        ret=video_support_or_not(this,fileInfo_to_play);
        if(!ret){

            player=new Video_Player();
            pStaticMaindesktop->on_main_desktop_disvisible();
            this->setHidden(true);
            player->show();
        }

    }else if(file_suffix=="jpg"||file_suffix=="jpeg"||file_suffix=="png"||file_suffix=="bmp"||file_suffix=="BMP")
    {
        qDebug()<<"open pic";
        fileInfo_to_show=fileInfo;
//        if(pic_view==NULL)
            pic_view=new Picture_view();
        pStaticMaindesktop->on_main_desktop_disvisible();
        this->setHidden(true);
        pic_view->show();

    }else if(file_suffix=="mp3"||file_suffix=="wav"||file_suffix=="MP3"||file_suffix=="aac"||file_suffix=="AAC"||file_suffix=="FLAC"||file_suffix=="ape"||file_suffix=="APE"||file_suffix=="pcm")
    {
        qDebug()<<"open music";
        fileInfo_music_to_play=fileInfo;
//        if(musicPlayer==NULL)
            musicPlayer=new Music_Player();
        pStaticMaindesktop->on_main_desktop_disvisible();
        this->setHidden(true);
        musicPlayer->show();
    }
    else{
        //QMessageBox::information(NULL,tr("Information"), tr("Haven't support this file type ,thanks!"));
		frmMessageBox *msg=new frmMessageBox(this);
        msg->SetMessage(QString("Haven't support this file type ,thanks!"),0);
        msg->exec();
    }
}

void movieDesk1::FormInCenter()
{
    QDesktopWidget w;
    int deskWidth = w.width();
    int deskHeight = w.height();
    this->resize(deskWidth*4/5,deskHeight*4/5);
    QPoint movePoint(deskWidth / 2 - this->width() / 2, deskHeight / 2 - this->height() / 2);
    this->move(movePoint);
}
void movieDesk1::on_returnButton_clicked()
{
    qDebug()<<"here-----------";
    this->setHidden(true);
    pStaticMaindesktop->setHidden(false);
}
void movieDesk1::on_mainCameraButton_clicked()
{
    qDebug()<<"main camera data";
    ui->mainCameraButton->setChecked(true);
    ui->mainCameraButton->setStyleSheet("background-color:red");
    ui->viceButton->setStyleSheet("border-style: none;"
                                      "border: 0px;"
                                      "color: #F0F0F0;"
                                      "padding: 5px;	"
                                      "border-radius:5px;"
                                     " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    if(ui->videoButton->isChecked())
    {
        on_videoButton_clicked();
    }
    if(ui->picButton->isChecked())
    {
        on_picButton_clicked();
    }
    if(ui->scanButton->isChecked())
    {
        on_scanButton_clicked();
    }
}
void movieDesk1::on_viceButton_clicked()
{
    qDebug()<<"vice camera data";
    ui->viceButton->setChecked(true);
    ui->viceButton->setStyleSheet("background-color:red");
    ui->mainCameraButton->setStyleSheet("border-style: none;"
                                      "border: 0px;"
                                      "color: #F0F0F0;"
                                      "padding: 5px;	"
                                      "border-radius:5px;"
                                     " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    if(ui->videoButton->isChecked())
    {
        on_videoButton_clicked();
    }
    if(ui->picButton->isChecked())
    {
        on_picButton_clicked();
    }
    if(ui->scanButton->isChecked())
    {
        on_scanButton_clicked();
    }
//    QString dir=QFileDialog::getOpenFileName(NULL, tr("Open Directory"),"/mnt/usb/sda4",
//                                             tr("movie (*.mp4 *.avi *.mp3)"));
//    qDebug()<<"get file name is:"<<dir;
}

void movieDesk1::on_videoButton_clicked()
{
    ui->videoButton->setChecked(true);
    ui->videoButton->setStyleSheet("background-color:red");
    ui->picButton->setStyleSheet("border-style: none;"
                                      "border: 0px;"
                                      "color: #F0F0F0;"
                                      "padding: 5px;	"
                                      "border-radius:5px;"
                                     " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->scanButton->setStyleSheet("border-style: none;"
                                      "border: 0px;"
                                      "color: #F0F0F0;"
                                      "padding: 5px;	"
                                      "border-radius:5px;"
                                     " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->musicButton->setStyleSheet("border-style: none;"
                                   "border: 0px;"
                                   "color: #F0F0F0;"
                                   "padding: 5px;	"
                                   "border-radius:5px;"
                                  " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");

    if(ui->mainCameraButton->isChecked())
    {
        ui->stackedWidget->setCurrentWidget(videowidget);
    } else if(ui->viceButton->isChecked())
    {
        ui->stackedWidget->setCurrentWidget(slave_videowidget);
    }
}

void movieDesk1::on_picButton_clicked()
{
    ui->picButton->setChecked(true);
    ui->picButton->setStyleSheet("background-color:red");
    ui->videoButton->setStyleSheet("border-style: none;"
                                      "border: 0px;"
                                      "color: #F0F0F0;"
                                      "padding: 5px;	"
                                      "border-radius:5px;"
                                     " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->scanButton->setStyleSheet("border-style: none;"
                                      "border: 0px;"
                                      "color: #F0F0F0;"
                                      "padding: 5px;	"
                                      "border-radius:5px;"
                                     " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->musicButton->setStyleSheet("border-style: none;"
                                   "border: 0px;"
                                   "color: #F0F0F0;"
                                   "padding: 5px;	"
                                   "border-radius:5px;"
                                  " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    if(ui->mainCameraButton->isChecked())
    {
        ui->stackedWidget->setCurrentWidget(picturewidget);
    }else if(ui->viceButton->isChecked()){
        ui->stackedWidget->setCurrentWidget(slave_picturewidget);
    }
}

void movieDesk1::on_scanButton_clicked()
{

    ui->scanButton->setChecked(true);
    ui->scanButton->setStyleSheet("background-color:red");
    ui->videoButton->setStyleSheet("border-style: none;"
                                      "border: 0px;"
                                      "color: #F0F0F0;"
                                      "padding: 5px;	"
                                      "border-radius:5px;"
                                     " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->picButton->setStyleSheet("border-style: none;"
                                      "border: 0px;"
                                      "color: #F0F0F0;"
                                      "padding: 5px;	"
                                      "border-radius:5px;"
                                     " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->musicButton->setStyleSheet("border-style: none;"
                                   "border: 0px;"
                                   "color: #F0F0F0;"
                                   "padding: 5px;	"
                                   "border-radius:5px;"
                                  " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->stackedWidget->setCurrentWidget(fileDialog);
}

void movieDesk1::on_musicButton_clicked()
{
    ui->musicButton->setChecked(true);
    ui->musicButton->setStyleSheet("background-color:red");
    ui->videoButton->setStyleSheet("border-style: none;"
                                      "border: 0px;"
                                      "color: #F0F0F0;"
                                      "padding: 5px;	"
                                      "border-radius:5px;"
                                     " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->picButton->setStyleSheet("border-style: none;"
                                      "border: 0px;"
                                      "color: #F0F0F0;"
                                      "padding: 5px;	"
                                      "border-radius:5px;"
                                     " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->scanButton->setStyleSheet("border-style: none;"
                                   "border: 0px;"
                                   "color: #F0F0F0;"
                                   "padding: 5px;	"
                                   "border-radius:5px;"
                                  " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->stackedWidget->setCurrentWidget(musicwidget);

}
