#include "picturewidget.h"
#include "ui_picturewidget.h"
#include "main_desktop.h"
#include "midwindow.h"
#include "frmmessagebox.h"
#include "moviedesk1.h"
#include <QTextCodec>
extern movieDesk1* pStaticMovieDesk;
extern main_desktop* pStaticMaindesktop;
// This is available in all editors.
extern QFileInfo fileInfo_to_show;
const QString win_path="E:/tech_practise/DvrUI/DvrUI/";
//const QString linux_path="/mnt/sdcard/mmcblk1p1/frontVideo/";//sdcard
extern QString linux_usb_path;//U
extern QString linux_sdcard_path;//sd
extern QString prase_path(QString linux_path);
extern QString print_info(unsigned char tmp[],int tmp2);
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<iostream>
using namespace std;
#pragma pack(2)
typedef struct BITMAPFILEHEADER
{
    u_int16_t bfType;
    u_int32_t bfSize;
    u_int16_t bfReserved1;
    u_int16_t bfReserved2;
    u_int32_t bfOffBits;
}BITMAPFILEHEADER;

typedef struct BITMAPINFOHEADER
{
    u_int32_t biSize;
    u_int32_t biWidth;
    u_int32_t biHeight;
    u_int16_t biPlanes;
    u_int16_t biBitCount;
    u_int32_t biCompression;
    u_int32_t biSizeImage;
    u_int32_t biXPelsPerMeter;
    u_int32_t biYPelsPerMeter;
    u_int32_t biClrUsed;
    u_int32_t biClrImportant;
}BITMAPINFODEADER;
void showBmpInforHead(BITMAPFILEHEADER &pBmpHead,BITMAPINFODEADER &pBmpInforHead)
{
    qDebug()<<"file type:"<<pBmpHead.bfType;
    qDebug()<<"file size:"<<pBmpHead.bfSize;
    qDebug()<<"reverse_1:"<<pBmpHead.bfReserved1;
    qDebug()<<"reverse_2:"<<pBmpHead.bfReserved2;
    qDebug()<<"bitmap data offsets:"<<pBmpHead.bfOffBits;

    qDebug()<<"struct BITMAPINFODEADER size:"<<pBmpInforHead.biSize;
    qDebug()<<"width:"<<pBmpInforHead.biWidth;
    qDebug()<<"height:"<<pBmpInforHead.biHeight;
    qDebug()<<"biPlanes:"<<pBmpInforHead.biPlanes;
    qDebug()<<"biBitCount:"<<pBmpInforHead.biBitCount;
    qDebug()<<"comprass:"<<pBmpInforHead.biCompression;
    qDebug()<<"biSizeImage ,bit map data size:"<<pBmpInforHead.biSizeImage;
    qDebug()<<"x resolution:"<<pBmpInforHead.biXPelsPerMeter;
    qDebug()<<"y resolution:"<<pBmpInforHead.biYPelsPerMeter;
    qDebug()<<"color count:"<<pBmpInforHead.biClrUsed;
    qDebug()<<"important color count:"<<pBmpInforHead.biClrImportant;
}
void show_bitmap_info(QString path)
{
    FILE *fp = fopen((char*)path.toStdString().c_str(), "rb");
    if(fp==NULL)
    {
        qDebug()<<"open file error";
        return ;
    }
    BITMAPFILEHEADER head;
    BITMAPINFODEADER info;

    fread(&head, sizeof(BITMAPFILEHEADER),1,  fp);
    fread(&info,sizeof(BITMAPINFODEADER), 1,  fp);

    showBmpInforHead(head,info);
}
extern MidWindow* midwindow;
const int W_ICONSIZE = 100;
const int H_ICONSIZE = 100;
const int H_ITEMSIZE = 120;
pictureWidget::pictureWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pictureWidget)
{
    ui->setupUi(this);

    show_model=true;
    ui->listWidget_file->clear();

    show_file();

    connect(this,SIGNAL(main_desktop_disvisible()),pStaticMaindesktop,SLOT(on_main_desktop_disvisible()));

    connect(midwindow,SIGNAL(usb_insert()),this,SLOT(on_usb_mount()));
    connect(midwindow,SIGNAL(usb_delete()),this,SLOT(on_usb_umount()));
    connect(ui->listWidget_file,SIGNAL(clicked(QModelIndex)),this,SLOT(show_big_picture(QModelIndex)));

}
void pictureWidget::show_file()
{
    qDebug()<<"pic widget is showing file";
    #if defined(Q_OS_LINUX)
    qDebug()<<"now path is "<<linux_usb_path;
    file_list=GetFileList(prase_path(linux_usb_path));
    #else
    file_list=GetFileList(QDir(win_path));
    #endif
    ui->listWidget_file->setObjectName(QString::fromUtf8("listWidget_file"));
    ui->listWidget_file->setMovement(QListView::Static);

    ui->listWidget_file->setSelectionMode(QAbstractItemView::ExtendedSelection);

    ui->listWidget_file->setSpacing(12);
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
pictureWidget::~pictureWidget()
{
    delete ui;
}
void pictureWidget::on_usb_mount()
{
    qDebug()<<"picwidget get the signal usb insert";
    show_file();
}
void pictureWidget::on_usb_umount()
{
    qDebug()<<"picwidget get the signal usb delete";
    ui->listWidget_file->clear();
}
QFileInfoList pictureWidget::GetFileList(QDir dir)
{
    qDebug()<<"GetFileList:"<<"now path is :"<<dir.path();
    qDebug()<<"get all file name";
    QStringList filters;
     filters << "*.bmp"<<"*.jpg"<<"*.jpeg"<<"*.png";
    dir.setNameFilters(filters);

    QFileInfoList file_list=dir.entryInfoList();
    for(int i=0;i<file_list.size();i++)
    {
        QFileInfo fileInfo=file_list.at(i);
        fileInfo.absoluteFilePath();
//        qDebug()<<fileInfo.fileName();
    }
    return file_list;
}
QImage covert_image_format(QString tempFilePath)
{
    QImage image(tempFilePath);
    QImage currentImage;
    if(image.format() == QImage::Format_Mono)
    {
        qDebug() << "format_mono";
        currentImage = image.convertToFormat(QImage::Format_Mono);
    }
    else if(image.format()  == QImage::Format_MonoLSB)
    {
        qDebug() << "format_monoLSB";
        currentImage = image.convertToFormat(QImage::Format_MonoLSB);
    }
    else if(image.format()  == QImage::Format_Indexed8)
    {
        qDebug() << "QImage::Format_Indexed8";
        currentImage = image.convertToFormat(QImage::Format_Indexed8);
    }
    else if(image.format()  == QImage::Format_RGB32)
    {
        qDebug() << "QImage::Format_RGB32";
        currentImage = image.convertToFormat(QImage::Format_RGB32);
    }
    else if(image.format()  == QImage::Format_ARGB32)
    {
        qDebug()<<"QImage::Format_ARGB32";
        currentImage = image.convertToFormat(QImage::Format_ARGB32);
    }

    else if(image.format()  ==QImage::Format_ARGB32_Premultiplied)
    {
         qDebug()<<"QImage::Format_ARGB32_Premultiplied";
         currentImage = image.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    }

    else if(image.format()  == QImage::Format_RGB16)
    {
        qDebug("QImage::Format_RGB16");
        currentImage = image.convertToFormat(QImage::Format_RGB16);
    }

    else if(image.format()  == QImage::Format_ARGB8565_Premultiplied)
    {
        qDebug()<<"QImage::Format_ARGB8565_Premultiplied";
        currentImage = image.convertToFormat(QImage::Format_ARGB8565_Premultiplied);
    }

    else if(image.format()  == QImage::Format_RGB666)
    {
        qDebug()<<"QImage::Format_RGB666";
        currentImage = image.convertToFormat(QImage::Format_RGB666);
    }

    else if(image.format()  == QImage::Format_ARGB6666_Premultiplied)
    {
        qDebug()<<"QImage::Format_ARGB6666_Premultiplied";
        currentImage = image.convertToFormat(QImage::Format_ARGB6666_Premultiplied);
    }

    else if(image.format()  == QImage::Format_RGB555)
    {
        qDebug()<<"QImage::Format_RGB555";
        currentImage = image.convertToFormat(QImage::Format_RGB555);
    }

    else if(image.format()  == QImage::Format_ARGB8555_Premultiplied)
    {
        qDebug()<<"QImage::Format_ARGB8555_Premultiplied";
        currentImage = image.convertToFormat(QImage::Format_ARGB8555_Premultiplied);
    }

    else if(image.format()  == QImage::Format_RGB888)
    {
        qDebug()<<"QImage::Format_RGB888";
        currentImage = image.convertToFormat(QImage::Format_RGB888);
    }

    else if(image.format() == QImage::Format_RGB444)
    {
        qDebug()<<"QImage::Format_RGB444";
        currentImage = image.convertToFormat(QImage::Format_RGB444);
    }
    else if(image.format()  == QImage::Format_ARGB4444_Premultiplied)
    {
        qDebug()<<"QImage::Format_ARGB4444_Premultiplied";
        currentImage = image.convertToFormat(QImage::Format_ARGB4444_Premultiplied);
    }
    else
    {
        qDebug()<<"unkown format";
        currentImage = image;
    }
    return currentImage;
}
void pictureWidget::show_file_by_iconview(QFileInfoList file_list)
{
    qDebug()<<"show_file_by_iconview";
    qDebug()<<"file_list has "<<file_list.size()<<" files";
    ui->listWidget_file->setIconSize(QSize(100,100));
    for(int i=0;i<file_list.size();i++)
    {
        QFileInfo file_info=file_list.at(i);
        QString tempFilePath=file_info.absoluteFilePath();
        int filename_index=tempFilePath.lastIndexOf("/");
        QString tempFileName=tempFilePath.right(tempFilePath.size()-filename_index-1);
        qDebug()<<"file name:"<<tempFileName;
        QString tempFileName_NoSuffix=tempFileName;
        int suffix_index=tempFileName_NoSuffix.lastIndexOf(".");
        QString suffix=tempFileName.right(tempFileName.size()-suffix_index-1);
        qDebug()<<"suffix is:"<<suffix;
        tempFileName_NoSuffix.truncate(suffix_index);
//        qDebug()<<"the no_suffix filename:"<<tempFileName_NoSuffix;
        QPixmap objPixmap;
        if(suffix=="bmp")
        {
            show_bitmap_info(tempFilePath);
            //QImage image=covert_image_format(tempFilePath);
            //qDebug()<<"is a bitmap"<<tempFileName<<"imageformat"<<image.format();
            //objPixmap.fromImage(image);
        }else{
            qDebug()<<"not a bitmap";
            objPixmap=QPixmap(tempFilePath);
        }
        QTextCodec *codec = QTextCodec::codecForName("GB2312");
        QString str = codec->toUnicode(tempFileName.toLatin1().data());
        if(objPixmap.isNull())
        {
            objPixmap=QPixmap(":/icon/no_shotvideo.png");
        }
        QListWidgetItem *pItem = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(W_ICONSIZE,H_ICONSIZE))),str);
        pItem->setSizeHint(QSize(W_ICONSIZE,H_ITEMSIZE));
        ui->listWidget_file->addItem(pItem);
    }
}
void pictureWidget::show_file_by_listview(QFileInfoList file_list)
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
//        qDebug()<<"the no_suffix filename:"<<tempFileName_NoSuffix;

        QPixmap objPixmap(tempFilePath);
        QListWidgetItem *pItem = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(20,20))),tempFileName);
        pItem->setSizeHint(QSize(W_ICONSIZE,H_ITEMSIZE));
        ui->listWidget_file->addItem(pItem);
    }
}
void pictureWidget::show_big_picture(QModelIndex pos)
{
    QListWidgetItem* item=ui->listWidget_file->currentItem();
    qDebug()<<"filename"<<item->text();
    qDebug()<<"which file:"<<pos.row();

    fileInfo_to_show=file_list.at(pos.row());
    QImage pic;
    pic.load(fileInfo_to_show.absoluteFilePath());
    if(pic.isNull())
    {
        frmMessageBox *msg=new frmMessageBox(this);
        msg->SetMessage(QString(tr("this image format can't attach!")),0);
        QTimer::singleShot(2000, msg, SLOT(close()));
        msg->exec();
        return ;
    }else{
        picture_views=new Picture_view(this);
        pStaticMovieDesk->setHidden(true);
        pStaticMaindesktop->on_main_desktop_disvisible();
        picture_views->showNormal();
    }
}
void pictureWidget::deal_picture_views_signal()
{

}
