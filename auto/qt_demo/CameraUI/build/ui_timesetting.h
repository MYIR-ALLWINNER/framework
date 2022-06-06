/********************************************************************************
** Form generated from reading UI file 'timesetting.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMESETTING_H
#define UI_TIMESETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTimeEdit>

QT_BEGIN_NAMESPACE

class Ui_TimeSetting
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QGridLayout *gridLayout_2;
    QDateEdit *dateEdit;
    QSpacerItem *horizontalSpacer;
    QTimeEdit *timeEdit;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *setButton;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *TimeSetting)
    {
        if (TimeSetting->objectName().isEmpty())
            TimeSetting->setObjectName(QString::fromUtf8("TimeSetting"));
        TimeSetting->resize(601, 377);
        gridLayout = new QGridLayout(TimeSetting);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(TimeSetting);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setEnabled(false);
        pushButton->setMinimumSize(QSize(151, 51));
        pushButton->setMaximumSize(QSize(151, 51));
        pushButton->setStyleSheet(QString::fromUtf8("color:rgb(255,255,255)"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(100, -1, 160, -1);
        dateEdit = new QDateEdit(TimeSetting);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dateEdit->sizePolicy().hasHeightForWidth());
        dateEdit->setSizePolicy(sizePolicy);
        dateEdit->setMinimumSize(QSize(141, 41));
        dateEdit->setMaximumSize(QSize(141, 41));
        dateEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(38, 112, 197);\n"
"border-radius:0px;\n"
"\n"
"QComboBox::drop-down,QDateEdit::drop-down {\n"
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
"QComboBox::down-arrow,QDateEdit::down-arrow {\n"
"	image: url(:/icon/arrowdown.png); \n"
"}\n"
"color:rgb(255,255,255)"));

        gridLayout_2->addWidget(dateEdit, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);

        timeEdit = new QTimeEdit(TimeSetting);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        sizePolicy.setHeightForWidth(timeEdit->sizePolicy().hasHeightForWidth());
        timeEdit->setSizePolicy(sizePolicy);
        timeEdit->setMinimumSize(QSize(131, 41));
        timeEdit->setMaximumSize(QSize(131, 41));
        timeEdit->setStyleSheet(QString::fromUtf8("background-color:rgb(38, 112, 197);\n"
"border-radius:0px;\n"
"\n"
"QComboBox::drop-down,QDateEdit::drop-down {\n"
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
"QComboBox::down-arrow,QDateEdit::down-arrow {\n"
"	image: url(:/icon/arrowdown.png); \n"
"}\n"
"\n"
"color:rgb(255,255,255)"));

        gridLayout_2->addWidget(timeEdit, 0, 2, 1, 1);


        gridLayout->addLayout(gridLayout_2, 1, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        label = new QLabel(TimeSetting);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(221, 41));
        label->setMaximumSize(QSize(221, 41));
        label->setStyleSheet(QString::fromUtf8("font: 75 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:rgb(255,255,255)"));

        horizontalLayout_5->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(268, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 1);
        horizontalLayout_5->setStretch(2, 1);

        gridLayout->addLayout(horizontalLayout_5, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_5 = new QSpacerItem(158, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        setButton = new QPushButton(TimeSetting);
        setButton->setObjectName(QString::fromUtf8("setButton"));
        sizePolicy.setHeightForWidth(setButton->sizePolicy().hasHeightForWidth());
        setButton->setSizePolicy(sizePolicy);
        setButton->setMinimumSize(QSize(111, 41));
        setButton->setMaximumSize(QSize(111, 41));
        setButton->setFocusPolicy(Qt::NoFocus);
        setButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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

        horizontalLayout_4->addWidget(setButton);

        horizontalSpacer_4 = new QSpacerItem(158, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 1);
        horizontalLayout_4->setStretch(2, 1);

        gridLayout->addLayout(horizontalLayout_4, 3, 0, 1, 1);


        retranslateUi(TimeSetting);

        QMetaObject::connectSlotsByName(TimeSetting);
    } // setupUi

    void retranslateUi(QDialog *TimeSetting)
    {
        TimeSetting->setWindowTitle(QApplication::translate("TimeSetting", "Dialog", nullptr));
        pushButton->setText(QApplication::translate("TimeSetting", "\347\263\273\347\273\237\346\227\266\351\227\264\345\222\214\346\227\245\346\234\237\350\256\276\347\275\256", nullptr));
        label->setText(QApplication::translate("TimeSetting", "\345\275\223\345\211\215\346\227\245\346\234\237\357\274\232", nullptr));
        setButton->setText(QApplication::translate("TimeSetting", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TimeSetting: public Ui_TimeSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMESETTING_H
