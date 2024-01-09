#include "setfirst.h"
#include "ui_setfirst.h"
#include <QDesktopWidget>
#include "midwindow.h"
#include "main_desktop.h"
#include "frmmessagebox.h"
extern main_desktop *g_pStaticMaindesktop;
#if defined(Q_OS_LINUX)
#include <ls_ctrl.h>
#include <asoundlib.h>
#endif
extern int g_iRecordTime;
static int old_recordTime=g_iRecordTime;
extern MidWindow *g_MidWindow;
extern int open_recordVideo_front,open_recordVideo_rear;
extern int open_recordAudio_front,open_recordAudio_rear;
extern int open_reverseLine_front,open_reverseLine_rear;
extern int open_adas_front,open_adas_rear;
extern int g_iCameraHeight,g_iCameraWidth;
extern int g_iNowVoiceValue;
extern SetFirst *g_pStaticSetfirst;
#if defined(Q_OS_LINUX)
extern dvr_factory* pdvr;
extern dvr_factory* pdvr1;
#endif

SetFirst::SetFirst(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetFirst)
{
    ui->setupUi(this);
    qDebug()<<"-----------here0";

    ui->comboBox->setView(new QListView());
    voiceButtonState=false;
    setWindowStyleSheet();

#if defined(Q_OS_LINUX)
    lcd_blk_ctrl_init();
#endif

    ui->voiceSlider->setRange(0,100);
    ui->voiceSlider->setSingleStep(0.5);
    ui->lightSlider->setRange(0,100);
    ui->lightSlider->setSingleStep(5);
    ui->ColorEffectSlider->setRange(0,100);
    ui->whiteBalanceSlider->setRange(0,100);
    ui->ExposureCompensationSlider->setRange(0,100);
    connect(ui->voiceSlider,SIGNAL(valueChanged(int)),this,SLOT(on_slider_valuechanged(int)));
    connect(ui->lightSlider,SIGNAL(valueChanged(int)),this,SLOT(on_slider_valuechanged(int)));
    connect(ui->ColorEffectSlider,SIGNAL(valueChanged(int)),this,SLOT(on_slider_valuechanged(int)));
    connect(ui->ExposureCompensationSlider,SIGNAL(valueChanged(int)),this,SLOT(on_slider_valuechanged(int)));
    connect(ui->whiteBalanceSlider,SIGNAL(valueChanged(int)),this,SLOT(on_slider_valuechanged(int)));
    ui->voiceSlider->setValue(g_iNowVoiceValue);
    ui->lightSlider->setValue(50);
    ui->ColorEffectSlider->setValue(50);
    ui->whiteBalanceSlider->setValue(50);
    ui->ExposureCompensationSlider->setValue(50);
    ui->voiceLabel->setText(tr("50"));
    ui->lightLabel->setText(tr("50"));
    ui->ColorEffectLabel->setText("50");
    ui->whiteBalanceLabel->setText("50");
    ui->ExposureCompensationLabel->setText("50");


    ui->movieTimeSetting->setRange(1,5);
    ui->movieTimeSetting->setSingleStep(2);
    ui->movieTimeSetting->setValue(1);
    ui->movieTimeSetting->setSuffix(tr("min"));


    ui->audioButton->setCheckable(true);
    ui->ADASButton->setCheckable(true);
    ui->reverseButton->setCheckable(true);
    ui->movieButton->setCheckable(true);
    ui->voiceButton->setCheckable(true);

    qDebug()<<"the value of the config ini:"<<open_adas_front<<open_recordVideo_front<<open_recordAudio_front<<open_reverseLine_front;
    if(open_adas_front){
        ui->ADASButton->setChecked(true);
        ui->ADASButton->setStyleSheet("background-color:#54ff4b;");
    }else{
        ui->ADASButton->setChecked(false);
        ui->ADASButton->setStyleSheet("background-color:#38a4d6;");
    }
    if(open_recordVideo_front){
        ui->movieButton->setChecked(true);
        ui->movieButton->setStyleSheet("background-color:#54ff4b;");
    }else{
        ui->movieButton->setChecked(false);
        ui->movieButton->setStyleSheet("background-color:#38a4d6;");
    }
    if(open_recordAudio_front){
        ui->audioButton->setChecked(true);
        ui->audioButton->setStyleSheet("background-color:#54ff4b;");
    }else{
        ui->audioButton->setChecked(false);
        ui->audioButton->setStyleSheet("background-color:#38a4d6;");
    }
    if(open_reverseLine_front){
        ui->reverseButton->setChecked(true);
        ui->reverseButton->setStyleSheet("background-color:#54ff4b;");
    }else{
        ui->reverseButton->setChecked(false);
        ui->reverseButton->setStyleSheet("background-color:#38a4d6;");
    }
    //need update when camera is mount or unmount

    if(720==g_iCameraHeight)
    {
        qDebug()<<"this is a 720p camera";
        ui->comboBox->setCurrentIndex(1);
    }else if(1080==g_iCameraHeight)
    {
        qDebug()<<"this is a 1080p camera";
        ui->comboBox->setCurrentIndex(0);
    }else{
        qDebug()<<"can't find correct resolution";
    }

    //update voice value

    setSecond_Desk=new Settings(this);
    setSecond_Desk->FormInCenter();
    g_pStaticSetfirst=this;
}
SetFirst::~SetFirst()
{
    delete ui;
    delete setSecond_Desk;
}
void SetFirst::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor(104, 98, 98, 0));
}
void SetFirst::on_want_window_close()
{
    qDebug()<<"here is on_want";
    qDebug()<<"the window will close";
    this->close();
}
void SetFirst::FormInCenter()
{
    QDesktopWidget w;
    int deskWidth = w.width();
    int deskHeight = w.height();
    this->resize(deskWidth*4/5,deskHeight*4/5);
    QPoint movePoint(deskWidth / 2 - this->width() / 2, deskHeight / 2 - this->height() / 2);
    this->move(movePoint);
}

void SetFirst::UpdateCurCameraState(int iCameraId)
{
    QString CruCamInfo = "当前设置:Video"+ QString::number(iCameraId,10);
    ui->DisInfoLabel->setText(tr(CruCamInfo.toStdString().data()));
    ui->DisInfoLabel->setAlignment(Qt::AlignCenter);
    ui->DisInfoLabel->setStyleSheet("font-size:30px;color:white");
	int iCurPreCamState = config_get_startup(iCameraId);
    if(iCurPreCamState == 1){
        ui->movieButton->setStyleSheet("background-color:#54ff4b;");
    }
    else
    {
        ui->movieButton->setStyleSheet("background-color:#38a4d6;");
    }

	int iCurPreAudioState = config_get_sound(iCameraId);
	if(iCurPreAudioState == 1){
		ui->audioButton->setStyleSheet("background-color:#54ff4b;");
	}
	else
	{
		ui->audioButton->setStyleSheet("background-color:#38a4d6;");
	}
	//printf("SetFirst::UpdateCurCameraState,iCameraId:%d iCurPreCamState:%d iCurPreAudioState:%d\n", iCameraId,iCurPreCamState,iCurPreAudioState);
}


void SetFirst::update_voice(int value)
{
    qDebug()<<"SetFirst change voice";
    ui->voiceSlider->setValue(value);
}
void SetFirst::on_slider_valuechanged(int n_value)
{
    QObject* sender = QObject::sender();
    if(sender==ui->voiceSlider){
        qDebug()<<"change the voice"<<n_value;
        g_iNowVoiceValue=n_value;
    #if defined(Q_OS_LINUX)
        qDebug()<<"ready to change the voice";
        //QString cmd="tinymix 2 "+ QString::number(n_value*2,10);
        //system((char*)cmd.toStdString().c_str());
        
    #endif
        ui->voiceLabel->setText(QString("%1").arg(n_value));
    }
    else if(sender==ui->lightSlider){
        qDebug()<<"change the light:"<<n_value;
    #if defined(Q_OS_LINUX)
        qDebug()<<"ready to change the light";
        lcd_blk_ctrl((unsigned long)n_value/5);
    #endif
        ui->lightLabel->setText(QString("%1").arg(n_value));
    }else if(sender==ui->ColorEffectSlider){
        qDebug()<<"change the ColorEffect:"<<n_value;
    #if defined(Q_OS_LINUX)
        qDebug()<<"ready to change the contrast";
//        if(pdvr!=NULL);
//            pdvr->setColorEffectData(n_value);
    #endif
        ui->ColorEffectLabel->setText(QString("%1").arg(n_value));
    }else if(sender==ui->whiteBalanceSlider){
        qDebug()<<"change the whiteBalance:"<<n_value;
    #if defined(Q_OS_LINUX)
        qDebug()<<"ready to change the whiteBalance";
//        if(pdvr!=NULL);
//            pdvr->setWhiteBlanceData(n_value);
    #endif
        ui->whiteBalanceLabel->setText(QString("%1").arg(n_value));
    }else if(sender==ui->ExposureCompensationSlider){
        qDebug()<<"change the saturation:"<<n_value;
    #if defined(Q_OS_LINUX)
        qDebug()<<"ready to change the saturation";
//        if(pdvr!=NULL);
//            pdvr->setExposureCompensationData(n_value);
    #endif
        ui->ExposureCompensationLabel->setText(QString("%1").arg(n_value));
    }
    else{
        qDebug()<<"no signals";
    }

}
void SetFirst::on_audioButton_clicked()
{
    if(ui->audioButton->isChecked()){
        qDebug()<<"Set Current audio "<<g_pStaticMaindesktop->m_iCurCamera<<" enable to record when reboot";
        config_set_sound(g_pStaticMaindesktop->m_iCurCamera,1);
        ui->audioButton->setStyleSheet("background-color:#54ff4b;");
    }
    else{
        qDebug()<<"Set Current audio "<<g_pStaticMaindesktop->m_iCurCamera<<" disable to record when reboot";
        config_set_sound(g_pStaticMaindesktop->m_iCurCamera,0);
        ui->audioButton->setStyleSheet("background-color:#38a4d6;");
    }
}
void SetFirst::on_ADASButton_clicked()
{
    if(ui->ADASButton->isChecked()){
        qDebug()<<"ADAS 1";
    #if defined(Q_OS_LINUX)
        config_set_adas(0,1);
        open_adas_front=1;
        ui->ADASButton->setStyleSheet("background-color:#54ff4b;");
    #endif
    }
    else{
        qDebug()<<"ADAS 0";
    #if defined(Q_OS_LINUX)
        config_set_adas(0,0);
        open_adas_front=0;
        ui->ADASButton->setStyleSheet("background-color:#38a4d6;");
    #endif
    }
}
void SetFirst::on_movieButton_clicked()
{
    if(ui->movieButton->isChecked()){
        qDebug()<<"Set Current Preview Camera"<<g_pStaticMaindesktop->m_iCurCamera<<" enable to record when reboot";
        config_set_startup(g_pStaticMaindesktop->m_iCurCamera,1);
        ui->movieButton->setStyleSheet("background-color:#54ff4b;");
    }
    else
    {
        qDebug()<<"Set Current Preview Camera"<<g_pStaticMaindesktop->m_iCurCamera<<" disbale to record when reboot";
        config_set_startup(g_pStaticMaindesktop->m_iCurCamera,0);
        ui->movieButton->setStyleSheet("background-color:#38a4d6;");
    }
}
void SetFirst::on_reverseButton_clicked()
{
    if(ui->reverseButton->isChecked()){
        qDebug()<<"REVERSE 1";
    #if defined(Q_OS_LINUX)
        #if 0
        config_set_reverseLine(0,1);
        #endif
        open_reverseLine_front=1;
        ui->reverseButton->setStyleSheet("background-color:#54ff4b;");
    #endif
    }
    else{
        qDebug()<<"REVERSE 0";
    #if defined(Q_OS_LINUX)
        #if 0
        config_set_reverseLine(0,0);
        #endif
        open_reverseLine_front=0;
        ui->reverseButton->setStyleSheet("background-color:#38a4d6;");
    #endif
    }
}

void SetFirst::on_voiceButton_clicked()
{
    if(!voiceButtonState){

        ui->voiceButton->setStyleSheet("QPushButton{border-image:url(:/icon/no_sound.png)};");
        ui->voiceSlider->setValue(0);
        ui->voiceSlider->setEnabled(false);
        voiceButtonState=true;
    }
    else{

        ui->voiceButton->setStyleSheet("QPushButton{border-image:url(:/icon/sound.png)};");
        ui->voiceSlider->setValue(g_iNowVoiceValue);
        ui->voiceSlider->setEnabled(true);
        voiceButtonState=false;
    }

}

void SetFirst::on_movieTimeSetting_valueChanged(int value)
{
    qDebug() << "Value : "  << value;
    qDebug() << "Text : "  << ui->movieTimeSetting->text();
    g_iRecordTime=value;
#if defined(os_test)
    config_set_cyctime(0,g_iRecordTime);
#endif
}
void SetFirst::on_comboBox_currentIndexChanged(int index)
{
    qDebug()<<"save the resolutiong change";
    if(ui->comboBox->currentIndex()==0){
    #if defined(os_test)
        config_set_width(0,1920);
        config_set_heigth(0,1080);
    #endif

    }else if(ui->comboBox->currentIndex()==1){
    #if defined(os_test)
        config_set_width(0,1280);
        config_set_heigth(0,720);
    #endif
    }
}
void SetFirst::setWindowStyleSheet()
{

    QPalette p=QPalette();
    p.setColor(QPalette::WindowText,Qt::white);

    ui->label->setPalette(p);
    ui->label_2->setPalette(p);
    ui->voiceLabel->setPalette(p);
    ui->lightLabel->setPalette(p);
    ui->ColorEffectLabel->setPalette(p);
    ui->ExposureCompensationLabel->setPalette(p);
    ui->whiteBalanceLabel->setPalette(p);

}

void SetFirst::on_settingsButton_clicked()
{       
    this->hide();
    setSecond_Desk->showNormal();
}

void SetFirst::on_returnButton_clicked()
{
    this->close();
    g_pStaticMaindesktop->setHidden(false);
}




