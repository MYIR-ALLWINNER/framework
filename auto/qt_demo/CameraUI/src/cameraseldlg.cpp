#include <QDebug>
#include <QString> 

#include "main_desktop.h"
#include "cameraseldlg.h"
#include "ui_cameraseldlg.h"

extern main_desktop *g_pStaticMaindesktop;

CameraSelDlg::CameraSelDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraSelDlg)
{
    ui->setupUi(this);
	InitCheckBoxStyle();
	m_iNewCameraId = -1;
    SelCheckBox(g_pStaticMaindesktop->m_iCurCamera);
    connect(ui->buttonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));

#if 0
    QPalette p=QPalette();
    p.setColor(QPalette::WindowText,Qt::white);
    ui->checkBoxVideo0->setPalette(p);
    ui->checkBoxVideo1->setPalette(p);
    ui->checkBoxVideo2->setPalette(p);
    ui->checkBoxVideo3->setPalette(p);
    ui->checkBoxVideo4->setPalette(p);
    ui->checkBoxVideo5->setPalette(p);
    ui->checkBoxVideo6->setPalette(p);
    ui->checkBoxVideo7->setPalette(p);
    QPalette pl = QPalette();//this->palette();
    pl.setColor(QPalette::Window, QColor(0, 0, 0, 200));    //   设置背景颜色为黑色，如果不设置默认为白色
    this->setPalette(pl);
    this->setAutoFillBackground(true);
    this->setWindowOpacity(0.6);     //   背景和元素都设置透明效果
#endif
}

CameraSelDlg::~CameraSelDlg()
{
    delete ui;
}

void CameraSelDlg::onButtonClicked(QAbstractButton *button)
{
    qDebug() << QString("Clicked Button : %1").arg(button->text());

    QList<QAbstractButton*> list = ui->buttonGroup->buttons();
    foreach (QAbstractButton *pCheckBox, list)
    {
        //QString strStatus = pCheckBox->isChecked() ? "Checked" : "Unchecked";
        //qDebug() << QString("Button : %1 is %2").arg(pCheckBox->text()).arg(strStatus);
		if(pCheckBox->isChecked())
		{
            m_iNewCameraId = GetCameraId(pCheckBox->text());
			qDebug() << "===Select" << pCheckBox->text() << "iCameraId" << m_iNewCameraId << endl;
			break;
		}
    }
}

void CameraSelDlg::on_pushButtonEnter_clicked()
{
    this->close();
    g_pStaticMaindesktop->setHidden(false);
	g_pStaticMaindesktop->CameraSwitch(m_iNewCameraId);
}

int CameraSelDlg::GetCameraId(QString QStr)
{
	char *pCameraVideo[MAX_TEST_CAMERA]={"Video0","Video1","Video2","Video3","Video4","Video5","Video6","Video7"};
	for(int iCnt = 0; iCnt < MAX_TEST_CAMERA; iCnt++)
	{
		QString Str(pCameraVideo[iCnt]);
		//qDebug()<<"Ori:"<<Str<<"Cmp:"<<QStr<<endl;
		if(Str.compare(QStr) == 0)
		{
			return iCnt;
		}
	}
	return -1;
}

void CameraSelDlg::SelCheckBox(int iCheBoxId)
{
    switch(iCheBoxId)
    {
        case 0:
            ui->checkBoxVideo0->setChecked(true);
            break;
        case 1:
            ui->checkBoxVideo1->setChecked(true);
            break;
        case 2:
            ui->checkBoxVideo2->setChecked(true);
            break;
        case 3:
            ui->checkBoxVideo3->setChecked(true);
            break;
        case 4:
            ui->checkBoxVideo4->setChecked(true);
            break;
        case 5:
            ui->checkBoxVideo5->setChecked(true);
            break;
        case 6:
            ui->checkBoxVideo6->setChecked(true);
            break;
        case 7:
            ui->checkBoxVideo7->setChecked(true);
            break;
        default:
            break;
    }
}

void CameraSelDlg::InitCheckBoxStyle()
{
    QString QStrStyle("QCheckBox{color:white;background-color:rgb(0, 0, 0,0);}\
                        QCheckBox::indicator{width: 35px; height:50px; }\
						 QCheckBox::indicator:unchecked{image:url(:/icon/unchecked.png);}\
                         QCheckBox::indicator:checked{image:url(:/icon/checked.png);}");

	ui->checkBoxVideo0->setStyleSheet(QStrStyle);
	ui->checkBoxVideo1->setStyleSheet(QStrStyle);
	ui->checkBoxVideo2->setStyleSheet(QStrStyle);
	ui->checkBoxVideo3->setStyleSheet(QStrStyle);
	ui->checkBoxVideo4->setStyleSheet(QStrStyle);
	ui->checkBoxVideo5->setStyleSheet(QStrStyle);
	ui->checkBoxVideo6->setStyleSheet(QStrStyle);
	ui->checkBoxVideo7->setStyleSheet(QStrStyle);
    ui->pushButtonEnter->setStyleSheet(
                //正常状态样式
                "QPushButton{"
                "background-color:rgba(100,225,100,30);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "border-width:4px;"                     //边框宽度像素
                "border-radius:10px;"                   //边框圆角半径像素
                "border-color:rgba(255,255,255,30);"    //边框颜色
                "color:white;"                //字体颜色
                "}"
                //鼠标按下样式
                "QPushButton:pressed{"
                "background-color:rgba(100,255,100,200);"
                "border-color:rgba(255,255,255,200);"
                "border-style:inset;"
                "color:white;"
                "}");
}



