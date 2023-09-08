#include <QDebug>
#include <QString>

#include "recordseldlg.h"
#include "ui_recordseldlg.h"
#include "main_desktop.h"


extern main_desktop *g_pStaticMaindesktop;

RecordSelDlg::RecordSelDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordSelDlg)
{
    ui->setupUi(this);
    ui->buttonGroup->setExclusive(false);
	InitCheckBoxStyle();
	m_pRedCamState = g_pStaticMaindesktop->m_iRedCameraState;
	SelCheckBox();
	UpdateCurCamera(g_pStaticMaindesktop->m_iCurCamera);
	m_pNewRedCameraId = new int[MAX_TEST_CAMERA];
	for(int iCnt = 0; iCnt < MAX_TEST_CAMERA; iCnt++)
	{
		m_pNewRedCameraId[iCnt] = 0xff;
	}
    connect(ui->buttonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));
}

RecordSelDlg::~RecordSelDlg()
{
    delete ui;
	delete []m_pNewRedCameraId;
}

void RecordSelDlg::SelCheckBox()
{
	for(int iCnt = 0; iCnt < MAX_TEST_CAMERA; iCnt++)
	{
		int iCamerdState = m_pRedCamState[iCnt];
		//printf("===RecordSelDlg::SelCheckBox:iCamerdState:%d m_pRedCamState[%d]:%d\n",iCamerdState,iCnt,m_pRedCamState[iCnt]);
		if(iCamerdState == 1)
		{
			switch(iCnt)
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
		else if(iCamerdState == 0)
		{
			switch(iCnt)
			{
				case 0:
					ui->checkBoxVideo0->setChecked(false);
					break;
				case 1:
					ui->checkBoxVideo1->setChecked(false);
					break;
				case 2:
					ui->checkBoxVideo2->setChecked(false);
					break;
				case 3:
					ui->checkBoxVideo3->setChecked(false);
					break;
				case 4:
					ui->checkBoxVideo4->setChecked(false);
					break;
				case 5:
					ui->checkBoxVideo5->setChecked(false);
					break;
				case 6:
					ui->checkBoxVideo6->setChecked(false);
					break;
				case 7:
					ui->checkBoxVideo7->setChecked(false);
					break;
				default:
					break;
			}
		}
		else
		{
			//printf("===The record of camera%d has not been started\n",iCnt);
			switch(iCnt)
			{
				case 0:
					ui->checkBoxVideo0->setChecked(false);
                    ui->checkBoxVideo0->setEnabled(false);
					break;
				case 1:
					ui->checkBoxVideo1->setChecked(false);
                    ui->checkBoxVideo1->setEnabled(false);
					break;
				case 2:
					ui->checkBoxVideo2->setChecked(false);
                    ui->checkBoxVideo2->setEnabled(false);
					break;
				case 3:
					ui->checkBoxVideo3->setChecked(false);
                    ui->checkBoxVideo3->setEnabled(false);
					break;
				case 4:
					ui->checkBoxVideo4->setChecked(false);
                    ui->checkBoxVideo4->setEnabled(false);
					break;
				case 5:
					ui->checkBoxVideo5->setChecked(false);
                    ui->checkBoxVideo5->setEnabled(false);
					break;
				case 6:
					ui->checkBoxVideo6->setChecked(false);
                    ui->checkBoxVideo6->setEnabled(false);
					break;
				case 7:
					ui->checkBoxVideo7->setChecked(false);
                    ui->checkBoxVideo7->setEnabled(false);
					break;
				default:
					break;
			}

		}
	}
}

bool RecordSelDlg::CheckBoxIsEnabled(int iCameraId)
{
	switch(iCameraId)
	{
		case 0:
			return ui->checkBoxVideo0->isEnabled();
			break;
		case 1:
			return ui->checkBoxVideo1->isEnabled();
			break;
		case 2:
			return ui->checkBoxVideo2->isEnabled();
			break;
		case 3:
			return ui->checkBoxVideo3->isEnabled();
			break;
		case 4:
			return ui->checkBoxVideo4->isEnabled();
			break;
		case 5:
			return ui->checkBoxVideo5->isEnabled();
			break;
		case 6:
			return ui->checkBoxVideo6->isEnabled();
			break;
		case 7:
			return ui->checkBoxVideo7->isEnabled();
			break;
		default:
			break;
	}
	return false;
}

void RecordSelDlg::onButtonClicked(QAbstractButton *button)
{
    qDebug() << QString("Clicked Button : %1").arg(button->text());

    QList<QAbstractButton*> list = ui->buttonGroup->buttons();
    foreach (QAbstractButton *pCheckBox, list)
    {
        //QString strStatus = pCheckBox->isChecked() ? "Checked" : "Unchecked";
        //qDebug() << QString("Button : %1 is %2").arg(pCheckBox->text()).arg(strStatus);
        if(pCheckBox->isChecked())
        {
			int iRedCameraId = GetRedCameraId(pCheckBox->text());
			if(iRedCameraId != 0xff)
			{
				m_pNewRedCameraId[iRedCameraId] = 1;
				qDebug() << "===Select" << pCheckBox->text() << "iCameraId" << iRedCameraId << endl;
			}
        }
		else
		{
			int iRedCameraId = GetRedCameraId(pCheckBox->text());
            if((iRedCameraId != 0xff) && CheckBoxIsEnabled(iRedCameraId))
			{
				m_pNewRedCameraId[iRedCameraId] = 0;
				qDebug() << "===Cancel" << pCheckBox->text() << "iCameraId" << iRedCameraId << endl;
			}
		}

    }
	
}

void RecordSelDlg::on_pushButtonEnter_clicked()
{
    this->close();
    g_pStaticMaindesktop->setHidden(false);
	g_pStaticMaindesktop->RecordCamSel(m_pNewRedCameraId);
}


int RecordSelDlg::GetRedCameraId(QString QStr)
{
	char *pRedCameraVideo[MAX_TEST_CAMERA]={"RedVideo0","RedVideo1","RedVideo2","RedVideo3","RedVideo4","RedVideo5","RedVideo6","RedVideo7"};
	for(int iCnt = 0; iCnt < MAX_TEST_CAMERA; iCnt++)
	{
		QString Str(pRedCameraVideo[iCnt]);
		//qDebug()<<"Ori:"<<Str<<"Cmp:"<<QStr<<endl;
		if(Str.compare(QStr) == 0)
		{
			return iCnt;
		}
	}
	return 0xff;
}

void RecordSelDlg::UpdateCurCamera(int iCameraId)
{
    QString CruCamInfo = "当前预览:Video"+ QString::number(iCameraId,10);
    ui->VideoLabel->setText(tr(CruCamInfo.toStdString().data()));
    ui->VideoLabel->setAlignment(Qt::AlignCenter);
    ui->VideoLabel->setStyleSheet("font-size:20px;background-color:rgb(0, 0, 0,0);color:white;");
}

void RecordSelDlg::InitCheckBoxStyle()
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



