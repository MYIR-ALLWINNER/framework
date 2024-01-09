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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MediaHome
{
public:
    QPushButton *media_btn;
    QPushButton *camera_home_btn;

    void setupUi(QWidget *MediaHome)
    {
        if (MediaHome->objectName().isEmpty())
            MediaHome->setObjectName(QString::fromUtf8("MediaHome"));
        MediaHome->setEnabled(true);
        MediaHome->resize(1024, 600);
        MediaHome->setMinimumSize(QSize(1024, 600));
        MediaHome->setMaximumSize(QSize(1024, 600));
        MediaHome->setStyleSheet(QString::fromUtf8("background-color: rgb(15,48,89);"));
        media_btn = new QPushButton(MediaHome);
        media_btn->setObjectName(QString::fromUtf8("media_btn"));
        media_btn->setGeometry(QRect(160, 180, 211, 211));
        media_btn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgba(255, 255, 255\357\274\214 0);\n"
"border-image: url(:/images/media.png);\n"
"}"));
        camera_home_btn = new QPushButton(MediaHome);
        camera_home_btn->setObjectName(QString::fromUtf8("camera_home_btn"));
        camera_home_btn->setGeometry(QRect(600, 180, 211, 211));
        camera_home_btn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgba(255, 255, 255\357\274\214 0);\n"
"border-image: url(:/images/cameraIcons/camera.png);\n"
"}\n"
""));

        retranslateUi(MediaHome);

        QMetaObject::connectSlotsByName(MediaHome);
    } // setupUi

    void retranslateUi(QWidget *MediaHome)
    {
        MediaHome->setWindowTitle(QApplication::translate("MediaHome", "Form", nullptr));
        media_btn->setText(QString());
        camera_home_btn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MediaHome: public Ui_MediaHome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDIAHOME_H
