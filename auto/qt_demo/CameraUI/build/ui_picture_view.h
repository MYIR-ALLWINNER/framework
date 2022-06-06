/********************************************************************************
** Form generated from reading UI file 'picture_view.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICTURE_VIEW_H
#define UI_PICTURE_VIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Picture_view
{
public:
    QGridLayout *gridLayout_3;
    QWidget *titlewidget;
    QGridLayout *gridLayout_2;
    QLabel *lab_Ico;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnMenu_Min;
    QPushButton *btnMenu_Max;
    QPushButton *btnMenu_Close;
    QWidget *widget;
    QWidget *widget_2;
    QGridLayout *gridLayout;
    QPushButton *prePicButton;
    QPushButton *largerButton;
    QPushButton *smallerButton;
    QPushButton *nextPicButton;

    void setupUi(QDialog *Picture_view)
    {
        if (Picture_view->objectName().isEmpty())
            Picture_view->setObjectName(QString::fromUtf8("Picture_view"));
        Picture_view->resize(1011, 603);
        gridLayout_3 = new QGridLayout(Picture_view);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        titlewidget = new QWidget(Picture_view);
        titlewidget->setObjectName(QString::fromUtf8("titlewidget"));
        titlewidget->setMinimumSize(QSize(0, 33));
        titlewidget->setMaximumSize(QSize(160000, 33));
        titlewidget->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #0F7DBE, stop:1 #1582C3);\n"
"border-radius:0px;\n"
"}"));
        gridLayout_2 = new QGridLayout(titlewidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(2);
        gridLayout_2->setVerticalSpacing(1);
        gridLayout_2->setContentsMargins(1, 1, 1, 1);
        lab_Ico = new QLabel(titlewidget);
        lab_Ico->setObjectName(QString::fromUtf8("lab_Ico"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lab_Ico->sizePolicy().hasHeightForWidth());
        lab_Ico->setSizePolicy(sizePolicy);
        lab_Ico->setMinimumSize(QSize(0, 0));
        lab_Ico->setMaximumSize(QSize(32, 33));
        lab_Ico->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	border-radius:0px;\n"
"	color: #F0F0F0;\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-style:none;\n"
"}"));
        lab_Ico->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lab_Ico, 0, 0, 1, 1);

        label = new QLabel(titlewidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 0));
        label->setMaximumSize(QSize(761, 33));
        label->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	border-radius:0px;\n"
"	color: #F0F0F0;\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-style:none;\n"
"}"));

        gridLayout_2->addWidget(label, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(107, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 1, 1);

        btnMenu_Min = new QPushButton(titlewidget);
        btnMenu_Min->setObjectName(QString::fromUtf8("btnMenu_Min"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnMenu_Min->sizePolicy().hasHeightForWidth());
        btnMenu_Min->setSizePolicy(sizePolicy1);
        btnMenu_Min->setMinimumSize(QSize(0, 0));
        btnMenu_Min->setMaximumSize(QSize(32, 33));
        btnMenu_Min->setCursor(QCursor(Qt::ArrowCursor));
        btnMenu_Min->setFocusPolicy(Qt::NoFocus);
        btnMenu_Min->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	border-radius:0px;\n"
"	color: #F0F0F0;\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-style:none;\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(25, 134, 199, 0), stop:1 #50A3F0);\n"
"}"));
        btnMenu_Min->setFlat(true);

        gridLayout_2->addWidget(btnMenu_Min, 0, 3, 1, 1);

        btnMenu_Max = new QPushButton(titlewidget);
        btnMenu_Max->setObjectName(QString::fromUtf8("btnMenu_Max"));
        sizePolicy1.setHeightForWidth(btnMenu_Max->sizePolicy().hasHeightForWidth());
        btnMenu_Max->setSizePolicy(sizePolicy1);
        btnMenu_Max->setMinimumSize(QSize(0, 0));
        btnMenu_Max->setMaximumSize(QSize(32, 33));
        btnMenu_Max->setCursor(QCursor(Qt::ArrowCursor));
        btnMenu_Max->setFocusPolicy(Qt::NoFocus);
        btnMenu_Max->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	border-radius:0px;\n"
"	color: #F0F0F0;\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-style:none;\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(25, 134, 199, 0), stop:1 #50A3F0);\n"
"}"));
        btnMenu_Max->setFlat(true);

        gridLayout_2->addWidget(btnMenu_Max, 0, 4, 1, 1);

        btnMenu_Close = new QPushButton(titlewidget);
        btnMenu_Close->setObjectName(QString::fromUtf8("btnMenu_Close"));
        sizePolicy1.setHeightForWidth(btnMenu_Close->sizePolicy().hasHeightForWidth());
        btnMenu_Close->setSizePolicy(sizePolicy1);
        btnMenu_Close->setMinimumSize(QSize(0, 0));
        btnMenu_Close->setMaximumSize(QSize(32, 33));
        btnMenu_Close->setCursor(QCursor(Qt::ArrowCursor));
        btnMenu_Close->setFocusPolicy(Qt::NoFocus);
        btnMenu_Close->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	border-radius:0px;\n"
"	color: #F0F0F0;\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-style:none;\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(238, 0, 0, 128), stop:1 rgba(238, 44, 44, 255));\n"
"}"));
        btnMenu_Close->setFlat(true);

        gridLayout_2->addWidget(btnMenu_Close, 0, 5, 1, 1);

        gridLayout_2->setColumnStretch(0, 1);
        gridLayout_2->setColumnStretch(1, 5);
        gridLayout_2->setColumnStretch(2, 1);
        gridLayout_2->setColumnStretch(3, 1);
        gridLayout_2->setColumnStretch(4, 1);
        gridLayout_2->setColumnStretch(5, 1);

        gridLayout_3->addWidget(titlewidget, 0, 0, 1, 1);

        widget = new QWidget(Picture_view);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("background-color:rgb(58, 58, 58,100);"));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(205, 481, 600, 80));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy2);
        widget_2->setMinimumSize(QSize(600, 80));
        widget_2->setFocusPolicy(Qt::NoFocus);
        widget_2->setStyleSheet(QString::fromUtf8("border-radius:5px;\n"
"background-color:rgb(58, 58,58,150);"));
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        prePicButton = new QPushButton(widget_2);
        prePicButton->setObjectName(QString::fromUtf8("prePicButton"));
        prePicButton->setMinimumSize(QSize(0, 0));
        prePicButton->setMaximumSize(QSize(51, 51));
        prePicButton->setFocusPolicy(Qt::NoFocus);
        prePicButton->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/prev.png);\n"
"background-color:rgb(255,255,255,0);"));

        gridLayout->addWidget(prePicButton, 0, 0, 1, 1);

        largerButton = new QPushButton(widget_2);
        largerButton->setObjectName(QString::fromUtf8("largerButton"));
        largerButton->setMinimumSize(QSize(0, 0));
        largerButton->setMaximumSize(QSize(51, 51));
        largerButton->setFocusPolicy(Qt::NoFocus);
        largerButton->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/larger.png);\n"
"background-color:rgb(255,255,255,0);"));

        gridLayout->addWidget(largerButton, 0, 1, 1, 1);

        smallerButton = new QPushButton(widget_2);
        smallerButton->setObjectName(QString::fromUtf8("smallerButton"));
        smallerButton->setMinimumSize(QSize(0, 0));
        smallerButton->setMaximumSize(QSize(51, 51));
        smallerButton->setFocusPolicy(Qt::NoFocus);
        smallerButton->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/smaller.png);\n"
"background-color:rgb(255,255,255,0);"));

        gridLayout->addWidget(smallerButton, 0, 2, 1, 1);

        nextPicButton = new QPushButton(widget_2);
        nextPicButton->setObjectName(QString::fromUtf8("nextPicButton"));
        nextPicButton->setMinimumSize(QSize(0, 0));
        nextPicButton->setMaximumSize(QSize(51, 51));
        nextPicButton->setFocusPolicy(Qt::NoFocus);
        nextPicButton->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/next.png);\n"
"background-color:rgb(255,255,255,0);"));

        gridLayout->addWidget(nextPicButton, 0, 3, 1, 1);


        gridLayout_3->addWidget(widget, 2, 0, 1, 1);


        retranslateUi(Picture_view);

        QMetaObject::connectSlotsByName(Picture_view);
    } // setupUi

    void retranslateUi(QDialog *Picture_view)
    {
        Picture_view->setWindowTitle(QApplication::translate("Picture_view", "Dialog", nullptr));
        lab_Ico->setText(QString());
        label->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnMenu_Min->setToolTip(QApplication::translate("Picture_view", "\346\234\200\345\260\217\345\214\226", nullptr));
#endif // QT_NO_TOOLTIP
        btnMenu_Min->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnMenu_Max->setToolTip(QApplication::translate("Picture_view", "\346\234\200\345\244\247\345\214\226", nullptr));
#endif // QT_NO_TOOLTIP
        btnMenu_Max->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnMenu_Close->setToolTip(QApplication::translate("Picture_view", "\345\205\263\351\227\255", nullptr));
#endif // QT_NO_TOOLTIP
        btnMenu_Close->setText(QString());
        prePicButton->setText(QString());
        largerButton->setText(QString());
        smallerButton->setText(QString());
        nextPicButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Picture_view: public Ui_Picture_view {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICTURE_VIEW_H
