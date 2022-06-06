/********************************************************************************
** Form generated from reading UI file 'main_desktop.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_DESKTOP_H
#define UI_MAIN_DESKTOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_main_desktop
{
public:
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QGridLayout *gridLayout_2;
    QLabel *time_Label;
    QPushButton *pushButtonHome;
    QWidget *widget;
    QGridLayout *gridLayout_4;
    QSpacerItem *verticalSpacer;
    QWidget *widget_2;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *setFirstButton;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *recordButton;
    QPushButton *camera_change_Button;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *cameraButton;

    void setupUi(QWidget *main_desktop)
    {
        if (main_desktop->objectName().isEmpty())
            main_desktop->setObjectName(QString::fromUtf8("main_desktop"));
        main_desktop->resize(1024, 600);
        main_desktop->setStyleSheet(QString::fromUtf8(""));
        gridLayout_5 = new QGridLayout(main_desktop);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setHorizontalSpacing(0);
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(60, -1, 60, -1);
        horizontalSpacer = new QSpacerItem(418, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 1, 1, 1);

        pushButton = new QPushButton(main_desktop);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 0));
        pushButton->setMaximumSize(QSize(100, 39));
        pushButton->setFocusPolicy(Qt::NoFocus);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color:rgba(100,225,100,150);\n"
"	border-style:outset;                 \n"
"	border-width:8px;\n"
"	border-radius:12px;                  \n"
"	border-color:rgba(255,255,255,30);   \n"
"	color:white;             \n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color:rgba(100,255,100,200);\n"
"	border-color:rgba(255,255,255,200);\n"
"	border-style:inset;\n"
"	color:white;\n"
"}"));

        gridLayout_3->addWidget(pushButton, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        time_Label = new QLabel(main_desktop);
        time_Label->setObjectName(QString::fromUtf8("time_Label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(time_Label->sizePolicy().hasHeightForWidth());
        time_Label->setSizePolicy(sizePolicy);
        time_Label->setMinimumSize(QSize(0, 0));
        time_Label->setMaximumSize(QSize(261, 51));
        time_Label->setStyleSheet(QString::fromUtf8("color:rgb(244, 255, 29);\n"
"font: 75 14pt \"Courier 10 Pitch\";\n"
""));
        time_Label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(time_Label, 0, 0, 1, 1);

        pushButtonHome = new QPushButton(main_desktop);
        pushButtonHome->setObjectName(QString::fromUtf8("pushButtonHome"));
        pushButtonHome->setMinimumSize(QSize(30, 50));
        pushButtonHome->setMaximumSize(QSize(50, 60));
        pushButtonHome->setStyleSheet(QString::fromUtf8("\n"
"QPushButton{\n"
"border-image:url(:/icon/home.png);\n"
"}\n"
""));

        gridLayout_2->addWidget(pushButtonHome, 0, 1, 1, 1);

        gridLayout_2->setColumnStretch(0, 5);

        gridLayout_3->addLayout(gridLayout_2, 0, 2, 1, 1);

        gridLayout_3->setColumnStretch(0, 2);

        gridLayout_5->addLayout(gridLayout_3, 0, 0, 1, 1);

        widget = new QWidget(main_desktop);
        widget->setObjectName(QString::fromUtf8("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(0, 0));
        widget->setMaximumSize(QSize(160000, 16000));

        gridLayout_5->addWidget(widget, 1, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalSpacer = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 0, 1, 1, 1);

        widget_2 = new QWidget(main_desktop);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        widget_2->setStyleSheet(QString::fromUtf8("background-color:rgba(94, 94, 94, 0)"));
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 10, 0, -1);
        horizontalSpacer_7 = new QSpacerItem(33, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 1, 7, 1, 1);

        setFirstButton = new QPushButton(widget_2);
        setFirstButton->setObjectName(QString::fromUtf8("setFirstButton"));
        setFirstButton->setMinimumSize(QSize(81, 81));
        setFirstButton->setMaximumSize(QSize(81, 81));
        setFirstButton->setFocusPolicy(Qt::NoFocus);
        setFirstButton->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/setting_main.png)"));

        gridLayout->addWidget(setFirstButton, 1, 6, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(33, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 1, 5, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(34, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 3, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(206, 78, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 1, 0, 1, 1);

        recordButton = new QPushButton(widget_2);
        recordButton->setObjectName(QString::fromUtf8("recordButton"));
        recordButton->setMinimumSize(QSize(81, 81));
        recordButton->setMaximumSize(QSize(81, 81));
        recordButton->setFocusPolicy(Qt::NoFocus);
        recordButton->setStyleSheet(QString::fromUtf8("\n"
"\n"
"QPushButton:pressed{ \n"
"	background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);\n"
"}\n"
"QPushButton{\n"
"border-image:url(:/record.png)\n"
"}\n"
""));

        gridLayout->addWidget(recordButton, 1, 4, 1, 1);

        camera_change_Button = new QPushButton(widget_2);
        camera_change_Button->setObjectName(QString::fromUtf8("camera_change_Button"));
        camera_change_Button->setMinimumSize(QSize(81, 81));
        camera_change_Button->setMaximumSize(QSize(81, 81));
        camera_change_Button->setFocusPolicy(Qt::NoFocus);
        camera_change_Button->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/Switch_Camera.png)"));

        gridLayout->addWidget(camera_change_Button, 1, 8, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(209, 78, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 9, 1, 1);

        cameraButton = new QPushButton(widget_2);
        cameraButton->setObjectName(QString::fromUtf8("cameraButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cameraButton->sizePolicy().hasHeightForWidth());
        cameraButton->setSizePolicy(sizePolicy1);
        cameraButton->setMinimumSize(QSize(81, 81));
        cameraButton->setMaximumSize(QSize(81, 81));
        cameraButton->setFocusPolicy(Qt::NoFocus);
        cameraButton->setStyleSheet(QString::fromUtf8("\n"
"QPushButton{\n"
"border-image:url(:/icon/camera.png);\n"
"}\n"
""));

        gridLayout->addWidget(cameraButton, 1, 1, 1, 1);

        gridLayout->setColumnStretch(0, 3);

        gridLayout_4->addWidget(widget_2, 0, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 2, 0, 1, 1);

        gridLayout_5->setRowStretch(0, 1);
        gridLayout_5->setRowStretch(1, 15);
        gridLayout_5->setRowStretch(2, 3);

        retranslateUi(main_desktop);

        QMetaObject::connectSlotsByName(main_desktop);
    } // setupUi

    void retranslateUi(QWidget *main_desktop)
    {
        main_desktop->setWindowTitle(QApplication::translate("main_desktop", "main_desktop", nullptr));
        pushButton->setText(QApplication::translate("main_desktop", "\345\274\200\345\247\213\351\242\204\350\247\210", nullptr));
        time_Label->setText(QString());
        pushButtonHome->setText(QString());
        setFirstButton->setText(QString());
        recordButton->setText(QString());
        camera_change_Button->setText(QString());
        cameraButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class main_desktop: public Ui_main_desktop {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_DESKTOP_H
