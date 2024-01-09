#include "slave_picturewidget.h"
#include "ui_slave_picturewidget.h"

int which_slavepic_show_big;
QString which_slavefilename_show_big;
 bool pic_slave_or_master;

const int W_ICONSIZE = 100; 
const int H_ICONSIZE = 100;
const int H_ITEMSIZE = 120; 

slave_PictureWidget::slave_PictureWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::slave_PictureWidget)
{
    ui->setupUi(this);

    pic_slave_or_master=false;

    ui->listWidget_file->setObjectName(QString::fromUtf8("listWidget_file"));
    ui->listWidget_file->setGeometry(QRect(0,0,0,0));

    #if defined(Q_OS_LINUX)
    QDirIterator m_DirIterator(QString("/mnt/sdcard/mmcblk1p1/rearPicture/"),QDir::Files|QDir::NoSymLinks,QDirIterator::Subdirectories);
    #else
    QDirIterator m_DirIterator(QString("../DvrUI/image/"),QDir::Files|QDir::NoSymLinks,QDirIterator::Subdirectories);
    #endif

    qDebug()<<" now path"<<m_DirIterator.path();
    qDebug()<<"file name"<<m_DirIterator.fileName();
    qDebug()<<"program file path"<<QDir::currentPath();
    ui->listWidget_file->clear();
    while (m_DirIterator.hasNext()) {
        QString tempFile=m_DirIterator.next();

        ui->listWidget_file->setIconSize(QSize(W_ICONSIZE,H_ICONSIZE));
        ui->listWidget_file->setResizeMode(QListView::Adjust);
        ui->listWidget_file->setViewMode(QListView::IconMode);
        ui->listWidget_file->setMovement(QListView::Static);

        ui->listWidget_file->setSelectionMode(QAbstractItemView::ExtendedSelection);

        ui->listWidget_file->setSortingEnabled(true);

        ui->listWidget_file->setDragEnabled(true);

        //ui->listWidget_file->selectAll();
        ui->listWidget_file->setSpacing(12);
        QPixmap objPixmap(tempFile);

        #if defined(Q_OS_LINUX)
        tempFile=tempFile.remove(QString("/mnt/sdcard/mmcblk1p1/rearPicture/"),Qt::CaseSensitive);
        #else
        tempFile=tempFile.remove(QString("../DvrUI/image/"),Qt::CaseSensitive);
        #endif

        QListWidgetItem *pItem = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(W_ICONSIZE,H_ICONSIZE))),tempFile);
        pItem->setSizeHint(QSize(W_ICONSIZE,H_ITEMSIZE));           
        ui->listWidget_file->addItem(pItem);              
    }
    ui->listWidget_file->setGeometry(NULL,NULL,450,420);

    connect(ui->listWidget_file,SIGNAL(clicked(QModelIndex)),this,SLOT(show_big_picture(QModelIndex)));
}

slave_PictureWidget::~slave_PictureWidget()
{
    delete ui;
}
void slave_PictureWidget::show_big_picture(QModelIndex pos)
{
    QListWidgetItem* item=ui->listWidget_file->currentItem();

    which_slavefilename_show_big=item->text();
    which_slavepic_show_big=pos.row();
    picture_views=new Picture_view(this);

    picture_views->showNormal();
}

