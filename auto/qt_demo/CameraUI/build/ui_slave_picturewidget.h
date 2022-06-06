/********************************************************************************
** Form generated from reading UI file 'slave_picturewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLAVE_PICTUREWIDGET_H
#define UI_SLAVE_PICTUREWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_slave_PictureWidget
{
public:
    QGridLayout *gridLayout;
    QListWidget *listWidget_file;

    void setupUi(QDialog *slave_PictureWidget)
    {
        if (slave_PictureWidget->objectName().isEmpty())
            slave_PictureWidget->setObjectName(QString::fromUtf8("slave_PictureWidget"));
        slave_PictureWidget->resize(656, 532);
        gridLayout = new QGridLayout(slave_PictureWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        listWidget_file = new QListWidget(slave_PictureWidget);
        listWidget_file->setObjectName(QString::fromUtf8("listWidget_file"));

        gridLayout->addWidget(listWidget_file, 0, 0, 1, 1);


        retranslateUi(slave_PictureWidget);

        QMetaObject::connectSlotsByName(slave_PictureWidget);
    } // setupUi

    void retranslateUi(QDialog *slave_PictureWidget)
    {
        slave_PictureWidget->setWindowTitle(QApplication::translate("slave_PictureWidget", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class slave_PictureWidget: public Ui_slave_PictureWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLAVE_PICTUREWIDGET_H
