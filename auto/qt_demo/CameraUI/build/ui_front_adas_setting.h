/********************************************************************************
** Form generated from reading UI file 'front_adas_setting.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRONT_ADAS_SETTING_H
#define UI_FRONT_ADAS_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_front_ADAS_setting
{
public:
    QGridLayout *gridLayout_4;
    QPushButton *nextButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QPushButton *returnButton;
    QPushButton *tittleButton;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *highLabel;
    QSlider *high_low_Slider;
    QLabel *lowLabel;
    QWidget *widget;
    QFrame *HorizontalLine;
    QFrame *VerticelLine;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;
    QLabel *leftLabel;
    QSlider *left_right_Slider;
    QLabel *rightLabel;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *front_ADAS_setting)
    {
        if (front_ADAS_setting->objectName().isEmpty())
            front_ADAS_setting->setObjectName(QString::fromUtf8("front_ADAS_setting"));
        front_ADAS_setting->resize(660, 430);
        gridLayout_4 = new QGridLayout(front_ADAS_setting);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        nextButton = new QPushButton(front_ADAS_setting);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        nextButton->setEnabled(false);
        nextButton->setMinimumSize(QSize(131, 51));
        nextButton->setMaximumSize(QSize(131, 51));
        nextButton->setStyleSheet(QString::fromUtf8("background-color:rgb(71, 154, 255);\n"
"color:rgb(255,255,255)"));

        gridLayout_4->addWidget(nextButton, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(481, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 0, 1, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 295, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_2, 1, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 295, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_3, 1, 2, 1, 1);

        returnButton = new QPushButton(front_ADAS_setting);
        returnButton->setObjectName(QString::fromUtf8("returnButton"));
        returnButton->setMinimumSize(QSize(41, 41));
        returnButton->setMaximumSize(QSize(41, 41));
        returnButton->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/Back.png)"));

        gridLayout_4->addWidget(returnButton, 2, 0, 1, 1);

        tittleButton = new QPushButton(front_ADAS_setting);
        tittleButton->setObjectName(QString::fromUtf8("tittleButton"));
        tittleButton->setMinimumSize(QSize(101, 51));
        tittleButton->setMaximumSize(QSize(101, 51));
        tittleButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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

        gridLayout_4->addWidget(tittleButton, 2, 2, 1, 1);

        groupBox = new QGroupBox(front_ADAS_setting);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(371, 351));
        groupBox->setMaximumSize(QSize(371, 351));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"border-width:2px;\n"
"border-style:solid;\n"
"border-radius: 10px;\n"
"border-color:blue;\n"
"margin-top:0.5ex;\n"
"}"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        highLabel = new QLabel(groupBox);
        highLabel->setObjectName(QString::fromUtf8("highLabel"));
        highLabel->setStyleSheet(QString::fromUtf8("font: 75 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:rgb(255,255,255)"));

        gridLayout_2->addWidget(highLabel, 0, 0, 1, 1);

        high_low_Slider = new QSlider(groupBox);
        high_low_Slider->setObjectName(QString::fromUtf8("high_low_Slider"));
        high_low_Slider->setOrientation(Qt::Vertical);

        gridLayout_2->addWidget(high_low_Slider, 1, 0, 1, 1);

        lowLabel = new QLabel(groupBox);
        lowLabel->setObjectName(QString::fromUtf8("lowLabel"));
        lowLabel->setStyleSheet(QString::fromUtf8("color:rgb(255,255,255)"));

        gridLayout_2->addWidget(lowLabel, 2, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        widget = new QWidget(groupBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        HorizontalLine = new QFrame(widget);
        HorizontalLine->setObjectName(QString::fromUtf8("HorizontalLine"));
        HorizontalLine->setGeometry(QRect(0, 260, 301, 10));
        HorizontalLine->setStyleSheet(QString::fromUtf8("color:\n"
"rgb(255, 8, 12)"));
        HorizontalLine->setFrameShape(QFrame::HLine);
        HorizontalLine->setFrameShadow(QFrame::Sunken);
        VerticelLine = new QFrame(widget);
        VerticelLine->setObjectName(QString::fromUtf8("VerticelLine"));
        VerticelLine->setGeometry(QRect(10, 40, 10, 241));
        VerticelLine->setStyleSheet(QString::fromUtf8("color:rgb(255, 90, 14)"));
        VerticelLine->setFrameShape(QFrame::VLine);
        VerticelLine->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(widget, 0, 1, 1, 2);

        verticalSpacer = new QSpacerItem(20, 33, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        leftLabel = new QLabel(groupBox);
        leftLabel->setObjectName(QString::fromUtf8("leftLabel"));
        leftLabel->setStyleSheet(QString::fromUtf8("color:rgb(255,255,255)"));

        gridLayout->addWidget(leftLabel, 0, 0, 1, 1);

        left_right_Slider = new QSlider(groupBox);
        left_right_Slider->setObjectName(QString::fromUtf8("left_right_Slider"));
        left_right_Slider->setStyleSheet(QString::fromUtf8(""));
        left_right_Slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(left_right_Slider, 0, 1, 1, 1);

        rightLabel = new QLabel(groupBox);
        rightLabel->setObjectName(QString::fromUtf8("rightLabel"));
        rightLabel->setStyleSheet(QString::fromUtf8("color:rgb(255,255,255)"));

        gridLayout->addWidget(rightLabel, 0, 2, 1, 1);


        gridLayout_3->addLayout(gridLayout, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 2, 1, 1);

        gridLayout_3->setRowStretch(0, 8);
        gridLayout_3->setRowStretch(1, 1);
        gridLayout_3->setColumnStretch(0, 1);
        gridLayout_3->setColumnStretch(1, 9);
        gridLayout_3->setColumnStretch(2, 1);
        widget->raise();

        gridLayout_4->addWidget(groupBox, 1, 1, 2, 1);


        retranslateUi(front_ADAS_setting);

        QMetaObject::connectSlotsByName(front_ADAS_setting);
    } // setupUi

    void retranslateUi(QDialog *front_ADAS_setting)
    {
        front_ADAS_setting->setWindowTitle(QApplication::translate("front_ADAS_setting", "Dialog", nullptr));
        nextButton->setText(QApplication::translate("front_ADAS_setting", "\345\211\215ADAS\350\256\276\347\275\256", nullptr));
        returnButton->setText(QString());
        tittleButton->setText(QApplication::translate("front_ADAS_setting", "\344\270\213\344\270\200\346\255\245", nullptr));
        groupBox->setTitle(QString());
        highLabel->setText(QApplication::translate("front_ADAS_setting", "\351\253\230", nullptr));
        lowLabel->setText(QApplication::translate("front_ADAS_setting", "\344\275\216", nullptr));
        leftLabel->setText(QApplication::translate("front_ADAS_setting", "\345\267\246", nullptr));
        rightLabel->setText(QApplication::translate("front_ADAS_setting", "\345\217\263", nullptr));
    } // retranslateUi

};

namespace Ui {
    class front_ADAS_setting: public Ui_front_ADAS_setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRONT_ADAS_SETTING_H
