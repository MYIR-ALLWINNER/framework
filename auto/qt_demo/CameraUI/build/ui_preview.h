/********************************************************************************
** Form generated from reading UI file 'preview.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREVIEW_H
#define UI_PREVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_Preview
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_5;
    QLabel *pictureLabel1;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *front_set_Button;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_9;
    QLabel *pictureLabel2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *rear_set_Button;
    QSpacerItem *horizontalSpacer_7;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *Preview)
    {
        if (Preview->objectName().isEmpty())
            Preview->setObjectName(QString::fromUtf8("Preview"));
        Preview->resize(660, 430);
        Preview->setLayoutDirection(Qt::LeftToRight);
        gridLayout_4 = new QGridLayout(Preview);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(20, 50, 20, 30);
        groupBox = new QGroupBox(Preview);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setStyleSheet(QString::fromUtf8("border: 2px solid #0000EE;\n"
"border-radius: 5px;\n"
"margin-top: 1ex; \n"
"font: 75 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
""));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(0, 0));
        label_3->setMaximumSize(QSize(16000, 16000));
        label_3->setStyleSheet(QString::fromUtf8("border-width:0px;\n"
"color:rgb(255,255,255)\n"
""));
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_3);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 4);
        horizontalLayout->setStretch(2, 1);

        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        pictureLabel1 = new QLabel(groupBox);
        pictureLabel1->setObjectName(QString::fromUtf8("pictureLabel1"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pictureLabel1->sizePolicy().hasHeightForWidth());
        pictureLabel1->setSizePolicy(sizePolicy1);
        pictureLabel1->setMinimumSize(QSize(0, 0));
        pictureLabel1->setMaximumSize(QSize(175555, 175555));
        pictureLabel1->setStyleSheet(QString::fromUtf8("border-width:0px;\n"
""));
        pictureLabel1->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(pictureLabel1, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        front_set_Button = new QPushButton(groupBox);
        front_set_Button->setObjectName(QString::fromUtf8("front_set_Button"));
        front_set_Button->setMinimumSize(QSize(0, 0));
        front_set_Button->setMaximumSize(QSize(16000, 16000));
        front_set_Button->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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

        horizontalLayout_2->addWidget(front_set_Button);

        horizontalSpacer_3 = new QSpacerItem(108, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 1);
        horizontalLayout_2->setStretch(2, 1);

        gridLayout_2->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        gridLayout_2->setRowStretch(0, 1);
        gridLayout_2->setRowStretch(1, 5);
        gridLayout_2->setRowStretch(2, 1);

        gridLayout_4->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(Preview);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setStyleSheet(QString::fromUtf8("border: 2px solid #0000EE;\n"
"border-radius: 5px;\n"
"margin-top: 1ex; \n"
"font: 75 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
""));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(0, 0));
        label_2->setMaximumSize(QSize(16000, 16000));
        label_2->setStyleSheet(QString::fromUtf8("border-width:0px;\n"
"color:rgb(255,255,255)"));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_2);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 4);
        horizontalLayout_4->setStretch(2, 1);

        gridLayout_3->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        pictureLabel2 = new QLabel(groupBox_2);
        pictureLabel2->setObjectName(QString::fromUtf8("pictureLabel2"));
        sizePolicy1.setHeightForWidth(pictureLabel2->sizePolicy().hasHeightForWidth());
        pictureLabel2->setSizePolicy(sizePolicy1);
        pictureLabel2->setMinimumSize(QSize(0, 0));
        pictureLabel2->setMaximumSize(QSize(117555, 117555));
        pictureLabel2->setStyleSheet(QString::fromUtf8("border-width:0px;\n"
""));
        pictureLabel2->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(pictureLabel2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_6 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        rear_set_Button = new QPushButton(groupBox_2);
        rear_set_Button->setObjectName(QString::fromUtf8("rear_set_Button"));
        rear_set_Button->setMinimumSize(QSize(0, 0));
        rear_set_Button->setMaximumSize(QSize(16000, 16000));
        rear_set_Button->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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

        horizontalLayout_3->addWidget(rear_set_Button);

        horizontalSpacer_7 = new QSpacerItem(68, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 1);
        horizontalLayout_3->setStretch(2, 1);

        gridLayout_3->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        gridLayout_3->setRowStretch(0, 1);
        gridLayout_3->setRowStretch(1, 5);
        gridLayout_3->setRowStretch(2, 1);

        gridLayout_4->addWidget(groupBox_2, 0, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(Preview);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 0));
        label->setMaximumSize(QSize(16000, 16000));
        label->setStyleSheet(QString::fromUtf8("color:rgb(255,255,255)"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(378, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        gridLayout->setColumnStretch(0, 2);
        gridLayout->setColumnStretch(1, 4);

        gridLayout_4->addLayout(gridLayout, 1, 0, 1, 2);

        gridLayout_4->setRowStretch(0, 5);
        gridLayout_4->setRowStretch(1, 1);

        retranslateUi(Preview);

        QMetaObject::connectSlotsByName(Preview);
    } // setupUi

    void retranslateUi(QDialog *Preview)
    {
        Preview->setWindowTitle(QApplication::translate("Preview", "Dialog", nullptr));
        groupBox->setTitle(QString());
        label_3->setText(QApplication::translate("Preview", "\345\211\215\346\221\204\345\203\217\345\244\264\351\242\204\350\247\210\350\256\276\347\275\256", nullptr));
        pictureLabel1->setText(QString());
        front_set_Button->setText(QApplication::translate("Preview", "\351\242\204\350\247\210", nullptr));
        groupBox_2->setTitle(QString());
        label_2->setText(QApplication::translate("Preview", "\345\220\216\346\221\204\345\203\217\345\244\264\351\242\204\350\247\210\350\256\276\347\275\256", nullptr));
        pictureLabel2->setText(QString());
        rear_set_Button->setText(QApplication::translate("Preview", "\351\242\204\350\247\210", nullptr));
        label->setText(QApplication::translate("Preview", "camera0\345\210\266\345\274\217\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Preview: public Ui_Preview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREVIEW_H
