/********************************************************************************
** Form generated from reading UI file 'setfirst.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETFIRST_H
#define UI_SETFIRST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetFirst
{
public:
    QGridLayout *gridLayout_10;
    QWidget *widget_4;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QPushButton *settingsButton;
    QSpacerItem *verticalSpacer;
    QPushButton *returnButton;
    QSpacerItem *verticalSpacer_3;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QPushButton *ADASButton;
    QPushButton *audioButton;
    QPushButton *movieButton;
    QPushButton *reverseButton;
    QWidget *widget_2;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QSpinBox *movieTimeSetting;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QComboBox *comboBox;
    QWidget *widget_3;
    QGridLayout *gridLayout_9;
    QWidget *widget_5;
    QGridLayout *gridLayout_4;
    QPushButton *voiceButton;
    QSlider *voiceSlider;
    QLabel *voiceLabel;
    QWidget *widget_6;
    QGridLayout *gridLayout_5;
    QPushButton *lightButton;
    QLabel *lightLabel;
    QSlider *lightSlider;
    QWidget *widget_7;
    QGridLayout *gridLayout_6;
    QPushButton *ColorEffectButton;
    QSlider *ColorEffectSlider;
    QLabel *ColorEffectLabel;
    QWidget *widget_8;
    QGridLayout *gridLayout_7;
    QPushButton *ExposureCompensationButton;
    QSlider *ExposureCompensationSlider;
    QLabel *ExposureCompensationLabel;
    QWidget *widget_9;
    QGridLayout *gridLayout_8;
    QPushButton *whiteBalanceButton;
    QSlider *whiteBalanceSlider;
    QLabel *whiteBalanceLabel;
    QLabel *DisInfoLabel;

    void setupUi(QDialog *SetFirst)
    {
        if (SetFirst->objectName().isEmpty())
            SetFirst->setObjectName(QString::fromUtf8("SetFirst"));
        SetFirst->resize(800, 480);
        SetFirst->setStyleSheet(QString::fromUtf8("background-color:rgb(104, 98, 98,90);\n"
"border-radius:15px;\n"
""));
        gridLayout_10 = new QGridLayout(SetFirst);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        widget_4 = new QWidget(SetFirst);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setStyleSheet(QString::fromUtf8("background-color:rgb(86, 76, 75,90);\n"
"border-radius:10px;"));
        gridLayout = new QGridLayout(widget_4);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        settingsButton = new QPushButton(widget_4);
        settingsButton->setObjectName(QString::fromUtf8("settingsButton"));
        settingsButton->setMinimumSize(QSize(41, 41));
        settingsButton->setMaximumSize(QSize(41, 41));
        settingsButton->setFocusPolicy(Qt::NoFocus);
        settingsButton->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/settings.png);\n"
"background-color:rgb(255,255,255,0);"));

        verticalLayout->addWidget(settingsButton);

        verticalSpacer = new QSpacerItem(20, 268, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        returnButton = new QPushButton(widget_4);
        returnButton->setObjectName(QString::fromUtf8("returnButton"));
        returnButton->setMinimumSize(QSize(41, 41));
        returnButton->setMaximumSize(QSize(41, 41));
        returnButton->setFocusPolicy(Qt::NoFocus);
        returnButton->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/Back.png);\n"
"background-color:rgb(255,255,255,0);s"));

        verticalLayout->addWidget(returnButton);

        verticalSpacer_3 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(2, 3);
        verticalLayout->setStretch(3, 2);
        verticalLayout->setStretch(4, 1);

        horizontalLayout_4->addLayout(verticalLayout);

        horizontalLayout_4->setStretch(0, 2);

        gridLayout->addLayout(horizontalLayout_4, 0, 0, 1, 1);


        gridLayout_10->addWidget(widget_4, 0, 0, 3, 1);

        widget = new QWidget(SetFirst);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("background-color:rgb(86, 76, 75,80);\n"
"border-radius:10px;"));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        ADASButton = new QPushButton(widget);
        ADASButton->setObjectName(QString::fromUtf8("ADASButton"));
        ADASButton->setMinimumSize(QSize(0, 0));
        ADASButton->setMaximumSize(QSize(16000, 16000));
        ADASButton->setFocusPolicy(Qt::NoFocus);
        ADASButton->setStyleSheet(QString::fromUtf8("background-color:#38a4d6;\n"
"font: 12pt \"\345\256\213\344\275\223\";\n"
"border-radius:5px;\n"
"  color:rgb(255,255,255);"));

        gridLayout_2->addWidget(ADASButton, 1, 0, 1, 1);

        audioButton = new QPushButton(widget);
        audioButton->setObjectName(QString::fromUtf8("audioButton"));
        audioButton->setMinimumSize(QSize(0, 0));
        audioButton->setMaximumSize(QSize(16000, 16000));
        audioButton->setFocusPolicy(Qt::NoFocus);
        audioButton->setStyleSheet(QString::fromUtf8("background-color:#38a4d6;\n"
"font: 75 12pt \"Aharoni\";\n"
"border-radius:5px;\n"
"  color:rgb(255,255,255);"));

        gridLayout_2->addWidget(audioButton, 0, 1, 1, 1);

        movieButton = new QPushButton(widget);
        movieButton->setObjectName(QString::fromUtf8("movieButton"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(movieButton->sizePolicy().hasHeightForWidth());
        movieButton->setSizePolicy(sizePolicy);
        movieButton->setMinimumSize(QSize(0, 0));
        movieButton->setMaximumSize(QSize(160000, 160000));
        movieButton->setFocusPolicy(Qt::NoFocus);
        movieButton->setStyleSheet(QString::fromUtf8("background-color:#38a4d6;\n"
"font: 12pt \"\345\256\213\344\275\223\";\n"
"border-radius:5px;\n"
"color:rgb(255,255,255);\n"
""));

        gridLayout_2->addWidget(movieButton, 0, 0, 1, 1);

        reverseButton = new QPushButton(widget);
        reverseButton->setObjectName(QString::fromUtf8("reverseButton"));
        reverseButton->setMinimumSize(QSize(0, 0));
        reverseButton->setMaximumSize(QSize(16000, 16000));
        reverseButton->setFocusPolicy(Qt::NoFocus);
        reverseButton->setStyleSheet(QString::fromUtf8("background-color:#38a4d6;\n"
"font: 75 12pt \"Aharoni\";\n"
"border-radius:5px;\n"
"  color:rgb(255,255,255);"));

        gridLayout_2->addWidget(reverseButton, 1, 1, 1, 1);


        gridLayout_10->addWidget(widget, 0, 1, 3, 1);

        widget_2 = new QWidget(SetFirst);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setStyleSheet(QString::fromUtf8("background-color:rgb(81,78,72,80);\n"
"border-radius:10px;\n"
""));
        gridLayout_3 = new QGridLayout(widget_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(10, -1, -1, -1);
        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 0));
        label->setMaximumSize(QSize(151, 31));
        label->setStyleSheet(QString::fromUtf8("color:#ffffff;\n"
"font: 75 11pt \"Aharoni\";"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        movieTimeSetting = new QSpinBox(widget_2);
        movieTimeSetting->setObjectName(QString::fromUtf8("movieTimeSetting"));
        movieTimeSetting->setMinimumSize(QSize(0, 0));
        movieTimeSetting->setMaximumSize(QSize(141, 41));
        movieTimeSetting->setStyleSheet(QString::fromUtf8("QSpinBox::up-button {subcontrol-origin:border;subcontrol-position:right;image: url(:/icon/right_arrow.png);width: 17px;height: 32px;}\n"
"QSpinBox::down-button:pressed{subcontrol-position:left;image: url(:/icon/left_arrow.png);width: 17px;height: 32px;}\n"
"QSpinBox::down-button {subcontrol-origin:border;subcontrol-position:left;border-image: url(:/icon/left_arrow.png);width: 17px;height: 32px;}\n"
"QSpinBox::down-button:enabled:hover {background: rgb(255, 255, 255, 30);}\n"
"QSpinBox::up-button:enabled:hover {background: rgb(255, 255, 255, 30);}\n"
"QSpinBox::up-button:pressed{subcontrol-origin:border;subcontrol-position:right;image: url(:/icon/right_arrow.png); width: 17px;height: 32px;}\n"
"\n"
"QSpinBox{border: 1px solid rgb(100, 100, 100);text-align: center; border-radius: 4px;color:rgb(255,255,255);}\n"
"  \n"
""));
        movieTimeSetting->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(movieTimeSetting);


        gridLayout_3->addLayout(verticalLayout_2, 1, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(10, -1, -1, -1);
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 0));
        label_2->setMaximumSize(QSize(141, 31));
        label_2->setStyleSheet(QString::fromUtf8("font: 75 11pt \"Aharoni\";\n"
"color:#ffffff;\n"
"\n"
""));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_2);

        comboBox = new QComboBox(widget_2);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(0, 0));
        comboBox->setMaximumSize(QSize(151, 41));
        comboBox->setStyleSheet(QString::fromUtf8("QComboBox::drop-down {\n"
"	subcontrol-origin: padding;\n"
"	subcontrol-position: top right;\n"
"	width: 15px; \n"
"	border-left-width: 1px;\n"
"	border-left-style: solid;\n"
"	border-top-right-radius: 3px;\n"
"	border-bottom-right-radius: 3px;\n"
"	border-left-color: #50A3F0;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"	border-image: url(:/icon/arrowdown.png); \n"
"}\n"
"QComboBox{border: 1px solid rgb(100, 100, 100);text-align: center;text-color:rgb(255,255,255); border-radius: 4px; color:rgb(255,255,255);}\n"
"\n"
" "));

        verticalLayout_3->addWidget(comboBox);


        gridLayout_3->addLayout(verticalLayout_3, 1, 1, 1, 1);


        gridLayout_10->addWidget(widget_2, 0, 2, 1, 1);

        widget_3 = new QWidget(SetFirst);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setStyleSheet(QString::fromUtf8("background-color:rgb(81,78,72,80);\n"
"border-radius:10px;"));
        gridLayout_9 = new QGridLayout(widget_3);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        widget_5 = new QWidget(widget_3);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        gridLayout_4 = new QGridLayout(widget_5);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        voiceButton = new QPushButton(widget_5);
        voiceButton->setObjectName(QString::fromUtf8("voiceButton"));
        voiceButton->setEnabled(true);
        voiceButton->setMinimumSize(QSize(31, 31));
        voiceButton->setMaximumSize(QSize(31, 31));
        voiceButton->setFocusPolicy(Qt::NoFocus);
        voiceButton->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/sound.png);\n"
"\n"
"background-color:rgb(255,255,255,0);\n"
"\n"
""));

        gridLayout_4->addWidget(voiceButton, 0, 0, 1, 1);

        voiceSlider = new QSlider(widget_5);
        voiceSlider->setObjectName(QString::fromUtf8("voiceSlider"));
        voiceSlider->setFocusPolicy(Qt::NoFocus);
        voiceSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal { \n"
"	background: #cbcbcb; \n"
"	height: 6px; \n"
"	border-radius: 1px; \n"
"	padding-left:-1px;\n"
"	padding-right:-1px;\n"
"	padding-top:-1px;\n"
"	padding-bottom:-1px;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal {\n"
"	background: #cbcbcb;\n"
"	border-radius: 2px;\n"
"}\n"
"QSlider::sub-page:horizontal\n"
"{\n"
"	background: qlineargradient(x1:0, y1:0, x2:0,y2:1,stop:0 #439cf4, stop:1 #439cf4);\n"
" 	background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,stop: 0 #439cf4, stop: 1 #439cf4);\n"
"    width: 10px;\n"
"	border-radius: 2px;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"	width: 13px; \n"
"	margin-top: -3px; \n"
"	margin-bottom: -3px; \n"
"	border-radius: 6px;\n"
"	background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5,stop:0.6 #F0F0F0, stop:0.778409 #50A3F0);\n"
"}\n"
"QSlider{\n"
"background-color:rgb(255,255,255,0);\n"
"}\n"
""));
        voiceSlider->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(voiceSlider, 0, 1, 1, 1);

        voiceLabel = new QLabel(widget_5);
        voiceLabel->setObjectName(QString::fromUtf8("voiceLabel"));
        voiceLabel->setMinimumSize(QSize(0, 0));
        voiceLabel->setMaximumSize(QSize(31, 31));
        voiceLabel->setStyleSheet(QString::fromUtf8("  color:rgb(255,255,255);\n"
"background-color:rgb(255,255,255,0);"));
        voiceLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(voiceLabel, 0, 2, 1, 1);

        gridLayout_4->setColumnStretch(0, 1);
        gridLayout_4->setColumnStretch(1, 4);
        gridLayout_4->setColumnStretch(2, 1);

        gridLayout_9->addWidget(widget_5, 0, 0, 1, 1);

        widget_6 = new QWidget(widget_3);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        gridLayout_5 = new QGridLayout(widget_6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        lightButton = new QPushButton(widget_6);
        lightButton->setObjectName(QString::fromUtf8("lightButton"));
        lightButton->setEnabled(false);
        lightButton->setMinimumSize(QSize(31, 31));
        lightButton->setMaximumSize(QSize(31, 31));
        lightButton->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/brightness.png);\n"
"background-color:rgb(255,255,255,0);"));

        gridLayout_5->addWidget(lightButton, 0, 0, 1, 1);

        lightLabel = new QLabel(widget_6);
        lightLabel->setObjectName(QString::fromUtf8("lightLabel"));
        lightLabel->setMinimumSize(QSize(0, 0));
        lightLabel->setMaximumSize(QSize(31, 31));
        lightLabel->setStyleSheet(QString::fromUtf8("  color:rgb(255,255,255);\n"
"background-color:rgb(255,255,255,0);"));
        lightLabel->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(lightLabel, 0, 2, 1, 1);

        lightSlider = new QSlider(widget_6);
        lightSlider->setObjectName(QString::fromUtf8("lightSlider"));
        lightSlider->setFocusPolicy(Qt::NoFocus);
        lightSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal { \n"
"	background: #cbcbcb; \n"
"	height: 6px; \n"
"	border-radius: 1px; \n"
"	padding-left:-1px;\n"
"	padding-right:-1px;\n"
"	padding-top:-1px;\n"
"	padding-bottom:-1px;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal {\n"
"	background: #cbcbcb;\n"
"	border-radius: 2px;\n"
"}\n"
"QSlider::sub-page:horizontal\n"
"{\n"
"	background: qlineargradient(x1:0, y1:0, x2:0,y2:1,stop:0 #439cf4, stop:1 #439cf4);\n"
" 	background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,stop: 0 #439cf4, stop: 1 #439cf4);\n"
"    width: 10px;\n"
"	border-radius: 2px;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"	width: 13px; \n"
"	margin-top: -3px; \n"
"	margin-bottom: -3px; \n"
"	border-radius: 6px;\n"
"	background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5,stop:0.6 #F0F0F0, stop:0.778409 #50A3F0);\n"
"}\n"
"\n"
"QSlider{\n"
"background-color:rgb(255,255,255,0);\n"
"}\n"
""));
        lightSlider->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(lightSlider, 0, 1, 1, 1);

        gridLayout_5->setColumnStretch(0, 1);
        gridLayout_5->setColumnStretch(1, 4);
        gridLayout_5->setColumnStretch(2, 1);

        gridLayout_9->addWidget(widget_6, 1, 0, 1, 1);

        widget_7 = new QWidget(widget_3);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        gridLayout_6 = new QGridLayout(widget_7);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        ColorEffectButton = new QPushButton(widget_7);
        ColorEffectButton->setObjectName(QString::fromUtf8("ColorEffectButton"));
        ColorEffectButton->setEnabled(false);
        ColorEffectButton->setMinimumSize(QSize(31, 31));
        ColorEffectButton->setMaximumSize(QSize(31, 31));
        ColorEffectButton->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/contrast.png);\n"
"background-color:rgb(255,255,255,0);"));

        gridLayout_6->addWidget(ColorEffectButton, 0, 0, 1, 1);

        ColorEffectSlider = new QSlider(widget_7);
        ColorEffectSlider->setObjectName(QString::fromUtf8("ColorEffectSlider"));
        ColorEffectSlider->setFocusPolicy(Qt::NoFocus);
        ColorEffectSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal { \n"
"	background: rgb(255,255,255,0); \n"
"	height: 6px; \n"
"	border-radius: 1px; \n"
"	padding-left:-1px;\n"
"	padding-right:-1px;\n"
"	padding-top:-1px;\n"
"	padding-bottom:-1px;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal {\n"
"	background: #cbcbcb;\n"
"	border-radius: 2px;\n"
"}\n"
"QSlider::sub-page:horizontal\n"
"{\n"
"	background: qlineargradient(x1:0, y1:0, x2:0,y2:1,stop:0 #439cf4, stop:1 #439cf4);\n"
" 	background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,stop: 0 #439cf4, stop: 1 #439cf4);\n"
"    width: 10px;\n"
"	border-radius: 2px;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"	width: 13px; \n"
"	margin-top: -3px; \n"
"	margin-bottom: -3px; \n"
"	border-radius: 6px;\n"
"	background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5,stop:0.6 #F0F0F0, stop:0.778409 #50A3F0);\n"
"}\n"
"QSlider{\n"
"background-color:rgb(255,255,255,0);\n"
"}\n"
"\n"
""));
        ColorEffectSlider->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(ColorEffectSlider, 0, 1, 1, 1);

        ColorEffectLabel = new QLabel(widget_7);
        ColorEffectLabel->setObjectName(QString::fromUtf8("ColorEffectLabel"));
        ColorEffectLabel->setMinimumSize(QSize(0, 0));
        ColorEffectLabel->setMaximumSize(QSize(31, 31));
        ColorEffectLabel->setStyleSheet(QString::fromUtf8("  color:rgb(255,255,255);\n"
"background-color:rgb(255,255,255,0);"));
        ColorEffectLabel->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(ColorEffectLabel, 0, 2, 1, 1);

        gridLayout_6->setColumnStretch(0, 1);
        gridLayout_6->setColumnStretch(1, 4);
        gridLayout_6->setColumnStretch(2, 1);

        gridLayout_9->addWidget(widget_7, 2, 0, 1, 1);

        widget_8 = new QWidget(widget_3);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        gridLayout_7 = new QGridLayout(widget_8);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        ExposureCompensationButton = new QPushButton(widget_8);
        ExposureCompensationButton->setObjectName(QString::fromUtf8("ExposureCompensationButton"));
        ExposureCompensationButton->setEnabled(false);
        ExposureCompensationButton->setMinimumSize(QSize(31, 31));
        ExposureCompensationButton->setMaximumSize(QSize(31, 31));
        ExposureCompensationButton->setStyleSheet(QString::fromUtf8("image: url(:/icon/ExposureCompensation.png);\n"
"background-color:rgb(255,255,255,0);"));

        gridLayout_7->addWidget(ExposureCompensationButton, 0, 0, 1, 1);

        ExposureCompensationSlider = new QSlider(widget_8);
        ExposureCompensationSlider->setObjectName(QString::fromUtf8("ExposureCompensationSlider"));
        ExposureCompensationSlider->setFocusPolicy(Qt::NoFocus);
        ExposureCompensationSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal { \n"
"	background: #cbcbcb; \n"
"	height: 6px; \n"
"	border-radius: 1px; \n"
"	padding-left:-1px;\n"
"	padding-right:-1px;\n"
"	padding-top:-1px;\n"
"	padding-bottom:-1px;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal {\n"
"	background: #cbcbcb;\n"
"	border-radius: 2px;\n"
"}\n"
"QSlider::sub-page:horizontal\n"
"{\n"
"	background: qlineargradient(x1:0, y1:0, x2:0,y2:1,stop:0 #439cf4, stop:1 #439cf4);\n"
" 	background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,stop: 0 #439cf4, stop: 1 #439cf4);\n"
"    width: 10px;\n"
"	border-radius: 2px;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"	width: 13px; \n"
"	margin-top: -3px; \n"
"	margin-bottom: -3px; \n"
"	border-radius: 6px;\n"
"	background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5,stop:0.6 #F0F0F0, stop:0.778409 #50A3F0);\n"
"}\n"
"\n"
"QSlider{\n"
"background-color:rgb(255,255,255,0);\n"
"}\n"
""));
        ExposureCompensationSlider->setOrientation(Qt::Horizontal);

        gridLayout_7->addWidget(ExposureCompensationSlider, 0, 1, 1, 1);

        ExposureCompensationLabel = new QLabel(widget_8);
        ExposureCompensationLabel->setObjectName(QString::fromUtf8("ExposureCompensationLabel"));
        ExposureCompensationLabel->setMinimumSize(QSize(0, 0));
        ExposureCompensationLabel->setMaximumSize(QSize(31, 31));
        ExposureCompensationLabel->setStyleSheet(QString::fromUtf8("  color:rgb(255,255,255);\n"
"background-color:rgb(255,255,255,0);"));
        ExposureCompensationLabel->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(ExposureCompensationLabel, 0, 2, 1, 1);

        gridLayout_7->setColumnStretch(0, 1);
        gridLayout_7->setColumnStretch(1, 4);
        gridLayout_7->setColumnStretch(2, 1);

        gridLayout_9->addWidget(widget_8, 3, 0, 1, 1);

        widget_9 = new QWidget(widget_3);
        widget_9->setObjectName(QString::fromUtf8("widget_9"));
        widget_9->setStyleSheet(QString::fromUtf8(""));
        gridLayout_8 = new QGridLayout(widget_9);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        whiteBalanceButton = new QPushButton(widget_9);
        whiteBalanceButton->setObjectName(QString::fromUtf8("whiteBalanceButton"));
        whiteBalanceButton->setEnabled(false);
        whiteBalanceButton->setMinimumSize(QSize(31, 31));
        whiteBalanceButton->setMaximumSize(QSize(31, 31));
        whiteBalanceButton->setStyleSheet(QString::fromUtf8("image: url(:/icon/whiteBalance.png);\n"
"background-color:rgb(255,255,255,0);"));

        gridLayout_8->addWidget(whiteBalanceButton, 0, 0, 1, 1);

        whiteBalanceSlider = new QSlider(widget_9);
        whiteBalanceSlider->setObjectName(QString::fromUtf8("whiteBalanceSlider"));
        whiteBalanceSlider->setFocusPolicy(Qt::NoFocus);
        whiteBalanceSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal { \n"
"	background: #cbcbcb; \n"
"	height: 6px; \n"
"	border-radius: 1px; \n"
"	padding-left:-1px;\n"
"	padding-right:-1px;\n"
"	padding-top:-1px;\n"
"	padding-bottom:-1px;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal {\n"
"	background: #cbcbcb;\n"
"	border-radius: 2px;\n"
"}\n"
"QSlider::sub-page:horizontal\n"
"{\n"
"	background: qlineargradient(x1:0, y1:0, x2:0,y2:1,stop:0 #439cf4, stop:1 #439cf4);\n"
" 	background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,stop: 0 #439cf4, stop: 1 #439cf4);\n"
"    width: 10px;\n"
"	border-radius: 2px;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"	width: 13px; \n"
"	margin-top: -3px; \n"
"	margin-bottom: -3px; \n"
"	border-radius: 6px;\n"
"	background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5,stop:0.6 #F0F0F0, stop:0.778409 #50A3F0);\n"
"}\n"
"\n"
"QSlider{\n"
"background-color:rgb(255,255,255,0);\n"
"}\n"
""));
        whiteBalanceSlider->setOrientation(Qt::Horizontal);

        gridLayout_8->addWidget(whiteBalanceSlider, 0, 1, 1, 1);

        whiteBalanceLabel = new QLabel(widget_9);
        whiteBalanceLabel->setObjectName(QString::fromUtf8("whiteBalanceLabel"));
        whiteBalanceLabel->setMinimumSize(QSize(0, 0));
        whiteBalanceLabel->setMaximumSize(QSize(31, 31));
        whiteBalanceLabel->setStyleSheet(QString::fromUtf8("  color:rgb(255,255,255);\n"
"background-color:rgb(255,255,255,0);"));
        whiteBalanceLabel->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(whiteBalanceLabel, 0, 2, 1, 1);

        gridLayout_8->setColumnStretch(0, 1);
        gridLayout_8->setColumnStretch(1, 4);
        gridLayout_8->setColumnStretch(2, 1);

        gridLayout_9->addWidget(widget_9, 4, 0, 1, 1);


        gridLayout_10->addWidget(widget_3, 2, 2, 1, 1);

        DisInfoLabel = new QLabel(SetFirst);
        DisInfoLabel->setObjectName(QString::fromUtf8("DisInfoLabel"));

        gridLayout_10->addWidget(DisInfoLabel, 1, 2, 1, 1);

        gridLayout_10->setColumnStretch(0, 1);
        gridLayout_10->setColumnStretch(1, 7);
        gridLayout_10->setColumnStretch(2, 5);
        widget_4->raise();
        widget_3->raise();
        widget->raise();
        widget_2->raise();
        DisInfoLabel->raise();

        retranslateUi(SetFirst);

        QMetaObject::connectSlotsByName(SetFirst);
    } // setupUi

    void retranslateUi(QDialog *SetFirst)
    {
        SetFirst->setWindowTitle(QApplication::translate("SetFirst", "Dialog", nullptr));
        settingsButton->setText(QString());
        returnButton->setText(QString());
        ADASButton->setText(QApplication::translate("SetFirst", "ADAS", nullptr));
        audioButton->setText(QApplication::translate("SetFirst", "\345\275\225\351\237\263", nullptr));
        movieButton->setText(QApplication::translate("SetFirst", "\345\274\200\346\234\272\345\275\225\345\203\217", nullptr));
        reverseButton->setText(QApplication::translate("SetFirst", "\345\200\222\350\275\246\347\272\277", nullptr));
        label->setText(QApplication::translate("SetFirst", "\345\275\225\345\203\217\346\227\266\351\227\264\350\256\276\347\275\256", nullptr));
        label_2->setText(QApplication::translate("SetFirst", "\345\210\206\350\276\250\347\216\207\350\256\276\347\275\256", nullptr));
        comboBox->setItemText(0, QApplication::translate("SetFirst", "1920\303\2271080", nullptr));
        comboBox->setItemText(1, QApplication::translate("SetFirst", "1280\303\227720", nullptr));

        voiceButton->setText(QString());
        voiceLabel->setText(QString());
        lightButton->setText(QString());
        lightLabel->setText(QString());
        ColorEffectButton->setText(QString());
        ColorEffectLabel->setText(QString());
        ExposureCompensationButton->setText(QString());
        ExposureCompensationLabel->setText(QString());
        whiteBalanceButton->setText(QString());
        whiteBalanceLabel->setText(QString());
        DisInfoLabel->setText(QApplication::translate("SetFirst", "\345\275\223\345\211\215\350\246\201\350\256\276\347\275\256\347\232\204Video", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetFirst: public Ui_SetFirst {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETFIRST_H
