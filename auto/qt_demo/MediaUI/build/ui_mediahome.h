/********************************************************************************
** Form generated from reading UI file 'mediahome.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEDIAHOME_H
#define UI_MEDIAHOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MediaHome
{
public:
    QWidget *widget;
    QLabel *label;
    QPushButton *return_btn;
    QPushButton *music_btn;
    QPushButton *video_btn;
    QLabel *label_2;

    void setupUi(QWidget *MediaHome)
    {
        if (MediaHome->objectName().isEmpty())
            MediaHome->setObjectName(QString::fromUtf8("MediaHome"));
        MediaHome->setEnabled(true);
        MediaHome->resize(1024, 600);
        MediaHome->setMinimumSize(QSize(1024, 600));
        MediaHome->setMaximumSize(QSize(1024, 600));
        MediaHome->setStyleSheet(QString::fromUtf8("background-color: rgb(87, 65, 115);"));
        widget = new QWidget(MediaHome);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 1024, 70));
        widget->setMaximumSize(QSize(1024, 70));
        widget->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(79, 38, 126), stop:1 rgb(111, 73, 127));"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 1024, 70));
        label->setMaximumSize(QSize(1024, 70));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(22);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color:white;"));
        label->setAlignment(Qt::AlignCenter);
        return_btn = new QPushButton(widget);
        return_btn->setObjectName(QString::fromUtf8("return_btn"));
        return_btn->setGeometry(QRect(940, 0, 78, 70));
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
        music_btn = new QPushButton(MediaHome);
        music_btn->setObjectName(QString::fromUtf8("music_btn"));
        music_btn->setGeometry(QRect(529, 186, 290, 290));
        music_btn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgba(255, 255, 255\357\274\214 0);\n"
"border-image: url(:/images/playerIcons/music_d.gif);\n"
"}\n"
"QPushButton:pressed{\n"
"	border-image: url(:/images/playerIcons/music_u.gif);\n"
"}\n"
"QPushButton:hover{\n"
"\n"
"}\n"
"QPushButton:released{\n"
"	border-image: url(:/images/playerIcons/music_d.gif);\n"
"}"));
        video_btn = new QPushButton(MediaHome);
        video_btn->setObjectName(QString::fromUtf8("video_btn"));
        video_btn->setGeometry(QRect(150, 186, 290, 290));
        video_btn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgba(255, 255, 255\357\274\214 0);\n"
"border-image: url(:/images/playerIcons/video_d.gif);\n"
"}\n"
"QPushButton:pressed{\n"
"	border-image: url(:/images/playerIcons/video_u.gif);\n"
"}\n"
"QPushButton:hover{\n"
"\n"
"\n"
"}\n"
"QPushButton:released{\n"
"	border-image: url(:/images/playerIcons/video_d.gif);\n"
"}"));
        label_2 = new QLabel(MediaHome);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 70, 1024, 530));
        widget->raise();
        label_2->raise();
        music_btn->raise();
        video_btn->raise();

        retranslateUi(MediaHome);

        QMetaObject::connectSlotsByName(MediaHome);
    } // setupUi

    void retranslateUi(QWidget *MediaHome)
    {
        MediaHome->setWindowTitle(QApplication::translate("MediaHome", "Form", nullptr));
        label->setText(QApplication::translate("MediaHome", "\345\252\222\344\275\223", nullptr));
        return_btn->setText(QString());
        music_btn->setText(QString());
        video_btn->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MediaHome: public Ui_MediaHome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDIAHOME_H
