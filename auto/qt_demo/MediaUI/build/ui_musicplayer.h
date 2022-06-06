/********************************************************************************
** Form generated from reading UI file 'musicplayer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUSICPLAYER_H
#define UI_MUSICPLAYER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MusicPlayer
{
public:
    QWidget *widget;
    QPushButton *pushButton;
    QLabel *label;
    QPushButton *return_btn;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *setttingButton;
    QPushButton *playOrderButton;
    QPushButton *preMusicButton;
    QPushButton *playButton;
    QPushButton *nextMusicButton;
    QPushButton *searchButton;
    QPushButton *playListButton;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *curTimeLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *totalTimeLabel;
    QSlider *progressSlider;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *MusicIconLabel;
    QLabel *MusicTextLabel;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *artistIconLabelLabel;
    QLabel *artistTextLabel;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *albumIcomLabel;
    QLabel *albumTextLabel;
    QLabel *posterLabel;

    void setupUi(QWidget *MusicPlayer)
    {
        if (MusicPlayer->objectName().isEmpty())
            MusicPlayer->setObjectName(QString::fromUtf8("MusicPlayer"));
        MusicPlayer->resize(1024, 600);
        MusicPlayer->setMinimumSize(QSize(1024, 600));
        MusicPlayer->setMaximumSize(QSize(1024, 600));
        MusicPlayer->setFocusPolicy(Qt::ClickFocus);
        MusicPlayer->setStyleSheet(QString::fromUtf8("background-color: rgb(87, 65, 115);"));
        widget = new QWidget(MusicPlayer);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 1024, 70));
        widget->setMinimumSize(QSize(1024, 70));
        widget->setMaximumSize(QSize(1024, 70));
        widget->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(79, 38, 126), stop:1 rgb(111, 73, 127));"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 10, 50, 50));
        pushButton->setMinimumSize(QSize(50, 50));
        pushButton->setMaximumSize(QSize(50, 50));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgba(255, 255, 255\357\274\214 0);\n"
"border-image: url(:/images/playerIcons/home.png);\n"
"}\n"
"QPushButton:pressed{\n"
"	background-color: rgb(133, 76, 255);\n"
"}\n"
"QPushButton:hover{\n"
"	background-color:  rgb(133, 76, 255);\n"
"}\n"
"QPushButton:released{\n"
"	background-color:rgba(255, 255, 255\357\274\214 0);\n"
"}"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 1024, 70));
        label->setMinimumSize(QSize(1024, 70));
        label->setMaximumSize(QSize(1024, 70));
        QFont font;
        font.setPointSize(21);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color:white;"));
        label->setAlignment(Qt::AlignCenter);
        return_btn = new QPushButton(widget);
        return_btn->setObjectName(QString::fromUtf8("return_btn"));
        return_btn->setGeometry(QRect(946, 0, 78, 70));
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
        widget_2 = new QWidget(MusicPlayer);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(0, 525, 1024, 75));
        widget_2->setMinimumSize(QSize(1024, 75));
        widget_2->setMaximumSize(QSize(1024, 75));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        setttingButton = new QPushButton(widget_2);
        setttingButton->setObjectName(QString::fromUtf8("setttingButton"));
        setttingButton->setMinimumSize(QSize(146, 75));
        setttingButton->setMaximumSize(QSize(146, 75));
        setttingButton->setFocusPolicy(Qt::NoFocus);
        setttingButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        icon.addFile(QString::fromUtf8(":/images/playerIcons/settings_new(1).png"), QSize(), QIcon::Normal, QIcon::On);
        setttingButton->setIcon(icon);
        setttingButton->setIconSize(QSize(50, 50));

        horizontalLayout->addWidget(setttingButton);

        playOrderButton = new QPushButton(widget_2);
        playOrderButton->setObjectName(QString::fromUtf8("playOrderButton"));
        playOrderButton->setMinimumSize(QSize(146, 75));
        playOrderButton->setMaximumSize(QSize(146, 75));
        playOrderButton->setFocusPolicy(Qt::NoFocus);
        playOrderButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        icon1.addFile(QString::fromUtf8(":/images/playerIcons/randomPlay.png"), QSize(), QIcon::Normal, QIcon::On);
        playOrderButton->setIcon(icon1);
        playOrderButton->setIconSize(QSize(60, 60));

        horizontalLayout->addWidget(playOrderButton);

        preMusicButton = new QPushButton(widget_2);
        preMusicButton->setObjectName(QString::fromUtf8("preMusicButton"));
        preMusicButton->setMinimumSize(QSize(146, 75));
        preMusicButton->setMaximumSize(QSize(146, 75));
        preMusicButton->setFocusPolicy(Qt::NoFocus);
        preMusicButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        preMusicButton->setIcon(icon2);
        preMusicButton->setIconSize(QSize(40, 40));

        horizontalLayout->addWidget(preMusicButton);

        playButton = new QPushButton(widget_2);
        playButton->setObjectName(QString::fromUtf8("playButton"));
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

        horizontalLayout->addWidget(playButton);

        nextMusicButton = new QPushButton(widget_2);
        nextMusicButton->setObjectName(QString::fromUtf8("nextMusicButton"));
        nextMusicButton->setMinimumSize(QSize(146, 75));
        nextMusicButton->setMaximumSize(QSize(146, 75));
        nextMusicButton->setFocusPolicy(Qt::NoFocus);
        nextMusicButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        nextMusicButton->setIcon(icon4);
        nextMusicButton->setIconSize(QSize(40, 40));

        horizontalLayout->addWidget(nextMusicButton);

        searchButton = new QPushButton(widget_2);
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

        horizontalLayout->addWidget(searchButton);

        playListButton = new QPushButton(widget_2);
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

        horizontalLayout->addWidget(playListButton);

        layoutWidget = new QWidget(MusicPlayer);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(420, 410, 521, 91));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        curTimeLabel = new QLabel(layoutWidget);
        curTimeLabel->setObjectName(QString::fromUtf8("curTimeLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(curTimeLabel->sizePolicy().hasHeightForWidth());
        curTimeLabel->setSizePolicy(sizePolicy);
        curTimeLabel->setMinimumSize(QSize(90, 30));
        curTimeLabel->setMaximumSize(QSize(90, 30));
        QFont font1;
        font1.setPointSize(13);
        curTimeLabel->setFont(font1);
        curTimeLabel->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"color: white;\n"
""));
        curTimeLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(curTimeLabel, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(308, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        totalTimeLabel = new QLabel(layoutWidget);
        totalTimeLabel->setObjectName(QString::fromUtf8("totalTimeLabel"));
        totalTimeLabel->setMinimumSize(QSize(90, 30));
        totalTimeLabel->setMaximumSize(QSize(90, 30));
        totalTimeLabel->setFont(font1);
        totalTimeLabel->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"color:white;"));
        totalTimeLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(totalTimeLabel, 0, 2, 1, 1);

        progressSlider = new QSlider(layoutWidget);
        progressSlider->setObjectName(QString::fromUtf8("progressSlider"));
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

        gridLayout->addWidget(progressSlider, 1, 0, 1, 3);

        layoutWidget1 = new QWidget(MusicPlayer);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(480, 140, 382, 52));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(30);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        MusicIconLabel = new QLabel(layoutWidget1);
        MusicIconLabel->setObjectName(QString::fromUtf8("MusicIconLabel"));
        MusicIconLabel->setMinimumSize(QSize(50, 50));
        MusicIconLabel->setMaximumSize(QSize(50, 50));
        MusicIconLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/images/playerIcons/music.png);\n"
"background-color: rgba(255, 255, 255, 0);"));

        horizontalLayout_2->addWidget(MusicIconLabel);

        MusicTextLabel = new QLabel(layoutWidget1);
        MusicTextLabel->setObjectName(QString::fromUtf8("MusicTextLabel"));
        MusicTextLabel->setMinimumSize(QSize(300, 50));
        MusicTextLabel->setMaximumSize(QSize(300, 50));
        QFont font2;
        font2.setPointSize(16);
        MusicTextLabel->setFont(font2);
        MusicTextLabel->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"color:white;"));

        horizontalLayout_2->addWidget(MusicTextLabel);

        layoutWidget2 = new QWidget(MusicPlayer);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(480, 230, 382, 52));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setSpacing(30);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        artistIconLabelLabel = new QLabel(layoutWidget2);
        artistIconLabelLabel->setObjectName(QString::fromUtf8("artistIconLabelLabel"));
        artistIconLabelLabel->setMinimumSize(QSize(50, 50));
        artistIconLabelLabel->setMaximumSize(QSize(50, 50));
        artistIconLabelLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/images/playerIcons/man.png);\n"
"background-color: rgba(255, 255, 255, 0);"));

        horizontalLayout_3->addWidget(artistIconLabelLabel);

        artistTextLabel = new QLabel(layoutWidget2);
        artistTextLabel->setObjectName(QString::fromUtf8("artistTextLabel"));
        artistTextLabel->setMinimumSize(QSize(300, 50));
        artistTextLabel->setMaximumSize(QSize(300, 50));
        artistTextLabel->setFont(font2);
        artistTextLabel->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"color:white;"));

        horizontalLayout_3->addWidget(artistTextLabel);

        layoutWidget3 = new QWidget(MusicPlayer);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(480, 310, 382, 52));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_4->setSpacing(30);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        albumIcomLabel = new QLabel(layoutWidget3);
        albumIcomLabel->setObjectName(QString::fromUtf8("albumIcomLabel"));
        albumIcomLabel->setMinimumSize(QSize(50, 50));
        albumIcomLabel->setMaximumSize(QSize(50, 50));
        albumIcomLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/images/playerIcons/album.png);\n"
"background-color: rgba(255, 255, 255, 0);"));

        horizontalLayout_4->addWidget(albumIcomLabel);

        albumTextLabel = new QLabel(layoutWidget3);
        albumTextLabel->setObjectName(QString::fromUtf8("albumTextLabel"));
        albumTextLabel->setMinimumSize(QSize(300, 50));
        albumTextLabel->setMaximumSize(QSize(300, 50));
        albumTextLabel->setFont(font2);
        albumTextLabel->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"color:white;"));

        horizontalLayout_4->addWidget(albumTextLabel);

        posterLabel = new QLabel(MusicPlayer);
        posterLabel->setObjectName(QString::fromUtf8("posterLabel"));
        posterLabel->setGeometry(QRect(93, 124, 320, 260));
        posterLabel->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255,0);"));

        retranslateUi(MusicPlayer);

        QMetaObject::connectSlotsByName(MusicPlayer);
    } // setupUi

    void retranslateUi(QWidget *MusicPlayer)
    {
        MusicPlayer->setWindowTitle(QApplication::translate("MusicPlayer", "Form", nullptr));
        pushButton->setText(QString());
        label->setText(QApplication::translate("MusicPlayer", "\351\237\263\344\271\220", nullptr));
        return_btn->setText(QString());
        setttingButton->setText(QString());
        playOrderButton->setText(QString());
        preMusicButton->setText(QString());
        playButton->setText(QString());
        nextMusicButton->setText(QString());
        searchButton->setText(QString());
        playListButton->setText(QString());
        curTimeLabel->setText(QApplication::translate("MusicPlayer", "00:00:00", nullptr));
        totalTimeLabel->setText(QApplication::translate("MusicPlayer", "00:00:00", nullptr));
        MusicIconLabel->setText(QString());
        MusicTextLabel->setText(QApplication::translate("MusicPlayer", "\351\237\263\344\271\220\345\220\215", nullptr));
        artistIconLabelLabel->setText(QString());
        artistTextLabel->setText(QApplication::translate("MusicPlayer", "\346\255\214\346\211\213", nullptr));
        albumIcomLabel->setText(QString());
        albumTextLabel->setText(QApplication::translate("MusicPlayer", "\344\270\223\350\276\221\345\220\215", nullptr));
        posterLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MusicPlayer: public Ui_MusicPlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSICPLAYER_H
