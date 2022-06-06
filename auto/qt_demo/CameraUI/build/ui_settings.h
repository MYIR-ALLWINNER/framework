/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Settings
{
public:
    QGridLayout *gridLayout_2;
    QWidget *widget_2;
    QGridLayout *gridLayout;
    QPushButton *previewButton;
    QPushButton *AdasButton;
    QPushButton *reverseLineButton;
    QPushButton *timeSetButton;
    QPushButton *aboutButton;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *returnButton;
    QSpacerItem *horizontalSpacer_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;

    void setupUi(QDialog *Settings)
    {
        if (Settings->objectName().isEmpty())
            Settings->setObjectName(QString::fromUtf8("Settings"));
        Settings->resize(800, 498);
        Settings->setStyleSheet(QString::fromUtf8("background-color:rgb(104, 98, 98,80);\n"
""));
        gridLayout_2 = new QGridLayout(Settings);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        widget_2 = new QWidget(Settings);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setStyleSheet(QString::fromUtf8("background-color:rgb(86, 76, 75,80);\n"
"border-radius:10px;"));
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        previewButton = new QPushButton(widget_2);
        previewButton->setObjectName(QString::fromUtf8("previewButton"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(previewButton->sizePolicy().hasHeightForWidth());
        previewButton->setSizePolicy(sizePolicy);
        previewButton->setMinimumSize(QSize(119, 51));
        previewButton->setMaximumSize(QSize(119, 51));
        previewButton->setFocusPolicy(Qt::NoFocus);
        previewButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
"}\n"
""));

        gridLayout->addWidget(previewButton, 0, 0, 1, 1);

        AdasButton = new QPushButton(widget_2);
        AdasButton->setObjectName(QString::fromUtf8("AdasButton"));
        sizePolicy.setHeightForWidth(AdasButton->sizePolicy().hasHeightForWidth());
        AdasButton->setSizePolicy(sizePolicy);
        AdasButton->setMinimumSize(QSize(119, 51));
        AdasButton->setMaximumSize(QSize(119, 51));
        AdasButton->setFocusPolicy(Qt::NoFocus);
        AdasButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
"}\n"
""));

        gridLayout->addWidget(AdasButton, 1, 0, 1, 1);

        reverseLineButton = new QPushButton(widget_2);
        reverseLineButton->setObjectName(QString::fromUtf8("reverseLineButton"));
        sizePolicy.setHeightForWidth(reverseLineButton->sizePolicy().hasHeightForWidth());
        reverseLineButton->setSizePolicy(sizePolicy);
        reverseLineButton->setMinimumSize(QSize(119, 51));
        reverseLineButton->setMaximumSize(QSize(119, 51));
        reverseLineButton->setFocusPolicy(Qt::NoFocus);
        reverseLineButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
"}\n"
""));

        gridLayout->addWidget(reverseLineButton, 2, 0, 1, 1);

        timeSetButton = new QPushButton(widget_2);
        timeSetButton->setObjectName(QString::fromUtf8("timeSetButton"));
        sizePolicy.setHeightForWidth(timeSetButton->sizePolicy().hasHeightForWidth());
        timeSetButton->setSizePolicy(sizePolicy);
        timeSetButton->setMinimumSize(QSize(119, 51));
        timeSetButton->setMaximumSize(QSize(119, 51));
        timeSetButton->setFocusPolicy(Qt::NoFocus);
        timeSetButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
"}\n"
""));

        gridLayout->addWidget(timeSetButton, 3, 0, 1, 1);

        aboutButton = new QPushButton(widget_2);
        aboutButton->setObjectName(QString::fromUtf8("aboutButton"));
        sizePolicy.setHeightForWidth(aboutButton->sizePolicy().hasHeightForWidth());
        aboutButton->setSizePolicy(sizePolicy);
        aboutButton->setMinimumSize(QSize(119, 51));
        aboutButton->setMaximumSize(QSize(119, 51));
        aboutButton->setFocusPolicy(Qt::NoFocus);
        aboutButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
"}\n"
""));

        gridLayout->addWidget(aboutButton, 4, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 125, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        returnButton = new QPushButton(widget_2);
        returnButton->setObjectName(QString::fromUtf8("returnButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(returnButton->sizePolicy().hasHeightForWidth());
        returnButton->setSizePolicy(sizePolicy1);
        returnButton->setMinimumSize(QSize(41, 41));
        returnButton->setMaximumSize(QSize(41, 41));
        returnButton->setFocusPolicy(Qt::NoFocus);
        returnButton->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/Back.png);\n"
"background-color:rgb(255,255,255,0);"));

        horizontalLayout->addWidget(returnButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 6, 0, 1, 1);


        gridLayout_2->addWidget(widget_2, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(Settings);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setStyleSheet(QString::fromUtf8("border-radius:5px;\n"
"background-color:rgb(86, 76, 75,20);"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);

        gridLayout_2->addWidget(stackedWidget, 0, 1, 1, 1);

        gridLayout_2->setColumnStretch(0, 1);
        gridLayout_2->setColumnStretch(1, 6);
        stackedWidget->raise();
        widget_2->raise();

        retranslateUi(Settings);

        QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QDialog *Settings)
    {
        Settings->setWindowTitle(QApplication::translate("Settings", "Dialog", nullptr));
#ifndef QT_NO_WHATSTHIS
        Settings->setWhatsThis(QApplication::translate("Settings", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        previewButton->setText(QApplication::translate("Settings", "\351\242\204\350\247\210\350\256\276\347\275\256", nullptr));
        AdasButton->setText(QApplication::translate("Settings", "ADAS", nullptr));
        reverseLineButton->setText(QApplication::translate("Settings", "\345\200\222\350\275\246\347\272\277\350\256\276\347\275\256", nullptr));
        timeSetButton->setText(QApplication::translate("Settings", "\346\227\266\351\227\264\350\256\276\347\275\256", nullptr));
        aboutButton->setText(QApplication::translate("Settings", "\345\205\263\344\272\216", nullptr));
        returnButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
