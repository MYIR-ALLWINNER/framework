/********************************************************************************
** Form generated from reading UI file 'picturewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICTUREWIDGET_H
#define UI_PICTUREWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_pictureWidget
{
public:
    QGridLayout *gridLayout;
    QListWidget *listWidget_file;

    void setupUi(QDialog *pictureWidget)
    {
        if (pictureWidget->objectName().isEmpty())
            pictureWidget->setObjectName(QString::fromUtf8("pictureWidget"));
        pictureWidget->resize(761, 551);
        gridLayout = new QGridLayout(pictureWidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        listWidget_file = new QListWidget(pictureWidget);
        listWidget_file->setObjectName(QString::fromUtf8("listWidget_file"));
        listWidget_file->setStyleSheet(QString::fromUtf8("QListWidget::scrollBar:vertical\n"
"{\n"
"    width:8px;\n"
"    background:rgba(0,0,0,0%);\n"
"    margin:0px,0px,0px,0px;\n"
"    padding-top:9px; \n"
"    padding-bottom:9px;\n"
"};\n"
"QListWidget::scrollBar::handle:vertical\n"
"{\n"
"    width:8px;\n"
"    background:rgba(0,0,0,25%);\n"
"    border-radius:4px;\n"
"    min-height:20;\n"
"};\n"
"QListWidget::scrollBar::handle:vertical:hover\n"
"{\n"
"    width:8px;\n"
"    background:rgba(0,0,0,50%);\n"
"    border-radius:4px;\n"
"    min-height:20;\n"
"};\n"
"QListWidget::scrollBar::add-line:vertical \n"
"{\n"
"    height:9px;width:8px;\n"
"    border-image:url(:/images/a/3.png);\n"
"    subcontrol-position:bottom;\n"
"};\n"
"QListWidget::scrollBar::sub-line:vertical \n"
"{\n"
"    height:9px;width:8px;\n"
"    border-image:url(:/images/a/1.png);\n"
"    subcontrol-position:top;\n"
"};\n"
"QListWidget::scrollBar::add-line:vertical:hover\n"
"{\n"
"    height:9px;width:8px;\n"
"    border-image:url(:/images/a/4.png);\n"
"    subcontrol-position:bottom;\n"
"}"
                        ";\n"
"QListWidget::scrollBar::sub-line:vertical:hover \n"
"{\n"
"    height:9px;width:8px;\n"
"    border-image:url(:/images/a/2.png);\n"
"    subcontrol-position:top;\n"
"};\n"
"QListWidget::scrollBar::sub-page:vertical   \n"
"{\n"
"    background:rgba(0,0,0,10%);\n"
"    border-radius:4px;\n"
"};\n"
"QListWidget::scrollBar::add-page:vertical \n"
"{\n"
"	background:rgba(0,0,0,10%);\n"
"    border-radius:4px;\n"
"}"));

        gridLayout->addWidget(listWidget_file, 0, 0, 1, 1);


        retranslateUi(pictureWidget);

        QMetaObject::connectSlotsByName(pictureWidget);
    } // setupUi

    void retranslateUi(QDialog *pictureWidget)
    {
        pictureWidget->setWindowTitle(QApplication::translate("pictureWidget", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pictureWidget: public Ui_pictureWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICTUREWIDGET_H
