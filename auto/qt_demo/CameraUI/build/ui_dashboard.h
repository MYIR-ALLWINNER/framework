/********************************************************************************
** Form generated from reading UI file 'dashboard.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASHBOARD_H
#define UI_DASHBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dashBoard
{
public:
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_4;
    QPushButton *GPSButton;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *bdButton;
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QDialog *dashBoard)
    {
        if (dashBoard->objectName().isEmpty())
            dashBoard->setObjectName(QString::fromUtf8("dashBoard"));
        dashBoard->resize(900, 500);
        gridLayout_5 = new QGridLayout(dashBoard);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(19, 50, 19, 15);
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(90, -1, 110, -1);
        GPSButton = new QPushButton(dashBoard);
        GPSButton->setObjectName(QString::fromUtf8("GPSButton"));
        GPSButton->setEnabled(false);
        GPSButton->setStyleSheet(QString::fromUtf8("background-color:rgb(177, 255, 8)"));

        gridLayout_4->addWidget(GPSButton, 0, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(468, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_4, 0, 1, 1, 1);

        bdButton = new QPushButton(dashBoard);
        bdButton->setObjectName(QString::fromUtf8("bdButton"));
        bdButton->setEnabled(false);
        bdButton->setStyleSheet(QString::fromUtf8("background-color:rgb(49, 138, 255)"));

        gridLayout_4->addWidget(bdButton, 0, 2, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 0, 0, 1, 2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        scrollArea = new QScrollArea(dashBoard);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setMinimumSize(QSize(400, 314));
        scrollArea->setMaximumSize(QSize(400, 314));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 400, 314));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 1, 1, 1);

        scrollArea_3 = new QScrollArea(dashBoard);
        scrollArea_3->setObjectName(QString::fromUtf8("scrollArea_3"));
        scrollArea_3->setMinimumSize(QSize(200, 200));
        scrollArea_3->setMaximumSize(QSize(200, 200));
        scrollArea_3->setStyleSheet(QString::fromUtf8("background-image:url(:/GPS.png)"));
        scrollArea_3->setFrameShape(QFrame::NoFrame);
        scrollArea_3->setFrameShadow(QFrame::Sunken);
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 200, 200));
        scrollArea_3->setWidget(scrollAreaWidgetContents_3);

        gridLayout->addWidget(scrollArea_3, 0, 2, 1, 1);

        scrollArea_2 = new QScrollArea(dashBoard);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setMinimumSize(QSize(200, 200));
        scrollArea_2->setMaximumSize(QSize(200, 200));
        scrollArea_2->setStyleSheet(QString::fromUtf8("background-image:url(:/GPS.png)"));
        scrollArea_2->setFrameShape(QFrame::NoFrame);
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 200, 200));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        gridLayout->addWidget(scrollArea_2, 0, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout, 1, 0, 1, 2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButton = new QPushButton(dashBoard);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(41, 41));
        pushButton->setMaximumSize(QSize(41, 41));
        pushButton->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/Back.png)"));

        gridLayout_2->addWidget(pushButton, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(808, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_2, 3, 0, 1, 2);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(60, -1, 60, -1);
        label = new QLabel(dashBoard);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(81, 31));
        label->setMaximumSize(QSize(81, 31));
        label->setStyleSheet(QString::fromUtf8("color:rgb(255, 69, 7)"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(dashBoard);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(120, 31));
        label_2->setMaximumSize(QSize(120, 31));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(121, 255, 32);"));

        gridLayout_3->addWidget(label_2, 0, 1, 1, 1);

        label_3 = new QLabel(dashBoard);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(71, 31));
        label_3->setMaximumSize(QSize(71, 31));
        label_3->setStyleSheet(QString::fromUtf8("color:rgb(129, 255, 11)"));

        gridLayout_3->addWidget(label_3, 0, 2, 1, 1);


        gridLayout_5->addLayout(gridLayout_3, 2, 0, 1, 2);


        retranslateUi(dashBoard);

        QMetaObject::connectSlotsByName(dashBoard);
    } // setupUi

    void retranslateUi(QDialog *dashBoard)
    {
        dashBoard->setWindowTitle(QApplication::translate("dashBoard", "Dialog", nullptr));
        GPSButton->setText(QApplication::translate("dashBoard", "GPS", nullptr));
        bdButton->setText(QApplication::translate("dashBoard", "\345\214\227\346\226\227", nullptr));
        pushButton->setText(QString());
        label->setText(QApplication::translate("dashBoard", "GPS\345\267\262\350\277\236\346\216\245", nullptr));
        label_2->setText(QApplication::translate("dashBoard", "\345\215\253\346\230\237\344\277\241\345\217\267\346\257\224>40", nullptr));
        label_3->setText(QApplication::translate("dashBoard", " \347\273\217\347\272\254\345\272\246\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dashBoard: public Ui_dashBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARD_H
