/********************************************************************************
** Form generated from reading UI file 'videoplaylist.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOPLAYLIST_H
#define UI_VIDEOPLAYLIST_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoPlayList
{
public:
    QStackedWidget *stackedWidget;
    QWidget *mediaFilePositionSelect;
    QToolButton *UsbListButton;
    QToolButton *favoriteListButton;
    QWidget *udiskMusicList;
    QTableWidget *tableWidget;
    QWidget *favoriteMusicList;
    QLabel *label;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *clearButton;
    QLabel *titleLabel;
    QPushButton *refreshButton;
    QLabel *statusLabel;

    void setupUi(QWidget *VideoPlayList)
    {
        if (VideoPlayList->objectName().isEmpty())
            VideoPlayList->setObjectName(QString::fromUtf8("VideoPlayList"));
        VideoPlayList->resize(320, 470);
        VideoPlayList->setMinimumSize(QSize(320, 470));
        VideoPlayList->setMaximumSize(QSize(320, 470));
        VideoPlayList->setStyleSheet(QString::fromUtf8("background-color: rgb(4, 2, 57,190);"));
        stackedWidget = new QStackedWidget(VideoPlayList);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 39, 320, 410));
        stackedWidget->setMinimumSize(QSize(320, 410));
        stackedWidget->setMaximumSize(QSize(320, 410));
        mediaFilePositionSelect = new QWidget();
        mediaFilePositionSelect->setObjectName(QString::fromUtf8("mediaFilePositionSelect"));
        UsbListButton = new QToolButton(mediaFilePositionSelect);
        UsbListButton->setObjectName(QString::fromUtf8("UsbListButton"));
        UsbListButton->setGeometry(QRect(60, 80, 181, 81));
        UsbListButton->setMinimumSize(QSize(181, 81));
        UsbListButton->setMaximumSize(QSize(181, 81));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        UsbListButton->setFont(font);
        UsbListButton->setFocusPolicy(Qt::NoFocus);
        UsbListButton->setStyleSheet(QString::fromUtf8("QToolButton{\n"
"color:rgba(255,255,255,255);\n"
"background-color:rgb(110, 84, 177);\n"
"border:none;\n"
"padding-top:5px;\n"
"padding-bottom:5px;\n"
"border:1px solid red;\n"
"border-radius:10px;\n"
"}\n"
"QToolButton:pressed{\n"
"	background-color: rgb(7, 255, 139);\n"
"}\n"
"QToolButton:hover{\n"
"	background-color: rgb(7, 255, 139);\n"
"}\n"
"QToolButton:released{\n"
"	background-color:rgb(110, 84, 177);\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/playerIcons/usb.png"), QSize(), QIcon::Normal, QIcon::On);
        UsbListButton->setIcon(icon);
        UsbListButton->setIconSize(QSize(50, 50));
        UsbListButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        favoriteListButton = new QToolButton(mediaFilePositionSelect);
        favoriteListButton->setObjectName(QString::fromUtf8("favoriteListButton"));
        favoriteListButton->setGeometry(QRect(60, 220, 181, 81));
        favoriteListButton->setMinimumSize(QSize(181, 81));
        favoriteListButton->setMaximumSize(QSize(181, 81));
        favoriteListButton->setFont(font);
        favoriteListButton->setFocusPolicy(Qt::NoFocus);
        favoriteListButton->setStyleSheet(QString::fromUtf8("QToolButton{\n"
"color:rgba(255,255,255,255);\n"
"background-color:rgb(110, 84, 177);\n"
"border:none;\n"
"padding-top:5px;\n"
"padding-bottom:5px;\n"
"border:1px solid red;\n"
"border-radius:10px;\n"
"}\n"
"QToolButton:pressed{\n"
"	background-color: rgb(7, 255, 139);\n"
"}\n"
"QToolButton:hover{\n"
"	background-color: rgb(7, 255, 139);\n"
"}\n"
"QToolButton:released{\n"
"	background-color:rgb(110, 84, 177);\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/playerIcons/favorite.png"), QSize(), QIcon::Normal, QIcon::On);
        favoriteListButton->setIcon(icon1);
        favoriteListButton->setIconSize(QSize(50, 50));
        favoriteListButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        stackedWidget->addWidget(mediaFilePositionSelect);
        udiskMusicList = new QWidget();
        udiskMusicList->setObjectName(QString::fromUtf8("udiskMusicList"));
        tableWidget = new QTableWidget(udiskMusicList);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        if (tableWidget->rowCount() < 159)
            tableWidget->setRowCount(159);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(10, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(11, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(12, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(13, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(14, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(15, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(16, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(17, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(18, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(19, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(20, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(21, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(22, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(23, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(24, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(25, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(26, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(27, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(28, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(29, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(30, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(31, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(32, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(33, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(34, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(35, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(36, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(37, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(38, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(39, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(40, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(41, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(42, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(43, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(44, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(45, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(46, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(47, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(48, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(49, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(50, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(51, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(52, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(53, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(54, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(55, __qtablewidgetitem55);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(56, __qtablewidgetitem56);
        QTableWidgetItem *__qtablewidgetitem57 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(57, __qtablewidgetitem57);
        QTableWidgetItem *__qtablewidgetitem58 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(58, __qtablewidgetitem58);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 320, 411));
        tableWidget->setMinimumSize(QSize(320, 411));
        tableWidget->setMaximumSize(QSize(320, 411));
        tableWidget->setFocusPolicy(Qt::NoFocus);
        tableWidget->setStyleSheet(QString::fromUtf8("QTableWidget{\n"
"	background-color: rgb(170, 255, 255);\n"
"	alternate-background-color: rgb(118, 177, 177);\n"
"	border:none;\n"
"	border-top: 4px solid  qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1, stop:0 rgba(191, 191, 191, 255), stop:1 		rgba(255, 255, 255, 255));\n"
"}\n"
"QTableWidget:pressed{\n"
"	background-color: skyblue;\n"
"}\n"
"QScrollBar:vertical {\n"
"      border: none;\n"
" 	  background-color: rgba(255, 255, 255);\n"
"      width: 4px;\n"
"      margin: 0px 0 0px 0;\n"
"  }\n"
"  QScrollBar::handle:vertical {\n"
"	 border: none;\n"
"     border-radius:2px;\n"
"      background: rgba(154, 154, 154, 150);\n"
"      min-height: 15px;\n"
"  }\n"
"QScrollBar::sub-line:vertical {\n"
"      border: none;\n"
"      height: 0px;\n"
"      subcontrol-position: top;\n"
"      subcontrol-origin: margin;\n"
"  }\n"
"QScrollBar::add-line:vertical {\n"
"      border: none;\n"
"      height: 0px;\n"
"      subcontrol-position: bottom;\n"
"      subcontrol-origin: margin;\n"
"  }\n"
"  QScrollBar:"
                        ":up-arrow:vertical, QScrollBar::down-arrow:vertical {\n"
"	border:none;\n"
"      width: 0px;\n"
"      height: 0px;\n"
"  }\n"
"  QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\n"
"      background: none;\n"
"  }"));
        tableWidget->setFrameShape(QFrame::NoFrame);
        tableWidget->setFrameShadow(QFrame::Raised);
        tableWidget->setLineWidth(0);
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setAutoScrollMargin(20);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setDragEnabled(false);
        tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget->setShowGrid(false);
        tableWidget->setGridStyle(Qt::NoPen);
        tableWidget->setRowCount(159);
        tableWidget->setColumnCount(3);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(160);
        tableWidget->verticalHeader()->setVisible(false);
        stackedWidget->addWidget(udiskMusicList);
        favoriteMusicList = new QWidget();
        favoriteMusicList->setObjectName(QString::fromUtf8("favoriteMusicList"));
        label = new QLabel(favoriteMusicList);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(79, 150, 171, 61));
        QFont font1;
        font1.setPointSize(16);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("color:white;"));
        label->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(favoriteMusicList);
        widget = new QWidget(VideoPlayList);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 320, 39));
        widget->setMinimumSize(QSize(320, 39));
        widget->setMaximumSize(QSize(320, 39));
        widget->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(0, 170, 255),stop:1  rgb(0, 255, 255));"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        clearButton = new QPushButton(widget);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        clearButton->setMinimumSize(QSize(35, 35));
        clearButton->setMaximumSize(QSize(35, 35));
        clearButton->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(clearButton);

        titleLabel = new QLabel(widget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setMinimumSize(QSize(251, 35));
        titleLabel->setMaximumSize(QSize(251, 35));
        titleLabel->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"color:white;"));
        titleLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(titleLabel);

        refreshButton = new QPushButton(widget);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));
        refreshButton->setMinimumSize(QSize(35, 35));
        refreshButton->setMaximumSize(QSize(35, 35));
        refreshButton->setFocusPolicy(Qt::NoFocus);
        refreshButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(0, 170, 255),stop:1  rgb(0, 255, 255));\n"
"border-radius:0px;\n"
"border:0px soild red;\n"
"}\n"
"QPushButton:pressed{\n"
"border-radius:5px;\n"
"	border:0px solid red;\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(0, 170, 255),stop:1  rgb(0, 255, 255));\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(0, 170, 255),stop:1  rgb(0, 255, 255));\n"
"\n"
"border-radius:5px;\n"
"	border:0px solid red;\n"
"}\n"
""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/playerIcons/reloadPlay.png"), QSize(), QIcon::Normal, QIcon::On);
        refreshButton->setIcon(icon2);
        refreshButton->setIconSize(QSize(26, 26));

        horizontalLayout->addWidget(refreshButton);

        statusLabel = new QLabel(VideoPlayList);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setGeometry(QRect(0, 450, 320, 21));
        statusLabel->setMinimumSize(QSize(320, 21));
        statusLabel->setMaximumSize(QSize(320, 21));
        statusLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(45, 189, 250);\n"
"color:white;"));

        retranslateUi(VideoPlayList);

        QMetaObject::connectSlotsByName(VideoPlayList);
    } // setupUi

    void retranslateUi(QWidget *VideoPlayList)
    {
        VideoPlayList->setWindowTitle(QApplication::translate("VideoPlayList", "Form", nullptr));
        UsbListButton->setText(QApplication::translate("VideoPlayList", "U\347\233\230\345\252\222\344\275\223\345\210\227\350\241\250", nullptr));
        favoriteListButton->setText(QApplication::translate("VideoPlayList", "\346\224\266\350\227\217\345\210\227\350\241\250", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("VideoPlayList", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(10);
        ___qtablewidgetitem10->setText(QApplication::translate("VideoPlayList", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(11);
        ___qtablewidgetitem11->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(12);
        ___qtablewidgetitem12->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->verticalHeaderItem(13);
        ___qtablewidgetitem13->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->verticalHeaderItem(14);
        ___qtablewidgetitem14->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->verticalHeaderItem(15);
        ___qtablewidgetitem15->setText(QApplication::translate("VideoPlayList", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->verticalHeaderItem(16);
        ___qtablewidgetitem16->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->verticalHeaderItem(17);
        ___qtablewidgetitem17->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->verticalHeaderItem(18);
        ___qtablewidgetitem18->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->verticalHeaderItem(19);
        ___qtablewidgetitem19->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->verticalHeaderItem(20);
        ___qtablewidgetitem20->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->verticalHeaderItem(21);
        ___qtablewidgetitem21->setText(QApplication::translate("VideoPlayList", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->verticalHeaderItem(22);
        ___qtablewidgetitem22->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget->verticalHeaderItem(23);
        ___qtablewidgetitem23->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget->verticalHeaderItem(24);
        ___qtablewidgetitem24->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget->verticalHeaderItem(25);
        ___qtablewidgetitem25->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget->verticalHeaderItem(26);
        ___qtablewidgetitem26->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget->verticalHeaderItem(27);
        ___qtablewidgetitem27->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget->verticalHeaderItem(28);
        ___qtablewidgetitem28->setText(QApplication::translate("VideoPlayList", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget->verticalHeaderItem(29);
        ___qtablewidgetitem29->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget->verticalHeaderItem(30);
        ___qtablewidgetitem30->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget->verticalHeaderItem(31);
        ___qtablewidgetitem31->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget->verticalHeaderItem(32);
        ___qtablewidgetitem32->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget->verticalHeaderItem(33);
        ___qtablewidgetitem33->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget->verticalHeaderItem(34);
        ___qtablewidgetitem34->setText(QApplication::translate("VideoPlayList", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget->verticalHeaderItem(35);
        ___qtablewidgetitem35->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidget->verticalHeaderItem(36);
        ___qtablewidgetitem36->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidget->verticalHeaderItem(37);
        ___qtablewidgetitem37->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem38 = tableWidget->verticalHeaderItem(38);
        ___qtablewidgetitem38->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem39 = tableWidget->verticalHeaderItem(39);
        ___qtablewidgetitem39->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem40 = tableWidget->verticalHeaderItem(40);
        ___qtablewidgetitem40->setText(QApplication::translate("VideoPlayList", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem41 = tableWidget->verticalHeaderItem(41);
        ___qtablewidgetitem41->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem42 = tableWidget->verticalHeaderItem(42);
        ___qtablewidgetitem42->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem43 = tableWidget->verticalHeaderItem(43);
        ___qtablewidgetitem43->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem44 = tableWidget->verticalHeaderItem(44);
        ___qtablewidgetitem44->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem45 = tableWidget->verticalHeaderItem(45);
        ___qtablewidgetitem45->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem46 = tableWidget->verticalHeaderItem(46);
        ___qtablewidgetitem46->setText(QApplication::translate("VideoPlayList", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem47 = tableWidget->verticalHeaderItem(47);
        ___qtablewidgetitem47->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem48 = tableWidget->verticalHeaderItem(48);
        ___qtablewidgetitem48->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem49 = tableWidget->verticalHeaderItem(49);
        ___qtablewidgetitem49->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem50 = tableWidget->verticalHeaderItem(50);
        ___qtablewidgetitem50->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem51 = tableWidget->verticalHeaderItem(51);
        ___qtablewidgetitem51->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem52 = tableWidget->verticalHeaderItem(52);
        ___qtablewidgetitem52->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem53 = tableWidget->verticalHeaderItem(53);
        ___qtablewidgetitem53->setText(QApplication::translate("VideoPlayList", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem54 = tableWidget->verticalHeaderItem(54);
        ___qtablewidgetitem54->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem55 = tableWidget->verticalHeaderItem(55);
        ___qtablewidgetitem55->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem56 = tableWidget->verticalHeaderItem(56);
        ___qtablewidgetitem56->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem57 = tableWidget->verticalHeaderItem(57);
        ___qtablewidgetitem57->setText(QApplication::translate("VideoPlayList", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem58 = tableWidget->verticalHeaderItem(58);
        ___qtablewidgetitem58->setText(QApplication::translate("VideoPlayList", "1", nullptr));
        label->setText(QApplication::translate("VideoPlayList", "\346\225\254\350\257\267\346\234\237\345\276\205...", nullptr));
        clearButton->setText(QString());
        titleLabel->setText(QApplication::translate("VideoPlayList", "<html><head/><body><p><span style=\" font-size:16pt; color:#ffffff;\">\346\222\255\346\224\276\345\210\227\350\241\250\351\200\211\346\213\251</span></p></body></html>", nullptr));
        refreshButton->setText(QString());
        statusLabel->setText(QApplication::translate("VideoPlayList", "\347\212\266\346\200\201\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VideoPlayList: public Ui_VideoPlayList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOPLAYLIST_H
