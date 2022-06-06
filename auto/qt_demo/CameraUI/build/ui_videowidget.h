/********************************************************************************
** Form generated from reading UI file 'videowidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOWIDGET_H
#define UI_VIDEOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_videoWidget
{
public:
    QGridLayout *gridLayout_2;
    QListWidget *listWidget_file;

    void setupUi(QDialog *videoWidget)
    {
        if (videoWidget->objectName().isEmpty())
            videoWidget->setObjectName(QString::fromUtf8("videoWidget"));
        videoWidget->resize(761, 551);
        gridLayout_2 = new QGridLayout(videoWidget);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        listWidget_file = new QListWidget(videoWidget);
        listWidget_file->setObjectName(QString::fromUtf8("listWidget_file"));
        listWidget_file->setStyleSheet(QString::fromUtf8("QListWidget::scrollbar:vertical\n"
"{\n"
"    width:8px;\n"
"    background:rgba(0,0,0,0%);\n"
"    margin:0px,0px,0px,0px;\n"
"    padding-top:9px; \n"
"    padding-bottom:9px;\n"
"};\n"
"QListWidget::scrollbar::handle:vertical\n"
"{\n"
"    width:8px;\n"
"    background:rgba(0,0,0,25%);\n"
"    border-radius:4px;\n"
"    min-height:20;\n"
"};\n"
"QListWidget::scrollbar::handle:vertical:hover\n"
"{\n"
"    width:8px;\n"
"    background:rgba(0,0,0,50%);\n"
"    border-radius:4px;\n"
"    min-height:20;\n"
"};\n"
"QListWidget::scrollbar::add-line:vertical \n"
"{\n"
"    height:9px;width:8px;\n"
"    border-image:url(:/images/a/3.png);\n"
"    subcontrol-position:bottom;\n"
"};\n"
"QListWidget::scrollbar::sub-line:vertical \n"
"{\n"
"    height:9px;width:8px;\n"
"    border-image:url(:/images/a/1.png);\n"
"    subcontrol-position:top;\n"
"};\n"
"QListWidget::scrollbar::add-line:vertical:hover\n"
"{\n"
"    height:9px;width:8px;\n"
"    border-image:url(:/images/a/4.png);\n"
"    subcontrol-position:bottom;\n"
"}"
                        ";\n"
"QListWidget::scrollbar::sub-line:vertical:hover \n"
"{\n"
"    height:9px;width:8px;\n"
"    border-image:url(:/images/a/2.png);\n"
"    subcontrol-position:top;\n"
"};\n"
"QListWidget::scrollbar::sub-page:vertical   \n"
"{\n"
"    background:rgba(0,0,0,10%);\n"
"    border-radius:4px;\n"
"};\n"
"QListWidget::scrollbar::add-page:vertical \n"
"{\n"
"	background:rgba(0,0,0,10%);\n"
"    border-radius:4px;\n"
"}"));

        gridLayout_2->addWidget(listWidget_file, 0, 0, 1, 1);


        retranslateUi(videoWidget);

        QMetaObject::connectSlotsByName(videoWidget);
    } // setupUi

    void retranslateUi(QDialog *videoWidget)
    {
        videoWidget->setWindowTitle(QApplication::translate("videoWidget", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class videoWidget: public Ui_videoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOWIDGET_H
