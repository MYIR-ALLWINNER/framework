#include "about.h"
#include "ui_about.h"
#include <QMessageBox>
#include <QListView>
#include <QProcess>
#include <QByteArray>
#include "frmmessagebox.h"
#if defined(Q_OS_LINUX)

int is_dir_exist(const char *dir_path)
{
    if(dir_path==NULL)
        return -1;
    if(opendir(dir_path)==NULL)
        return -1;
    return 0;
}
#endif
About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{

    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->ROM_usage->setRange(0,100);
    connect(ui->formatButton,SIGNAL(clicked()),this,SLOT(on_formatButton_clicked()),Qt::UniqueConnection);

#if defined(Q_OS_LINUX)
    #if 0
    int sdklog_level=sdk_log_getlevel();
    if(sdklog_level<=6)
        ui->logLevelComboBox->setCurrentIndex(sdklog_level);
    #endif
    if(!is_dir_exist(PATH_SDCARD))
    {

        dev_type=0;
        QProcess process;
        QString cmd=QString("df /mnt/sdcard/mmcblk1p1 | grep %1").arg(QString("/dev/mmcblk1p1"));

        process.start(cmd);
        process.waitForFinished();
        QByteArray output = process.readAllStandardOutput();
        QString str_output = output;
        str_output=str_output.simplified();
        QStringList list=str_output.split(' ');
        qDebug()<<str_output<<"\n"<<"usage of sdcard"<<list[11];
        QString t=list[11];
        t=t.left(t.length()-1);
        test=t.toInt();
        qDebug()<<test;

    }else if(!is_dir_exist(PATH_USB)){
        dev_type=1;

        QProcess process;
        QString cmd=QString("df /mnt/usb/sda4/  | grep %1").arg(QString("/dev/sda4/"));

        process.start(cmd);
        process.waitForFinished();
        QByteArray output = process.readAllStandardOutput();
        QString str_output = output;
        str_output=str_output.simplified();
        QStringList list=str_output.split(' ');
        qDebug()<<str_output<<"\n"<<"usage of usb"<<list[11];
        QString t=list[11];
        t=t.left(t.length()-1);
        test=t.toInt();
        qDebug()<<test;

    }else{
//        ui->formatButton->setEnabled(false);
    }

#else
    #if 0

        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        test =qrand()%100;
        qDebug()<<"random number"<<test;
    #endif
    test=66;
#endif
    ui->ROM_usage->setValue(test);
}

About::~About()
{
    delete ui;
}
void About::on_formatButton_clicked()
{
//    QMessageBox::StandardButton ret =QMessageBox::question(this,tr("format question"),tr("sure to format?"),QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel);
    frmMessageBox* mesg=new frmMessageBox();
    mesg->SetMessage(QString(tr("Sure to Format?")), 1);
    if(1==mesg->exec()){
    #if defined(Q_OS_LINUX)
        if(dev_type==0){
            pfat=new Fat();
            pfat->format(PATH_SD_DEV, PATH_SDCARD);
        }else{
            pfat=new Fat();
            pfat->format(PATH_USB_DEV,PATH_USB);
        }

    #else
        qDebug()<<"format";
    #endif
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(set_pro_value()));
    timer->start(10);
    }
}
void About::set_pro_value()
{
    if(test>=0){
        ui->ROM_usage->setValue(test--);
    }else{
        timer->stop();
    }
}

void About::on_logLevelComboBox_currentIndexChanged(int index)
{
    qDebug()<<"log level set:"<<index;
#if defined(Q_OS_LINUX)
    sdk_log_setlevel(index);
#endif
}
