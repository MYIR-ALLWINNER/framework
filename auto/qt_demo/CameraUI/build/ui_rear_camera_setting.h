/********************************************************************************
** Form generated from reading UI file 'rear_camera_setting.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REAR_CAMERA_SETTING_H
#define UI_REAR_CAMERA_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_Rear_Camera_Setting
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_4;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout_3;
    QPushButton *upperButton;
    QSpacerItem *verticalSpacer;
    QPushButton *downButton;
    QSpacerItem *verticalSpacer_2;
    QGridLayout *gridLayout_2;
    QPushButton *returnButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *sureButton;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QDialog *Rear_Camera_Setting)
    {
        if (Rear_Camera_Setting->objectName().isEmpty())
            Rear_Camera_Setting->setObjectName(QString::fromUtf8("Rear_Camera_Setting"));
        Rear_Camera_Setting->resize(671, 431);
        gridLayout = new QGridLayout(Rear_Camera_Setting);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pushButton = new QPushButton(Rear_Camera_Setting);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setEnabled(false);
        pushButton->setMinimumSize(QSize(121, 41));
        pushButton->setMaximumSize(QSize(121, 41));
        pushButton->setStyleSheet(QString::fromUtf8("background-color:rgb(47, 207, 255);\n"
"color:rgb(255,255,255)"));

        gridLayout_4->addWidget(pushButton, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(518, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 0, 1, 1, 1);


        gridLayout->addLayout(gridLayout_4, 0, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        upperButton = new QPushButton(Rear_Camera_Setting);
        upperButton->setObjectName(QString::fromUtf8("upperButton"));
        upperButton->setMinimumSize(QSize(55, 55));
        upperButton->setMaximumSize(QSize(55, 55));
        upperButton->setStyleSheet(QString::fromUtf8("border-image:url(\":/icon/navigate-up.png\")"));

        gridLayout_3->addWidget(upperButton, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 128, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 1, 0, 1, 1);

        downButton = new QPushButton(Rear_Camera_Setting);
        downButton->setObjectName(QString::fromUtf8("downButton"));
        downButton->setMinimumSize(QSize(55, 55));
        downButton->setMaximumSize(QSize(55, 55));
        downButton->setStyleSheet(QString::fromUtf8("border-image:url(\":/icon/navigate-down.png\")"));

        gridLayout_3->addWidget(downButton, 2, 0, 1, 1);


        gridLayout->addLayout(gridLayout_3, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 54, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(10, -1, 10, -1);
        returnButton = new QPushButton(Rear_Camera_Setting);
        returnButton->setObjectName(QString::fromUtf8("returnButton"));
        returnButton->setMinimumSize(QSize(41, 41));
        returnButton->setMaximumSize(QSize(41, 41));
        returnButton->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/Back.png)"));

        gridLayout_2->addWidget(returnButton, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(498, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);

        sureButton = new QPushButton(Rear_Camera_Setting);
        sureButton->setObjectName(QString::fromUtf8("sureButton"));
        sureButton->setMinimumSize(QSize(81, 41));
        sureButton->setMaximumSize(QSize(81, 41));
        sureButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	border-style: none;\n"
"	border: 0px;\n"
"	color: #F0F0F0;\n"
"	padding: 5px;	\n"
"	border-radius:5px;\n"
"	background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3); \n"
"}\n"
"\n"
".QPushButton[focusPolicy=\"0\"] {\n"
"	border-style: none;\n"
"	border: 0px;\n"
"	color: #F0F0F0;\n"
"	padding: 0px;	\n"
"	border-radius:3px;\n"
"	background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3); \n"
"}\n"
"\n"
".QPushButton:hover{ \n"
"	background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #50A3F0, stop:1 #489CEA);\n"
"}\n"
"\n"
".QPushButton:pressed{ \n"
"	background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);\n"
"}"));

        gridLayout_2->addWidget(sureButton, 0, 2, 1, 1);


        gridLayout->addLayout(gridLayout_2, 4, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 1, 0, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 1);
        gridLayout->setRowStretch(2, 3);
        gridLayout->setRowStretch(3, 1);
        gridLayout->setRowStretch(4, 1);

        retranslateUi(Rear_Camera_Setting);

        QMetaObject::connectSlotsByName(Rear_Camera_Setting);
    } // setupUi

    void retranslateUi(QDialog *Rear_Camera_Setting)
    {
        Rear_Camera_Setting->setWindowTitle(QApplication::translate("Rear_Camera_Setting", "Dialog", nullptr));
        pushButton->setText(QApplication::translate("Rear_Camera_Setting", "\345\220\216\346\221\204\345\203\217\345\244\264\350\256\276\347\275\256", nullptr));
        upperButton->setText(QString());
        downButton->setText(QString());
        returnButton->setText(QString());
        sureButton->setText(QApplication::translate("Rear_Camera_Setting", "next", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Rear_Camera_Setting: public Ui_Rear_Camera_Setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REAR_CAMERA_SETTING_H
