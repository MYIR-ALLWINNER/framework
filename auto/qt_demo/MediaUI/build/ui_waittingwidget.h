/********************************************************************************
** Form generated from reading UI file 'waittingwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAITTINGWIDGET_H
#define UI_WAITTINGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WaittingWidget
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *waittingMovieLabel;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;

    void setupUi(QWidget *WaittingWidget)
    {
        if (WaittingWidget->objectName().isEmpty())
            WaittingWidget->setObjectName(QString::fromUtf8("WaittingWidget"));
        WaittingWidget->setWindowModality(Qt::NonModal);
        WaittingWidget->resize(1024, 530);
        WaittingWidget->setMinimumSize(QSize(0, 0));
        WaittingWidget->setMaximumSize(QSize(1024, 600));
        WaittingWidget->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255,0);"));
        widget = new QWidget(WaittingWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(411, 151, 233, 119));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        waittingMovieLabel = new QLabel(widget);
        waittingMovieLabel->setObjectName(QString::fromUtf8("waittingMovieLabel"));
        waittingMovieLabel->setMinimumSize(QSize(70, 70));
        waittingMovieLabel->setMaximumSize(QSize(70, 70));
        waittingMovieLabel->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(waittingMovieLabel, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(231, 41));
        label->setMaximumSize(QSize(231, 41));
        label->setStyleSheet(QString::fromUtf8("color:white;"));

        gridLayout->addWidget(label, 1, 0, 1, 3);


        retranslateUi(WaittingWidget);

        QMetaObject::connectSlotsByName(WaittingWidget);
    } // setupUi

    void retranslateUi(QWidget *WaittingWidget)
    {
        WaittingWidget->setWindowTitle(QApplication::translate("WaittingWidget", "Form", nullptr));
        waittingMovieLabel->setText(QString());
        label->setText(QApplication::translate("WaittingWidget", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">\346\255\243\345\234\250\345\212\240\350\275\275\344\270\255,\350\257\267\347\250\215\345\220\216....</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WaittingWidget: public Ui_WaittingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAITTINGWIDGET_H
