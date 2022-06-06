/********************************************************************************
** Form generated from reading UI file 'playlist.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYLIST_H
#define UI_PLAYLIST_H

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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayList
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *prePageButton;
    QLabel *titleLabel;
    QPushButton *refreshButton;
    QPushButton *clearButton;
    QStackedWidget *stackedWidget;
    QWidget *mediaFilePositionSelect;
    QToolButton *UsbListButton;
    QToolButton *favoriteListButton;
    QWidget *udiskMusicList;
    QTableWidget *tableWidget;
    QWidget *favoriteMusicList;
    QTableWidget *tableWidget_2;
    QLabel *statusLabel;

    void setupUi(QWidget *PlayList)
    {
        if (PlayList->objectName().isEmpty())
            PlayList->setObjectName(QString::fromUtf8("PlayList"));
        PlayList->resize(320, 470);
        PlayList->setMinimumSize(QSize(320, 470));
        PlayList->setMaximumSize(QSize(320, 470));
        PlayList->setStyleSheet(QString::fromUtf8("background-color: rgb(4, 2, 57,190);"));
        verticalLayout = new QVBoxLayout(PlayList);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(PlayList);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(320, 39));
        widget->setMaximumSize(QSize(320, 39));
        widget->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(0, 170, 255),stop:1  rgb(0, 255, 255));"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(8);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        prePageButton = new QPushButton(widget);
        prePageButton->setObjectName(QString::fromUtf8("prePageButton"));
        prePageButton->setMinimumSize(QSize(32, 39));
        prePageButton->setMaximumSize(QSize(32, 39));
        prePageButton->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(prePageButton);

        titleLabel = new QLabel(widget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setMinimumSize(QSize(180, 35));
        titleLabel->setMaximumSize(QSize(180, 35));
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
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/playerIcons/reloadPlay.png"), QSize(), QIcon::Normal, QIcon::On);
        refreshButton->setIcon(icon);
        refreshButton->setIconSize(QSize(26, 26));

        horizontalLayout->addWidget(refreshButton);

        clearButton = new QPushButton(widget);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        clearButton->setMinimumSize(QSize(35, 35));
        clearButton->setMaximumSize(QSize(35, 35));
        clearButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border-image: url(:/images/playerIcons/playlistdelete.png);\n"
"border:0px;\n"
"}\n"
"QPushButton:pressed{\n"
"border-image:url(:/images/playerIcons/playlistdeletePress.png);\n"
"border:0px;\n"
"}"));

        horizontalLayout->addWidget(clearButton);


        verticalLayout->addWidget(widget);

        stackedWidget = new QStackedWidget(PlayList);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
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
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/playerIcons/usb.png"), QSize(), QIcon::Normal, QIcon::On);
        UsbListButton->setIcon(icon1);
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
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/playerIcons/favorite.png"), QSize(), QIcon::Normal, QIcon::On);
        favoriteListButton->setIcon(icon2);
        favoriteListButton->setIconSize(QSize(50, 50));
        favoriteListButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        stackedWidget->addWidget(mediaFilePositionSelect);
        udiskMusicList = new QWidget();
        udiskMusicList->setObjectName(QString::fromUtf8("udiskMusicList"));
        tableWidget = new QTableWidget(udiskMusicList);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        if (tableWidget->rowCount() < 100)
            tableWidget->setRowCount(100);
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
        tableWidget->setRowCount(100);
        tableWidget->setColumnCount(3);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(160);
        tableWidget->verticalHeader()->setVisible(false);
        stackedWidget->addWidget(udiskMusicList);
        favoriteMusicList = new QWidget();
        favoriteMusicList->setObjectName(QString::fromUtf8("favoriteMusicList"));
        tableWidget_2 = new QTableWidget(favoriteMusicList);
        if (tableWidget_2->columnCount() < 3)
            tableWidget_2->setColumnCount(3);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setGeometry(QRect(0, 0, 320, 411));
        tableWidget_2->setMinimumSize(QSize(320, 411));
        tableWidget_2->setMaximumSize(QSize(320, 411));
        tableWidget_2->setFocusPolicy(Qt::NoFocus);
        tableWidget_2->setStyleSheet(QString::fromUtf8("QTableWidget{\n"
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
        tableWidget_2->setFrameShape(QFrame::NoFrame);
        tableWidget_2->setFrameShadow(QFrame::Raised);
        tableWidget_2->setLineWidth(0);
        tableWidget_2->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidget_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget_2->setAutoScrollMargin(20);
        tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_2->setDragEnabled(false);
        tableWidget_2->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget_2->setShowGrid(false);
        tableWidget_2->setGridStyle(Qt::NoPen);
        tableWidget_2->setRowCount(0);
        tableWidget_2->setColumnCount(3);
        tableWidget_2->horizontalHeader()->setVisible(false);
        tableWidget_2->horizontalHeader()->setDefaultSectionSize(160);
        tableWidget_2->verticalHeader()->setVisible(false);
        stackedWidget->addWidget(favoriteMusicList);

        verticalLayout->addWidget(stackedWidget);

        statusLabel = new QLabel(PlayList);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setMinimumSize(QSize(320, 21));
        statusLabel->setMaximumSize(QSize(320, 21));
        statusLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(45, 189, 250);\n"
"color:white;"));

        verticalLayout->addWidget(statusLabel);


        retranslateUi(PlayList);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(PlayList);
    } // setupUi

    void retranslateUi(QWidget *PlayList)
    {
        PlayList->setWindowTitle(QApplication::translate("PlayList", "Form", nullptr));
        prePageButton->setText(QString());
        titleLabel->setText(QApplication::translate("PlayList", "<html><head/><body><p><span style=\" font-size:16pt; color:#ffffff;\">\346\222\255\346\224\276\345\210\227\350\241\250\351\200\211\346\213\251</span></p></body></html>", nullptr));
        refreshButton->setText(QString());
        clearButton->setText(QString());
        UsbListButton->setText(QApplication::translate("PlayList", "U\347\233\230\345\252\222\344\275\223\345\210\227\350\241\250", nullptr));
        favoriteListButton->setText(QApplication::translate("PlayList", "\346\224\266\350\227\217\345\210\227\350\241\250", nullptr));
        statusLabel->setText(QApplication::translate("PlayList", "\347\212\266\346\200\201\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayList: public Ui_PlayList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYLIST_H
