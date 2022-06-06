#include "settings.h"
#include "ui_settings.h"
#include "setfirst.h"
#include "ui_setfirst.h"

#include <QDesktopWidget>
#include <QButtonGroup>
Settings* pStatic_settings=NULL;

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

//    this->setWindowFlags(Qt::FramelessWindowHint);

    #if 0
    ui->settingTab->setStyleSheet("QTabWidget::pane{ \
            border-left: 0px solid #eeeeee;\
        }");
    #endif


    abouts=new About(this);
    previews=new Preview(this);
    adass=new ADAS(this);
    reverselines=new ReverseLine(this);
    timesettings=new TimeSetting(this);
    QButtonGroup* btnGroup1=new QButtonGroup();
    btnGroup1->addButton(ui->previewButton);
    btnGroup1->addButton(ui->AdasButton);
    btnGroup1->addButton(ui->reverseLineButton);
    btnGroup1->addButton(ui->timeSetButton);
    btnGroup1->addButton(ui->aboutButton);
    btnGroup1->setExclusive(true);

    ui->previewButton->setCheckable(true);
    ui->AdasButton->setCheckable(true);
    ui->reverseLineButton->setCheckable(true);
    ui->timeSetButton->setCheckable(true);
    ui->aboutButton->setCheckable(true);

    ui->stackedWidget->addWidget(abouts);
    ui->stackedWidget->addWidget(previews);
    ui->stackedWidget->addWidget(adass);
    ui->stackedWidget->addWidget(reverselines);
    ui->stackedWidget->addWidget(timesettings);

    ui->stackedWidget->setCurrentWidget(previews);

    ui->previewButton->setChecked(true);
    ui->previewButton->setStyleSheet("background-color:red");

    connect(ui->returnButton,SIGNAL(clicked()),this,SLOT(on_returnButton_clicked()));

    pStatic_settings=this;
}


    void Settings::FormInCenter()
    {
        QDesktopWidget w;
        int deskWidth = w.width();
        int deskHeight = w.height();
            this->resize(deskWidth*3/4,deskHeight*3/4);
        QPoint movePoint(deskWidth / 2 - this->width() / 2, deskHeight / 2 - this->height() / 2);
        this->move(movePoint);
    }
Settings::~Settings()
{
    delete ui;
}



void Settings::on_returnButton_clicked()
{
    this->close();

    SetFirst* psetFirst=static_cast<SetFirst*>(parentWidget());
    psetFirst->setHidden(false);
}

void Settings::on_previewButton_clicked()
{
    ui->previewButton->setChecked(true);
    ui->previewButton->setStyleSheet("background-color:red");
    ui->AdasButton->setStyleSheet("border-style: none;"
                                      "border: 0px;"
                                      "color: #F0F0F0;"
                                      "padding: 5px;	"
                                      "border-radius:5px;"
                                     " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->reverseLineButton->setStyleSheet("border-style: none;"
                                      "border: 0px;"
                                      "color: #F0F0F0;"
                                      "padding: 5px;	"
                                      "border-radius:5px;"
                                     " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->timeSetButton->setStyleSheet("border-style: none;"
                                   "border: 0px;"
                                   "color: #F0F0F0;"
                                   "padding: 5px;	"
                                   "border-radius:5px;"
                                  " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->aboutButton->setStyleSheet("border-style: none;"
                                   "border: 0px;"
                                   "color: #F0F0F0;"
                                   "padding: 5px;	"
                                   "border-radius:5px;"
                                  " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->stackedWidget->setCurrentWidget(previews);

}

void Settings::on_AdasButton_clicked()
{
    ui->AdasButton->setChecked(true);
    ui->AdasButton->setStyleSheet("background-color:red");
    ui->previewButton->setStyleSheet("border-style: none;"
                                      "border: 0px;"
                                      "color: #F0F0F0;"
                                      "padding: 5px;	"
                                      "border-radius:5px;"
                                     " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->reverseLineButton->setStyleSheet("border-style: none;"
                                      "border: 0px;"
                                      "color: #F0F0F0;"
                                      "padding: 5px;	"
                                      "border-radius:5px;"
                                     " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->timeSetButton->setStyleSheet("border-style: none;"
                                   "border: 0px;"
                                   "color: #F0F0F0;"
                                   "padding: 5px;	"
                                   "border-radius:5px;"
                                  " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->aboutButton->setStyleSheet("border-style: none;"
                                   "border: 0px;"
                                   "color: #F0F0F0;"
                                   "padding: 5px;	"
                                   "border-radius:5px;"
                                  " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->stackedWidget->setCurrentWidget(adass);

}

void Settings::on_reverseLineButton_clicked()
{
    ui->reverseLineButton->setChecked(true);
    ui->reverseLineButton->setStyleSheet("background-color:red");
    ui->AdasButton->setStyleSheet("border-style: none;"
                                      "border: 0px;"
                                      "color: #F0F0F0;"
                                      "padding: 5px;	"
                                      "border-radius:5px;"
                                     " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->previewButton->setStyleSheet("border-style: none;"
                                      "border: 0px;"
                                      "color: #F0F0F0;"
                                      "padding: 5px;	"
                                      "border-radius:5px;"
                                     " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->timeSetButton->setStyleSheet("border-style: none;"
                                   "border: 0px;"
                                   "color: #F0F0F0;"
                                   "padding: 5px;	"
                                   "border-radius:5px;"
                                  " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->aboutButton->setStyleSheet("border-style: none;"
                                   "border: 0px;"
                                   "color: #F0F0F0;"
                                   "padding: 5px;	"
                                   "border-radius:5px;"
                                  " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->stackedWidget->setCurrentWidget(reverselines);

}

void Settings::on_timeSetButton_clicked()
{
    ui->timeSetButton->setChecked(true);
    ui->timeSetButton->setStyleSheet("background-color:red");
    ui->AdasButton->setStyleSheet("border-style: none;"
                                      "border: 0px;"
                                      "color: #F0F0F0;"
                                      "padding: 5px;	"
                                      "border-radius:5px;"
                                     " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->reverseLineButton->setStyleSheet("border-style: none;"
                                      "border: 0px;"
                                      "color: #F0F0F0;"
                                      "padding: 5px;	"
                                      "border-radius:5px;"
                                     " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->previewButton->setStyleSheet("border-style: none;"
                                   "border: 0px;"
                                   "color: #F0F0F0;"
                                   "padding: 5px;	"
                                   "border-radius:5px;"
                                  " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->aboutButton->setStyleSheet("border-style: none;"
                                   "border: 0px;"
                                   "color: #F0F0F0;"
                                   "padding: 5px;	"
                                   "border-radius:5px;"
                                  " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->stackedWidget->setCurrentWidget(timesettings);

}

void Settings::on_aboutButton_clicked()
{
    ui->aboutButton->setChecked(true);
    ui->aboutButton->setStyleSheet("background-color:red");
    ui->AdasButton->setStyleSheet("border-style: none;"
                                      "border: 0px;"
                                      "color: #F0F0F0;"
                                      "padding: 5px;	"
                                      "border-radius:5px;"
                                     " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->reverseLineButton->setStyleSheet("border-style: none;"
                                      "border: 0px;"
                                      "color: #F0F0F0;"
                                      "padding: 5px;	"
                                      "border-radius:5px;"
                                     " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->timeSetButton->setStyleSheet("border-style: none;"
                                   "border: 0px;"
                                   "color: #F0F0F0;"
                                   "padding: 5px;	"
                                   "border-radius:5px;"
                                  " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->previewButton->setStyleSheet("border-style: none;"
                                   "border: 0px;"
                                   "color: #F0F0F0;"
                                   "padding: 5px;	"
                                   "border-radius:5px;"
                                  " background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);");
    ui->stackedWidget->setCurrentWidget(abouts);

}
