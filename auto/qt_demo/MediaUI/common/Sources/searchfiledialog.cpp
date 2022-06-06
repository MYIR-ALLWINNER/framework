/*!
 * @file searchfiledialog.cpp
 * Copyright (c) 2018
 * @brief des
 * detailed des
 *
 * @date 2018
 * @author lee
 */
#include "common/Header/searchfiledialog.h"
#include "ui_searchfiledialog.h"

#include <QMutex>
#include <QMutexLocker>
#include <QDebug>
#include <QDir>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QTextCodec>

/**************************************
Function:
Description:
***************************************/
searchFileDialog::searchFileDialog(int Type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchFileDialog)
{
    qDebug()<<__FUNCTION__ ;
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    m_pFileDialog = NULL;
    m_FileType = Type;
    m_Path="/mnt/";


    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));

    if(m_FileType == 0){
        ui->titleLabel->setText("查找歌曲");
        m_filter<<"*.mp3 *.wav *.ape *.flac *.aac *.wma";
    }else if(m_FileType == 1){
        ui->titleLabel->setText("查找视频");
        m_filter << "*.divx *.3gp *.asf *.avi *.flv *.mkv *.mov *.mp4 *.mpeg *.mpg *.ra *.rm *.rmvb *.ts *.vob *.webm *.wma *.wmv";
    }else if(m_FileType == 2){
        ui->titleLabel->setText("查找图片");
        m_filter<<"*.jpg";
    }

}

/**************************************
Function:
Description:
***************************************/
void searchFileDialog::createFileDialog()
{
    qDebug()<<__FUNCTION__ ;
    if(m_pFileDialog==NULL){

        m_pFileDialog = new QFileDialog(ui->stackedWidget, Qt::SubWindow);
        m_pFileDialog->setNameFilters(m_filter);
        m_pFileDialog->setDirectory(m_Path);

        qDebug()<<__FUNCTION__<<"m_pFileDialog->setDirectory"<<m_Path;
        qDebug()<<__FUNCTION__<<"m_pFileDialog->m_filter"<<m_filter;
        ui->stackedWidget->addWidget(m_pFileDialog);
        ui->stackedWidget->setCurrentWidget(m_pFileDialog);

        if (QLabel *label = m_pFileDialog->findChild<QLabel *>("fileNameLabel")){
            label->setText(tr("文件名:"));
        }
        if (QLabel *label = m_pFileDialog->findChild<QLabel *>("fileTypeLabel")){
            label->setText(tr("文件类型:"));
        }
        if (QLabel *label = m_pFileDialog->findChild<QLabel *>("lookInLabel")){
            label->setText(tr("文件路径:"));
        }
        if (QDialogButtonBox *buttonbox = m_pFileDialog->findChild<QDialogButtonBox *>("buttonBox")){
            buttonbox->button(QDialogButtonBox::Open)->setText(tr("open"));
            buttonbox->button(QDialogButtonBox::Cancel)->setHidden(false);
            buttonbox->button(QDialogButtonBox::Open)->setStyleSheet("border-style: \
                                                     none;border: 0px;color: rgb(255,255,255);\
                                                     padding: 5px;border-radius:5px;\
                                                     background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
        }

        QDialogButtonBox *buttonbox = m_pFileDialog->findChild<QDialogButtonBox *>("buttonBox");

        connect(buttonbox->button(QDialogButtonBox::Open),SIGNAL(clicked()),this,SLOT(onGetFileName()));
        connect(buttonbox->button(QDialogButtonBox::Cancel),SIGNAL(clicked()),this,SLOT(onCancel()));
        qDebug()<<__FUNCTION__<<__LINE__ ;
    }

}


/**************************************
Function:
Description:
***************************************/
searchFileDialog::~searchFileDialog()
{
    delete ui;
}

/**************************************
Function:
Description:
***************************************/
void searchFileDialog::showD()
{
    createFileDialog();
    this->show();
    if(int ret = m_pFileDialog->exec())
    {
        qDebug()<<"m_pFileDialog->exec ret: "<< ret;
        QStringList filelist = m_pFileDialog->selectedFiles();
        qDebug()<<"fileDialog->selectFiles:"<<filelist;
        qDebug()<<"the path is "<< filelist[0];
        onGetFileName();
    }
}

/**************************************
Function:
Description:
***************************************/
void searchFileDialog::onGetFileName()
{
    qDebug()<<__FUNCTION__ ;
    QFileInfo fileinfo;
    QComboBox *combox = m_pFileDialog->findChild<QComboBox *>("lookInCombo");
    QString fileDir = combox->currentText();
    QLineEdit *lineEdit = m_pFileDialog->findChild<QLineEdit *>("fileNameEdit");
    QString fileName = lineEdit->text();
    QString filePath = fileDir + "/" + fileName;

    //QTextCodec *code = QTextCodec::codecForName("gb2312");
    //filePath = code->fromUnicode(filePath).data();

    qDebug()<<"add "<<filePath<<"to list";

    fileinfo.setFile(filePath);
    if(fileinfo.isFile()){

        if(m_pFileDialog!=NULL){
            delete m_pFileDialog;
            m_pFileDialog = NULL;
        }

        if(m_FileType == 0){
            emit notifyMusicPlayerAddFile(filePath);
        }else if(m_FileType == 1){
            emit notifyVideoPlayerAddFile(filePath);
        }else if(m_FileType == 2){
            emit notifyGalleryAddFile(filePath);
        }
    }else{
       m_Path=filePath;
    }
}

/**************************************
Function:
Description:
***************************************/
void searchFileDialog::onCancel()
{
    qDebug()<<"onCancel "<< m_FileType;

    if(m_pFileDialog!=NULL){
        delete m_pFileDialog;
        m_pFileDialog = NULL;
    }

    if(m_FileType == 0){
        emit notifyMusicCancelSearch();
    }else if(m_FileType == 1){
        emit notifyVideoCancelSearch();
    }else if(m_FileType == 2){
        emit notifyGalleryCancelSearch();
    }

}
