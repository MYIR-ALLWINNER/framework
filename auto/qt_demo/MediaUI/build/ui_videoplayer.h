/********************************************************************************
** Form generated from reading UI file 'videoplayer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOPLAYER_H
#define UI_VIDEOPLAYER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoPlayer
{
public:
    QWidget *tilteWidget;
    QLabel *titleLabel;
    QPushButton *return_btn;
    QWidget *controlButtonwidget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *subtitleSelectButton;
    QPushButton *fullScreenButton;
    QPushButton *preVideoButton;
    QPushButton *playButton;
    QPushButton *nextVideoButton;
    QPushButton *searchButton;
    QPushButton *playListButton;
    QWidget *subtitlewidget;
    QGridLayout *gridLayout;
    QLabel *subtitleLabel;
    QHBoxLayout *horizontalLayout_2;
    QLabel *curTimeLabel;
    QSlider *progressSlider;
    QLabel *totalTimeLabel;
    QPushButton *UnFullscreenButton;
    QWidget *sliderAndTimeLabelWidget;
    QGridLayout *gridLayout_2;
    QWidget *videoNameWidget;
    QGridLayout *gridLayout_3;
    QLabel *videoNameLabel;
    QLabel *label;

    void setupUi(QWidget *VideoPlayer)
    {
        if (VideoPlayer->objectName().isEmpty())
            VideoPlayer->setObjectName(QString::fromUtf8("VideoPlayer"));
        VideoPlayer->resize(1024, 600);
        VideoPlayer->setMinimumSize(QSize(1024, 600));
        VideoPlayer->setMaximumSize(QSize(1024, 600));
        VideoPlayer->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255,0);"));
        tilteWidget = new QWidget(VideoPlayer);
        tilteWidget->setObjectName(QString::fromUtf8("tilteWidget"));
        tilteWidget->setGeometry(QRect(0, 0, 1024, 70));
        tilteWidget->setMinimumSize(QSize(1024, 70));
        tilteWidget->setMaximumSize(QSize(1024, 70));
        tilteWidget->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(40, 15, 166), stop:1 rgb(14, 47, 136));"));
        titleLabel = new QLabel(tilteWidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(0, 0, 1024, 70));
        titleLabel->setMinimumSize(QSize(1024, 70));
        titleLabel->setMaximumSize(QSize(1024, 70));
        QFont font;
        font.setPointSize(21);
        font.setBold(true);
        font.setWeight(75);
        titleLabel->setFont(font);
        titleLabel->setStyleSheet(QString::fromUtf8("color:white;"));
        titleLabel->setAlignment(Qt::AlignCenter);
        return_btn = new QPushButton(tilteWidget);
        return_btn->setObjectName(QString::fromUtf8("return_btn"));
        return_btn->setGeometry(QRect(946, 0, 78, 70));
        return_btn->setMaximumSize(QSize(78, 70));
        return_btn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgba(255, 255, 255\357\274\214 0);\n"
"border-image: url(:/images/playerIcons/return_d.gif);\n"
"}\n"
"QPushButton:pressed{\n"
"	border-image: url(:/images/playerIcons/return_u.gif);\n"
"}\n"
"QPushButton:hover{\n"
"\n"
"\n"
"}\n"
"QPushButton:released{\n"
"	border-image: url(:/images/playerIcons/return_d.gif);\n"
"}"));
        controlButtonwidget = new QWidget(VideoPlayer);
        controlButtonwidget->setObjectName(QString::fromUtf8("controlButtonwidget"));
        controlButtonwidget->setGeometry(QRect(0, 525, 1024, 75));
        controlButtonwidget->setMinimumSize(QSize(1024, 75));
        controlButtonwidget->setMaximumSize(QSize(1024, 75));
        horizontalLayout_3 = new QHBoxLayout(controlButtonwidget);
        horizontalLayout_3->setSpacing(3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        subtitleSelectButton = new QPushButton(controlButtonwidget);
        subtitleSelectButton->setObjectName(QString::fromUtf8("subtitleSelectButton"));
        subtitleSelectButton->setMinimumSize(QSize(146, 75));
        subtitleSelectButton->setMaximumSize(QSize(146, 75));
        subtitleSelectButton->setFocusPolicy(Qt::NoFocus);
        subtitleSelectButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(40, 15, 166), stop:1 rgb(14, 47, 136));\n"
"border-radius:5px;\n"
"border:0px soild red;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"border-radius:5px;\n"
"	border:3px solid red;\n"
"	background-color: qradialgradient(spread:repeat, cx:0.5, cy:0.5, radius:0.077, fx:0.5, fy:0.5, stop:0 rgba(0, 169, 255, 147), stop:0.497326 rgba(0, 0, 0, 147), stop:1 rgba(0, 169, 255, 147));\n"
"}\n"
"\n"
"QPushButton:released{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(40, 15, 166), stop:1 rgb(14, 47, 136));\n"
"border-radius:5px;\n"
"border:0px soild red;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/playerIcons/settings_new(1).png"), QSize(), QIcon::Normal, QIcon::Off);
        subtitleSelectButton->setIcon(icon);
        subtitleSelectButton->setIconSize(QSize(60, 60));

        horizontalLayout_3->addWidget(subtitleSelectButton);

        fullScreenButton = new QPushButton(controlButtonwidget);
        fullScreenButton->setObjectName(QString::fromUtf8("fullScreenButton"));
        fullScreenButton->setMinimumSize(QSize(146, 75));
        fullScreenButton->setMaximumSize(QSize(146, 75));
        fullScreenButton->setFocusPolicy(Qt::NoFocus);
        fullScreenButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(40, 15, 166), stop:1 rgb(14, 47, 136));\n"
"border-radius:5px;\n"
"border:0px soild red;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"border-radius:5px;\n"
"	border:3px solid red;\n"
"	background-color: qradialgradient(spread:repeat, cx:0.5, cy:0.5, radius:0.077, fx:0.5, fy:0.5, stop:0 rgba(0, 169, 255, 147), stop:0.497326 rgba(0, 0, 0, 147), stop:1 rgba(0, 169, 255, 147));\n"
"}\n"
"\n"
"QPushButton:released{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(40, 15, 166), stop:1 rgb(14, 47, 136));\n"
"border-radius:5px;\n"
"border:0px soild red;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/playerIcons/fullscreenNormal.png"), QSize(), QIcon::Normal, QIcon::On);
        fullScreenButton->setIcon(icon1);
        fullScreenButton->setIconSize(QSize(50, 50));

        horizontalLayout_3->addWidget(fullScreenButton);

        preVideoButton = new QPushButton(controlButtonwidget);
        preVideoButton->setObjectName(QString::fromUtf8("preVideoButton"));
        preVideoButton->setMinimumSize(QSize(146, 75));
        preVideoButton->setMaximumSize(QSize(146, 75));
        preVideoButton->setFocusPolicy(Qt::NoFocus);
        preVideoButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(40, 15, 166), stop:1 rgb(14, 47, 136));\n"
"border-radius:5px;\n"
"border:0px soild red;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"border-radius:5px;\n"
"	border:3px solid red;\n"
"	background-color: qradialgradient(spread:repeat, cx:0.5, cy:0.5, radius:0.077, fx:0.5, fy:0.5, stop:0 rgba(0, 169, 255, 147), stop:0.497326 rgba(0, 0, 0, 147), stop:1 rgba(0, 169, 255, 147));\n"
"}\n"
"\n"
"QPushButton:released{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(40, 15, 166), stop:1 rgb(14, 47, 136));\n"
"border-radius:5px;\n"
"border:0px soild red;\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/playerIcons/preVideo.png"), QSize(), QIcon::Normal, QIcon::On);
        preVideoButton->setIcon(icon2);
        preVideoButton->setIconSize(QSize(40, 40));

        horizontalLayout_3->addWidget(preVideoButton);

        playButton = new QPushButton(controlButtonwidget);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setEnabled(true);
        playButton->setMinimumSize(QSize(0, 0));
        playButton->setMaximumSize(QSize(146, 75));
        playButton->setFocusPolicy(Qt::NoFocus);
        playButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(40, 15, 166), stop:1 rgb(14, 47, 136));\n"
"border-radius:5px;\n"
"border:0px soild red;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"border-radius:5px;\n"
"	border:3px solid red;\n"
"	background-color: qradialgradient(spread:repeat, cx:0.5, cy:0.5, radius:0.077, fx:0.5, fy:0.5, stop:0 rgba(0, 169, 255, 147), stop:0.497326 rgba(0, 0, 0, 147), stop:1 rgba(0, 169, 255, 147));\n"
"}\n"
"\n"
"QPushButton:released{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(40, 15, 166), stop:1 rgb(14, 47, 136));\n"
"border-radius:5px;\n"
"border:0px soild red;\n"
"}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/playerIcons/Play.png"), QSize(), QIcon::Normal, QIcon::On);
        playButton->setIcon(icon3);
        playButton->setIconSize(QSize(50, 50));

        horizontalLayout_3->addWidget(playButton);

        nextVideoButton = new QPushButton(controlButtonwidget);
        nextVideoButton->setObjectName(QString::fromUtf8("nextVideoButton"));
        nextVideoButton->setMinimumSize(QSize(146, 75));
        nextVideoButton->setMaximumSize(QSize(146, 75));
        nextVideoButton->setFocusPolicy(Qt::NoFocus);
        nextVideoButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(40, 15, 166), stop:1 rgb(14, 47, 136));\n"
"border-radius:5px;\n"
"border:0px soild red;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"border-radius:5px;\n"
"	border:3px solid red;\n"
"	background-color: qradialgradient(spread:repeat, cx:0.5, cy:0.5, radius:0.077, fx:0.5, fy:0.5, stop:0 rgba(0, 169, 255, 147), stop:0.497326 rgba(0, 0, 0, 147), stop:1 rgba(0, 169, 255, 147));\n"
"}\n"
"\n"
"QPushButton:released{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(40, 15, 166), stop:1 rgb(14, 47, 136));\n"
"border-radius:5px;\n"
"border:0px soild red;\n"
"}"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/playerIcons/nextVideo.png"), QSize(), QIcon::Normal, QIcon::On);
        nextVideoButton->setIcon(icon4);
        nextVideoButton->setIconSize(QSize(40, 40));

        horizontalLayout_3->addWidget(nextVideoButton);

        searchButton = new QPushButton(controlButtonwidget);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));
        searchButton->setMinimumSize(QSize(146, 75));
        searchButton->setMaximumSize(QSize(146, 75));
        searchButton->setFocusPolicy(Qt::NoFocus);
        searchButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(40, 15, 166), stop:1 rgb(14, 47, 136));\n"
"border-radius:5px;\n"
"border:0px soild red;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"border-radius:5px;\n"
"	border:3px solid red;\n"
"	background-color: qradialgradient(spread:repeat, cx:0.5, cy:0.5, radius:0.077, fx:0.5, fy:0.5, stop:0 rgba(0, 169, 255, 147), stop:0.497326 rgba(0, 0, 0, 147), stop:1 rgba(0, 169, 255, 147));\n"
"}\n"
"\n"
"QPushButton:released{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(40, 15, 166), stop:1 rgb(14, 47, 136));\n"
"border-radius:5px;\n"
"border:0px soild red;\n"
"}"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/playerIcons/Search.png"), QSize(), QIcon::Normal, QIcon::On);
        searchButton->setIcon(icon5);
        searchButton->setIconSize(QSize(50, 50));

        horizontalLayout_3->addWidget(searchButton);

        playListButton = new QPushButton(controlButtonwidget);
        playListButton->setObjectName(QString::fromUtf8("playListButton"));
        playListButton->setMinimumSize(QSize(146, 75));
        playListButton->setMaximumSize(QSize(146, 75));
        playListButton->setFocusPolicy(Qt::NoFocus);
        playListButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(40, 15, 166), stop:1 rgb(14, 47, 136));\n"
"border-radius:5px;\n"
"border:0px soild red;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"border-radius:5px;\n"
"	border:3px solid red;\n"
"	background-color: qradialgradient(spread:repeat, cx:0.5, cy:0.5, radius:0.077, fx:0.5, fy:0.5, stop:0 rgba(0, 169, 255, 147), stop:0.497326 rgba(0, 0, 0, 147), stop:1 rgba(0, 169, 255, 147));\n"
"}\n"
"\n"
"QPushButton:released{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(40, 15, 166), stop:1 rgb(14, 47, 136));\n"
"border-radius:5px;\n"
"border:0px soild red;\n"
"}"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/playerIcons/list.png"), QSize(), QIcon::Normal, QIcon::On);
        playListButton->setIcon(icon6);
        playListButton->setIconSize(QSize(80, 80));

        horizontalLayout_3->addWidget(playListButton);

        subtitlewidget = new QWidget(VideoPlayer);
        subtitlewidget->setObjectName(QString::fromUtf8("subtitlewidget"));
        subtitlewidget->setGeometry(QRect(0, 430, 1024, 60));
        subtitlewidget->setMinimumSize(QSize(1024, 60));
        subtitlewidget->setMaximumSize(QSize(1024, 60));
        gridLayout = new QGridLayout(subtitlewidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        subtitleLabel = new QLabel(subtitlewidget);
        subtitleLabel->setObjectName(QString::fromUtf8("subtitleLabel"));
        subtitleLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(subtitleLabel, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        curTimeLabel = new QLabel(subtitlewidget);
        curTimeLabel->setObjectName(QString::fromUtf8("curTimeLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(curTimeLabel->sizePolicy().hasHeightForWidth());
        curTimeLabel->setSizePolicy(sizePolicy);
        curTimeLabel->setMinimumSize(QSize(110, 30));
        curTimeLabel->setMaximumSize(QSize(110, 30));
        QFont font1;
        font1.setPointSize(14);
        curTimeLabel->setFont(font1);
        curTimeLabel->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"color: white;\n"
""));
        curTimeLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(curTimeLabel);

        progressSlider = new QSlider(subtitlewidget);
        progressSlider->setObjectName(QString::fromUtf8("progressSlider"));
        progressSlider->setEnabled(true);
        progressSlider->setMaximumSize(QSize(820, 16777215));
        progressSlider->setStyleSheet(QString::fromUtf8("QSlider{\n"
"border-color: #bcbcbc;\n"
"background-color:rgba(255,255,255,0);\n"
"}\n"
"QSlider::groove:horizontal {                                \n"
"     border: 1px solid #999999;                             \n"
"     height: 1px;                                           \n"
"    margin: 0px 0;                                         \n"
"     left: 5px; right: 5px; \n"
" }\n"
"QSlider::handle:horizontal {                               \n"
"     border: 0px ;                           \n"
"     border-image: url(:/images/cameraIcons/silderController.png);\n"
"     width: 15px;                                           \n"
"     margin: -7px -7px -7px -7px;                  \n"
"} \n"
"QSlider::add-page:horizontal{\n"
"background: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 #bcbcbc, stop:0.25 #bcbcbc, stop:0.5 #bcbcbc, stop:1 #bcbcbc); \n"
"\n"
"}\n"
"QSlider::sub-page:horizontal{                               \n"
" background: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 #439"
                        "cf3, stop:0.25 #439cf3, stop:0.5 #439cf3, stop:1 #439cf3);                     \n"
"}"));
        progressSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(progressSlider);

        totalTimeLabel = new QLabel(subtitlewidget);
        totalTimeLabel->setObjectName(QString::fromUtf8("totalTimeLabel"));
        totalTimeLabel->setMinimumSize(QSize(110, 30));
        totalTimeLabel->setMaximumSize(QSize(110, 30));
        totalTimeLabel->setFont(font1);
        totalTimeLabel->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"color:white;"));
        totalTimeLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(totalTimeLabel);


        gridLayout->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        UnFullscreenButton = new QPushButton(VideoPlayer);
        UnFullscreenButton->setObjectName(QString::fromUtf8("UnFullscreenButton"));
        UnFullscreenButton->setGeometry(QRect(10, 270, 50, 50));
        UnFullscreenButton->setMinimumSize(QSize(50, 50));
        UnFullscreenButton->setMaximumSize(QSize(50, 50));
        UnFullscreenButton->setFocusPolicy(Qt::NoFocus);
        UnFullscreenButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color:rgba(0, 255, 255,120);\n"
"border-radius:15px;\n"
"border:0px soild red;\n"
"}\n"
"QPushButton:pressed{\n"
"border-radius:15px;\n"
"	border:0px solid red;\n"
"	background-color: qradialgradient(spread:repeat, cx:0.5, cy:0.5, radius:0.077, fx:0.5, fy:0.5, stop:0 rgba(0, 169, 255, 147), stop:0.497326 rgba(0, 0, 0, 147), stop:1 rgba(0, 169, 255, 147));\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: qradialgradient(spread:repeat, cx:0.5, cy:0.5, radius:0.077, fx:0.5, fy:0.5, stop:0 rgba(0, 169, 255, 147), stop:0.497326 rgba(0, 0, 0, 147), stop:1 rgba(0, 169, 255, 147));\n"
"border-radius:15px;\n"
"	border:0px solid red;\n"
"}\n"
""));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/playerIcons/fullscreenPressed.png"), QSize(), QIcon::Normal, QIcon::On);
        UnFullscreenButton->setIcon(icon7);
        UnFullscreenButton->setIconSize(QSize(40, 40));
        sliderAndTimeLabelWidget = new QWidget(VideoPlayer);
        sliderAndTimeLabelWidget->setObjectName(QString::fromUtf8("sliderAndTimeLabelWidget"));
        sliderAndTimeLabelWidget->setGeometry(QRect(0, 490, 1024, 30));
        sliderAndTimeLabelWidget->setMinimumSize(QSize(1024, 30));
        sliderAndTimeLabelWidget->setMaximumSize(QSize(1024, 30));
        gridLayout_2 = new QGridLayout(sliderAndTimeLabelWidget);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        videoNameWidget = new QWidget(VideoPlayer);
        videoNameWidget->setObjectName(QString::fromUtf8("videoNameWidget"));
        videoNameWidget->setGeometry(QRect(0, 70, 512, 40));
        videoNameWidget->setMinimumSize(QSize(512, 40));
        videoNameWidget->setMaximumSize(QSize(512, 40));
        videoNameWidget->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255,0);"));
        gridLayout_3 = new QGridLayout(videoNameWidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(0);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        videoNameLabel = new QLabel(videoNameWidget);
        videoNameLabel->setObjectName(QString::fromUtf8("videoNameLabel"));
        videoNameLabel->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255,0);\n"
"color:rgb(170, 255, 255);"));

        gridLayout_3->addWidget(videoNameLabel, 0, 1, 1, 1);

        label = new QLabel(videoNameWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        gridLayout_3->setColumnStretch(0, 1);
        gridLayout_3->setColumnStretch(1, 5);
        controlButtonwidget->raise();
        subtitlewidget->raise();
        UnFullscreenButton->raise();
        sliderAndTimeLabelWidget->raise();
        videoNameWidget->raise();
        tilteWidget->raise();

        retranslateUi(VideoPlayer);

        QMetaObject::connectSlotsByName(VideoPlayer);
    } // setupUi

    void retranslateUi(QWidget *VideoPlayer)
    {
        VideoPlayer->setWindowTitle(QApplication::translate("VideoPlayer", "Form", nullptr));
        titleLabel->setText(QApplication::translate("VideoPlayer", "\350\247\206\351\242\221", nullptr));
        return_btn->setText(QString());
        subtitleSelectButton->setText(QString());
        fullScreenButton->setText(QString());
        preVideoButton->setText(QString());
        playButton->setText(QString());
        nextVideoButton->setText(QString());
        searchButton->setText(QString());
        playListButton->setText(QString());
        subtitleLabel->setText(QApplication::translate("VideoPlayer", "<html><head/><body><p align=\"center\"><br/></p></body></html>", nullptr));
        curTimeLabel->setText(QApplication::translate("VideoPlayer", "00:00:00", nullptr));
        totalTimeLabel->setText(QApplication::translate("VideoPlayer", "00:00:00", nullptr));
        UnFullscreenButton->setText(QString());
        videoNameLabel->setText(QString());
        label->setText(QApplication::translate("VideoPlayer", "<html><head/><body><p><span style=\" font-size:12pt; color:#aaffff;\">\345\275\223\345\211\215\346\255\243\345\234\250\346\222\255\346\224\276\357\274\232</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VideoPlayer: public Ui_VideoPlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOPLAYER_H
