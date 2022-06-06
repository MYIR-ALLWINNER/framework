/********************************************************************************
** Form generated from reading UI file 'reverseline_setting.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REVERSELINE_SETTING_H
#define UI_REVERSELINE_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReverseLine_Setting
{
public:
    QGridLayout *gridLayout;
    QWidget *widget_3;
    QGridLayout *gridLayout_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_5;
    QWidget *widget;

    void setupUi(QDialog *ReverseLine_Setting)
    {
        if (ReverseLine_Setting->objectName().isEmpty())
            ReverseLine_Setting->setObjectName(QString::fromUtf8("ReverseLine_Setting"));
        ReverseLine_Setting->resize(1018, 550);
        ReverseLine_Setting->setStyleSheet(QString::fromUtf8("background-color:rgb(255,255,255,0);"));
        gridLayout = new QGridLayout(ReverseLine_Setting);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget_3 = new QWidget(ReverseLine_Setting);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setStyleSheet(QString::fromUtf8("border-radius:10px;\n"
"background-color:rgba(167, 167, 167,40);"));
        gridLayout_2 = new QGridLayout(widget_3);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(5, 0, 5, 0);
        widget_2 = new QWidget(widget_3);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(0, 0));
        widget_2->setMaximumSize(QSize(1000, 60));
        widget_2->setStyleSheet(QString::fromUtf8("background-color:rgb(255,255,255,0);"));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(228, 19, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(40, 40));
        pushButton->setMaximumSize(QSize(40, 40));
        pushButton->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/Back.png)"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(78, 19, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(40, 40));
        pushButton_2->setMaximumSize(QSize(40, 40));
        pushButton_2->setStyleSheet(QString::fromUtf8("border-image:url(\":/icon/navigate-up.png\");\n"
"border-radius:0px;"));

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer_3 = new QSpacerItem(77, 19, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton_3 = new QPushButton(widget_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(40, 40));
        pushButton_3->setMaximumSize(QSize(40, 40));
        pushButton_3->setStyleSheet(QString::fromUtf8("border-image:url(\":/icon/navigate-down.png\");\n"
"border-radius:0px;"));

        horizontalLayout->addWidget(pushButton_3);

        horizontalSpacer_4 = new QSpacerItem(78, 19, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        pushButton_4 = new QPushButton(widget_2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(40, 40));
        pushButton_4->setMaximumSize(QSize(40, 40));
        pushButton_4->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/Save.png);\n"
"border-radius:0px;"));

        horizontalLayout->addWidget(pushButton_4);

        horizontalSpacer_5 = new QSpacerItem(298, 19, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);


        gridLayout_2->addWidget(widget_2, 0, 0, 1, 1);

        widget = new QWidget(widget_3);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(980, 430));
        widget->setMaximumSize(QSize(1000, 430));

        gridLayout_2->addWidget(widget, 1, 0, 1, 1);

        gridLayout_2->setRowStretch(0, 1);
        gridLayout_2->setRowStretch(1, 7);

        gridLayout->addWidget(widget_3, 0, 0, 1, 1);


        retranslateUi(ReverseLine_Setting);

        QMetaObject::connectSlotsByName(ReverseLine_Setting);
    } // setupUi

    void retranslateUi(QDialog *ReverseLine_Setting)
    {
        ReverseLine_Setting->setWindowTitle(QApplication::translate("ReverseLine_Setting", "Dialog", nullptr));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ReverseLine_Setting: public Ui_ReverseLine_Setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REVERSELINE_SETTING_H
